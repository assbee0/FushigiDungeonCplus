#pragma once
#include "Component.h"
#include <vector>


class Wall
{
public:
	Wall(int x, int y);

	int gx;
	int gy;

	friend bool operator==(const Wall& a, const Wall& b)
	{
		return (a.gx == b.gx && a.gy == b.gy);
	}
};

class Room
{
public:
	Room(int w, int h, int x, int y);

	int rw;
	int rh;
	int rx;
	int ry;

};

class Map
{
public:
	Map(int* array, int w, int h);

	// Get a random position from all of the rooms
	class Vector2 GetRandomPos();

	int* mapArray;
	int width;
	int height;

	void SetRooms(std::vector<class Room> rooms) { mRooms = rooms; }

private:
	std::vector<class Room> mRooms;
};


class MapMaker : public Component
{
public:
	MapMaker(class GameObject* gameObject, int w, int h, int rw, int rh);
	class Map* BuildMap();

	void SetParameters(int w, int h, int rw, int rh) 
		{ mMapW = w; mMapH = h; mRoomMaxW = rw; mRoomMaxH = rh; }

private:
	// Build a rw * rh room and the left up position is (rx, ry)
	// The area which is able to walk through is (rw - 1) * (rh - 1)
	void BuildRoom(class Room room);
	// Build a new room from this wall
	void BuildConnectRoom(class Room &room, class Wall &wall);
	// Randomly choose a wall from current mWalls
	class Wall ChooseWall();
	// Try generating a random room from this wall
	Room CheckRoom(class Wall& wall);
	// Check if room r intersects with any of the rooms generated
	bool CheckIntersect(class Room& r);
	// Check if room r1 intersects with room r2
	bool RoomIntersect(class Room& r1, class Room& r2);
	// Remove the wall from mWalls
	void RemoveWall(class Wall& wall);
	// Output the map array and all the walls on the console window
	void PrintMap();

	int* mMapArray;
	std::vector<class Wall> mWalls;
	std::vector<class Room> mRooms;

	int mMapW;
	int mMapH;
	// Max width of the room can be generated
	int mRoomMaxW;
	// Max height of the room can be generated
	int mRoomMaxH;
	class Wall mDir;
};

