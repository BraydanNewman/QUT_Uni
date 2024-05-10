from flask_login import UserMixin
from datetime import datetime
from . import db


# model for user table
# table names necessary for foreign keys
class User(db.Model, UserMixin):
    __tablename__ = "users"
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(128), nullable=False, unique=True)
    email = db.Column(db.String(128), nullable=False, unique=True)
    hashed_password = db.Column(db.String(128), nullable=False)
    comments = db.relationship("Comment", backref="user")
    events = db.relationship("Event", backref="user")


# model for events table
class Event(db.Model):
    __tablename__ = "events"
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(128), nullable=False)
    price = db.Column(db.Integer, nullable=True)
    date = db.Column(db.Date, nullable=False)
    time = db.Column(db.Time, nullable=False)
    overview = db.Column(db.String(256), nullable=False)
    description = db.Column(db.String(4096), nullable=False)
    purchaseinfo = db.Column(db.String(4096), nullable=True)
    location = db.Column(db.String, nullable=False)
    available = db.Column(db.Integer, nullable=False)
    genre = db.Column(db.String(400), nullable=False)
    image = db.Column(db.String(400))
    featured = db.Column(db.String(128), nullable=False)
    user_id = db.Column(db.Integer, db.ForeignKey("users.id"))
    comments = db.relationship("Comment", backref="event")

    def __repr__(self):  # string print method
        return "<Name: {}>".format(self.name)


class Comment(db.Model):
    __tablename__ = "comments"
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(400))
    text = db.Column(db.String(400))
    created_at = db.Column(db.DateTime, default=datetime.now())
    # add the foreign keys
    user_id = db.Column(db.Integer, db.ForeignKey("users.id"))
    event_id = db.Column(db.Integer, db.ForeignKey("events.id"))

    def __repr__(self):
        return "<Comment: {}>".format(self.text)
