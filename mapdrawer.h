#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__


#include "SDL.h"

#include "map.h"


const size_t MAX_WDW_WIDTH  = 2048;
const size_t MAX_WDW_HEIGHT = 2048;


class MapDrawer {
public:
	MapDrawer(size_t x, size_t y) : width(x), height(y) {
		assert(x <= MAX_WDW_WIDTH && x > 0);
		assert(y <= MAX_WDW_HEIGHT && y > 0);
	}

	void init();
	void exit();

	void draw(Stategrid);
	void print(Stategrid);
private:
	size_t width;
	size_t height;

	SDL_Window* window = nullptr;
	SDL_Surface *surf = nullptr;
	SDL_Renderer* renderer = nullptr;
};


#endif