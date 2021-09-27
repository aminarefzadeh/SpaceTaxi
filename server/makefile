output:main.o date.o driver.o passenger.o road_system.o taxy_system.o galaxy.o planet.o trip.o server.o server_socket.o tools.o output.o
	g++ -o output main.o date.o driver.o passenger.o road_system.o galaxy.o planet.o server.o taxy_system.o trip.o server_socket.o tools.o output.o
main.o:main.cpp taxy_system.h output.h
	g++ -c main.cpp
taxy_system.o:taxy_system.cpp taxy_system.h date.h driver.h passenger.h road_system.h 
	g++ -c taxy_system.cpp
date.o:date.h date.cpp output.h
	g++ -c date.cpp
driver.o:driver.cpp driver.h date.h
	g++ -c driver.cpp
passenger.o:passenger.cpp passenger.h date.h trip.h output.h
	g++ -c passenger.cpp
road_system.o:road_system.cpp road_system.h galaxy.h
	g++ -c road_system.cpp
galaxy.o:galaxy.cpp galaxy.h planet.h
	g++ -c galaxy.cpp
planet.o:planet.cpp planet.h
	g++ -c planet.cpp
trip.o:trip.cpp trip.h
	g++ -c trip.cpp
server.o: server.cpp server.h
	g++ -c server.cpp
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
output.o:output.cpp output.h
	g++ -c output.cpp
