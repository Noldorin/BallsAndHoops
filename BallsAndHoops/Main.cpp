// Driver for NextBall.cpp
//
// This driver does not robustly or exhaustively 
// test all of the required functionality 
// described in the problem statement.
//
// It's pretty simple. But it displays basic functionality in
// a couple different ways, and if you modify the MockData sets
// and throw a few breakpoints around, you should be able to 
// verify the code pretty thoroughly 


#include "NextBall.h"
#include "Objects.h"
#include <iostream>

using namespace std;

// Function headers
vector<NextBall::MapData> InitMockData1();
vector<NextBall::MapData> InitMockData2();


// Test Driver Entry Point
int main()
{
	vector<NextBall::MapData> MapData;

	NextBall myNextBall;
	Player myPlayer;

	myPlayer.xpos = 1;
	myPlayer.ypos = 1;

	int input;

	cout << "Instantiating NextBall class." << endl
		<< "Enter 1 to test for basic init or 2 to test for point grab : ";

	cin >> input;
	cin.ignore();

	if (input == 1)
	{
		MapData = InitMockData1();
	}
	else if (input == 2)
	{
		MapData = InitMockData2();
	}

	myNextBall.Init(MapData);

	cout << endl << "NextBall was successfully initialized. Press enter to trigger Tick()  >";
	cin.ignore();

	while (input != 0)
	{
		myNextBall.Tick(&myPlayer);

		Hoop currentHoop = myPlayer.GetCurrentHoop();
		Ball nextBall = myPlayer.GetNextBall();
		cout << "the ID of the current hoop is " << currentHoop.GetID() << endl
			<< "the player's current score is " << myPlayer.GetScore() << endl;

		if (nextBall.GetID() < 0)
		{
			cout << "There are no balls in the current hoop" << endl
				<< "The player will need to:" << endl
				<< "A) move close to another hoop" << endl
				<< "B) complete this hoop by moving 5 meters in front of it" << endl
				<< "C) if they are already 5 meters in front of it, just wait one more Tick()!" << endl;
		}
		else
		{
			cout << "the ID of the next ball to get is " << nextBall.GetID() << endl;
		}

		cout << endl << "Enter 1 to trigger Tick again, or 0 to exit: ";
		cin >> input;
		cin.ignore();
	}

	return 0;
}

// Helper functions
vector<NextBall::MapData> InitMockData1()
{
	Object tempObj; // used to access the CONST TypeID values
	vector<NextBall::MapData> myMapData;

	#pragma region MockHoops
	NextBall::MapData tempData1;
	NextBall::MapData tempData2;

	tempData1.ID = 10;
	tempData1.TypeID = tempObj.HOOP;
	tempData1.xpos = -1;
	tempData1.ypos = -2;
	tempData1.orientation = 240;

	tempData2.ID = 20;
	tempData2.TypeID = tempObj.HOOP;
	tempData2.xpos = 5;
	tempData2.ypos = 4;
	tempData2.orientation = 180;
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

// Helper functions
vector<NextBall::MapData> InitMockData2()
{
	Object tempObj; // used to access the CONST TypeID values
	vector<NextBall::MapData> myMapData;

#pragma region MockHoops
	NextBall::MapData tempData1;
	NextBall::MapData tempData2;

	tempData1.ID = 10;
	tempData1.TypeID = tempObj.HOOP;
	tempData1.xpos = -1;
	tempData1.ypos = -1;
	tempData1.orientation = 45;

	tempData2.ID = 20;
	tempData2.TypeID = tempObj.HOOP;
	tempData2.xpos = 5;
	tempData2.ypos = 4;
	tempData2.orientation = 180;
#pragma endregion

#pragma region MockBalls
	NextBall::MapData tempData3;
	//NextBall::MapData tempData4;

	tempData3.ID = 1;
	tempData3.TypeID = tempObj.BALL;
	tempData3.color = 1;
	tempData3.xpos = 6;
	tempData3.ypos = 7;

#pragma endregion

#pragma region push_backs
	myMapData.push_back(tempData1);
	myMapData.push_back(tempData2);
	myMapData.push_back(tempData3);
	//myMapData.push_back(tempData4);
#pragma endregion

	return myMapData;
}