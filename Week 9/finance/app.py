import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    rows = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

    holdings = []
    total_value_portfolio = 0

    for row in rows:
        symbol = row["symbol"]
        shares = row["total_shares"]

        stock = lookup(symbol)

        if not stock:
            continue

        price = stock["price"]
        total = float(price) * float(shares)
        total_value_portfolio += total

        holdings.append({
            "symbol": symbol,
            "name": stock["name"],
            "shares": shares,
            "price": price,
            "total": total
        })

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total_value_portfolio += cash

    return render_template("index.html", holdings=holdings, cash=cash, total=total_value_portfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        stock = lookup(symbol)

        if not stock:
            return apology("Symbol is not Correct!!", 400)

        try:
            share = int(shares)
            if share <= 0:
                raise ValueError
        except ValueError:
            return apology("Shares less than 0", 400)

        user_id = session["user_id"]
        user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]
        cash = user["cash"]

        total_cash = float(stock["price"]) * float(shares)

        if total_cash > cash:
            return apology("Not Enough Cash", 400)

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cash, user_id)

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?,?,?,?,'BUY')", user_id, stock[
                "symbol"], shares, stock["price"]
        )

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    transactions = db.execute(
        "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", user_id
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("No such stock symbol Exists!!!", 400)

        stock = lookup(symbol)

        if not stock:
            return apology(f"No stock for the symbol {symbol}", 400)

        if stock:
            return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html", )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        # Validate submission
        username = request.form.get("username").strip().lower()
        password = request.form.get("password").strip()
        confirmation = request.form.get("confirmation").strip()

        # Query database for username

        # Ensure password == confirmation
        if not (password == confirmation):
            return apology("the passwords do not match", 400)

        # Ensure password not blank
        if password == "" or confirmation == "" or username == "":
            return apology("input is blank", 400)

        # Ensure username does not exists already
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) == 1:
            return apology("username already exist", 400)
        else:
            hashcode = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashcode)

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        stock = lookup(symbol)

        if not symbol or not stock:
            return apology("Must Select Symbol", 403)

        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("Not Enough Shares", 200)

        result = db.execute(
            "SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol
        )

        if not result or result[0]["total_shares"] < shares:
            return apology("Not Enough shares!!", 400)

        price = stock["price"]
        total_price = float(price) * float(shares)

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", total_price, user_id
        )

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?,?,?,?,'SELL')", user_id, stock[
                "symbol"], -shares, stock["price"]
        )

        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE id = ? GROUP BY symbol ", user_id
        )
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])
