const jwt = require('jsonwebtoken');

// module.exports = function (req, res, next) {
//     console.log("HERE")
//     if (!("authorization" in req.headers)
//         || !req.headers.authorization.match(/^Bearer /)
//     ) {
//         res.status(401).json({error: true, message: "Authorization header ('Bearer token') not found"});
//         return;
//     }
//     const token = req.headers.authorization.replace(/^Bearer /, "");
//     try {
//         jwt.verify(token, process.env.JWT_SECRET);
//         console.log("ALL GOOD");
//     } catch (e) {
//         console.log("FUCKED")
//         if (e.name === "TokenExpiredError") {
//             res.status(401).json({error: true, message: "JWT token has expired"});
//         } else {
//             res.status(401).json({error: true, message: "Invalid JWT token"});
//         }
//         return;
//     }
//     next();
// };

module.exports = function (req, res, next) {
    if (
        !("authorization" in req.headers) ||
        !req.headers.authorization.match(/^Bearer /)
    ) {
        res.status(401).json({
            error: true,
            message: "Authorization header ('Bearer token') not found",
        });
        return;
    }
    const token = req.headers.authorization.replace(/^Bearer /, "");
    let token_data = {};
    try {
        token_data = jwt.verify(token, process.env.JWT_SECRET);
        if (Date.now() / 1000 > token_data.exp) {
            throw {error: true, name: "TokenExpiredError"};
        }
    } catch (e) {
        if (e.name === "TokenExpiredError") {
            res.status(401).json({error: true, message: "JWT token has expired"});
        } else {
            res.status(401).json({error: true, message: "Invalid JWT token"});
        }
        return;
    }

    res.locals.token_data = token_data;
    next();
};