#ifndef __MAP_H__
#define __MAP_H__


#include <random>
#include <vector>
#include <cassert>

#include "cell.h"


const size_t MAX_WIDTH  = 512;
const size_t MAX_HEIGHT = 512;

// template <size_t N>
// using Vector = Matrix<N, 1>;


using Stategrid = std::vector<std::vector<std::vector<size_t> > >;


class Map {
public:
	Map(size_t x, size_t y) : x_dim(x), y_dim(y) {
		assert(x <= MAX_WIDTH && x > 0);
		assert(y <= MAX_HEIGHT && y > 0);

		for (size_t i = 0; i < x*y; ++i) {
			map.emplace_back(Cell(255*3, 3, fitness, mutations, rng));
		}
	}

	Stategrid get_state();

	void next();

private:
	size_t x_dim;
	size_t y_dim;

	std::vector<Cell> map;

	std::mt19937 rng;
	std::vector<double> fitness{1, 2, 3};
	std::vector<std::vector<double>> mutations{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
};

#endif