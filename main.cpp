#include <iostream>
#include <memory>
#include <tclap/CmdLine.h>

#include "map.h"
#include "mapdrawer.h"
#include "cell.h"


using namespace std;


const char * VERSION {"0.0.1"};


struct Arguments {
};


int main() {
	// Arguments a;
	try {
		TCLAP::CmdLine cmd("Moran-automaton", ' ', VERSION);
		// TCLAP::ValueArg<string> a_input("i", "input", "Path to input file", true, "__invalid__", "~/somewhere/filename.hdf5", cmd);
		// TCLAP::ValueArg<string> a_output("o", "output", "Path for output file (overwrites existing)", false, "./out.hdf5", "~/somewhere/filename.hdf5", cmd);
		// TCLAP::ValueArg<string> a_ssave("s", "save", "Path for probability file (overwrites existing)", false, "./s.hdf5", "~/somewhere/filename.hdf5", cmd);
		// TCLAP::ValueArg<string> a_sload("l", "load", "Path for probability file to be loaded", false, "__invalid__", "~/somewhere/filename.hdf5", cmd);
		// TCLAP::ValueArg<unsigned long> a_manual_seed("e", "rng-seed", "Provide the seed manually", false, 0, "integer", cmd);
  //       TCLAP::SwitchArg a_useseed("r", "use-input-seed", "Use rng seed in input file rather than std::random_device", cmd, false);
		// TCLAP::SwitchArg a_outname_seed("m", "outname-seed", "Adds the rng-seed used to the output filename", cmd, false);

		// cmd.parse(argc, argv);

		// // Place in convenient container
		// a.input_filename = a_input.getValue();
		// a.output_filename = a_output.getValue();

		// if (a_ssave.isSet() && a_sload.isSet()) throw TCLAP::ArgException("Simultaneous saving and loading a probability file is disallowed");
		// if (a_ssave.isSet()) {
		// 	a.s_option = "save";
		// 	a.s_filename = a_ssave.getValue();
		// } else if (a_sload.isSet()) {
		// 	a.s_option = "load";
		// 	a.s_filename = a_sload.getValue();
		// } else {
		// 	a.s_option = "generate";
		// }

  //       if (a_manual_seed.isSet()) {
  //           a.manual_seed = a_manual_seed.getValue();
  //           a.use_manual_seed = true;
  //       }

		// a.use_input_seed = a_useseed.getValue();
		// a.outname_seed = a_outname_seed.getValue();

	} catch (TCLAP::ArgException &e) {
		cerr << "TCLAP Error: " << e.error() << endl << "\targ: " << e.argId() << endl;
		return 1;
	}

	Map m(16, 16);
	MapDrawer md(512, 512);
	md.update(m.get_state());
	for (int i = 0; i < 100; ++i) {
		m.next();
	}
}