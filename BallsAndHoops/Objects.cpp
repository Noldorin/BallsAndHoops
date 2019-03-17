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
Object::Object(unsigned int x, unsigned int y)
{
	xpos = x;
	ypos = y;
}

// default destructor
Object::~Object()
{
}

// Gets/Sets

unsigned int Object::GetXPos()
{
	return xpos;
}
void Object::SetXPos(int newX)
{
	xpos = newX;
}
unsigned int Object::GetYPos()
{
	return ypos;
}
void Object::SetYPos(int newY)
{
	ypos = newY;
}

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

Player::Player(unsigned int x, unsigned int y, int id) 
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

Ball::Ball(unsigned int x, unsigned int y, unsigned int c, int id)
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

Hoop::Hoop(unsigned int x, unsigned int y, unsigned int orient, vector<Ball> ballList, int id)
{
	TypeID = HOOP;
	xpos = x;
	ypos = y;
	MyBallList = ballList;
	ID = id;
}

Hoop::~Hoop()
{
}

int Hoop::operator=(const Hoop &rhs)
{
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	orientation = rhs.orientation;
	MyBallList = rhs.MyBallList;
	ID = rhs.ID;

	return 1;
}

int Hoop::GetOrientation()
{
	return orientation;
}

#pragma endregion
