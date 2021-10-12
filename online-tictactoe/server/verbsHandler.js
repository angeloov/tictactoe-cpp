import { players, roomID } from './server.js';
import * as utils from './utils.js';

const createRoom = socket => {
	players.push(socket);
	const roomID = Math.floor(Math.random() * 9000) + 1000;
	socket.write(`SERVERRESPONSE success ${roomID}`);

	return roomID;
};

const joinRoom = (socket, userRoomID) => {
	if (parseInt(roomID) === parseInt(userRoomID)) {
		players.push(socket);
		socket.write('SERVERRESPONSE success');
	} else {
		utils.sendErrorToClient(socket);
	}
};

export { createRoom, joinRoom };
