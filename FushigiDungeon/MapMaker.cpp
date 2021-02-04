#include "MapMaker.h"
#include "GameObject.h"
#include "Random.h"

MapMaker::MapMaker(GameObject* gameObject) :
	Component(gameObject),
	mMapArray(nullptr),
	mMapW(20),
	mMapH(15),
	mRoomMaxW(10),
	mRoomMaxH(10),
	mDir(Grid(0,0))
{

}

void MapMaker::BuildMap()
{
	mMapArray = new int[mMapW * mMapH];
	for (int i = 0; i < mMapW * mMapH; i++)
		mMapArray[i] = 0;
	BuildRoom(Room(6, 6, mMapW/2-3, mMapH/2-3));

	int randomCountWall = 0;
	int randomCountRoom = 0;

	Room room = Room(0, 0, 0, 0);
	while (randomCountWall < 100)
	{
		Grid wall = ChooseWall();
		
		while (randomCountRoom < 10)
		{
			room = CheckRoom(wall);
			if (room.rw == 0)
				randomCountRoom++;
			else
			{
				randomCountRoom = 0;
				break;
			}
		}
		if (randomCountRoom >= 10)
		{
			randomCountWall++;
			randomCountRoom = 0;
			continue;
		}
		else
			BuildConnectRoom(room, wall);
	}

	PrintMap();
}

void MapMaker::BuildRoom(Room room)
{
	for (int j = 0; j < room.rh; j++)
	{
		for (int i = 0; i < room.rw; i++)
		{
			if (i == 0 || j == 0 || i == room.rw - 1 || j == room.rh - 1)
			{
				mMapArray[(j + room.ry) * mMapW + i + room.rx] = 1;
				if ((i == 0 || i == room.rw - 1) && (j == 0 || j == room.rh - 1))
					continue;
				if (i + room.rx== 0 || j + room.ry  == 0 || i + room.rx == mMapH - 1 || j + room.ry == mMapW - 1)
					continue;

				mWalls.emplace_back(Grid(i + room.rx, j + room.ry));
			}
			else
				mMapArray[(j + room.ry) * mMapW + i + room.rx] = 2;
			
		}
	}
	mRooms.emplace_back(room);
}

void MapMaker::BuildConnectRoom(Room& room, Grid& wall)
{
	BuildRoom(room);
	mMapArray[wall.gy * mMapW + wall.gx] = 2;
	mMapArray[(wall.gy + mDir.gy) * mMapW + wall.gx + mDir.gx] = 2;
}

Grid MapMaker::ChooseWall()
{
	Random::Init();
	int index = Random::GetIntRange(0, mWalls.size() - 1);
	Grid wall = mWalls[index];
	//printf("index:%d\n", index);
	//printf("%d, %d\n", wall.gx, wall.gy);
	return wall;
}

Room MapMaker::CheckRoom(Grid wall)
{
	int roomW = Random::GetIntRange(4, mRoomMaxW);
	int roomH = Random::GetIntRange(4, mRoomMaxH);
	int wallX = wall.gx;
	int wallY = wall.gy;

	// Return r0 for false
	Room r0 = Room(0, 0, 0, 0);

	// Check Up
	if (mMapArray[wallY * mMapW + wallX - mMapW] == 0)
	{
		int rx = wallX - roomW / 2;
		int ry = wallY - roomH;
		// Out of the map
		if (rx < 0 || rx + roomW >= mMapW || ry < 0)
			return r0;
		Room r = Room(roomW, roomH, rx, ry);
		// Check if intersect with rooms already generated
		if (!CheckIntersect(r))
		{
			mDir = Grid(0, -1);
			return r;
		}
	}
	// Check Down
	else if (mMapArray[wallY * mMapW + wallX + mMapW] == 0)
	{
		int rx = wallX - roomW / 2;
		int ry = wallY + 1;
		// Out of the map
		if (rx < 0 || rx + roomW >= mMapW || ry + roomH >= mMapH)
			return r0;
		Room r = Room(roomW, roomH, rx, ry);
		printf("%d,%d,%d,%d\n", roomW, roomH, rx, ry);
		// Check if intersect with rooms already generated
		if (!CheckIntersect(r))
		{
			mDir = Grid(0, 1);
			return r;
		}
	}
	// Check Left
	else if (mMapArray[wallY * mMapW + wallX - 1] == 0)
	{
		int rx = wallX - roomW;
		int ry = wallY - roomH / 2;
		// Out of the map
		if (rx < 0 || ry < 0 || ry + roomH >= mMapH)
			return r0;
		Room r = Room(roomW, roomH, rx, ry);
		// Check if intersect with rooms already generated
		if (!CheckIntersect(r))
		{
			mDir = Grid(-1, 0);
			return r;
		}
	}
	// Check Right
	else if (mMapArray[wallY * mMapW + wallX + 1] == 0)
	{
		int rx = wallX + 1;
		int ry = wallY - roomH / 2;
		// Out of the map
		if (rx + roomW >= mMapW || ry < 0 || ry + roomH >= mMapH)
			return r0;
		Room r = Room(roomW, roomH, rx, ry);
		// Check if intersect with rooms already generated
		if (!CheckIntersect(r))
		{
			mDir = Grid(1, 0);
			return r;
		}
	}

	// Can't generate in the area, return r0
	return r0;
}

bool MapMaker::CheckIntersect(Room &r)
{
	for (auto &r2 : mRooms)
	{
		if (RoomIntersect(r, r2))
			return true;
	}
	return false;
}

bool MapMaker::RoomIntersect(Room &r1, Room &r2)
{
	int maxminX = (r1.rx > r2.rx) ? r1.rx : r2.rx;
	int maxminY = (r1.ry > r2.ry) ? r1.ry : r2.ry;
	int minmaxX = (r1.rx + r1.rw < r2.rx + r2.rw) ? r1.rx + r1.rw : r2.rx + r2.rw;
	int minmaxY = (r1.ry + r1.rh < r2.ry + r2.rh) ? r1.ry + r1.rh : r2.ry + r2.rh;
	return (maxminX < minmaxX && maxminY < minmaxY);
}

void MapMaker::PrintMap()
{
	for (int i = 0; i < mMapH; i++)
	{
		for (int j = 0; j < mMapW; j++)
		{
			printf("%d ", mMapArray[i * mMapW + j]);
		}
		printf("\n");
	}

	for (auto vec : mWalls)
	{
		printf("%d,%d\n", vec.gx, vec.gy);
	}
}

Room::Room(int w, int h, int x, int y):
	rw(w),
	rh(h),
	rx(x),
	ry(y)
{

}

Grid::Grid(int x, int y) :
	gx(x),
	gy(y)
{

}