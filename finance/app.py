import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd
from datetime import datetime


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
    all_transactions = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='transactions'")
    cash = db.execute(f"SELECT cash FROM users WHERE id = '{user_id}'")[0]["cash"]

    if len(all_transactions) == 0:
        return render_template("index.html", portfolio=None, cash=cash)

    all_transactions = db.execute(f'''
                        SELECT symbol,
                        SUM(CASE WHEN action = 'buy' THEN shares ELSE -shares END) as total_shares
                        FROM transactions
                        WHERE user_id = '{user_id}'
                        GROUP BY symbol
                        ''')

    portfolio = []

    for transaction in all_transactions:
        symbol = transaction["symbol"]
        shares = transaction["total_shares"]
        if shares != 0:
            current_price = lookup(symbol)["price"]
            total = shares * current_price
            portfolio.append({
                "symbol": symbol,
                "shares": shares,
                "current_price": current_price,
                "total": total
            })

    return render_template("index.html", portfolio=portfolio, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not shares.isdigit():
            return apology("Only digits for shares", 400)

        if symbol == "":
            return apology("Need symbol", 400)

        quote = lookup(symbol)

        if quote is None:
            return apology("Sorry, we did not find anything")

        price = float(quote["price"])
        user_id = session["user_id"]
        cash = db.execute(f"SELECT cash FROM users WHERE id = '{user_id}'")[0]["cash"]
        total = int(shares) * price
        remaining_cash = round(cash - total, 2)

        if remaining_cash <= 0:
            return apology("U broke, bro!")

        db.execute(f"UPDATE users SET cash = '{remaining_cash}' WHERE id = '{user_id}'")
        db.execute('''
        CREATE TABLE IF NOT EXISTS transactions
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            user_id TEXT NOT NULL,
            symbol TEXT NOT NULL,
            shares INTEGER NOT NULL,
            price FLOAT NOT NULL,
            total FLOAT NOT NULL,
            action TEXT NOT NULL,
            date TEXT NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id)
        )
        ''')

        db.execute(f'''INSERT INTO transactions
                   (user_id, symbol, shares, price, total, action, date)
                   VALUES ('{user_id}','{symbol.upper()}', '{shares}', '{price}', '{total}', 'buy', '{datetime.today()}')''')

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    all_transactions = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='transactions'")

    if len(all_transactions) == 0:
        return render_template("history.html", all_transactions=None)

    all_transactions = db.execute(f"SELECT * FROM transactions WHERE user_id = '{user_id}'")

    return render_template("history.html", all_transactions=all_transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote is not None:
            return render_template("quote.html", quote=quote)

    return apology("Sorry, we did not find anything")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if username == "" or password == "" or confirmation == "":
            return apology("All fields must be provided", 400)

        if password != confirmation:
            return apology("Passwords do not match")

        users = db.execute("SELECT username FROM users")

        for user in users:
            if user["username"] == username:
                return apology("Username already exists")

        hash = generate_password_hash(password)
        db.execute(f"INSERT INTO users (username, hash) VALUES ('{username}', '{hash}')")
        return redirect("/")


@app.route("/sell", methods=["POST", "GET"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    all_transactions = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='transactions'")

    if request.method == "GET":
        if len(all_transactions) == 0:
            return render_template("sell.html")

        all_transactions = db.execute(f'''
                        SELECT symbol,
                        SUM(CASE WHEN action = 'buy' THEN shares ELSE -shares END) as total_shares
                        FROM transactions
                        WHERE user_id = '{user_id}'
                        GROUP BY symbol
                        ''')
        symbols = []

        for transaction in all_transactions:
            shares = transaction["total_shares"]
            if shares != 0:
                symbols.append(transaction["symbol"])

        return render_template("sell.html", symbols=symbols)

    if len(all_transactions) == 0:
        return apology("Child, you have nothing!")

    all_transactions = db.execute(f'''
                        SELECT symbol,
                        SUM(CASE WHEN action = 'buy' THEN shares ELSE -shares END) as total_shares
                        FROM transactions
                        WHERE user_id = '{user_id}'
                        GROUP BY symbol
                        ''')

    symbol = request.form.get("symbol")
    print("**************************", request.form)
    print("::::::::::::::::::::::::::", symbol)

    shares = int(request.form.get("shares"))
    print("----------------------", shares)

    for transaction in all_transactions:
        if symbol == transaction["symbol"]:
            if shares <= int(transaction["total_shares"]):
                cash = db.execute(f"SELECT cash FROM users WHERE id = '{user_id}'")[0]["cash"]
                quote = lookup(symbol)
                current_price = float(quote["price"])
                sell_price = current_price
                total = shares * current_price
                cash += total
                db.execute(f"UPDATE users SET cash = '{round(cash, 2)}' WHERE id = '{user_id}'")
                db.execute(f'''INSERT INTO transactions
                       (user_id, symbol, shares, price, total, action, date)
                       VALUES ('{user_id}','{symbol}', '{shares}', '{sell_price}', '{total}', 'sell', '{datetime.today()}')''')
                return redirect("/")
            else:
                return apology("Not enough shares")

    return apology("You don't have these shares")

