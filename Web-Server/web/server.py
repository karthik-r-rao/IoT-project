import flask
import flask_socketio as fsio
import socketio

app = flask.Flask(__name__)
socketio = fsio.SocketIO(app, always_connect=True)

@app.route("/", methods=['GET'])
@app.route("/home", methods=['GET'])
def home():
    if flask.request.method == "GET":
        # button click
        msg = "[SERVER-SSE] Hello World"
        socketio.emit('sse event', msg)
    return flask.render_template("home.html")

@app.route("/team")
def team():
    return flask.render_template("team.html")

# reply to client
@socketio.on('my message')
def my_custom_event(message):
    print(f"[SERVER] Received message: {message}")
    reply = "[SERVER] Thanks for connecting!"
    fsio.emit('my response', reply)
    print(f"[SERVER] Sent message: {reply}")

if __name__ == "__main__":
    socketio.run(app, host="192.168.1.35", port=5000, debug=True)