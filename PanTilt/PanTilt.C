/*
 * PanTilt.C
 *
 *  Created on: 06.08.2018
 *      Author: aml
 */

#include "PanTilt.H"

#include <string>
#include <iostream>

using namespace std;

namespace PanTilt{

void   PanTiltDegree::openSerialCom(string dev){

	if(sc_ != NULL){
		sc_->closeSerialCom();
		delete sc_;
		sc_ = NULL;
	}

	try{
		sc_ = new SerialCom();
	}catch(string msg){
		sc_ = NULL;
		throw (string("Error while creating serialCom-object (PanTiltDegree::openSerial()):") + msg);
	}catch(...){
		sc_ = NULL;
		throw (string("Unknown error while creating serialCom-object (PanTiltDegree::openSerial())"));
	}


	try{
		sc_->openSerialCom(dev, 9600);
	}catch(string msg){
		delete sc_;
		sc_ = NULL;
		throw (string("Error while open serial com chanel (PanTiltDegree::openSerial())") + msg);
	}catch(...){
		delete sc_;
		sc_ = NULL;
		throw (string("Unknown error while open serial com chanel (PanTiltDegree::openSerial())"));
	}

}

void   PanTiltDegree::closeSerialCom(){
	if(sc_ != NULL){
		sc_->closeSerialCom();
		delete sc_;
		sc_ = NULL;
	}
}

/**
 *
 * Calculates for a given pan-tilt angle the
 * corresponding sorvomotor position.
 *
 */
int PanTiltDegree::degree2pos(int degreeValue){
	return (-degreeValue + 90);
}

/**
 *
 * Calculates for a given servomotor position  the
 * corresponding pan-tilt angle.
 *
 */
int PanTiltDegree::pos2degree(int positionValue){
	return (-positionValue + 90);
}

int    PanTiltDegree::getPanAngle(){
	int position;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::getPanAngle())"));
	}

	try{
		position = sc_->getValueA();
		return (this->pos2degree(position));
	}catch(string msg){
		throw (string("Error while reading (PanTiltDegree::getPanAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while reading (PanTiltDegree::getPanAngle())"));
	}
}

int    PanTiltDegree::getTiltAngle(){
	int position;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::getTiltAngle())"));
	}

	try{
		position = sc_->getValueB();
		return (this->pos2degree(position));
	}catch(string msg){
		throw (string("Error while reading (PanTiltDegree::getTiltAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while reading (PanTiltDegree::getTiltAngle())"));
	}
}

void   PanTiltDegree::setPanAngle(int angle){
	int targetAngle;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::setPanAngle())"));
	}

	if(angle < -90 ){
		targetAngle = -90;
	}else if (angle > 90){
		targetAngle = 90;
	}else{
		targetAngle = angle;
	}

	try{
		sc_->setValueA(this->degree2pos(targetAngle));
		return;
	}catch(string msg){
		throw (string("Error while sending (PanTiltDegree::setPanAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while sending (PanTiltDegree::setPanAngle())"));
	}
}

void   PanTiltDegree::setTiltAngle(int angle){
	int targetAngle;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::setTiltAngle())"));
	}

	if(angle < -90 ){
		targetAngle = -90;
	}else if (angle > 90){
		targetAngle = 90;
	}else{
		targetAngle = angle;
	}

	try{
		sc_->setValueB(this->degree2pos(targetAngle));
		return;
	}catch(string msg){
		throw (string("Error while sending (PanTiltDegree::setTiltAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while sending (PanTiltDegree::setTiltAngle())"));
	}
}

void   PanTiltDegree::changePanAngle(int deltaAngle){
	int panAngle;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::changePanAngle())"));
	}

	try{
		panAngle = this->getPanAngle();
		panAngle += deltaAngle;
		if(panAngle < -90 ){
			panAngle = -90;
		}else if (panAngle > 90){
			panAngle = 90;
		}else{
			panAngle = panAngle;
		}

		sc_->setValueA(this->degree2pos(panAngle));
	}catch(string msg){
		throw (string("Error while sending (PanTiltDegree::changePanAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while sending (PanTiltDegree::changePanAngle())"));
	}
}

