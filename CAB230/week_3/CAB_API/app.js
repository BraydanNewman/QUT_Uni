const options = require('./knexfile.js');
const knex = require('knex')(options);
const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const helmet = require("helmet")
const swaggerUI = require("swagger-ui-express");
const userRouter = require('./routes/user');
const moviesRouter = require('./routes/movies');
const personRouter = require('./routes/person');
const cors = require("cors");
require("dotenv").config();
const app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

app.use(cors());
app.use((req, res, next) => {
    req.db = knex;
    next();
});
app.use(helmet());
const swaggerDoc = require("./docs/openapi.json");
app.use("/", swaggerUI.serve);
app.get("/", swaggerUI.setup(swaggerDoc));
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use('/user', userRouter);
app.use('/movies', moviesRouter);
app.use('/people', personRouter);

app.get("/knex", function (req, res, next) {
    req.db.raw("SELECT VERSION()")
        .then((version) => console.log(version[0][0]))
        .catch((err) => {
            console.log(err);
            throw err;
        });

    res.send("Version Logged successfully");
});

app.use((req, res, next) => {
    req.db = knex
    next()
});

// catch 404 and forward to error handler
app.use(function (req, res, next) {
    next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
    // set locals, only providing error in development
    res.locals.message = err.message;
    res.locals.error = req.app.get('env') === 'development' ? err : {};

    // render the error page
    res.status(err.status || 500);
    res.render('error');
});

module.exports = app;
