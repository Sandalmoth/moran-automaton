#include "cell.h"

#include <iostream>

#include "multinomial.h"


using namespace std;



std::vector<size_t> Cell::get_state() {
	return state;
}


void Cell::next() {
	// cout << "HERE" << endl;
	// Reproduce a member based on fitness
	vector<double> plist;
	for (size_t i = 0; i < fitness.size(); ++i) {
		plist.push_back(fitness[i] * state[i] * state[i]);
	}
	// cout << "GOT PLIST" << endl;
	discrete_distribution<int> d(plist.begin(), plist.end());
	auto repr_t = d(rng);
	// cout << "REPR " << repr_t << endl;
	++state[repr_t];
	// Kill a random member
	discrete_distribution<int> d2(state.begin(), state.end());
	auto death_t = d2(rng);
	// cout << "DEATH " << death_t << endl;
	--state[death_t];
}


// This function is probably super slow. fix sometime. maybe.
void Cell::partition() {
	// uniform_int_distribution<int> cardinal(0, 3);
	// part = std::vector<std::vector<size_t>> (4, std::vector<size_t> (n_types, 0));
	// for (size_t i = 0; i < n_types; ++i) {
	// 	// cout << state[0] << '\t' << state[1] << '\t' << state[2] << endl;
	// 	for (size_t j = 0; j < state[i]; ++j) {
	// 		++part[cardinal(rng)][i];
	// 	}
	// }

	part = std::vector<std::vector<size_t>> (4, std::vector<size_t> (n_types, 0));

	cout << "2-1" << endl;

	for (size_t i = 0; i < n_types; ++i) {

		cout << "2-" << i+2 << endl;

		multinomial_distribution<int> d(state[i], vector<double>(4, 1.5));
		auto t = d(rng);

		cout << state[i] << ' ' << t[0] << ' ' << t[1] << ' ' << t[2] << ' ' << t[3] << ' ' << endl;

		for (int j = 0; j < 4; ++j) {
			cout << i << ' ' << j << endl;
			part[j][i] = t[j];
		}
	}
}


void Cell::recombine() {
	state = std::vector<size_t> (n_types, 0);
	for (size_t i = 0; i < n_types; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			state[i] += part[j][i];
		}
	}
}


void mix(Cell &a, Cell &b, GEOGRAPHY a_is_to_b, int mix_count) {
	int a_c, b_c; //Index of relevant cardinal direction partitions
	switch (a_is_to_b) {
		default:
			case GEOGRAPHY::N:
				a_c = 2;
				b_c = 0;
				break;
			case GEOGRAPHY::E:
				a_c = 3;
				b_c = 1;
				break;
			case GEOGRAPHY::S:
				a_c = 0;
				b_c = 2;
				break;
			case GEOGRAPHY::W:
				a_c = 1;
				b_c = 3;
				break;
			throw "Unknown cell relationship";
	}

	// Mix
	while (mix_count >0) {
		int a_choice = discrete_distribution<int>(a.part[a_c].begin(), a.part[a_c].end())(a.rng);
		int b_choice = discrete_distribution<int>(b.part[b_c].begin(), b.part[b_c].end())(b.rng);

		if (a.part[a_c][a_choice] == 0) continue;
		if (b.part[b_c][b_choice] == 0) continue;

		++a.part[a_c][b_choice];
		--a.part[a_c][a_choice];
		++b.part[b_c][a_choice];
		--b.part[b_c][b_choice];

		--mix_count;
	}
}