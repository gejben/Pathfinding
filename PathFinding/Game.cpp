#include "Game.hpp"
#include "Graphics.hpp"
#include <random>
#include <vector>
#include <memory>

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
	int x;
	int y;
} playerStart;

struct PlayerState{
	shared_ptr<Player> player;
	shared_ptr<Player> parentPlayer;
};

shared_ptr<PlayerState> winningState;

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


	shared_ptr<PlayerState> first = make_shared<PlayerState>();
	first->player = make_shared<Player>(playerStart);
	open.push_back(first);

	return true;
}

static void testDirection(int x, int y, shared_ptr<Player> player){
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
		newState->parentPlayer = player;
		open.push_back(newState);
		visited.push_back(newState);
	}
}

static void checkSurrounding(shared_ptr<Player> player){
	int x, y;
	x = player->x - 1;
	y = player->y;
	if(map[x][y] == GRASS){
		testDirection(x, y, player);
	}


	x = player->x;
	y = player->y - 1;
	if(map[x][y] == GRASS){
		testDirection(x, y, player);
	}

	x = player->x + 1;
	y = player->y;
	if(map[x][y] == GRASS){
		testDirection(x, y, player);
	}

	x = player->x;
	y = player->y + 1;
	if(map[x][y] == GRASS){
		testDirection(x, y, player);
	}
}

void game_update() {
	if(searching && open.size() > 0){
			shared_ptr<PlayerState> pState = open.at(0);
			open.erase(open.begin());
			checkSurrounding(pState->player);
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
	for each (shared_ptr<PlayerState> state in visited){
		DrawTexture(&playerTexture, state->player->x*TileSize, state->player->y*TileSize);
	}
}