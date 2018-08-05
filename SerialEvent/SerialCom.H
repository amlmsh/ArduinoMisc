/*
 * SerialCOm.H
 *
 *  Created on: 04.08.2018
 *      Author: aml
 */

#ifndef SERIALCOM_H_
#define SERIALCOM_H_

#include <string>
using namespace std;


class SerialCom{
public:
	SerialCom();
	void openSerialCom(string dev, const int bps);
	void closeSerialCom();
	int  getValueA();
	int  getValueB();
	void setValueA(int value);
	void setValueB(int value);

private:

	void setValueAandB(int valueA, int valueB);
	void sendIntStr   (int fileDescrp, const char stopChar, int value);
	int  receiveIntStr(int fileDescrp, const char  stopChar);


	int currValueA_ = 0;
	int currValueB_ = 0;

	const char STOPSIGN_  = 'X';

	int fd_ = -1;
};


void demoSerialCom();

#endif /* SERIALCOM_H_ */
