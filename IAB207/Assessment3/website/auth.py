from flask import Blueprint, render_template, request, redirect, url_for
from website.forms import LoginForm, RegisterForm
from flask_login import login_user, logout_user
from werkzeug.security import generate_password_hash, check_password_hash
from .models import db, User


auth = Blueprint(
    "auth",
    __name__,
    template_folder="templates",
    static_url_path="",
    static_folder="assets",
)


@auth.route("/login", methods=["GET", "POST"])
def login():
    form = LoginForm()
    error = None
    if request.method == "POST" and form.validate():
        user = db.session.execute(
            db.select(User).filter(User.username == form.username.data)
        ).first()
        if user and check_password_hash(user[0].hashed_password, form.password.data):
            login_user(user[0])
            return redirect(url_for("main.index"))
        error = "Incorrect username or password"
    return render_template("login.html", form=form, error=error)


@auth.route("/register", methods=["GET", "POST"])
def register():
    register = RegisterForm()
    if register.validate_on_submit() == True:
        uname = register.username.data
        pwd = register.password.data
        email = register.email.data
        u1 = User.query.filter_by(username=uname).first()
        if u1:

            return redirect(url_for("auth.login"))
        pwd_hash = generate_password_hash(pwd)
        new_user = User(username=uname, hashed_password=pwd_hash, email=email)
        db.session.add(new_user)
        db.session.commit()
        return redirect(url_for("main.index"))
    else:
        return render_template("register.html", form=register)


@auth.route("/logout", methods=["POST", "GET"])
def logout():
    logout_user()
    return redirect(url_for("main.index"))
