// Include Header File
#include "UI.h"

UIclass::UIclass() {}

int UIclass::start() {
	cout << "Mars Exploration" << endl << endl;
	Sleep(300);
	cout << "1 - Interactive Mode" << endl;
	cout << "2 - Step-By-Step Mode" << endl;
	cout << "3 - Silent Mode" << endl;
	cout << "Please, select the Program mode (Enter the number of mode) : ";

	int mode;
	cin >> mode;

	cout << endl;

	switch (mode){
	case 1: 
		cout << "Interactive Mode" << endl; 
		break;
	case 2: 
		cout << "Step-By-Step Mode" << endl;
		Sleep(10);
		break;
	case 3: 
		cout << "Silent Mode" << endl; 
		Sleep(500);
		cout << "Simulation Starts";
		for (int i = 0; i < 3; i++)
		{
			Sleep(500);
			cout << ".";
		}
		cout << endl; 
		Sleep(1000);
		cout << "Simulation ends, Output file created" << endl;
		break;
	default: 
		break;
	}

	return mode;
}

void UIclass::InputFile(int& numRovP, int& numRovE, int *& speedRovP, int *& speedRovE, int& numCheckup, int& checkupDurP, int& checkupDurE, LinkedQueue<Formulation*>& Events)
{
	char missionType;
	int ED = 0;
	int Id = 0;
	int TLOC = 0;
	int MDUR = 0;
	int SIG = 0;
	int eventsNum;


	ifstream inputFile("input.txt", ios::in);

	if (inputFile.is_open())
	{
		inputFile >> numRovE >> numRovP;
		for (int i = 0; i < numRovE; i++)
		{
			inputFile >> speedRovE[i];
		}
		
		for (int i = 0; i < numRovP; i++)
		{
			inputFile >> speedRovP[i];
		}

		inputFile >> numCheckup >> checkupDurE >> checkupDurP;
		inputFile >> eventsNum;

		for (int i = 0; i < eventsNum; i++)
		{
			char eventType;
			if (inputFile >> eventType, eventType == 'F')
			{
				Formulation* F = new Formulation ;
				inputFile >> missionType;

				inputFile >> ED >> Id >> TLOC >> MDUR >> SIG;
				F->setMissionType(missionType);
				F->setED(ED);
				F->setID(Id);
				F->setTLOC(TLOC);
				F->setMDUR(MDUR);
				F->setSIG(SIG);
				Events.enqueue(F);
			}
		}
	}
	else {
		cout << "File is not found ...";
	}

	inputFile.close();
}

