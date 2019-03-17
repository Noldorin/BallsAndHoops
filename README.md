# BallsAndHoops
Submission for UndeadLabs Programming Test

This is my class for:
1. Determining which ball the player should get next
2. Score tracking
3. Enabling collected ball tracking.

It has a very rudimentary driver that does not cover all the functionality; manually messing
around with the MockData in Main.cpp will let you test against various game states.

I have made a number of important assumptions that do not break 
the requirements of the problem statement as far as I can tell.

They are all listed appropriately in the in-code comments but 
I'm going to relist them here for your convenience.

ASSUMPTION 1:
The player alway starts at the origin, (0,0) which is the bottom left-most 
location on the map, akin to how pixel resolution is stored.
i.e. there are no negative coordinates on the map

ASSUMPTION 2:
All objects that get passed to NextBall::Init() as part of the 
vector<MapData> MapData list have been initialized in a way that 
follows the explicit and implicit rules of the class's design.

There is not exhaustive checking for valid values of all the objects.

ASSUMPTION 3:
When a player collects a ball associated with a hoop, that ball 
is popped off the MyBallList of the current hoop and pushed onto 
the CollectedBalls list of the player. 

If MyBallList is empty, the player will get a point if
they are standing in the correct position relative to
the hoop.


Finally I have some notes on implementation details that were left up to me.

NOTE 1: 
If the player is equidistant from multiple hoops, it will
stick with whichever hoop it was most recently closer to

i.e. if it was 6m away from HoopA and 8m away from HoopB,
and then moved 1m such that it was 7m away from both A and B,
it's "CurrentHoop" would remain A.

Similarly, when building the BallLists for each Hoop, if a Ball is  
placed equidistant from two Hoops, it will be added to whichever
Hoop comes first in the vector<Hoops> list for the map

NOTE 2:
When the player leaves the range of a Hoop that they may 
or may not have collected balls from and then re-enters 
the range of that hoop, the game treats it as if it is
the first time the player has been in range of that Hoop. 

i.e. it doesn't remember what the last ball the player got from that 
loop was, and "resets" to the top ball in that Hoop's BallList

NOTE 3:
When the player has collected all balls from the current hoop, 
they will NOT get a new targeted ball to pursue until they either
complete the hoop they are closest to by "moving within 5 meters 
of the hoop and 30 degrees of the hoop's forward vector" or move
closer to another hoop

Note 4:
Nowhere in the problem requirements does it say that this class is
responsible either for detecting if the player has encountered a ball,
or allowing them to pick it up. 

Therefor I provide a vector<Ball> list in the player object that would
be very easy to add found balls to as they are popped off the BallLists
of the various hoops. However, none of the methods in this class actually
performs those actions.
