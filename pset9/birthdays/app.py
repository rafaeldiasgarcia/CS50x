import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get("name")
        month_str = request.form.get("month")
        day_str = request.form.get("day")

        if not name or not month_str or not day_str:
            # Poderia adicionar flash messages aqui para feedback, mas o PSet não exige
            return redirect("/")

        try:
            month = int(month_str)
            day = int(day_str)
        except ValueError:
            # Usuário digitou algo que não é número para mês ou dia
            return redirect("/")

        if not (1 <= month <= 12 and 1 <= day <= 31):
            # Mês ou dia fora do intervalo válido
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        birthdays_list = db.execute("SELECT id, name, month, day FROM birthdays ORDER BY name")
        return render_template("index.html", birthdays=birthdays_list)
