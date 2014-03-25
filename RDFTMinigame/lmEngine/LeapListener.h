#ifndef __LEAPLISTENER__
#define __LEAPLISTENER__

#include <iostream>
#include "C:\Users\Matt\Documents\LeapDeveloperKit\LeapSDK\include\leap.h"
using namespace Leap;

class MyListener : public Listener{
public:
	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
private:

};
void MyListener::onInit(const Controller& controller){
	std::cout << "Initalized" << std::endl;
	//initalized
}
void MyListener::onConnect(const Controller& controller){
	std::cout << "Conencted" << std::endl;
	//connected
}
void MyListener::onDisconnect(const Controller& controller){
	std::cout << "Disconnected" << std::endl;
	//disconnected
}
void MyListener::onExit(const Controller& controller){
	std::cout << "Exited" << std::endl;
	//exited
}
void MyListener::onFrame(const Controller& controller){
	const Frame frame = controller.frame();
	if (!frame.hands().isEmpty()){
		const Hand hand = frame.hands()[0];
		const FingerList fingers = hand.fingers();
		if (!fingers.isEmpty()){
			Vector avgPos;
			for (int i = 0; i < fingers.count(); ++i){
				avgPos += fingers[i].tipPosition();
			}
			avgPos /= (float)fingers.count();
			std::cout << avgPos << std::endl;
		}
	}
}
void MyListener::onFocusGained(const Controller& controller){
	//focus gained
}
void MyListener::onFocusLost(const Controller& controller){
	//focus lost
}
int main(){
	MyListener listener;
	Controller controller;
	controller.addListener(listener);
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();
	controller.removeListener(listener);
	return 0;
}

#endif