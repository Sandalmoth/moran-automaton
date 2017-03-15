#include "map.h"


using namespace std;


Stategrid Map::get_state() {
	return Stategrid();
}


void Map::next() {
	for (auto &cell: map) {
		cell.next();
		cell.partition();

		for (int x = 0; (size_t)x < x_dim; ++x) {
			for (int y = 0; (size_t)x < y_dim; ++y) {
				y_below = (y - 1) % y_dim;
				x_right = (x - 1) % x_dim;
			}			
		}

		cell.recombine();
	}
}