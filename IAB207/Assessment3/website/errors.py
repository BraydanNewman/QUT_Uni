from flask import Blueprint, render_template

error = Blueprint("error", __name__)


@error.app_errorhandler(400)
def handle_400(err):
    error_message = "This request was corrupted on the way.\nPlease try again"
    return render_template(
        "error.html", error_number="400", error_message=error_message
    )


@error.app_errorhandler(401)  # unauthorized access
def handle_401(err):
    error_message = "You are not authorized to request this.\nPlease login to continue"
    return render_template(
        "error.html", error_number="401", error_message=error_message
    )


@error.app_errorhandler(404)
def handle_404(err):
    error_message = "This page doesn't exist.\nPlease try again or search here.... "
    return render_template(
        "error.html", error_number="404", error_message=error_message
    )


# 404 occur


@error.app_errorhandler(500)
def handle_500(err):
    error_message = (
        "Internal Server Error.\nWe are trying to fix this as soon as possible. "
    )
    return render_template(
        "error.html", error_number="500", error_message=error_message
    )
