// Purpose: Defines data-structures and methods for use in the Ball-Hoop Game
//

// Function Libraries
#include <cstdlib>
#include <vector>

using namespace std;

// Base Game Object Type
//
// Contains the trait(s) common to all game objects, i.e. an (x,y) position.
//
// The gameplay space is a grid in meters, and x and y are integers
// So an object at (1,3) is 1 meter "north" and 3 meters "west" of the origin
//
// (0,0) is the bottom, left-most point on the graph; there are no negative x or y
//
// Some objects have an orientation, this value is stored as a degree-integer 0-359
// where 0 indicates "due-west" in the gameplay map

#ifndef OBJECTS_H
#define OBJECTS_H

class Object
{
	private:

	protected:
		unsigned int xpos = 0;
		unsigned int ypos = 0;
		int ID = -1; // A globally unique ID
					 // Defaults to -1 if uninitialized.
					 // Explicit Assignment is required for full functionality
		unsigned int TypeID; // Indicates Object Type (see below)*

	public:
		// default constructor
		Object();

		// init constructor, takes position.
		Object(unsigned int x, unsigned int y);

		// default destructor
		~Object();

		// Gets-Sets
		unsigned int GetXPos();
		void SetXPos(int newX);
		unsigned int GetYPos();
		void SetYPos(int newY);

		int GetID();

		unsigned int GetType();

		// *Constants that determine objects type.
		// Indicates the game object type in derived classes
		// This isn't good design, but given the problem statement
		// it's the quickest way I can think of to sort through the
		// list of arbitrary game-data the NextBall program receives
		//
		// In this implementation, all the sub-class constructors will give
		// each object instance the appropriate type
		const int PLAYER = 1;
		const int BALL = 2;
		const int HOOP = 3;
};



#endif // OBJECTS_H

#ifndef BALL_H
#define BALL_H

// Ball Object
//
// It has a color

class Ball : public Object
{
private:
	unsigned int color; // color is 1-6: red, orange, yellow, green, blue, purple
	unsigned int typeID = BALL;

public:
	// Default Constructor
	Ball();

	// Init color Constructor
	Ball(unsigned int x, unsigned int y, unsigned int color, int id);

	~Ball();

	// Assignment operator
	int operator=(const Ball &rhs);

	// Get-Set
	unsigned int GetColor();
	void SetColor(unsigned int c);
};

#endif // BALL_H


#ifndef HOOP_H
#define HOOP_H

// Hoop Object
//
// Hoops have a forward-facing orientation
// Hoops have a list of balls that are associated with them
//
// IMPORTANT : This project ASSUMES that When a player collects a ball 
//             associated with a hoop, that ball is popped off 
//             MyBallList of the current hoop and pushed onto 
//             CollectedBalls of the player. 
//
//             If MyBallList is empty, the player will get a point if
//             they are standing in the correct position relative to
//             the hoop
//
//
// These are the balls the player must collect to get a point
// from this hoop

class Hoop : public Object
{
private:
	unsigned int TypeID = HOOP;
	int orientation;

public:
	// Default Constructor
	Hoop();

	// Init list constructor
	Hoop(unsigned int x, unsigned int y, unsigned int orient, vector<Ball> ballList, int id);

	~Hoop();

	// Assignment operator
	int operator=(const Hoop &rhs);

	int GetOrientation();

	// List of balls associated with this hoop
	vector<Ball> MyBallList;
};

#endif // HOOP_H

// Player Object
// Inherits from Object
// It has a Score
// It tracks whichever hoop the player is currently closest to
// It also tracks the next ball the player must gather for that hoop

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Object
{
	private:
		Hoop currentHoop; // ID of the hoop the player is closest to
		Ball nextBall; // ID of the next ball the player needs to get
		int score = 0;
		int orientation = 0; // a degree value 0-359 where 0 is "due west"

	public:
		// Default Constructor
		Player();

		Player(unsigned int x, unsigned int y, int id);

		~Player();

		// Assignment operator
		int operator=(const Player &rhs);

		// Get-Sets-Increments
		// All sets, set the property = to the parameter 

		int GetScore();
		void SetScore(int newScore);
		void IncrementScore(); // Increments score by 1

		Hoop GetCurrentHoop();
		void SetCurrentHoop(Hoop hoop);

		Ball GetNextBall();
		void SetNextBall(Ball ball);

		int GetOrientation();

		vector<Ball> CollectedBalls;
};

#endif



