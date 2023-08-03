const jwt = require('jsonwebtoken');

module.exports = function (req, res, next) {
    // console.log(req.body.refreshToken)

    let token_data = {};
    try {
        token_data = jwt.verify(req.body.refreshToken, process.env.JWT_SECRET);
        if (Date.now() / 1000 > token_data.exp) {
            throw {error: true, name: "TokenExpiredError"};
        }
    } catch (e) {
        if (e.name === "TokenExpiredError") {
            res.status(401).json({error: true, message: "JWT token has expired"});
            return;
        } else if (e.message !== "jwt must be provided") {
            res.status(401).json({error: true, message: "Invalid JWT token"});
            return;
        }
    }
    res.locals.token_data = token_data;
    next();
};