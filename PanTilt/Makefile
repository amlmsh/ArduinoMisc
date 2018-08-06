INCLDIR=.

CFLAGS= -I$(INCLDIR) -I. -std=c++98  -std=c++0x

LIBS= -lm 

main:	main.o	SerialCom.o PanTilt.o UnitTest.o Demos.o
	g++ -o main main.o  SerialCom.o PanTilt.o  Demos.o $(LIBS)
	
mainTest:	mainTest.o SerialCom.o	PanTilt.o UnitTest.o PanTiltTest.o
	g++ -o mainTest mainTest.o SerialCom.o	PanTilt.o UnitTest.o PanTiltTest.o $(LIBS)

	
main.o:	main.C 
	g++ -c $(CFLAGS) main.C
	
mainTest.o:	mainTest.C
	g++ -c $(CFLAGS) mainTest.C

Demos.o:	Demos.C Demos.H
	g++ -c $(CFLAGS) Demos.C

SerialCom.o:	SerialCom.C SerialCom.H
	g++ -c $(CFLAGS) SerialCom.C

PanTilt.o:	PanTilt.C PanTilt.H
	g++ -c $(CFLAGS) PanTilt.C

PanTiltTest.o:	PanTiltTest.C PanTiltTest.H
	g++ -c $(CFLAGS) PanTiltTest.C

UnitTest.o:	UnitTest.H UnitTest.C
	g++ -c $(CFLAGS) UnitTest.C

doc:
	doxygen Doxyfile 

clean:
	rm -r  *.o  *.xml main mainTest ./DOXYGENDOC
	
