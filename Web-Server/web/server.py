import flask

app = flask.Flask(__name__)

@app.route("/")
@app.route("/home")
def home():
    return flask.render_template("home.html")

@app.route("/team")
def team():
    return flask.render_template("team.html")

@app.route("/hello", methods=['GET', 'POST'])
def hello():
    return flask.render_template("hello.html")

if __name__ == "__main__":
    app.run(debug=True)