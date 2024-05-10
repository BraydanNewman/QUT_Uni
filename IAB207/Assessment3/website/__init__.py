from flask import Flask, abort
from flask_login import LoginManager
from flask_bootstrap import Bootstrap5
from flask_sqlalchemy import SQLAlchemy
import os

db = SQLAlchemy()
app = Flask(
    __name__,
    template_folder="templates",
)


def create_app():  # create app

    Bootstrap5(app)
    # Database configuration
    app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"

    # Login Handling
    login_manager = LoginManager()  # init. flasklogin.loginmanager
    login_manager.init_app(app)
    login_manager.login_view = "auth.login"

    @login_manager.unauthorized_handler  # error handling for loginrequired() func.
    def unauthorized():
        return abort(401)  # returns error code (handled in errors.py)

    from .models import User

    @login_manager.user_loader
    def load_user(user_id):
        return User.query.get(int(user_id))

    db.init_app(app)
    with app.app_context():
        db.create_all()

    app.secret_key = "SECRET KEY"  # Might need to be changed

    from .views import views as main_blueprints
    from .event import event as event_blueprints
    from .auth import auth as auth_blueprints
    from .errors import error as error_blueprints
    from .history import history as history_blueprints
    from .buying import buying as buy_blueprints

    app.register_blueprint(main_blueprints)
    app.register_blueprint(event_blueprints)
    app.register_blueprint(auth_blueprints)
    app.register_blueprint(error_blueprints)
    app.register_blueprint(history_blueprints)
    app.register_blueprint(buy_blueprints)
    return app
