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
	void BuildRoom(class Room room);
	void BuildConnectRoom(class Room &room, class Wall &wall);
	class Wall ChooseWall();
	Room CheckRoom(class Wall& wall);
	bool CheckIntersect(class Room& r);
	bool RoomIntersect(class Room& r1, class Room& r2);
	void RemoveWall(class Wall& wall);
	void PrintMap();

	int* mMapArray;
	std::vector<class Wall> mWalls;
	std::vector<class Room> mRooms;

	int mMapW;
	int mMapH;
	int mRoomMaxW;
	int mRoomMaxH;
	class Wall mDir;
};

