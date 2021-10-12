import net from 'net';
import * as utils from './utils.js';
import * as verbs from './verbsHandler.js';

let roomID;
let players = [];
let gameBoard = [];
let winner = null; // null || 1 || -1
let gameState = 'playing';

let numberOfMoves = 0;

utils.initializeGameBoard(gameBoard);

const server = net.createServer(socket => {
	socket.on('data', data => {
		let msg = data.toString('utf-8');
		const messageParsed = msg.trim().split(' ');
		if (!utils.validateMsg(messageParsed, socket)) return;

		console.log(messageParsed);

		switch (messageParsed[0]) {
			case 'CREATEROOM':
				if (roomID) return utils.sendErrorToClient(socket);
				roomID = verbs.createRoom(socket);
				break;
			case 'JOIN':
				verbs.joinRoom(socket, messageParsed[1]);
				break;
			case 'PLACEMOVE':
				if (gameState === 'playing') {
					numberOfMoves++;

					let arrayIndex = messageParsed[1];
					let symbol = messageParsed[2]; // Symbol has to be 'X' || 'O'
					if (!arrayIndex || !symbol) utils.sendErrorToClient();

					let playerNum = symbol === 'X' ? 1 : -1;

					if (gameBoard[parseInt(arrayIndex / 3)][arrayIndex % 3] === 0) {
						gameBoard[parseInt(arrayIndex / 3)][arrayIndex % 3] = playerNum;
						socket.write('SERVERRESPONSE success');
					} else {
						utils.sendErrorToClient(socket);
					}

					let result = checkIfSomeoneWon(gameBoard);
					if (result !== 0) {
						gameState = 'won';
						winner = result;
					}

					console.log(gameBoard);
				}
				break;
			case 'GETMATCHSTATE':
				// draw
				if (numberOfMoves === 9 && !winner) {
					return socket.write('SERVERRESPONSE draw');
				}
				// playing
				if (gameState === 'playing') {
					return socket.write('SERVERRESPONSE playing');
				}

				// winner
				if (gameState === 'won') {
					return socket.write(`SERVERRESPONSE winner ${winner === 1 ? 'X' : 'O'}`);
				}
				break;
		}

		// socket.write('SERVERRESPONSE success');
	});

	socket.on('end', () => console.log('ended session'));
});

// Given a 2D array B, returns 1 if X has made tictactoe, -1 if O has done it instead,
// 0 if no one won
function checkIfSomeoneWon() {
	// Sum all rows
	for (let i = 0; i < 3; i++) {
		let sum = 0;
		for (let j = 0; j < 3; j++) {
			sum += gameBoard[i][j];
		}

		if (sum === 3) return 1;
		else if (sum === -3) return -1;
	}

	// Sum all columns
	for (let i = 0; i < 3; i++) {
		let sum = 0;
		for (let j = 0; j < 3; j++) {
			sum += gameBoard[j][i];
		}

		if (sum === 3) return 1;
		else if (sum === -3) return -1;
	}

	let sum = 0;
	for (let i = 0; i < 3; i++) {
		sum += gameBoard[i][i];
	}
	if (sum === 3) return 1;
	else if (sum === -3) return -1;

	sum = 0;
	for (let i = 0; i < 3; i++) {
		for (let j = 0; j < 3; j++) {
			if (i + j === 2) sum += gameBoard[i][j];
		}
	}
	if (sum === 3) return 1;
	else if (sum === -3) return -1;

	return 0;
}

server.listen(8080, '127.0.0.1');

export { players, roomID };
