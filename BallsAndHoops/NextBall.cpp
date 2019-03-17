// BallsAndHoops.cpp 
//
// This program uses the current game state to calculate the next ball the 
// player needs to collect.
//
// ASSUMPTION: The player alway starts at the origin, (0,0) which is the bottom
// left most location on the map
#include "Objects.h"
#include "NextBall.h"

using namespace std;


// Helper Methods
// Gets the distance between two game objects
float NextBall::GetDistance(unsigned int x1, unsigned int y1,
	unsigned int x2, unsigned int y2)
{
	int temp_x = (x1 - x2);
	int temp_y = (y1 - y2);

	float distance = sqrt((double)temp_x * temp_x + temp_y * temp_y);
	return distance;
}

// default constructor
NextBall::NextBall()
{
	// The player starts every level at (0,0)
	prevX = 0;
	prevY = 0;
}

// default destructor
NextBall::~NextBall()
{
}

// Implementation of Tick, as defined in NextBall.h
//
// ASSUMES Init() has been called
void NextBall::Tick(Player *myPlayer)
{
	// Get the ID's of the Hoop and NextBall the player had
	// at the end of the last tick
	//
	// If this is the first tick of the game, both will be -1
	previousHoop = myPlayer->GetCurrentHoop();
	prevNextBall = myPlayer->GetNextBall();

	// If the player has moved, or if it's the very first tick
	// Calculate the hoop that the player is closest too
	if (prevX != myPlayer->GetXPos() || prevY != myPlayer->GetYPos() || previousHoop.GetID() == -1)
	{
		float tempDistance;
		int smallestD = INT16_MAX;
		int tempIndex = 0;

		for (int i = 0; i < Hoops.size(); i++)
		{
			tempDistance = GetDistance(myPlayer->GetXPos(), myPlayer->GetYPos(),
				Hoops[i].GetXPos(), Hoops[i].GetYPos());

			// NOTE: If the player is equidistant from multiple hoops, it will
			// stick with whichever hoop it was most recently closer to
			//
			// i.e. if it was 6m away from HoopA and 8m away from HoopB,
			// and then moved 1m such that it was 7m away from both A and B,
			// It's "CurrentHoop" would remain A.
			if (tempDistance < smallestD)
			{
				smallestD = tempDistance;
				tempIndex = i;
			}
		}
		// Save the new CurrentHoop, might be unchanged
		myPlayer->SetCurrentHoop(Hoops[tempIndex]);

		// Update stored location
		prevX = myPlayer->GetXPos();
		prevY = myPlayer->GetYPos();
	}
	// WE NOW HAVE AN ACCURATE CURRENT HOOP

	// If the current Hoops ball-list is empty check if the 
	// player is in the right position to get a point
	if (myPlayer->GetCurrentHoop().MyBallList.empty())
	{
		cout << "fuck u" << endl; // check vector stuff
	}
	else if (myPlayer->GetCurrentHoop().GetID() != previousHoop.GetID())
	{
		// Else, if the current hoop has changed since the last tick
		// Simply Assign the top-ball from the new CurrentHoop
		//
		// This branch will also trigger when it's the first tick of the game
		//
		// IMPORTANT NOTE : whenever the player leaves the range of a 
		// Hoop that they have collected balls from before and then 
		// re-enters range of that hoop, the game treats it as if it's 
		// the first time the player has been in range of that Hoop. 
		//
		// i.e. it doesn't remember what the last ball the player got
		// from that loop was, and "resets" to the top ball in that Hoops
		// BallList
		myPlayer->SetNextBall(myPlayer->GetCurrentHoop().MyBallList[0]);
	}
	else if (myPlayer->CollectedBalls.size() > 0 && prevNextBall.GetID() == myPlayer->CollectedBalls[myPlayer->CollectedBalls.size() - 1].GetID())
	{
		// Else if the player has collected the previousNextBall
		//
		// find the new NextBall the player should collect
		bool found = false;
		int iter = 0;

		// if the player has collected a ball
		if (prevNextBall.GetID() > 0)
		{
			int prevColor = prevNextBall.GetColor();

			//Note : the Init() function sorts all Hoop's BallLists in color order

			// Find the next available ball of a different color or if there is 
			// only one color left, just assign the next ball in the list
			while (!found)
			{
				// If we've searched the whole list and not found a ball of a different color
				if (iter >= myPlayer->GetCurrentHoop().MyBallList.size())
				{
					// Assign the next available ball
					myPlayer->SetNextBall(myPlayer->GetCurrentHoop().MyBallList[0]);
					found = true;
				}
				// Else, if we have found the next ball of a different color
				else if (myPlayer->GetCurrentHoop().MyBallList[iter].GetColor() != prevColor)
				{
					// Assign that ball as the next available ball
					myPlayer->SetNextBall(myPlayer->GetCurrentHoop().MyBallList[iter]);
					found = true;
				}
				iter++;
			}
		}
	}
}

// Implementation of Init, as defined in NextBall.h
void NextBall::Init(vector<MapData> MyMapData)
{
	Object temp;

	// Sort through data list storing only data needed
	for (int i = 0; i < MyMapData.size(); i++)
	{
		if (MyMapData[i].TypeID == temp.BALL)
		{
			Balls.push_back(Ball(MyMapData[i].xpos,
				MyMapData[i].ypos,
				MyMapData[i].color,
				MyMapData[i].ID));
		}
		else if (MyMapData[i].TypeID == temp.HOOP)
		{
			Hoops.push_back(Hoop(MyMapData[i].xpos,
				MyMapData[i].ypos,
				MyMapData[i].orientation,
				MyMapData[i].MyBallList,
				MyMapData[i].ID));
		}
	}

	// Build Ball lists for each hoop.
	//
	// NOTE: A much more efficient way to do this would be for two vectors
	//	     vector<Balls> and vector<Hoops> to be built up during the Init() of
	//       the map, where each hoop is assigned a list of balls that are closest
	//       to it. These two vectors would then be passed to this Class:
	//
	//       NextBall.Init(Balls, Hoops)
	//
	//       But based on the problem statement, we have to do extra work here 
	//       to sort it out. complexity is O(numHoops^numBalls). It's inefficient
	//       for really large maps but we only have to call it once per level.

	float tempDistance;
	int smallestD = INT16_MAX;
	int tempIndex = 0;

	// For each ball, find the hoop that is closest to it, and put the ball
	// in that hoop's ball list
	for (int i = 0; i < Balls.size(); i++)
	{
		for (int j = 0; j < Hoops.size(); j++)
		{
			tempDistance = GetDistance(Balls[i].GetXPos(), Balls[i].GetYPos(),
				Hoops[j].GetXPos(), Hoops[j].GetYPos());

			// NOTE: If the ball is equidistant to multiple hoops, it will go
			// in the BallList of whichever one of those hoops it checks
			// first
			if (tempDistance < smallestD)
			{
				smallestD = tempDistance;
				tempIndex = j;
			}
		}
		Hoops[tempIndex].MyBallList.push_back(Balls[i]);
		tempIndex = 0;
		smallestD = INT16_MAX;
	}

	// Finally, sort all Ball lists in color order
	for (int i = 0; i < Hoops.size(); i++)
	{
		sort(Hoops[i].MyBallList.begin(), Hoops[i].MyBallList.end(), [](Ball &a, Ball &b) {return a.GetColor() < b.GetColor(); });
	}

	return;
}

// Shutdown call
void NextBall::Shutdown()
{
	Hoops.clear();
	Balls.clear();

	// Do any other Garbage Collection
}

