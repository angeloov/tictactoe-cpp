import crypto from 'crypto';

const sendErrorToClient = socket => socket.write('SERVERRESPONSE error');

const validateMsg = (msg, socket) => {
	const allowedVerbs = ['JOIN', 'CREATEROOM', 'PLACEMOVE', 'GETMATCHSTATE'];

	if (!allowedVerbs.includes(msg[0])) {
		console.error("The verb isn't valid");
		socket.write('SERVERRESPONSE error');
		return false;
	}

	return true;
};

const initializeGameBoard = B => {
	for (let i = 0; i < 3; i++) {
		B[i] = new Array(3);
		for (let j = 0; j < 3; j++) {
			B[i][j] = 0;
		}
	}
};

const generateRandomHash = () => crypto.randomBytes(4).toString('hex');


export { sendErrorToClient, validateMsg, generateRandomHash, initializeGameBoard };
