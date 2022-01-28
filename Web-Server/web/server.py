import flask
import flask_socketio as fsio

app = flask.Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = fsio.SocketIO(app, always_connect=True)

@app.route("/", methods=['GET', 'POST'])
@app.route("/home", methods=['GET', 'POST'])
def home():
    return flask.render_template("home.html")

@app.route("/team")
def team():
    return flask.render_template("team.html")

@socketio.on('my message')
def my_custom_event(message):
    print(f"[SERVER] Received message: {message}")
    reply = "Thanks for connecting!"
    fsio.emit('my response', reply)
    print(f"[SERVER] Sent message: {reply}")

if __name__ == "__main__":
    socketio.run(app, host="192.168.1.35", port=5000, debug=True)