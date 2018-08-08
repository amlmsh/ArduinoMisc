/*
 * PanTiltTest.C
 *
 *  Created on: 06.08.2018
 *      Author: aml
 */

#include <iostream>
#include <cmath>

#include "PanTiltTest.H"
#include "UnitTest.H"
#include "PanTilt.H"

using namespace std;
using namespace UnitTest;

#define PI 3.14159

string COMDEV=string("/dev/ttyUSB0");

namespace IPanTiltDegreeTest{

class TC0 : public TestCase{
	TC0() : TestCase(){};
public:
	TC0(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pt.openSerialCom(COMDEV);
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC1 : public TestCase{
	TC1() : TestCase(){};
public:
	TC1(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltDegree pt;
			pt.closeSerialCom();
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};



class TC2 : public TestCase{
	TC2() : TestCase(){};
public:
	TC2(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltDegree pt;
			pt.getPanAngle();
			return false;
		}catch(string msg){
			return true;
		}catch(...){
			return false;
		}
	}
};

class TC3 : public TestCase{
	TC3() : TestCase(){};
public:
	TC3(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pt.closeSerialCom();
			pt.getPanAngle();
			return false;
		}catch(string msg){
			return true;
		}catch(...){
			return false;
		}
	}
};


class TC4 : public TestCase{
	TC4() : TestCase(){};
public:
	TC4(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pt.getPanAngle();
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};



class TC5 : public TestCase{
	TC5() : TestCase(){};
public:
	TC5(string s) : TestCase(s){};
	virtual bool testRun(){
		int pan, tilt;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pan = pt.getPanAngle();
			tilt = pt.getTiltAngle();
			if((pan <= 90) && (pan >= -90) && (tilt <= 90) && (tilt >= -90)){
				return true;
			}else{
				return false;
			}

		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC6 : public TestCase{
	TC6() : TestCase(){};
public:
	TC6(string s) : TestCase(s){};
	virtual bool testRun(){
		int pan = 10;
		int tilt = -10;
		int currPan, currTilt;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pt.setPanAngle(pan);
			pt.setTiltAngle(tilt);
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((pan == currPan) && (tilt == currTilt)){
				return true;
			}else{
				return false;
			}
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC7 : public TestCase{
	TC7() : TestCase(){};
public:
	TC7(string s) : TestCase(s){};
	virtual bool testRun(){
		int currPan, currTilt;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pt.setPanAngle(91);
			pt.setTiltAngle(91);
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((currPan <= 90) && (currTilt <= 90)){
				return true;
			}else{
				return false;
			}

			pt.setPanAngle(-91);
			pt.setTiltAngle(-91);
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((currPan >= -90) && (currTilt >= -90)){
				return true;
			}else{
				return false;
			}

		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};




class TC8 : public TestCase{
	TC8() : TestCase(){};
public:
	TC8(string s) : TestCase(s){};
	virtual bool testRun(){
		int currPan, currTilt, tilt;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			currPan = pt.getPanAngle();
			tilt = pt.getTiltAngle();

			for(int i=-35; i < 89; i++){
				pt.setPanAngle(i);
				currPan = pt.getPanAngle();
				currTilt = pt.getTiltAngle();

				if((currPan != i) || (currTilt != tilt)){
					return false;
				}
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC9 : public TestCase{
	TC9() : TestCase(){};
public:
	TC9(string s) : TestCase(s){};
	virtual bool testRun(){
		int currPan, currTilt, pan;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			currTilt = pt.getTiltAngle();
			pan = pt.getPanAngle();

			for(int i=-35; i < 89; i++){
				pt.setTiltAngle(i);
				currPan = pt.getPanAngle();
				currTilt = pt.getTiltAngle();

				if((currTilt != i) || (currPan != pan)){
					return false;
				}
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC10 : public TestCase{
	TC10() : TestCase(){};
public:
	TC10(string s) : TestCase(s){};
	virtual bool testRun(){
		int currPan, pan;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			pan = 3;
			pt.setPanAngle(pan);

			for(int i=-5; i < 5; i++){
				pt.changePanAngle(i);
				currPan = pt.getPanAngle();
				if(currPan != (pan + i)){
					return false;
				}
				pan = currPan;
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC11 : public TestCase{
	TC11() : TestCase(){};
public:
	TC11(string s) : TestCase(s){};
	virtual bool testRun(){
		int currTilt, tilt;
		try{
			PanTilt::PanTiltDegree pt;
			pt.openSerialCom(COMDEV);
			tilt = -3;
			pt.setTiltAngle(tilt);

			for(int i=-5; i < 5; i++){
				pt.changeTiltAngle(i);
				currTilt = pt.getTiltAngle();
				if(currTilt != (tilt + i)){
					return false;
				}
				tilt = currTilt;
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


} // end namespace IPanTiltDegreeTest



namespace IPanTiltRadianTest{

class TC0 : public TestCase{
	TC0() : TestCase(){};
public:
	TC0(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pt.openSerialCom(COMDEV);
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC1 : public TestCase{
	TC1() : TestCase(){};
public:
	TC1(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltRadian pt;
			pt.closeSerialCom();
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};



class TC2 : public TestCase{
	TC2() : TestCase(){};
public:
	TC2(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltRadian pt;
			pt.getPanAngle();
			return false;
		}catch(string msg){
			return true;
		}catch(...){
			return false;
		}
	}
};

class TC3 : public TestCase{
	TC3() : TestCase(){};
public:
	TC3(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pt.closeSerialCom();
			pt.getPanAngle();
			return false;
		}catch(string msg){
			return true;
		}catch(...){
			return false;
		}
	}
};


class TC4 : public TestCase{
	TC4() : TestCase(){};
public:
	TC4(string s) : TestCase(s){};
	virtual bool testRun(){
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pt.getPanAngle();
			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};



class TC5 : public TestCase{
	TC5() : TestCase(){};
public:
	TC5(string s) : TestCase(s){};
	virtual bool testRun(){
		float delta = 0.0001;
		float pan, tilt;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pan = pt.getPanAngle();
			tilt = pt.getTiltAngle();

			if(((PI/2) - delta) <= fabs(pan) <= ((PI/2) + delta) &&
					((PI/2) - delta) <= fabs(tilt) <= ((PI/2) + delta) ){
				return true;
			}else{
				return false;
			}

		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC6 : public TestCase{
	TC6() : TestCase(){};
public:
	TC6(string s) : TestCase(s){};
	virtual bool testRun(){
		float delta = 0.03;
		float pan = 0.2;
		float tilt = -0.4;
		float currPan, currTilt;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pt.setPanAngle(pan);
			pt.setTiltAngle(tilt);
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((fabs(pan - currPan) <= delta) && (fabs(tilt - currTilt) <= delta)){
				return true;
			}else{
				return false;
			}
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC7 : public TestCase{
	TC7() : TestCase(){};
public:
	TC7(string s) : TestCase(s){};
	virtual bool testRun(){
		float delta = 0.0001;
		float currPan, currTilt;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pt.setPanAngle(PI/2 + 0.1);
			pt.setTiltAngle(PI/2 + 0.1);
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((currPan <= ((PI/2) + delta)) && (currTilt <= ((PI/2) + delta))){
				return true;
			}else{
				return false;
			}

			pt.setPanAngle(-(PI/2 + 0.1));
			pt.setTiltAngle(-(PI/2 + 0.1));
			currPan = pt.getPanAngle();
			currTilt = pt.getTiltAngle();
			if((currPan >= ((-PI/2) - delta)) && (currTilt >= ((-PI/2) - delta))){
				return true;
			}else{
				return false;
			}

		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};




class TC8 : public TestCase{
	TC8() : TestCase(){};
public:
	TC8(string s) : TestCase(s){};
	virtual bool testRun(){
		double delta = 0.03;
		double currPan, currTilt, tilt;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			currPan = pt.getPanAngle();
			tilt = pt.getTiltAngle();

			for(double i=-(PI/2); i < (PI/2); i=i+0.1){
				pt.setPanAngle(i);
				currPan = pt.getPanAngle();
				currTilt = pt.getTiltAngle();

				if(  (fabs(currPan - i) > delta) || (fabs(currTilt - tilt) > delta) ){
					return false;
				}
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC9 : public TestCase{
	TC9() : TestCase(){};
public:
	TC9(string s) : TestCase(s){};
	virtual bool testRun(){
		double delta = 0.03;
		double currPan, currTilt, pan;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			currTilt = pt.getTiltAngle();
			pan = pt.getPanAngle();

			for(double i=-(PI/2); i < (PI/2); i=i+0.1){
				pt.setTiltAngle(i);
				currPan = pt.getPanAngle();
				currTilt = pt.getTiltAngle();

				if(  (fabs(currTilt - i) > delta) || (fabs(currPan - pan) > delta) ){
					return false;
				}
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC10 : public TestCase{
	TC10() : TestCase(){};
public:
	TC10(string s) : TestCase(s){};
	virtual bool testRun(){
		double delta = 0.03;
		double currPan, pan;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			pan = 0.3;
			pt.setPanAngle(pan);

			for(double i=-0.5; i < 0.5; i=i+0.1){
				pt.changePanAngle(i);
				currPan = pt.getPanAngle();
				if(fabs(currPan - (pan + i)) > delta) {
					return false;
				}
				pan = currPan;
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


class TC11 : public TestCase{
	TC11() : TestCase(){};
public:
	TC11(string s) : TestCase(s){};
	virtual bool testRun(){
		double delta = 0.04;
		double currTilt, tilt;
		try{
			PanTilt::PanTiltRadian pt;
			pt.openSerialCom(COMDEV);
			tilt = -0.3;
			pt.setTiltAngle(tilt);

			for(double i=-0.1; i < 0.1; i=i+0.1){
				pt.changeTiltAngle(i);
				currTilt = pt.getTiltAngle();
				if(fabs(currTilt - (tilt + i)) > delta) {
					return false;
				}
				tilt = currTilt;
			}

			return true;
		}catch(string msg){
			return false;
		}catch(...){
			return false;
		}
	}
};


} // end namespace IPanTiltRadianTest




void testPanTiltDegreeTest(){
	using namespace IPanTiltDegreeTest;

	/**
	 * Test cases
	 *
	 */
	TC0 tc0("DoubleOpen");
	TC1 tc1("closeWithoutOpen");
	TC2 tc2("readingWithoutOpen");
	TC3 tc3("readingWithClosedChannel");
	TC4 tc4("readingWithOpenChannel");

	TC5 tc5("readAndTestRange");
	TC6 tc6("readAndWrite");
	TC7 tc7("keepThe90Range");

	TC8 tc8("readPanOnly");
	TC9 tc9("readTiltOnly");

	TC10 tc10("relativeChangesPan");
	TC11 tc11("relativeChangesTilt");

	/**
	 *
	 * Test Suites
	 *
	 */
	UnitTest::TestSuite tsOpenClose("OpenCloseSerial");
	tsOpenClose.addTestItem(&tc0);
	tsOpenClose.addTestItem(&tc1);
	tsOpenClose.addTestItem(&tc2);
	tsOpenClose.addTestItem(&tc3);
	tsOpenClose.addTestItem(&tc4);

	UnitTest::TestSuite tsGetAngle("GetAngle");
	tsGetAngle.addTestItem(&tc5);
	tsGetAngle.addTestItem(&tc6);
	tsGetAngle.addTestItem(&tc7);

	UnitTest::TestSuite tsSetAngle("SetAngle");
	tsSetAngle.addTestItem(&tc8);
	tsSetAngle.addTestItem(&tc9);

	UnitTest::TestSuite tsChangeAngle("ChangeAngle");
	tsChangeAngle.addTestItem(&tc10);
	tsChangeAngle.addTestItem(&tc11);


	/**
	 *
	 * unit test
	 *
	 */
	UnitTest::UnitTest unit("PanTilt::PanTiltDegree");
	unit.addTestItem(&tsOpenClose);
	unit.addTestItem(&tsGetAngle);
	unit.addTestItem(&tsSetAngle);
	unit.addTestItem(&tsChangeAngle);

	unit.testExecution();
	unit.writeResultsToFile("penTiltDegreeTestResults.xml");

}

void testPanTiltRadianTest(){
	using namespace IPanTiltRadianTest;

	/**
	 * Test cases
	 *
	 */
	TC0 tc0("DoubleOpen");
	TC1 tc1("closeWithoutOpen");
	TC2 tc2("readingWithoutOpen");
	TC3 tc3("readingWithClosedChannel");
	TC4 tc4("readingWithOpenChannel");

	TC5 tc5("readAndTestRange");
	TC6 tc6("readAndWrite");
	TC7 tc7("keepThe90Range");

	TC8 tc8("readPanOnly");
	TC9 tc9("readTiltOnly");

	TC10 tc10("relativeChangesPan");
	TC11 tc11("relativeChangesTilt");

	/**
	 *
	 * Test Suites
	 *
	 */
	UnitTest::TestSuite tsOpenClose("OpenCloseSerial");
	tsOpenClose.addTestItem(&tc0);
	tsOpenClose.addTestItem(&tc1);
	tsOpenClose.addTestItem(&tc2);
	tsOpenClose.addTestItem(&tc3);
	tsOpenClose.addTestItem(&tc4);

	UnitTest::TestSuite tsGetAngle("GetAngle");
	tsGetAngle.addTestItem(&tc5);
	tsGetAngle.addTestItem(&tc6);
	tsGetAngle.addTestItem(&tc7);

	UnitTest::TestSuite tsSetAngle("SetAngle");
	tsSetAngle.addTestItem(&tc8);
	tsSetAngle.addTestItem(&tc9);

	UnitTest::TestSuite tsChangeAngle("ChangeAngle");
	tsChangeAngle.addTestItem(&tc10);
	tsChangeAngle.addTestItem(&tc11);


	/**
	 *
	 * unit test
	 *
	 */
	UnitTest::UnitTest unit("PanTilt::PanTiltRadian");
	unit.addTestItem(&tsOpenClose);
	unit.addTestItem(&tsGetAngle);
	unit.addTestItem(&tsSetAngle);
	unit.addTestItem(&tsChangeAngle);

	unit.testExecution();
	unit.writeResultsToFile("penTiltRadianTestResults.xml");

}

