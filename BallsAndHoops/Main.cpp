// Driver for NextBall.cpp

#include "NextBall.h"
#include "Objects.h"
#include <iostream>

using namespace std;

// Function headers
vector<NextBall::MapData> InitMockData();

int main()
{
	vector<NextBall::MapData> MapData = InitMockData();

	NextBall myNextBall;
	Player myPlayer;

	cout << "Instantiating NextBall class. Press enter to trigger Init() >" << endl;
	cin.ignore();

	myNextBall.Init(MapData);

	cout << "NextBall was successfully initialized. Press enter to trigger Tick() >";
	cin.ignore();

	while (true)
	{
		myNextBall.Tick(&myPlayer);

		Hoop currentHoop = myPlayer.GetCurrentHoop();
		Ball nextBall = myPlayer.GetNextBall();
		cout << "the current hoop is " << currentHoop.GetID() << endl;
		cout << "the next ball to get is " << nextBall.GetID() << endl;

		cout << "Press enter to trigger Tick() again >";
		cin.ignore();	

	} 

	return 0;
}

// Helper functions
vector<NextBall::MapData> InitMockData()
{
	Object tempObj; // used to access the CONST TypeID values
	vector<NextBall::MapData> myMapData;

	#pragma region MockHoops
	NextBall::MapData tempData1;
	NextBall::MapData tempData2;

	tempData1.ID = 10;
	tempData1.TypeID = tempObj.HOOP;
	tempData1.xpos = 9;
	tempData1.ypos = 12;
	tempData1.orientation = 240;

	tempData2.ID = 20;
	tempData2.TypeID = tempObj.HOOP;
	tempData2.xpos = 7;
	tempData2.ypos = 4;
	tempData2.orientation = 179;
	#pragma endregion

	#pragma region MockBalls
	NextBall::MapData tempData3;
	NextBall::MapData tempData4;
	NextBall::MapData tempData5;
	NextBall::MapData tempData6;
	NextBall::MapData tempData7;
	NextBall::MapData tempData8;

	tempData3.ID = 1;
	tempData3.TypeID = tempObj.BALL;
	tempData3.color = 1;
	tempData3.xpos = 11;
	tempData3.ypos = 13;

	tempData4.ID = 2;
	tempData4.TypeID = tempObj.BALL;
	tempData4.color = 3;
	tempData4.xpos = 9;
	tempData4.ypos = 8;

	tempData5.ID = 3;
	tempData5.TypeID = tempObj.BALL;
	tempData5.color = 4;
	tempData5.xpos = 5;
	tempData5.ypos = 4;

	tempData6.ID = 4;
	tempData6.TypeID = tempObj.BALL;
	tempData6.color = 1;
	tempData6.xpos = 1;
	tempData6.ypos = 2;

	tempData7.ID = 5;
	tempData7.TypeID = tempObj.BALL;
	tempData7.color = 6;
	tempData7.xpos = 2;
	tempData7.ypos = 3;

	tempData8.ID = 6;
	tempData8.TypeID = tempObj.BALL;
	tempData8.color = 5;
	tempData8.xpos = 3;
	tempData8.ypos = 3;
	#pragma endregion

	#pragma region push_backs
	myMapData.push_back(tempData1);
	myMapData.push_back(tempData2);
	myMapData.push_back(tempData3);
	myMapData.push_back(tempData4);
	myMapData.push_back(tempData5);
	myMapData.push_back(tempData6);
	myMapData.push_back(tempData7);
	#pragma endregion

	return myMapData;
}