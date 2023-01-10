CXX=g++
CXXLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 -c
OBJS=main.o ip.o port.o string.o
EXEC=firewall.exe
RM=rm -rf *.o *.exe libfirewall.so

# The first rule is invoked by default
$(EXEC): $(OBJS)
	$(CXXLINK)	$(OBJS) -o firewall.exe -lfirewall -linput -L.

libfirewall.so: ip.o port.o string.o
	$(CXXLINK) -shared ip.o port.o string.o -o libfirewall.so -L.
	
ip.o: ip.cpp ip.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -fpic ip.cpp
	
port.o: port.cpp port.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -fpic port.cpp
	
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -fpic string.cpp
	
main.o: main.cpp string.h port.h ip.h libfirewall.so input.h
	$(CXX) $(CXXFLAGS)  main.cpp

clean:
	$(RM)