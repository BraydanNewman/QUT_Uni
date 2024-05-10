from flask_wtf import FlaskForm
from wtforms.fields import (
    SubmitField,
    StringField,
    PasswordField,
    EmailField,
    IntegerField,
    DateField,
    TextAreaField,
    TimeField,
    SelectField,
)
from flask_wtf.file import FileRequired, FileField, FileAllowed
from wtforms.validators import (
    Email,
    EqualTo,
    Length,
    InputRequired,
)

ALLOWED_FILE = {"PNG", "JPG", "png", "jpg"}


class LoginForm(FlaskForm):
    username = StringField("Username", validators=[InputRequired("Enter Username")])
    password = PasswordField("Password", validators=[InputRequired("Enter Password")])
    submit = SubmitField("Login")


class RegisterForm(FlaskForm):
    username = StringField("Username", validators=[InputRequired()])
    email = EmailField("Email", validators=[Email("Please enter valid email")])

    password = PasswordField(
        "Password",
        validators=[
            InputRequired(),
            EqualTo("confirm", message="Passwords should match"),
        ],
    )
    confirm = PasswordField("Confirm Password")

    submit = SubmitField("Register")


class EventForm(FlaskForm):
    imagestates = [("1", ("Normal")), ("2", ("Featured"))]
    genres = [
        ("Rock", ("Rock")),
        ("Metal", ("Metal")),
        ("Rap", ("Rap")),
        ("Pop", ("Pop")),
    ]
    name = StringField(
        "Name or Band",
        validators=[
            InputRequired("Enter Name or Band of Event"),
            Length(min=3, message="Title is too short!"),
        ],
    )
    price = IntegerField(
        "Ticket Price", validators=[InputRequired("Enter ticket price of Event")]
    )
    date = DateField("Date", validators=[InputRequired("Enter Date of Event")])
    time = TimeField("Time")
    overview = TextAreaField(
        "Overview of event",
        validators=[InputRequired("Enter an overview of the event")],
    )
    description = TextAreaField(
        "Description", validators=[InputRequired("Enter description of Event")]
    )
    purchaseinfo = TextAreaField(
        "Purchase Information",
        validators=[
            InputRequired("Enter the any billing or related ticketing information")
        ],
    )
    location = StringField(
        "Location", validators=[InputRequired("Specify the events location")]
    )
    available = IntegerField(
        "Available tickets",
        validators=[InputRequired("Specify how many tickets are available")],
    )
    genre = SelectField(choices=genres, default=1)
    # featured field will feature the entry in the carousel
    featured = SelectField(choices=imagestates, default=1)
    # image handling
    # main site image
    image = FileField(
        "Thumbnail",
        validators=[
            FileRequired("Select a Thumbnail to Upload"),
            FileAllowed(ALLOWED_FILE, message="Only supports png,jpg,JPG,PNG"),
        ],
    )
    # submit the form
    create = SubmitField("Create")


class CommentForm(FlaskForm):
    title = StringField("Title", [InputRequired()])
    text = StringField("Comment", [InputRequired()])
    submit = SubmitField("Post")
