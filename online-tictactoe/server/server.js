import net from 'net';

let i = 0;

const server = net.createServer(socket => {
	
	socket.on('data', data => {
		console.log('From client: ', data.toString('utf-8'));
		socket.write('SERVERRESPONSE success' + i);
		i++;
	});

	socket.on('end', () => console.log('ended session'));

	// socket.on('connect', () => {
	// 	console.log('Client connesso 2');
	// });

	// socket.on('data', function (data) {
	// 	socket.write('SERVERRESPONSE success');
	// 	let msg = data.toString('utf-8');
	// 	let messageDivided = msg.trim().split(' ');
	// 	const command = messageDivided[0];
	// 	switch (command) {
	// 		case 'JOIN':
	// 			if (!messageDivided[1]) socket.write('SERVERRESPONSE error');
	// 			console.log('The client wants to join', messageDivided[1]);
	// 			socket.write('SERVERRESPONSE success');
	// 			break;
	// 		default:
	// 			break;
	// 	}
	// 	console.dir(messageDivided);
	// });
});

server.listen(8080, '127.0.0.1');
