INCLDIR=.

CFLAGS= -I$(INCLDIR) -I. -std=c++98  -std=c++0x

LIBS= -lm 

main:	main.o	SerialCom.o
	g++ -o main main.o  SerialCom.o $(LIBS)

main.o:	main.C SerialCom.C SerialCom.H
	g++ -c $(CFLAGS) main.C


SerialCom.o:	SerialCom.C SerialCom.H
	g++ -c $(CFLAGS) SerialCom.C

doc:
	doxygen Doxyfile 

clean:
	rm -r  *.o  main ./DOXYGENDOC

