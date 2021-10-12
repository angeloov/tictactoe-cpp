const sendErrorToClient = (socket) => {
  socket.write("SERVERRESPONSE error");
}

const validateData = socket => {
	console.log('ciao');
	return true;
};
