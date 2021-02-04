#pragma once
#include "Component.h"
#include <vector>


class Grid
{
public:
	Grid(int x, int y);

	int gx;
	int gy;
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


class MapMaker : public Component
{
public:
	MapMaker(class GameObject* gameObject);
	void BuildMap();

	int* GetMap() const { return mMapArray; }

private:
	void BuildRoom(class Room room);
	void BuildConnectRoom(class Room &room, class Grid &wall);
	class Grid ChooseWall();
	Room CheckRoom(class Grid wall);
	bool CheckIntersect(class Room &r);
	bool RoomIntersect(class Room &r1, class Room &r2);
	void PrintMap();

	int* mMapArray;
	std::vector<class Grid> mWalls;
	std::vector<class Room> mRooms;

	int mMapW;
	int mMapH;
	int mRoomMaxW;
	int mRoomMaxH;
	class Grid mDir;
};

