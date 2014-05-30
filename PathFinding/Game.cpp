#include "Game.hpp"
#include "Graphics.hpp"
#include <random>
#include <vector>
#include <memory>
#include <algorithm>
#include <math.h>

bool gameover = false;

using namespace GejbEngine;
using std::make_shared;
using std::shared_ptr;

bool searching = true;

struct Goal{
	int x;
	int y;
}goal;

struct Player{
	double x;
	double y;
} playerStart;

struct PlayerState{
	shared_ptr<Player> player;
	shared_ptr<PlayerState> parentState;
	double g = 0;
	double h = 0;
	double f = 0;
};


bool player_sorter(shared_ptr<PlayerState> const lhs, shared_ptr<PlayerState> const rhs){
	return lhs->f < rhs->f;
}

shared_ptr<PlayerState> winningState;
shared_ptr<PlayerState> first;
std::vector<shared_ptr<PlayerState>> open;
std::vector<shared_ptr<PlayerState>> visited;

int openIndex = 0;
int visitedIndex = 0;

Texture goalTexture;
Texture grassTexture;
Texture playerTexture;
Texture waterTexture;

enum tile{
	GRASS = 1,
	WATER = 2
};

int map[mapSize][mapSize];

bool game_preload() {
	return true;
}

bool game_init(HWND hWnd) {
	if(!LoadTexture("Goal.png", &goalTexture))
		return false;
	if(!LoadTexture("Grass.png", &grassTexture))
		return false;
	if(!LoadTexture("Player.png", &playerTexture))
		return false;
	if(!LoadTexture("Water.png", &waterTexture))
		return false;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution1(1, 5);
	std::uniform_int_distribution<int> distribution2(0, 49);

	for(int i = 0; i < mapSize; i++){
		for(int j = 0; j < mapSize; j++){
			if(distribution1(generator) > 4){
				map[i][j] = WATER;
			} else{
				map[i][j] = GRASS;
			}
		}
	}

	int x = distribution2(generator);
	int y = distribution2(generator);

	while(map[x][y] != GRASS){
		x = distribution2(generator);
		y = distribution2(generator);
	}

	goal.x = x;
	goal.y = y;


	x = distribution2(generator);
	y = distribution2(generator);

	while(map[x][y] != GRASS){
		x = distribution2(generator);
		y = distribution2(generator);
	}

	playerStart.x = x;
	playerStart.y = y;


	first = make_shared<PlayerState>();
	first->player = make_shared<Player>(playerStart);
	open.push_back(first);

	return true;
}

static double lengthToGoal(int x, int y){
	double a = (sqrt(abs(x - goal.x) ^ 2) + sqrt(abs(y - goal.y) ^ 2));
	return a;
}

static void testDirection(double x, double y, shared_ptr<PlayerState> state){
	bool ok = true;
	for each(shared_ptr<PlayerState> state in visited){
		if((state->player->x == x) && (state->player->y == y)){
			ok = false;
			break;
		}
	}
	if(ok == true){
		shared_ptr<PlayerState> newState = make_shared<PlayerState>();
		newState->player = make_shared < Player >() ;
		newState->player->x = x;
		newState->player->y = y;
		newState->parentState = state;
		newState->g = 0;
		newState->h = lengthToGoal(x, y);
		newState->f = newState->g + newState->h;
		open.push_back(newState);
		visited.push_back(newState);
	}
}

static void checkSurrounding(shared_ptr<PlayerState> state){
	int x, y;
	x = state->player->x - 1;
	y = state->player->y;
	if(map[x][y] == GRASS){
		testDirection(x, y, state);
	}


	x = state->player->x;
	y = state->player->y - 1;
	if(map[x][y] == GRASS){
		testDirection(x, y, state);
	}

	x = state->player->x + 1;
	y = state->player->y;
	if(map[x][y] == GRASS){
		testDirection(x, y, state);
	}

	x = state->player->x;
	y = state->player->y + 1;
	if(map[x][y] == GRASS){
		testDirection(x, y, state);
	}

	std::sort(open.begin(), open.end(),&player_sorter);
}

void game_update() {
	if(searching && open.size() > 0){
			shared_ptr<PlayerState> pState = open.at(0);
			open.erase(open.begin());
			checkSurrounding(pState);
			if((pState->player->x == goal.x) && (pState->player->y == goal.y)){
				winningState = pState;
				searching = false;
			}
	}
}

void game_end() {
	ReleaseTexture(&goalTexture);
	ReleaseTexture(&grassTexture);
	ReleaseTexture(&playerTexture);
	ReleaseTexture(&waterTexture);
}

void game_graphics_update() {

	for(int i = 0; i < mapSize; i++){
		for(int j = 0; j < mapSize; j++){
			if(map[i][j] == WATER){
				DrawTexture(&waterTexture, i*TileSize, j*TileSize);
			} else{
				DrawTexture(&grassTexture, i*TileSize, j*TileSize);
			}
		}
	}

	DrawTexture(&goalTexture, goal.x*TileSize, goal.y*TileSize);
	if(searching){
		for each (shared_ptr<PlayerState> state in visited){
			DrawTexture(&playerTexture, state->player->x*TileSize, state->player->y*TileSize);
		}
	} else{
		shared_ptr<PlayerState> temp = winningState;
		while(temp != first){
			DrawTexture(&playerTexture, temp->player->x*TileSize, temp->player->y*TileSize);
			temp = temp->parentState;
		}
	}
}