void   PanTiltDegree::changeTiltAngle(int deltaAngle){
	int tiltAngle;
	if(sc_ == NULL){
		throw (string("Com-object is NULL pointer(PanTiltDegree::changeTiltAngle())"));
	}

	try{
		tiltAngle = this->getTiltAngle();
		tiltAngle += deltaAngle;
		if(tiltAngle < -90 ){
			tiltAngle = -90;
		}else if (tiltAngle > 90){
			tiltAngle = 90;
		}else{
			tiltAngle = tiltAngle;
		}
		sc_->setValueB(this->degree2pos(tiltAngle));
	}catch(string msg){
		throw (string("Error while sending (PanTiltDegree::changeTiltAngle()):") + msg);
	}
	catch(...){
		throw (string("Unknown error while sending (PanTiltDegree::changeTiltAngle())"));
	}
}



void   PanTiltRadian::openSerialCom(string dev){

	if(panTiltDegree_ != NULL){
		panTiltDegree_->closeSerialCom();
		delete panTiltDegree_;
		panTiltDegree_ = NULL;
	}

	try{
		panTiltDegree_ = new  PanTiltDegree();
		panTiltDegree_->openSerialCom(dev);
	}catch(string msg){
		panTiltDegree_ = NULL;
		throw (string("Error while creating serialCom-object (PanTiltRadian::openSerial()):") + msg);
	}catch(...){
		panTiltDegree_ = NULL;
		throw (string("Unknown error while creating serialCom-object (PanTiltRadian::openSerial())"));
	}
}

void   PanTiltRadian::closeSerialCom(){
	if(panTiltDegree_ != NULL){
		panTiltDegree_->closeSerialCom();
		delete panTiltDegree_;
		panTiltDegree_ = NULL;
	}
}

double  PanTiltRadian::getPanAngle(){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}
	try{
		return this->degree2radian((panTiltDegree_->getPanAngle()));
	}catch(string msg){
		throw (string("Unknown error while reading (PanTiltRadian::getPanAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while reading (PanTiltRadian::getPanAngle())"));
	}
}

double  PanTiltRadian::getTiltAngle(){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}

	try{
		return this->degree2radian((panTiltDegree_->getTiltAngle()));
	}catch(string msg){
		throw (string("Unknown error while reading (PanTiltRadian::getTiltAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while reading (PanTiltRadian::getTiltAngle())"));
	}
}

void   PanTiltRadian::setPanAngle(double angle){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}

	try{
		panTiltDegree_->setPanAngle(this->radian2degree(angle));
		return ;
	}catch(string msg){
		throw (string("Unknown error while sending (PanTiltRadian::setPanAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while sending (PanTiltRadian::setPanAngle())"));
	}
}

void   PanTiltRadian::setTiltAngle(double angle){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}

	try{
		panTiltDegree_->setTiltAngle(this->radian2degree(angle));
		return ;
	}catch(string msg){
		throw (string("Unknown error while sending (PanTiltRadian::setTiltAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while sending (PanTiltRadian::setTiltAngle())"));
	}
}

void   PanTiltRadian::changePanAngle(double deltaAngle){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}

	try{
		panTiltDegree_->changePanAngle(this->radian2degree(deltaAngle));
		return ;
	}catch(string msg){
		throw (string("Unknown error while sending (PanTiltRadian::changePanAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while sending (PanTiltRadian::changePanAngle())"));
	}

}

void   PanTiltRadian::changeTiltAngle(double deltaAngle){
	if(panTiltDegree_ == NULL){
		throw (string("PanTiltDegree-object is NULL pointer(PanTiltRadian::setTiltAngle())"));
	}

	try{
		panTiltDegree_->changeTiltAngle(this->radian2degree(deltaAngle));
		return ;
	}catch(string msg){
		throw (string("Unknown error while sending (PanTiltRadian::changeTiltAngle()):") + msg);
	}catch(...){
		throw (string("Unknown error while sending (PanTiltRadian::changeTiltAngle())"));
	}
}

double PanTiltRadian::degree2radian(int degreeValue){
	return ( (((double) degreeValue)*3.14159)/180.0);
}

int   PanTiltRadian::radian2degree(double radianValue){
	double degree = ((180.0*radianValue)/3.14159)+0.5;
	return degree;
}


} // end namespace PanTilt




