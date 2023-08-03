const express = require("express");
const router = express.Router();
router.get("/search", function (req, res, next) {
    const PAGE_ITEM_COUNT = 100;
    if (req.query.year && !/^\d{4}$/.test(req.query.year)) {
        return res.status(400).json({
            error: true,
            message: "Invalid year format. Format must be yyyy.",
        });
    }
    if (req.query.page && !/^\d+$/.test(req.query.page)) {
        return res.status(400).json({
            "error": true,
            "message": "Invalid page format. page must be a number."
        });
    }
    const page = req.query.page !== undefined ? Number(req.query.page) : 1;
    req.db
        .from("basics")
        .select()
        .where("primaryTitle", "like", `%${req.query.title ?? ""}%`)
        .where("year", "like", `%${req.query.year ?? ""}%`)
        .orderBy("tconst", "asc")
        .then((data) => {
            const endRow = page * PAGE_ITEM_COUNT > data.length ? data.length : (page * PAGE_ITEM_COUNT);
            const startRow = (page - 1) * PAGE_ITEM_COUNT;
            const row_array = page > 1 ? data.slice(startRow, endRow) : data.slice(0, PAGE_ITEM_COUNT)
            res.json({
                data: row_array.map((row) => {
                    return {
                        "title": row.primaryTitle,
                        "year": row.year,
                        "imdbID": row.tconst,
                        "imdbRating": parseFloat(row.imdbRating),
                        "rottenTomatoesRating": parseInt(row.rottentomatoesRating),
                        "metacriticRating": parseInt(row.metacriticRating),
                        "classification": row.rated
                    }
                }),
                pagination: {
                    "total": data.length,
                    "lastPage": Math.ceil(data.length / PAGE_ITEM_COUNT),
                    "prevPage": (page > 1) ? page - 1 : null,
                    "nextPage": (page < Math.ceil(data.length / PAGE_ITEM_COUNT)) ? page + 1 : null,
                    "perPage": PAGE_ITEM_COUNT,
                    "currentPage": page,
                    "from": startRow,
                    "to": startRow + row_array.length
                }
            });
            res.status(200);
        })
});

router.get("/data/:imdbID", function (req, res, next) {
    if (Object.keys(req.query).length > 0) {
        res.status(400).json({
            error: true,
            message:
                "Invalid query parameters: QueryParam. Query parameters are not permitted.",
        });
        return;
    }
    req.db
        .select()
        .from("basics")
        .leftJoin("principals", "basics.tconst", "principals.tconst")
        .leftJoin("ratings", "basics.tconst", "ratings.tconst")
        .where("basics.tconst", "=", req.params.imdbID)
        .then((rows) => {
            if (rows.length === 0) {
                res.status(404).json({
                    error: true,
                    message: "No record exists of a movie with this ID",
                });
                return;
            }
            if (rows.length === 0) {
                res.status(404)
                res.json({
                    error: true,
                    message: "No record exists of a movie with this ID",
                });
            }
            const base_data = rows[0]
            // Fuck Javascript for doing set unique check by references not god-damn values, So stupid
            const ratings = []
            const uniqRatings = new Set()
            const principals = []
            const uniqPrincipals = new Set()
            for (const row in rows) {
                if (!uniqRatings.has(rows[row].source)) {
                    uniqRatings.add(rows[row].source)
                    ratings.push({
                        "source": rows[row].source,
                        "value": parseFloat(rows[row].value)
                    })
                }
                if (!uniqPrincipals.has(rows[row].nconst)) {
                    uniqPrincipals.add(rows[row].nconst)
                    principals.push({
                        "id": rows[row].nconst,
                        "category": rows[row].category,
                        "name": rows[row].name,
                        "characters": rows[row].characters ? JSON.parse(rows[row].characters) : []
                    })
                }
            }
            res.json({
                "title": base_data.primaryTitle,
                "year": base_data.year,
                "runtime": base_data.runtimeMinutes,
                "genres": base_data.genres.split(","),
                "country": base_data.country,
                "principals": principals,
                "ratings": ratings,
                "boxoffice": base_data.boxoffice,
                "poster": base_data.poster,
                "plot": base_data.plot,

            })
        })
})

module.exports = router;