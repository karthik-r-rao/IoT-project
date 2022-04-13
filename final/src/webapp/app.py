import os
import flask
import redis
from flask_cors import CORS

red = redis.StrictRedis.from_url('redis://redis:6379/0')
controller = flask.Blueprint('count', 'count', url_prefix='/count')
 
def count_stream():
    pub_sub = red.pubsub()
    pub_sub.subscribe('count')
 
    for message in pub_sub.listen():
        if isinstance(message['data'], (bytes, bytearray)):
            result = message['data'].decode('utf-8')
            yield "data: %s\n\n" % result
 
 
@controller.route('/push', methods=['POST'])
def post():
    message = flask.request.data
    red.publish('count', message)
    return flask.Response(status=204)
 
 
@controller.route('/stream')
def stream():
    return flask.Response(count_stream(), mimetype="text/event-stream")

app = flask.Flask(__name__, static_folder=os.path.abspath('/static'))
app.register_blueprint(controller)
CORS(app)

@app.route('/')
def root():
    return app.send_static_file('home.html')
    
@app.route('/team')
def team():
    return app.send_static_file('team.html')

@app.route('/about')
def about():
    return app.send_static_file('about.html')
 
if __name__ == '__main__':
    app.static_folder = 'static'
    app.run(debug=True, host='0.0.0.0')