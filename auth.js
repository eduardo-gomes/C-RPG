var WEBPORT = 8081;
var http = require('http');
var fs = require('fs');
var url = require('url');
var net = require('net');
var crypto = require('crypto');
function call_socket(msg){
	console.log(msg.socket);
	console.log(msg.token);
	if(msg.socket !== null){
		if(msg.token !== null){
			var hash = crypto.createHash('sha256').update(msg.token).digest('base64');
			msg.token = hash;
			var msgstr = JSON.stringify(msg);
			var socket = net.connect({
				port: 1406,
				host: 'localhost',
			}, function(){
				socket.end(msgstr + '\003');
			});
			socket.on('error', function(ex){
				console.log("Socket error");
			});
		}
	}
}

http.createServer(function (req, res) {
	var url_parse = url.parse(req.url, true)
	var path_url = url_parse.pathname;
	switch(path_url){
		case "/jogo/auth/handler":
			res.writeHead(200, { 'Content-Type': 'text/html' });
			fs.readFile('html/handler.html', function(err, data){
				res.end(data);
			});
			break;
		case "/jogo/auth":
			res.writeHead(200, { 'Content-Type': 'text/html' });
			fs.readFile('html/firebase.html', function (err, data) {
				res.end(data);
			});
			break;
		case "/jogo/after":
			res.writeHead(200, { 'Content-Type': 'text/html' });
			fs.readFile('html/fireafter.html', function (err, data) {
				res.end(data);
			});
			break;
		case "/jogo/auth/end":
			res.writeHead(200, { 'Content-Type': 'text/html' });
			fs.readFile('html/end.html', function (err, data) {
				res.end(data);
			});
			break;
		case "/jogo/auth/login.php":
			//console.log(url_parse.query);
			res.writeHead(200, { 'Content-Type': 'text/html' });
			fs.readFile('html/login.html', function (err, data) {
				res.end(data);
			});
			call_socket(JSON.parse(url_parse.query.auth));
			break;
		default:
			res.writeHead(404, 'Not Found');
			res.end();
	}
}).listen(WEBPORT);