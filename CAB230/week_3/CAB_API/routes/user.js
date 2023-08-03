const express = require('express');
const router = express.Router();
const bcrypt = require('bcrypt');
const jwt = require("jsonwebtoken");
const profileAuthorization = require("../middleware/profile");
const authorization = require("../middleware/authorization");
const refreshAuthorization = require("../middleware/refresh");

router.get('/:email/profile', profileAuthorization, function (req, res, next) {
    const email = res.locals.token_data.email ?? ''
    let selectStatement = ["email", "firstName", "lastName"]
    if (email === req.params.email) selectStatement = selectStatement.concat(["dob", "address"])
    req.db.from("users").select(...selectStatement).where("email", "=", req.params.email).then((data) => {
        if (data.length === 0) {
            res.status(404).json({
                "error": true,
                "message": "User not found"
            });
            return;
        }
        res.json(data[0])
    })


})

router.put('/:email/profile', authorization, function (req, res, next) {
    if (!res.locals.token_data) return;
    if (Object.keys(req.query).length > 0) {
        res.status(400).json({
            error: true,
            message:
                "Invalid query parameters: QueryParam. Query parameters are not permitted.",
        });
        return;
    }
    const providedEmail = req.params.email
    const email = res.locals.token_data.email
    if (providedEmail !== email) {
        res.status(403).json({
            "error": true,
            "message": "Forbidden"
        });
        return;
    }
    const updateObject = {}
    if (req.body.firstName) updateObject["firstName"] = req.body.firstName
    if (req.body.lastName) updateObject["lastName"] = req.body.lastName
    if (req.body.dob) updateObject["dob"] = req.body.dob
    if (req.body.address) updateObject["address"] = req.body.address

    if (
        Object.keys(updateObject).length === 0
    ) {
        res.status(400).json({
            "error": true,
            // "message": "Request body invalid: firstName, lastName and address must be strings only."
            "message": "Request body incomplete: firstName, lastName, dob and address are required."
        });
        return;
    }
    if (
        typeof req.body.firstName !== "string" ||
        typeof req.body.lastName !== "string" ||
        typeof req.body.dob !== "string" ||
        typeof req.body.address !== "string"
    ) {
        res.status(400).json({
            "error": true,
            "message": "Request body invalid: firstName, lastName and address must be strings only."
            // "message": "Request body incomplete: firstName, lastName, dob and address are required."
        });
        return;
    }
    const dobRegex = /(?:[1-9]\d{3}\-(?:(?:0[1-9]|1[0-2])\-(?:0[1-9]|1\d|2[0-8])|(?:0[13-9]|1[0-2])\-(?:29|30)|(?:0[13578]|1[02])\-31)|(?:[1-9]\d(?:0[48]|[2468][048]|[13579][26])|(?:[2468][048]|[13579][26])00)\-02\-29)/g;
    let dobResult = dobRegex.exec(req.body.dob);
    if (!dobResult || dobResult[0] !== dobResult.input) {
        res.status(400).json({
            error: true,
            message: "Invalid input: dob must be a real date in format YYYY-MM-DD.",
        });
        return;
    }
    if (isFutureDate(req.body.dob)) {
        res.status(400).json({
            error: true,
            message: "Invalid input: dob must be a date in the past.",
        });
        return;
    }

    req.db.from("users").update(updateObject).where("email", "=", email).then(() => {
        req.db.from("users").select(
            "email",
            "firstName",
            "lastName",
            "dob",
            "address",
        ).where("email", "=", email).then((data) => {
            res.json(data[0])
        })
    })
})


router.post('/register', function (req, res, next) {
    const SALT_ROUNDS = 10;
    const email = req.body.email;
    const password = req.body.password;
    if (!email || !password) {
        res.status(400).json({
            error: true,
            message: "Request body incomplete - email and password needed"
        });
        return;
    }
    req.db.from("users").select("*").where("email", "=", email)
        .then(users => {
            if (users.length > 0) {
                return res.status(409).json({
                    "error": true,
                    "message": "User already exists"
                })
            }
            const hash = bcrypt.hashSync(password, SALT_ROUNDS);
            return req.db.from("users").insert({email, hash})
        })
        .then(() => {
            res.status(201).json({
                "message": "User created"
            })
        })
});

router.post('/login', function (req, res, next) {
    const email = req.body.email;
    const password = req.body.password;
    if (!email || !password) {
        res.status(400).json({
            error: true,
            message: "Request body incomplete - email and password needed"
        });
        return;
    }
    const queryUsers = req.db.from("users").select("*").where("email", "=", email);
    queryUsers
        .then(users => {
            if (users.length === 0) return false
            const user = users[0];
            return bcrypt.compare(password, user.hash);
        }).then((match) => {
        if (!match) {
            res.status(401).json({
                "error": true,
                "message": "Incorrect email or password"
            })
        } else {
            const bearerExpiresIn = 60 * 10; // 10 min
            const bearerExp = Math.floor(Date.now() / 1000) + bearerExpiresIn;
            const refreshExpiresIn = 60 * 60 * 24; // 24 Hours
            const refreshExp = Math.floor(Date.now() / 1000) + refreshExpiresIn;
            const bearerToken = jwt.sign({exp: bearerExp, email: email}, process.env.JWT_SECRET);
            const refreshToken = jwt.sign({exp: refreshExp, email: email}, process.env.JWT_SECRET);

            res.status(200).json({
                "bearerToken": {
                    "token": bearerToken,
                    "token_type": "Bearer",
                    "expires_in": bearerExpiresIn
                },
                "refreshToken": {
                    "token": refreshToken,
                    "token_type": "Refresh",
                    "expires_in": refreshExpiresIn
                }
            });
        }
    })
});

router.post('/refresh', refreshAuthorization, function (req, res, next) {
    console.log(res.locals.token_data)

    if (!res.locals.token_data.email) {
        res.status(400).json({
            "error": true,
            "message": "Request body incomplete, refresh token required"
        })
        return
    }

    // console.log(req.body)
    const email = res.locals.token_data.email


    const bearerExpiresIn = 60 * 10; // 10 min
    const bearerExp = Math.floor(Date.now() / 1000) + bearerExpiresIn;
    const refreshExpiresIn = 60 * 60 * 24; // 24 Hours
    const refreshExp = Math.floor(Date.now() / 1000) + refreshExpiresIn;
    const bearerToken = jwt.sign({exp: bearerExp, email: email}, process.env.JWT_SECRET);
    const refreshToken = jwt.sign({exp: refreshExp, email: email}, process.env.JWT_SECRET);

    res.status(200).json({
        "bearerToken": {
            "token": bearerToken,
            "token_type": "Bearer",
            "expires_in": bearerExpiresIn
        },
        "refreshToken": {
            "token": refreshToken,
            "token_type": "Refresh",
            "expires_in": refreshExpiresIn
        }
    });
})

router.post('/logout', refreshAuthorization, function (req, res, next) {
    if (!res.locals.token_data.email) {
        res.status(400).json({
            "error": true,
            "message": "Request body incomplete, refresh token required"
        })
        return
    }
    res.status(200)
    res.json({
        "error": false,
        "message": "Token successfully invalidated"
    })
})

function isFutureDate(value) {
    d_now = new Date();
    d_inp = new Date(value)
    return d_now.getTime() <= d_inp.getTime();
}

module.exports = router;
