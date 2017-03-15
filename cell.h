#ifndef __CELL_H__
#define __CELL_H__


#include <random>
#include <vector>


enum class GEOGRAPHY {
	N,
	E,
	S,
	W
};


class Cell {
public:
	Cell(
		  size_t N
		, size_t n_types
		, const std::vector<double> &fitness
		, const std::vector<std::vector<double>> &mutations
		, std::mt19937 &rng) 
		: N(N), n_types(n_types), fitness(fitness), mutations(mutations), rng(rng) {
		n_types = fitness.size();
		state = std::vector<size_t> (n_types, N/n_types);
		part = std::vector<std::vector<size_t>> (4, std::vector<size_t> (n_types, 0));
	}

	void next();

	void partition();

	void recombine();

	friend void mix(Cell &, Cell &, GEOGRAPHY);

private:
	size_t N;
	size_t n_types;
	const std::vector<double> &fitness;
	const std::vector<std::vector<double>> &mutations;
	std::mt19937 &rng;

	std::vector<size_t> state;
	std::vector<std::vector<size_t>> part;
};


#endif