from flask import Blueprint, render_template, request, redirect, url_for
from .forms import EventForm, CommentForm
from .models import Event, Comment
from . import db
from flask_login import login_required, current_user
from werkzeug.utils import secure_filename
import os

event = Blueprint("event", __name__, template_folder="templates", url_prefix="/events")


@event.route("/<id>")
def show(id):
    event = Event.query.filter_by(id=id).first()
    cform = CommentForm()
    return render_template("events/show.html", event=event, form=cform)


@event.route("/create", methods=["GET", "POST"])
@login_required
def create():
    print("Method type: ", request.method)
    form = EventForm()
    msg = ""
    if form.validate_on_submit():
        img_file_path = check_image_file(form)
        event = Event(
            name=form.name.data,
            price=form.price.data,
            date=form.date.data,
            time=form.time.data,
            overview=form.overview.data,
            description=form.description.data,
            purchaseinfo=form.purchaseinfo.data,
            location=form.location.data,
            image=img_file_path,
            available=form.available.data,
            genre=form.genre.data,
            featured=form.featured.data,
            user=current_user,
        )
        db.session.add(event)
        db.session.commit()
        msg = "Successfully Added"
        return redirect(url_for("event.create"))
    error = form.errors.items()
    return render_template("create.html", error=error, form=form, msg=msg)


def check_image_file(form):
    fp = form.image.data
    filename = fp.filename
    BASE_PATH = os.path.dirname(__file__)
    upload_path = os.path.join(BASE_PATH, "static/image", secure_filename(filename))
    db_upload_path = "/static/image/" + secure_filename(filename)
    fp.save(upload_path)
    return db_upload_path


@event.route("/<event>/comment", methods=["GET", "POST"])
@login_required
def comment(event):
    form = CommentForm()
    event_obj = Event.query.filter_by(id=event).first()
    if form.validate_on_submit():
        comment = Comment(
            title=form.text.data,
            text=form.text.data,
            event=event_obj,
            user=current_user,
        )
        db.session.add(comment)
        db.session.commit()
    return redirect(url_for("event.show", id=event))
