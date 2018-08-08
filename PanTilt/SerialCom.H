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

	/*
	 * return value is undefined until the
	 * method setValueA is successfully executed.
	 */
	int  getValueA();

	/*
	 * return value is undefined until the
	 * method setValueB is successfully executed.
	 */
	int  getValueB();
	void setValueA(int value);
	void setValueB(int value);

private:

	void sendIntStr   (int fileDescrp, const char stopChar, int value);
	int  receiveIntStr(int fileDescrp, const char  stopChar);

	int currValueA_ = 0;
	int currValueB_ = 0;

	const char STOPSIGNPAN_  = 'P';
	const char STOPSIGNTILT_  = 'T';

	int fd_ = -1;
};



#endif /* SERIALCOM_H_ */
