#include "Objects.h"

#pragma region ObjectImp

// Object Class Implementations

// Default Constructor
Object::Object()
{
	xpos = 0;
	ypos = 0;
}

// init constructor, takes position.
Object::Object(int x, int y)
{
	xpos = x;
	ypos = y;
}

// default destructor
Object::~Object()
{
}

// Gets/Sets

int Object::GetID()
{
	return ID;
}

unsigned int Object::GetType()
{
	return TypeID;
}
#pragma endregion

#pragma region PlayerImp

// Constructors
Player::Player()
{
	TypeID = PLAYER;
}

Player::Player(int x, int y, int id) 
{
	TypeID = PLAYER;
	xpos = x;
	ypos = y;
	ID = id;
}

int Player::operator=(const Player &rhs)
{
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	CollectedBalls = rhs.CollectedBalls;
	currentHoop = rhs.currentHoop;
	nextBall = rhs.nextBall;
	score = rhs.score;
	ID = rhs.ID;

	return 1;
}

Player::~Player() 
{
}

// Player Class implementations
Hoop Player::GetCurrentHoop()
{
	return currentHoop;
}
void Player::SetCurrentHoop(Hoop curHoop)
{
	currentHoop = curHoop;
}

Ball Player::GetNextBall()
{
	return nextBall;
}
void Player::SetNextBall(Ball ball)
{
	nextBall = ball;
}

int Player::GetScore()
{
	return score;
}
void Player::SetScore(int newScore)
{
	score = newScore;
}
void Player::IncrementScore()
{
	score++;
}

int Player::GetOrientation()
{
	return orientation;
}

#pragma endregion

#pragma region BallImp

// Ball Class implementations
Ball::Ball()
{
	TypeID = BALL;
}

Ball::Ball(int x, int y, unsigned int c, int id)
{
	TypeID = BALL;
	xpos = x;
	ypos = y;
	color = c;
	ID = id;
}

Ball::~Ball()
{
}

int Ball::operator=(const Ball &rhs)
{
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	color = rhs.color;
	ID = rhs.ID;

	return 1;
}

unsigned int Ball::GetColor()
{
	return color;
}

void Ball::SetColor(unsigned int c)
{
	color = c;
}

#pragma endregion

#pragma region HoopImp

// Hoop Class Implementations
Hoop::Hoop()
{
}

Hoop::Hoop(int x, int y, unsigned int orient, vector<Ball> ballList, int id)
{
	TypeID = HOOP;
	xpos = x;
	ypos = y;
	orientation = orient;
	MyBallList = ballList;
	ID = id;

	// Convert orientation to radians
	double pi = acos(-1);
	double r1 = ((orient - 15) * pi) / 180.0;
	double r2 = ((orient + 15) * pi) / 180.0;

	// Use orientation find the ending coordinatse of 2 "lines"
	// both start at (xpos,ypos)
	// one ends at (x1, y1), the other ends at (x2, y2)
	//
	// Together these two lines create the facing arc the 
	// player has to be within to score points from a 
	// completed hoop
	facing.x1_end = xpos + (cos(r1) * 10); // Since the player needs to be within 5 meters of the hoop
	facing.y1_end = ypos + (sin(r1) * 10); // 10 is more than enough max, length to draw these lines to
	facing.x2_end = xpos + (cos(r2) * 10);
	facing.y2_end = ypos + (sin(r2) * 10);
}

Hoop::~Hoop()
{
}

int Hoop::operator=(const Hoop &rhs)
{
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	orientation = rhs.orientation;
	facing.x1_end = rhs.facing.x1_end;
	facing.y1_end = rhs.facing.y1_end;
	facing.x2_end = rhs.facing.x2_end;
	facing.y2_end = rhs.facing.y2_end;
	MyBallList = rhs.MyBallList;
	ID = rhs.ID;

	return 1;
}

int Hoop::GetOrientation()
{
	return orientation;
}

#pragma endregion
