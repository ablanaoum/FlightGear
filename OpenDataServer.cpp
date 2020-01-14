
#include "OpenDataServer.h"


//#include "OpenDataServer.h"
using namespace std;


void OpenDataServer::openServer(int port) {

	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1) {
		//error
		throw  "Could not create a socket";
	}

	//bind socket to IP address
	// we first need to create the sockaddr obj.
	sockaddr_in address, client_addr; //in means IP4
	bzero((char *)&address, sizeof(address));


	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
	address.sin_port = htons(port);
	//we need to convert our number
	// to a number that the network understands.

	//the actual bind command
	if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
		throw "Could not bind the socket to an IP";
	}

	//making socket listen to the port
	if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
		throw "Error during listening command";
	}
	else {
		std::cout << "Server is now listening ..." << std::endl;
	}

	int clientLen = sizeof(client_addr);
	// accepting a client
	int client_socket = accept(socketfd, (struct sockaddr *) &client_addr,
		(socklen_t *)& clientLen);

	if (client_socket == -1) {
		throw "Error accepting client";
	}



	//reading from client
    map<int,string> simvar;
	simvar = this->varsOrder();
	while (true) {
        char buffer[1024];
        int n;
        map<string, double> alldata;
		bzero(buffer, 1024);
		n = read(client_socket, buffer, 1024);
		if (n < 0)
			throw ("Error reading from the client");
		buffer[n] = '\0';
		string var = "";
		int i = 0;
		int num = 0;
		while (i < n) {
			while (buffer[i] != ',' && i < n ) {
				var += buffer[i];
				i++;
			}
			alldata.insert(std::pair<string, double>((simvar[num]), stod(var)));
			num++;
			var = "";
			i++;
		}
		map<string, double>::iterator itSim;
		map<string, Var>::iterator it;
		for (itSim = alldata.begin(); itSim != alldata.end(); ++itSim) {
			for (it = this->symbolTable->begin(); it != this->symbolTable->end(); ++it) {
				if (itSim->first == (it->second).sim) {
					if ((it->second).type == "<-") {
					    (it->second).value = itSim->second;
					}
				}
			}
		}
		this->pass = true; //let the main thread continue
		//////////////////////
		sleep((unsigned int)1 / 10);
	}

}
int OpenDataServer::execute(list<string> parameters) {
	int counter = 1;
	parameters.pop_front();
	list <string> restOfLine;
	list<string>::iterator it = parameters.begin();

	while (*it != "END") {
		restOfLine.push_back(*it);
		counter++;
		it++;
	}
	int port;
	double p;
	try {

		Interpreter *inter = new Interpreter();
		inter->setVariables(*(this->symbolTable));
		Expression *expression = inter->interpret(restOfLine);
		p = expression->calculate();
	}
	catch (const char* e) {
		throw ("invalid argument to OpenDataServer function");
	}
	//int port = (int) p;
	port = static_cast<int>(p);
	thread t(&OpenDataServer::openServer, this, port);
	//this_thread::sleep_for(chrono::milliseconds(long(500.0)));
	t.detach();
	while(!pass){}
	//+1 for END
	counter++;
	return (counter);
	//create socket
}

///instrumentation/heading-indicator/offset-deg
map<int,string> OpenDataServer::varsOrder() {
    map<int,string> simVars;
	simVars[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
	simVars[1] = "/sim/time/warp";
	simVars[2] = "/controls/switches/magnetos";
	simVars[3] = "/instrumentation/heading-indicator/offset-deg";
	simVars[4] = "/instrumentation/altimeter/indicated-altitude-ft";
	simVars[5] = "/instrumentation/altimeter/pressure-alt-ft";
	simVars[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
	simVars[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
	simVars[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
	simVars[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
	simVars[10] = "/instrumentation/encoder/indicated-altitude-ft";
	simVars[11] = "/instrumentation/encoder/pressure-alt-ft";
	simVars[12] = "/instrumentation/gps/indicated-altitude-ft";
	simVars[13] = "/instrumentation/gps/indicated-ground-speed-kt";
	simVars[14] = "/instrumentation/gps/indicated-vertical-speed";
	simVars[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
	simVars[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
	simVars[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
	simVars[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
	simVars[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
	simVars[20] = "/controls/flight/aileron";
	simVars[21] = "/controls/flight/elevator";
	simVars[22] = "/controls/flight/rudder";
	simVars[23] = "/controls/flight/flaps";
	simVars[24] = "/controls/engines/engine/throttle";
	simVars[25] = "/controls/engines/current-engine/throttle";
	simVars[26] = "/controls/switches/master-avionics";
	simVars[27] = "/controls/switches/starter";
	simVars[28] = "/engines/active-engine/auto-start";
	simVars[29] = "/controls/flight/speedbrake";
	simVars[30] = "/sim/model/c172p/brake-parking";
	simVars[31] = "/controls/engines/engine/primer";
	simVars[32] = "/controls/engines/current-engine/mixture";
	simVars[33] = "/controls/switches/master-bat";
	simVars[34] = "/controls/switches/master-alt";
	simVars[35] = "/engines/engine/rpm";
	return simVars;
}