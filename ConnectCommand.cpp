#include "ConnectCommand.h"

#define PORT 5402
using  namespace std;

/*
 * the function turn the status of the the msgSend to true and
 * give the message that send.
 */
void ConnectCommand::sendMsg(string mesage) {
	this->msgSend = true;
	this->msg = mesage;
}

/*
 * the thread function that will work all the time to be ready
 * get a message that we want sent to the similatur when the msgSenc flag turn to true.
 */
void ConnectCommand::connectToSim(string ip, int port) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //char buffer[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        throw ("Error Opening socket with server");
    server = gethostbyname(ip.c_str());

    if (server == NULL)
        throw ("Can not connect to host , please check the ip");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);


    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw ("Error in connecting to host");
    }
	//if here we made a connection
	while (true) {
		if (this->msgSend) {
			this->msg += "\r\n";
			int is_sent = write(sockfd, this->msg.c_str(), strlen(this->msg.c_str()));
			if (is_sent == -1) {
				std::cout << "Error sending message" << std::endl;
			}
			else {
				this->msgSend = false;
			}
		}
	}
}

/*
 * the execution of the Connect command that will create a socket and connect
 * to the similatur to sent a messages  .
 */
int ConnectCommand::execute(list<string> parameters)
{
	list<string>::iterator it;
	//erase connectCommand
	parameters.pop_front();
	//erase (
	parameters.pop_front();
	int counter = 2;
	//get the first arguments that is the IP
	it = parameters.begin();
	string ipStr=*it;
    ipStr.erase(ipStr.begin() + 0); // delete the first ".
    ipStr.erase(ipStr.end() - 1);
	int port=0;
	counter++;

	//get the second argument that is the PORT
	it++;
	list<string> restOf;
	while (*it != "END") {
		restOf.push_back(*it);
		counter++;
		it++;
	}
	///erase "("
	restOf.pop_back();
	try {
		Interpreter *inter = new Interpreter();
		inter->setVariables(*(this->symbolTable));
		Expression *expression = inter->interpret(restOf);
		port = static_cast<int>(expression->calculate());
	}
	catch (const char* e) {
		throw("invalid argument to sleep function");
	}
 	thread t(&ConnectCommand::connectToSim, this, ipStr, port);
	t.detach();
	//+1 is for "END"
	return (counter + 1);
}