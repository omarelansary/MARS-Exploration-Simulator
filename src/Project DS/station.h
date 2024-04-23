#ifndef station_H
#define station_H

// Include all paths of project
#include "Mission.h"
#include "Rover.h"
#include "event.h"
#include "Formulation.h"

// Include D.S.
#include "LinkedQueue.h"
#include "LinkedPriQueue.h"

// Include Input and Output Class
#include "UI.h"

// To Use function Sleep(milliseconds);
#include <windows.h>

// To generate random number
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

class station
{

private:
	// the num of the Day since the station start to Exceute Missions and Rovers 
	int Day;
	int RoverNumPolar;

	// All queues that we need.
	LinkedQueue<Mission*> WaitMissionsP;
	LinkedPriQueue<Mission*> WaitMissionsE;

	LinkedPriQueue<Mission*> InExMissions;

	LinkedPriQueue<Rover*> AvailRovP;
	LinkedPriQueue<Rover*> AvailRovE;

	LinkedQueue<Rover*> InCheckRovP;
	LinkedQueue<Rover*> InCheckRovE;


	LinkedQueue<Mission*> CompletedMissions;

	LinkedPriQueue<Rover*> InExRov;

	// Events (Formulation Only)
	LinkedQueue<Formulation*> Events;

	// Class of Input and Output
	UIclass UI;

public:
	station();

	// Load input file and extract information from it
	void Load();

	// Save output file and Show information on Screen
	void Save();

	// Execute the mission and rovers 
	void Execute();

	// Control the station 
	void Control();
};

#endif