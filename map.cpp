#include "map.h"

#include <iostream>


using namespace std;


Stategrid Map::get_state() {
	Stategrid s;

	for (int x = 0; (size_t)x < x_dim; ++x) {
		std::vector<std::vector<size_t> > t;
		for (int y = 0; (size_t)y < y_dim; ++y) {
			t.push_back(map[x + y*x_dim].get_state());
		}
		s.push_back(t);
	}

	return s;
}


void Map::next() {

	// cout << "1" << endl;

	for (auto &cell: map) {
		cell.next();
	}
	
	// cout << "2" << endl;

	for (auto &cell: map) {
		cell.partition();
	}
	
	// cout << "3" << endl;

	auto d = binomial_distribution<int>(pop_per_cell/4, 0.01);

	for (int x = 0; (size_t)x < x_dim; ++x) {
		for (int y = 0; (size_t)y < y_dim; ++y) {
			int y_below = (y + 1) % y_dim;
			int x_right = (x + 1) % x_dim;

			mix(map[x + y*x_dim], map[x + y_below*x_dim], GEOGRAPHY::N, d(rng));
			mix(map[x + y*x_dim], map[x_right + y*x_dim], GEOGRAPHY::W, d(rng));
		}			
	}
	
	// cout << "4" << endl;

	for (auto &cell: map) {
		cell.recombine();
	}
	
	// cout << "5\n";
}