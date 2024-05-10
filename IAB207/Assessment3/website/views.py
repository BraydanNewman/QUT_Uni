from flask import Blueprint, render_template, request, redirect, url_for
from flask_login import login_required, current_user
from .models import Event


views = Blueprint("main", __name__)


@views.route("/")
def index():
    events = Event.query.all()
    return render_template("index.html", events=events)


@views.route("/viewall")
def all():
    events = Event.query.all()
    return render_template("showall.html", events=events)


@views.route("/myevents")
@login_required
def my():
    compuser = current_user.id
    events = Event.query.select_from(Event).filter(compuser == Event.user_id)

    return render_template("showall.html", events=events)


@views.route("/showRock")
def rock():
    events = Event.query.select_from(Event).filter(Event.genre == "Rock")
    return render_template("showall.html", events=events)


@views.route("/showMetal")
def metal():
    events = Event.query.select_from(Event).filter(Event.genre == "Metal")
    return render_template("showall.html", events=events)


@views.route("/showRap")
def rap():
    events = Event.query.select_from(Event).filter(Event.genre == "Rap")
    return render_template("showall.html", events=events)


@views.route("/showPop")
def pop():
    events = Event.query.select_from(Event).filter(Event.genre == "Pop")
    return render_template("showall.html", events=events)


@views.route("/search")
def search():
    if request.args["search"]:
        print(request.args["search"])
        evnt = "%" + request.args["search"] + "%"
        events = Event.query.filter(Event.name.like(evnt)).all()
        return render_template("showall.html", events=events)
    else:
        return redirect(url_for("main.index"))
