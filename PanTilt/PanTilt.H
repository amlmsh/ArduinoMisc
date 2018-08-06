/*
 * PanTilt.H
 *
 *  Created on: 06.08.2018
 *      Author: aml
 */

#ifndef PANTILT_H_
#define PANTILT_H_


#include "SerialCom.H"

/**
 *
 * namespace
 *
 */
namespace PanTilt{



/**
 *
 *  \class IPanTiltDegree
 *
 * \brief Interface class steering a pan-tilt-system
 * controlled by an arduino  uno or compatiple
 * system.
 *
 * The class allows to set the position of the
 * two servo-motors via communicating with the
 * arduino via serial communication channel.
 *
 * Pan and tilt are two servo motors. Each motor
 * position is represented as integer. The range
 * is -90 to 90 degree.
 *
 */
class IPanTiltDegree{
public:
	/**
	 *
	 * \brief Opens the serial communication
	 * with the arduino device. The data transfer rate
	 * is 9600 bps (baud).
	 *
	 *
	 * \@param string dev specifies the serial communication device
	 *
	 *  \throws string "no com" if serial communication is not available
	 *
	 */
	virtual void   openSerialCom(string dev) = 0;

	/**
	 *
	 * \brief Closes the serial communication with the
	 * arduino board.
	 *
	 */
	virtual void   closeSerialCom() = 0;

	/**
	 *
	 * \brief Delivers the curret servo motor position
	 * of the pan motor.
	 *
	 * \@return int servo-motor position in degree within the range [-90;90]
	 *
	 * \throws string "no com" if serial communication is not available
	 */
	virtual int  getPanAngle() = 0;

	/**
	 *
	 * \brief Delivers the curret servo motor position
	 * of the tilt motor.
	 *
	 * \@return int servo-motor position in degree within the range [-90;90]
	 *
	 * \throws string "no com" if serial communication is not available
	 *
	 */
	virtual int  getTiltAngle() = 0;


	/**
	 *
	 * \brief Sets the target position of servo motor steering the pan motor.
	 *
	 * \@return int servo-motor position in degree within the range [-90;90]
	 *
	 * \throws string "no com" if serial communication is not available
	 * \throws string "out or range" if given value is outside the range [-90;90]
	 *
	 *
	 */
	virtual void setPanAngle(int position) = 0;

	/**
	 *
	 * \brief Sets the target position of servo motor steering the tilt motor.
	 *
	 * \@return int servo-motor position in degree within the range [-90;90]
	 *
	 * \throws string "no com" if serial communication is not available
	 * \throws string "out or range" if given value is outside the range [-90;90]
	 *
	 *
	 */
	virtual void setTiltAngle(int position) = 0;

	virtual void   changePanAngle(int deltaPosition) = 0;
	virtual void   changeTiltAngle(int deltaPosition) = 0;
};


/**
 *
 *  \class PanTiltDegree
 *
 * \brief Implements the interface class IPanTiltDegree
 *
 * This implementation uses the class SerialCom for
 * data exchange between arduino and pc.
 *
 */
class PanTiltDegree : public IPanTiltDegree{
public:
	virtual void   openSerialCom(string dev);
	virtual void   closeSerialCom();
	virtual int    getPanAngle();
	virtual int    getTiltAngle();
	virtual void   setPanAngle(int angle);
	virtual void   setTiltAngle(int angle);
	virtual void   changePanAngle(int deltaAngle);
	virtual void   changeTiltAngle(int deltaAngle);

private:

	int degree2pos(int degreeValue);
	int pos2degree(int positionValue);

	/**
	 *
	 *
	 */
	const int BAUDRATE_ = 9600;

	/**
	 *
	 *
	 */
	SerialCom *sc_ = NULL;
};



/**
 *
 *  \class IPanTiltRadian
 *
 * \brief Interface class steering a pan-tilt-system
 * controlled by an arduino  uno or compatiple
 * system.
 *
 * The class allows to set the position of the
 * two servo-motors via communicating with the
 * arduino via serial communication channel.
 *
 * Pan and tilt are two servo motors. Each motor
 * position is represented as float. The range
 * is -PI/2 to +PI/2 degree.
 *
 */
class IPanTiltRadian{
public:
	/**
	 *
	 * \brief Opens the serial communication
	 * with the arduino device. The data transfer rate
	 * is 9600 bps (baud).
	 *
	 *
	 * \@param string dev specifies the serial communication device
	 *
	 *  \throws string "no com" if serial communication is not available
	 *
	 */
	virtual void   openSerialCom(string dev) = 0;

	/**
	 *
	 * \brief Closes the serial communication with the
	 * arduino board.
	 *
	 */
	virtual void   closeSerialCom() = 0;

	/**
	 *
	 * \brief Delivers the curret servo motor position
	 * of the pan motor.
	 *
	 * \@return int servo-motor position in radian within the range [-PI/2;+PI/2]
	 *
	 * \throws string "no com" if serial communication is not available
	 */
	virtual double  getPanAngle() = 0;

	/**
	 *
	 * \brief Delivers the curret servo motor position
	 * of the tilt motor.
	 *
	 * \@return int servo-motor position in radian within the range [-PI/2;+PI/2]
	 *
	 * \throws string "no com" if serial communication is not available
	 *
	 */
	virtual double  getTiltAngle() = 0;


	/**
	 *
	 * \brief Sets the target position of servo motor steering the pan motor.
	 *
	 * \@return int servo-motor position in radian within the range [-PI/2;+PI/2]
	 *
	 * \throws string "no com" if serial communication is not available
	 * \throws string "out or range" if given value is outside the range [-PI/2;+PI/2]
	 *
	 *
	 */
	virtual void setPanAngle(double position) = 0;

	/**
	 *
	 * \brief Sets the target position of servo motor steering the tilt motor.
	 *
	 * \@return int servo-motor position in radian within the range [-PI/2;+PI/2]
	 *
	 * \throws string "no com" if serial communication is not available
	 * \throws string "out or range" if given value is outside the range [-PI/2;+PI/2]
	 *
	 *
	 */
	virtual void setTiltAngle(double position) = 0;

	virtual void   changePanAngle(double deltaPosition) = 0;
	virtual void   changeTiltAngle(double deltaPosition) = 0;
};


/**
 *
 *  \class PanTiltRadian
 *
 * \brief Implements the interface class IPanTiltRadian
 *
 * This implementation uses the class SerialCom for
 * data exchange between arduino and pc.
 *
 */
class PanTiltRadian : public IPanTiltRadian{
public:
	virtual void   openSerialCom(string dev);
	virtual void   closeSerialCom();
	virtual double getPanAngle();
	virtual double getTiltAngle();
	virtual void   setPanAngle(double angle);
	virtual void   setTiltAngle(double angle);
	virtual void   changePanAngle(double deltaAngle);
	virtual void   changeTiltAngle(double deltaAngle);

private:

	double degree2radian(int degreeValue);
	int   radian2degree(double radianValue);

	/**
	 *
	 *
	 */
	PanTiltDegree *panTiltDegree_ = NULL;
};


}






#endif /* PANTILT_H_ */
