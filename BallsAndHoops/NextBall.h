#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Objects.h"

class NextBall 
{
	private:
		// Properties
		vector<Hoop> Hoops;
		vector<Ball> Balls;
		Hoop currentHoop;
		Ball currentBall;
		Hoop previousHoop;
		Ball prevNextBall;

		unsigned int prevX, prevY;
		
		// Private Helpers
		float GetDistance(unsigned int x1, unsigned int y1,
				          unsigned int x2, unsigned int y2);

		// Gets the area of the triangle formed by
		// (x1, y1), (x2, y2) and (x3, y3) 
		float GetArea(double x1, double y1, double x2, double y2, double x3, double y3);

		// Determines if a point (x, y) lies inside the triangle formed
		//  by (x1, y1), (x2, y2) and (x3, y3) 
		bool WithinTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y);


	public:
		NextBall();

		// default destructor
		~NextBall();

		#pragma region StructsNumsConst
		// Structs, Enums and Constants

		// Enum for determining both the color of a Ball
		// and the relative collection order of the colors
		// IMPORTANT: This entire class ASSUMES that this Enum was used to populate 
		// the Balls on the map, and that the balls are collected in this order
		enum Color
		{
			red = 1,
			orange = 2,
			yellow = 3,
			green = 4,
			blue = 5,
			purple = 6
		};

		// Allows Ball and Hoop data to be received in a single list along with other Data
		struct MapData
		{
			// Obj Attr
			unsigned int xpos = 0;
			unsigned int ypos = 0;
			unsigned int ID; // A globally unique ID 
			unsigned int TypeID; // Indicates Object Type 

			// Ball Attr
			unsigned int color = 0;

			// Hoop Attr
			vector<Ball> MyBallList;
			unsigned int orientation = -1;

			// other data attributes that may be mixed in with the 
			// ball and hoop data as per problem statement
			// ...
		};
		#pragma endregion

		// This function contains the main decision logic, and is called each Tick
		// It takes in a pointer to the current Player and updates that player's 
		// current Hoop/score/nextBall based on it's current location and orientation.
		void Tick(Player *myPlayer);

		// This is the initialization call for this class. It is separate from
		// the constructor, and must be explicitly invoked before the class instance
		// is usable
		//
		// It takes in a list of MapData structs, and assumes that each item
		// contains valid data according to it's TypeID.
		// i.e. if its TypeID == Ball, it will have a valid color etc
		//
		// It will filter out any objects that it doesn't need to know about, and stores
		// and preprocess the remaining objects as needed.
		//
		// This preprocessing notably includes sorting all the Balls into Hoop BallLists
		// and then sorting each of those BallLists in ascending order of color
		void Init(vector<MapData> MyMapData);
		void Shutdown();
};