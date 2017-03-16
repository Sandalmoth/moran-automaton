#ifndef __MAP_H__
#define __MAP_H__


#include <random>
#include <vector>
#include <cassert>
#include <iostream>

#include "cell.h"


const size_t MAX_WIDTH  = 512;
const size_t MAX_HEIGHT = 512;

// template <size_t N>
// using Vector = Matrix<N, 1>;


using Stategrid = std::vector<std::vector<std::vector<size_t> > >;


class Map {
public:
	Map(size_t x, size_t y, std::vector<double> fitness, double mixing_probability) 
		: x_dim(x)
		, y_dim(y)
		, fitness(fitness)
		, mixing_probability(mixing_probability) {
		assert(x <= MAX_WIDTH && x > 0);
		assert(y <= MAX_HEIGHT && y > 0);

		for (size_t i = 0; i < x*y; ++i) {
			map.emplace_back(Cell(pop_per_cell, 3, fitness, mutations, rng));
		}

		std::random_device device;
		rng.seed(device());


		// std::cout << "\tmixing probability: " << mixing_probability << std::endl;
		// std::cout << "\tfitness: " << fitness[0] << ' ' << fitness[1] << ' ' << fitness[2] << std::endl;
	}

	Stategrid get_state();

	void next();

private:
	size_t x_dim;
	size_t y_dim;

	std::vector<Cell> map;

	std::mt19937 rng;
	std::vector<double> fitness;
	std::vector<std::vector<double>> mutations{{200, 10, 10}, {10, 200, 10}, {10, 10, 200}};

	size_t pop_per_cell = 3*4*10;
	double mixing_probability;
};

#endif