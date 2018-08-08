/*
 * Demos.C
 *
 *  Created on: 04.08.2018
 *      Author: aml
 */

#include "Demos.H"
#include "SerialCom.H"
#include "PanTilt.H"

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


void demoPanTilt(){
	using namespace PanTilt;

	PanTiltDegree leftCam;

	leftCam.openSerialCom("/dev/ttyUSB0");

	cout << "[" << leftCam.getPanAngle()  << "; " << leftCam.getTiltAngle() << "]\n";

	leftCam.setPanAngle(-30);
	leftCam.setTiltAngle(-30);
	cout << "[" << leftCam.getPanAngle()  << "; " << leftCam.getTiltAngle() << "]\n";




	leftCam.closeSerialCom();
}


void demoSerialCom(){
	SerialCom sc;

	try {
		sc.openSerialCom(string("/dev/ttyUSB0"), 9600);

		int i = 50;

		while (i < 100) {
			sc.setValueA(i);
			sc.setValueB(i+1);

			cout << "A: '" << sc.getValueA() << "'  B: '" << sc.getValueB() << "'" << endl;
			i+=2;
		}

		sc.closeSerialCom();
	} catch (string msg) {
		cout << "Error: " << msg << "\n(program terminated)\n";
	} catch (...) {
		cout << "Unknown error \n(program terminated)\n";
	}
}



void demo(){
    int fileDescriptor = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

    struct termios newtio;
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

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
    tcflush(fileDescriptor, TCIFLUSH);
    if (tcsetattr(fileDescriptor, TCSANOW, &newtio)) {
        throw string("could not set the serial settings!");
    }

    int i = 60;
    char buf[64];
    long received;
    long wrote;
    char c[1];
    int idx = 0;

    while(i < 120) {

        string res = std::to_string(i++) + "X";
        wrote = write(fileDescriptor, res.c_str(), sizeof(char)*res.size() );

        cout << "sent: '" << res << "'  -->  ";

        idx = 0;
        buf[idx] = '\0';

        cout << "received: '";
        do{
        	read(fileDescriptor, &c[0], sizeof(char));
        	if(c[0] != 'X'){
        		cout << c[0];
        		buf[idx] = c[0];
        		buf[idx + 1] = '\0';
        		idx++;
        	}else{
        		cout << "'   " <<  buf << "  : " << atoi(buf) << endl;
        		break;
        	}
        }while(1);
    }


    cout << "ready" << endl;

    return;
}


