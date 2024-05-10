from flask import Blueprint, render_template
from flask_login import login_required

buying = Blueprint("buying", __name__)


@buying.route("/buy")
@login_required
def buy():
    return render_template("buy.html")
