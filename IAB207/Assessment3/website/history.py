from flask import Blueprint, render_template
from flask_login import login_required

history = Blueprint("history", __name__)


@history.route("/history")
@login_required
def myhistory():
    return render_template("histroy.html")
