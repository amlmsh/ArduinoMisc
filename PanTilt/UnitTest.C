/*
 * UnitTest.C
 *
 *  Created on: 06.08.2018
 *      Author: aml
 */

#include "UnitTest.H"

#include <iostream>

using namespace std;

namespace UnitTest{


TestItem::TestItem(string s ){
	name_ = s;
	result_ = false;
};

string TestItem::getName(){
	return name_;
};

bool TestItem::getResult(){
	return result_;
};

void TestItem::addTestItem(ITestItem *item) {
	throw "TestItem cannot add TestItem\n";
};



TestCase::TestCase(string s) : TestItem(s){

};

void TestCase::testExecution(){
	result_ = testRun();
	cout << ".";
	cout.flush();
}



string TestCase::toXmlStr(){
	string s("");
	s += "<TestCase name=\"" + getName() + "\">";
	if(result_){
		s += "PASSED";
	}else{
		s += "FAILED";
	};
	s += "</TestCase>";

	return s;
}



TestSuite::TestSuite(string s) : TestItem(s){

};

void TestSuite::testExecution(){
	result_ = true;
	TestItem *ptrTC;
	List::Queue<TestItem*> tmpTC;
	while(!testItems_.isEmpty()){
		ptrTC = testItems_.dequeue();
		ptrTC->testExecution();
		result_ = result_ && ptrTC->getResult();
		tmpTC.enqueue(ptrTC);
	}

	while(!tmpTC.isEmpty()){
		ptrTC = tmpTC.dequeue();
		testItems_.enqueue(ptrTC);
	}
};

string TestSuite::toXmlStr(){
	string s("");
	s += "<" + this->testType_ + " name=\"" + this->name_   + "\" status=\"";
	if(getResult()){
		s += "PASSED\">";
	}else{
		s += "FAILED\">";
	}

	TestItem *ptrTC;
	List::Queue<TestItem*> tmpTC;
	while(!testItems_.isEmpty()){
		ptrTC = testItems_.dequeue();
		s += ptrTC->toXmlStr();
		tmpTC.enqueue(ptrTC);
	}

	while(!tmpTC.isEmpty()){
		ptrTC = tmpTC.dequeue();
		testItems_.enqueue(ptrTC);
	}

	s += "</" + testType_ + ">";

	return s;
}

void TestSuite::addTestItem(TestItem *tc) {
	testItems_.enqueue(tc);
};



UnitTest::UnitTest(string s) : TestSuite(s){
	testType_ = "UnitTest";
};

void UnitTest::writeResultsToFile(string fileName){
	std::ofstream file(fileName);
	file <<  toXmlStr();
	file.close();
	return;
}




} // namespace UnitTest