void UIclass::OutputFile(LinkedQueue<Mission*> CompletedMissions, int RovP, int RovE)
{
	float AvgExec = 0;
	float AvgWait = 0;

	int MissionP = 0;
	int MissionE = 0;

	int Compsize = 0;

	ofstream outputFile("output.txt", ios::out);

	outputFile << "CD" << "\t" << "ID" << "\t" << "FD" << "\t" << "WD" << "\t" << "ED" << endl;

	Mission* M;
	while (CompletedMissions.dequeue(M))
	{
		if (M->getType() == Emergency) MissionE++;
		else MissionP++;

		outputFile << M->getCD() << "\t" << M->getID() << "\t" << M->getFD() << "\t" << M->getWD() << "\t" << M->getED() << endl;
		
		AvgExec += M->getED();
		AvgWait += M->getWD();
		Compsize++;
	}

	if (Compsize > 0)
	{
		AvgExec = AvgExec / Compsize;
		AvgWait = AvgWait / Compsize;
	}
	

	


	outputFile << "..................................." << endl << "..................................." << endl;

	outputFile << "Missions: " << MissionP + MissionE << " [P: " << MissionP << ", E: " << MissionE << "]" << endl;
	outputFile << "Rovers: " << RovP+RovE << " [P: " << RovP << ", E: " << RovE << "]" << endl;
	outputFile << "Avg Wait = " << AvgWait << ", Avg Exec = " << AvgExec << endl;
}
 
 void UIclass::OutputScreen(int Day, LinkedQueue<Mission*> WaitMissionsP, LinkedPriQueue<Mission*> WaitMissionsE, LinkedPriQueue<Mission*> InExMissions, LinkedPriQueue<Rover*> AvailRovP, LinkedPriQueue<Rover*> AvailRovE, LinkedQueue<Rover*> InCheckRovP, LinkedQueue<Rover*> InCheckRovE, LinkedQueue<Mission*> CompletedMissions) {

	Mission* M;
	Rover* R;
	int i = 0;

	cout << endl;
	cout << "Current Day:" << Day << endl;
	
	int sizeWaitE = WaitMissionsE.size();
	int sizeWaitP = WaitMissionsP.size();
	cout << sizeWaitE + sizeWaitP << " Waiting Missions: ";

	i = 0;
	cout << "[";
	while (WaitMissionsE.dequeue(M))
	{
		if (i > 0 && i !=sizeWaitE)
		{
			cout << ", ";
		}
		if (M->getType() == Emergency)
		{
			cout << M->getID();
		}
		i++;
	}
	cout << "] ";
	i = 0;
	cout << "(";
	while (WaitMissionsP.dequeue(M))
	{
		if (i > 0 && i !=sizeWaitP)
		{
			cout << ", ";
		}
		if (M->getType() == Polar)
		{
			cout << M->getID();
		}
		i++;
	}
	cout << ")";

	cout << endl;

	cout << "------------------------------------------------------" << endl;

	int InExSize = InExMissions.size();
	LinkedPriQueue<Mission*> InExMissionsE;
	LinkedPriQueue<Mission*> InExMissionsP;
	while (InExMissions.dequeue(M))
	{
		if (M->getType() == Emergency) InExMissionsE.enqueueAsc(M, M->getCD());
		else if (M->getType() == Polar) InExMissionsP.enqueueAsc(M, M->getCD());
	}
	int InExSizeE = InExMissionsE.size();
	int InExSizeP = InExMissionsP.size();

	cout << InExSize <<" In-Execution Missions/Rovers: ";

	cout << "[";
	for (int i = 0; i < InExSizeE; i++)
	{
		if (InExMissionsE.dequeue(M)) {
			if (i > 0 && i != InExSizeE)
			{
				cout << ", ";
			}
			if (M->getType() == Emergency)
			{
				cout << M->getID() << "/" << M->getRover()->getId();
			}
		}
	}
	cout << "] ";

	cout << "(";
	for (int i = 0; i < InExSizeP; i++)
	{
		if (InExMissionsP.dequeue(M)) {
			if (i > 0 && i != InExSizeP)
			{
				cout << ", ";
			}
			if (M->getType() == Polar)
			{
				cout << M->getID() << "/" << M->getRover()->getId();
			}
		}
	}
	cout << ")";
	

	cout << endl;
	
	cout << "------------------------------------------------------" << endl;
	
	int sizeAvailE = AvailRovE.size();
	int sizeAvailP = AvailRovP.size();
	cout << sizeAvailE + sizeAvailP << " Available Rovers: ";

	cout << "[";
	for (int i = 0; i < sizeAvailE; i++)
	{
		if (AvailRovE.dequeue(R)) {
			if (i > 0 && i != sizeAvailE)
			{
				cout << ", ";
			}
			if (R->getRovertype() == Emergency)
			{
				cout << R->getId();
			}
		}
	}
	cout << "] ";

	cout << "(";
	for (int i = 0; i < sizeAvailP; i++)
	{
		if (AvailRovP.dequeue(R)) {
			if (i > 0 && i != sizeAvailP)
			{
				cout << ", ";
			}
			if (R->getRovertype() == Polar)
			{
				cout << R->getId();
			}
		}
	}
	cout << ")";

	cout << endl;
	
	cout << "------------------------------------------------------" << endl;
	
	int InCheckRovEsize = InCheckRovE.size();
	int InCheckRovPsize = InCheckRovP.size();

	cout << InCheckRovEsize + InCheckRovPsize << " In-Checkup Rovers: ";

	cout << "[";
	for (int i = 0; i < InCheckRovEsize; i++)
	{
		if (InCheckRovE.dequeue(R)) {
			if (i > 0 && i != InCheckRovEsize)
			{
				cout << ", ";
			}
			if (R->getRovertype() == Emergency)
			{
				cout << R->getId();
			}
		}
	}
	cout << "] ";

	cout << "(";
	for (int i = 0; i < InCheckRovPsize; i++)
	{
		if (InCheckRovP.dequeue(R)) {
			if (i > 0 && i != InCheckRovPsize)
			{
				cout << ", ";
			}
			if (R->getRovertype() == Polar)
			{
				cout << R->getId();
			}
		}
	}
	cout << ")";

	cout << endl;
	
	cout << "------------------------------------------------------" << endl;


	int sizeComp = CompletedMissions.size();
	LinkedPriQueue<Mission*> CompE;
	LinkedPriQueue<Mission*> CompP;
	while (CompletedMissions.dequeue(M))
	{
		if (M->getType() == Emergency) CompE.enqueueAsc(M, M->getCD());
		else if (M->getType() == Polar) CompP.enqueueAsc(M, M->getCD());
	}
	int CompEsize = CompE.size();
	int CompPsize = CompP.size();

	cout << sizeComp << " Completed Missions: ";

	cout << "[";
	for (int i = 0; i < CompEsize; i++)
	{
		if (CompE.dequeue(M)) {
			if (i > 0 && i != CompEsize)
			{
				cout << ", ";
			}
			if (M->getType() == Emergency)
			{
				cout << M->getID();
			}
		}
	}
	cout << "] ";

	cout << "(";
	for (int i = 0; i < CompPsize; i++)
	{
		if (CompP.dequeue(M)) {
			if (i > 0 && i != CompPsize)
			{
				cout << ", ";
			}
			if (M->getType() == Polar)
			{
				cout << M->getID();
			}
		}
	}
	cout << ")";


	cout << endl;	
}