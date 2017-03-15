#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__


#include "map.h"


const size_t MAX_WDW_WIDTH  = 512;
const size_t MAX_WDW_HEIGHT = 512;


class MapDrawer {
public:
	MapDrawer(size_t x, size_t y) : width(x), height(y) {
		assert(x <= MAX_WDW_WIDTH && x > 0);
		assert(y <= MAX_WDW_HEIGHT && y > 0);
	}

	void update(Stategrid);
private:
	size_t width;
	size_t height;
};


#endif