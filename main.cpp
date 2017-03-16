#include <iostream>
#include <memory>
#include <tclap/CmdLine.h>
#include "SDL.h"

#include "map.h"
#include "mapdrawer.h"
#include "cell.h"


using namespace std;


const char * VERSION {"1.0.0"};


struct Arguments {
	double mix;
	vector<double> fitness;
	int dim;
};


int main(int argc, char **argv) {
	Arguments a;
	try {

		TCLAP::CmdLine cmd("Moran-automaton", ' ', VERSION);
		TCLAP::ValueArg<double> a_mix("m", "mixing-probability", "Chance that a member goes from one cell to another", false, 0.001, "positive floating point", cmd);
		TCLAP::ValueArg<double> a_g("g", "green-fitness", "Fitness value for green cells", false, 1, "positive floating point", cmd);
		TCLAP::ValueArg<double> a_r("r", "red-fitness", "Fitness value for red cells", false, 1, "positive floating point", cmd);
		TCLAP::ValueArg<double> a_b("b", "blue-fitness", "Fitness value for blue cells", false, 1, "positive floating point", cmd);
		TCLAP::ValueArg<int> a_dim("d", "dimension", "Size of cell grid", false, 32, "positive integer", cmd);
		
		cmd.parse(argc, argv);

		a.mix = a_mix.getValue();
		a.fitness = vector<double> {a_r.getValue(), a_g.getValue(), a_b.getValue()};
		a.dim = a_dim.getValue();

	} catch (TCLAP::ArgException &e) {
		cerr << "TCLAP Error: " << e.error() << endl << "\targ: " << e.argId() << endl;
		return 1;
	}

	cout << "Parsed arguments:" << endl;
	cout << "\tmixing probability: " << a.mix << endl;
	cout << "\tfitness: " << a.fitness[0] << ' ' << a.fitness[1] << ' ' << a.fitness[2] << endl;

	int z = a.dim;

	Map m(z, z, a.fitness, a.mix);
	MapDrawer md(9*z + 1, 9*z + 1);
	md.init();

	SDL_Event e;

	int frameskip = 1;
	bool run = true;
	int i = 0;
	while (run) {

		cout << "begin run" << endl;

		m.next();

		cout << "next done" << endl;

		if (i % frameskip == 0) {
			auto s = m.get_state();
			md.draw(s);

			cout << "draw done" << endl;
			// cout << "iteration " << i << endl;
			// i = 0;
		}

		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) { 
				run = false;
			}
		}
		++i;

		cout << "events done" << endl;
	}

	md.exit();
}