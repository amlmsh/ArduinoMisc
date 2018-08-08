/*
 * SerialCom.C
 *
 *  Created on: 04.08.2018
 *      Author: aml
 */

#include "SerialCom.H"

#include <iostream>
#include <string>


#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */

//
// include for the arduino--PC serial communication
//
#include <stdio.h> // standard input / output functions
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls

#define BAUDRATE B9600

using namespace std;


SerialCom::SerialCom(){
	currValueA_ = 90;
	currValueB_ = 90;
}

void SerialCom::openSerialCom(string dev, const int bps){
    fd_ = open(dev.c_str(), O_RDWR | O_NOCTTY);

    struct termios newtio;
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = bps | CRTSCTS | CS8 | CLOCAL | CREAD;

    // set to 8N1
    newtio.c_cflag &= ~PARENB;
    newtio.c_cflag &= ~CSTOPB;
    newtio.c_cflag &= ~CSIZE;
    newtio.c_cflag |= CS8;

    newtio.c_iflag = IGNPAR;

    // output mode to
    //newtio.c_oflag = 0;
    newtio.c_oflag |= OPOST;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME] = 10; /* inter-character timer 1 sec */
    newtio.c_cc[VMIN] = 0; /* blocking read disabled  */

    usleep(200000);  // sleep(2);
    tcflush(fd_, TCIFLUSH);
    if (tcsetattr(fd_, TCSANOW, &newtio)) {
    	fd_ = -1;
        throw string("could not set the serial settings!");
    }

}
void SerialCom::closeSerialCom(){
	if(fd_ > 0){
		close(fd_);
		fd_ = -1;
	}
}

int  SerialCom::getValueA(){
	if(fd_ < 0) throw string("No serial communication.");
	return currValueA_;
}

int  SerialCom::getValueB(){
	if(fd_ < 0) throw string("No serial communication.");
	return currValueB_;
}

void SerialCom::setValueA(int value){
	try{
		// send first string with value A
		sendIntStr(fd_, STOPSIGNPAN_, value);

		// receive int value A
		currValueA_ = receiveIntStr(fd_, STOPSIGNPAN_);
	}catch(string msg){
		throw msg;
	}catch(...){
		throw (string ("unknown error during method call setValueA"));
	}
}

void SerialCom::setValueB(int value){
	try{
		// send first string with value B
		sendIntStr(fd_, STOPSIGNTILT_, value);

		// receive int value B
		currValueB_ = receiveIntStr(fd_, STOPSIGNTILT_);
	}catch(string msg){
		throw msg;
	}catch(...){
		throw (string ("unknown error during method call setValueB"));
	}
}

void SerialCom::sendIntStr(int fileDescrp, const char stopChar, int value){
	string sendStr;
	const char *data;

	sendStr = std::to_string(value) + stopChar;
	data = sendStr.c_str();

	int i=0;
	while(i < sendStr.size()){
		write(fileDescrp, &data[i], sizeof(char));
		if(data[i] == stopChar){
			break;
		}
		i++;
	}

	return;
}


int  SerialCom::receiveIntStr(int fileDescrp, const char stopChar){
	char buf[64];
	buf[0] = '\0';

	char c[1];
    int idx = 0;
    int resValue;

    do{
    	read(fileDescrp, &c[0], sizeof(char));
    	if(c[0] != stopChar){
    		buf[idx] = c[0];
    		buf[idx + 1] = '\0';
    		idx++;
    	}else{
    		//cout << " buffer read:" << buf << "\n";
    		resValue = atoi(buf);
    	    return resValue;
    	}
    }while(1);

}




