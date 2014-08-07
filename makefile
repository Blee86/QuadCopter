
QuadCopter: main.o vn100.o vncp_services.o vndevice.o fan.o serialDevice.o pololuMaestroMotorController.o PID_Yo.o FanControl.o
	g++ -std=c++0x -o QuadCopter main.o vn100.o vndevice.o vncp_services.o fan.o serialDevice.o pololuMaestroMotorController.o PID_Yo.o FanControl.o -lrt -lpthread
	mkdir obj
	mv *.o ./obj

main.o: main.cpp
	g++ -std=c++0x -c -Wall -I./include main.cpp

vn100.o: ./src/vn100.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/vn100.cpp

vndevice.o: ./src/vndevice.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/vndevice.cpp

vncp_services.o: ./src/arch/linux/vncp_services.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/arch/linux/vncp_services.cpp
	
fan.o: ./src/fan.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/fan.cpp 

serialDevice.o: ./src/serialDevice.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/serialDevice.cpp 
	
pololuMaestroMotorController.o: ./src/pololuMaestroMotorController.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/pololuMaestroMotorController.cpp 
	
PID_Yo.o: ./src/PID_Yo.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/PID_Yo.cpp

FanControl.o: ./src/FanControl.cpp
	g++ -std=c++0x -c -Wall -I./include ./src/FanControl.cpp
clean:
	rm -f -r ./obj QuadCopter
