#ifndef C_UI
#define C_UI

#include <windows.h>
#include <iostream>
#include <fstream>

#include "event.h"
#include "Formulation.h"
#include "LinkedQueue.h"
#include "LinkedPriQueue.h"

using namespace std;


class UIclass
{
public:
	
public:
	UIclass();
	int start();
	void InputFile(int& numRovP, int& numRovE, int *& speedRovP, int *& speedRovE, int& numCheckup, int& checkupDurP, int& checkupDurE, LinkedQueue<Formulation*>& Events);
	void OutputFile(LinkedQueue<Mission*> CompletedMissions, int RovP, int RovE);
	void OutputScreen(int Day, LinkedQueue<Mission*> WaitMissionsP, LinkedPriQueue<Mission*> WaitMissionsE,LinkedPriQueue<Mission*> InExMissions, LinkedPriQueue<Rover*> AvailRovP, LinkedPriQueue<Rover*> AvailRovE, LinkedQueue<Rover*> InCheckRovP, LinkedQueue<Rover*> InCheckRovE, LinkedQueue<Mission*> CompletedMissions);

};


#endif