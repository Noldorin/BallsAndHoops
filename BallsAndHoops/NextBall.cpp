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

#pragma region HelperMethods
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

float NextBall::GetArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

// Determines if a point (x y) lies inside the main triangle
// formed by (x1, y1), (x2, y2) and (x3, y3) 
bool NextBall::WithinTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y)
{
	// Calculate the area of the main triangle 
	float A = GetArea(x1, y1, x2, y2, x3, y3);

	// Calculate area of each triangle formed by connecting  
	// 2 of the vertices of the main triangle with (x, y)
	float A1 = GetArea(x, y, x2, y2, x3, y3);

	float A2 = GetArea(x1, y1, x, y, x3, y3);

	float A3 = GetArea(x1, y1, x2, y2, x, y);

	// If the sum of the areas made by these sub-triangles
	// is equal to the area of the main triangle, then (x,y)
	// must be within it
	return (A == A1 + A2 + A3);
}

#pragma endregion

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
	
	int searchFor = previousHoop.GetID();; // For use in find_if

	// If the player has moved, or 
	// if it's the very first tick, or
	// if the player completed the previous hoop
	//
	// Calculate the hoop that the player is closest too
	if (prevX != myPlayer->xpos || prevY != myPlayer->ypos || previousHoop.GetID() == -1 || Hoops.end() == (find_if(Hoops.begin(), Hoops.end(), [&searchFor](Hoop& obj) {return obj.GetID() == searchFor; })))
	{
		float tempDistance;
		int smallestD = INT16_MAX;
		int tempIndex = 0;

		for (int i = 0; i < Hoops.size(); i++)
		{
			tempDistance = GetDistance(myPlayer->xpos, myPlayer->ypos,
				Hoops[i].xpos, Hoops[i].ypos);

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

		currentHoop = myPlayer->GetCurrentHoop();

		// Update stored location
		prevX = myPlayer->xpos;
		prevY = myPlayer->ypos;
	}
	// WE NOW HAVE AN ACCURATE CURRENT HOOP

	// If the current Hoops ball-list is empty check if the 
	// player is in the right position to get a point
	//
	// NOTE : If a hoop gets put on the map without any balls
	// close to it, the player will still get a point for 
	// "completing" it
	if (myPlayer->GetCurrentHoop().MyBallList.empty())
	{
		// If the player is close enough to the hoop
		if (GetDistance(prevX, prevY, currentHoop.xpos, currentHoop.ypos) <= 5)
		{
			double x1 = currentHoop.xpos;
			double y1 = currentHoop.ypos;
			double x2 = currentHoop.facing.x1_end;
			double y2 = currentHoop.facing.y1_end;
			double x3 = currentHoop.facing.x2_end;
			double y3 = currentHoop.facing.y2_end;

			// If the player is within the facing arc of the hoop
			if (WithinTriangle(x1, y1, x2, y2, x3, y3, myPlayer->xpos, myPlayer->ypos))
			{
				// find the hoop and remove it from the Hoops list.
				searchFor = currentHoop.GetID();
				auto iter = find_if(Hoops.begin(), Hoops.end(), [&searchFor](Hoop& obj) {return obj.GetID() == searchFor; });
				Hoops.erase(iter);
				cout << endl << "the player completed the current hoop!" << endl
					<< "it has been removed from the game.. >";
				cin.ignore();

				// Give the player a point for completing the hoop
				myPlayer->IncrementScore();

				cout << "the player gets a point!! >";
			}
			else
			{
				cout << "no points for you... gotta move >";
			}
			cin.ignore();
			cout << endl;
		}
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
			tempDistance = GetDistance(Balls[i].xpos, Balls[i].ypos,
				Hoops[j].xpos, Hoops[j].ypos);

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

