#pragma once
#include "../constants.h"

struct Floor
{
	float PosX;
	float PosZ;
	Floor(float posx, float posz) : PosX(posx* MazeConstants::TILE_SIZE), PosZ(posz* MazeConstants::TILE_SIZE) {}
	Floor() = default;
};

struct Wall
{
	float PosX;
	float PosZ;
	Wall(float posx, float posz) : PosX(posx* MazeConstants::TILE_SIZE), PosZ(posz* MazeConstants::TILE_SIZE) {}
	Wall() = default;
};

struct Door1
{
	float PosX;
	float PosZ;
	Door1(float posx, float posz) : PosX(posx* MazeConstants::TILE_SIZE), PosZ(posz* MazeConstants::TILE_SIZE) {}
	Door1() = default;
};

struct Collider
{
	float PosX;
	float PosY;
	float PosZ;
	SelfVector3 size;
	Collider(float posx, float posy, float posz, SelfVector3 size) : PosX(posx), PosY(posy), PosZ(posz), size(size) {}
	Collider(float posx, float posy, float posz, float sizex, float sizey, float sizez) : PosX(posx), PosY(posy), PosZ(posz), size(sizex, sizey, sizez) {}
	Collider() = default;
};

struct Player
{
	SelfVector3 Pos;
	Player(SelfVector3 pos) : Pos(pos) {}
	Player(float posx, float posy, float posz) : Pos(posx, posy, posz) {}
	Player() = default;
};

//A bigger button or pressure plate
struct Button1
{
	float PosX;
	float PosZ;
	Button1(float posx, float posz) : PosX(posx* MazeConstants::TILE_SIZE), PosZ(posz* MazeConstants::TILE_SIZE) {}
	Button1() = default;
};

struct Door1State 
{
	float openAmount = 1.0f; // 1.0 = stängd, 0.0 = helt öppen
	bool isClosing = false;

	Door1State() = default;
};

struct Button1click
{
	bool clicked = false;
	Button1click() = default;
};

struct Goal
{
	float PosX;
	float PosZ;
	Goal(float posx, float posz) : PosX(posx* MazeConstants::TILE_SIZE), PosZ(posz* MazeConstants::TILE_SIZE) {}
	Goal() = default;
};

struct WinTrigger
{
	bool* winFlag = nullptr;
	WinTrigger() = default;
	WinTrigger(bool* ptr) : winFlag(ptr) {}
};

struct CoroutineComponent 
{
	int coroutineRef;
	CoroutineComponent() = default;
	CoroutineComponent(int ref) : coroutineRef(ref) {}
};
