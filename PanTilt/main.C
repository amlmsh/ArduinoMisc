#include "SerialCom.H"
#include "PanTilt.H"
#include "Demos.H"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	try {
		//demo();
		//demoSerialCom();
		//demoPanTilt();
		//exit(0);
	} catch (string msg) {
		cout << "error " << msg << endl;
		exit(0);
	}

	PanTilt::PanTiltDegree leftCam;
	PanTilt::PanTiltDegree rigtCam;
	PanTilt::PanTiltDegree laser;

	try {
		leftCam.openSerialCom("/dev/ttyACM0");
		cout << "set position: ";
		if (argc == 2) {
			int pos = atoi(argv[1]);
			cout << pos << endl;
			leftCam.setPanAngle(pos);
		} else {
			cout << "default value 90" << endl;
			leftCam.setPanAngle(90);
		}
		leftCam.closeSerialCom();
	} catch (string msg) {
		cout << "Error, terminate: " << msg << endl;
	} catch (...) {
		cout << "Unknown error, terminate.";
	}

	return 0;
}
;

