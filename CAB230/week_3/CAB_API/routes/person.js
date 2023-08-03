const express = require('express');
const router = express.Router();
const authorization = require("../middleware/authorization");

router.get('/:personId', authorization, function (req, res, next) {
    if (Object.keys(req.query).length > 0) {
        res.status(400).json({
            "error": true,
            "message": "Invalid query parameters: year. Query parameters are not permitted."
        });
        return;
    }
    req.db
        .select()
        .from("names")
        .leftJoin("principals", "names.nconst", "principals.nconst")
        .leftJoin("basics", "principals.tconst", "basics.tconst")
        .where("names.nconst", "=", req.params.personId)
        .then((rows) => {
            if (rows.length === 0) {
                res.status(404).json({
                    error: true,
                    message: "No record exists of a person with this ID",
                });
                return;
            }
            const test = {
                "name": rows[0].name,
                "birthYear": rows[0].birthYear,
                "deathYear": rows[0].deathYear,
                "roles": rows.map((row) => {
                    return {
                        "movieName": row["originalTitle"],
                        "movieId": row["tconst"],
                        "category": row["category"],
                        "characters": row.characters ? JSON.parse(row.characters) : [],
                        "imdbRating": parseFloat(row.imdbRating),
                    }
                }),
            }
            res.json(test)
        })
});

module.exports = router;
