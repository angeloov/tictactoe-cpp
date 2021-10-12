import net from 'net';
import * as utils from './utils.js';
import * as protocol from './protocolUtils.js';

const server = net.createServer(socket => {
	socket.on('data', data => {
		const messageParsed = msg.trim().split(' ');
		utils.validateData(messageParsed, socket);

		// console.log('From client: ', data.toString('utf-8'));
		socket.write('SERVERRESPONSE success');
	});

	socket.on('end', () => console.log('ended session'));
});

server.listen(8080, '127.0.0.1');
