#include "mapdrawer.h"

#include <iostream>
#include <cmath>
#include <algorithm>


using namespace std;


void MapDrawer::init() {
	SDL_Init(SDL_INIT_VIDEO);
	 window = SDL_CreateWindow( 
	 	  "moran-automaton"
	 	  , SDL_WINDOWPOS_UNDEFINED
	 	  , SDL_WINDOWPOS_UNDEFINED
	 	  , width
	 	  , height
	 	  , SDL_WINDOW_SHOWN );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if (renderer) cout << "Renderer created successfully" << endl;
}


void MapDrawer::exit() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void MapDrawer::draw(Stategrid s) {
	// surf = SDL_GetWindowSurface(window);
	// SDL_FillRect(surf, nullptr, SDL_MapRGB(surf->format, 0, 0, 0));
	// SDL_UpdateWindowSurface(window);

	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF); 
	SDL_RenderClear(renderer);

	for (int x = 0; (size_t)x < s.size(); ++x) {
		for (int y = 0; (size_t)y < s[x].size(); ++y) {
			SDL_Rect rx = {1 + x*9, 1 + y*9, 8, 8};
			double r = s[x][y][0] / 1200.0 * 256.0;
			double g = s[x][y][1] / 1200.0 * 256.0;
			double b = s[x][y][2] / 1200.0 * 256.0;
			// cout << r << '\t' << g << '\t' << b << endl;
			SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
			SDL_RenderFillRect(renderer, &rx);
		}
	}

	SDL_RenderPresent( renderer );
}


void MapDrawer::print(Stategrid s) {
	double sm = std::accumulate(s[0][0].begin(), s[0][0].end(), 0.0);
	for (auto x: s) {
		for (auto y: x) {
			cout << - log2(y[0]/sm)*y[0]/sm - log2(y[1]/sm)*y[1]/sm - log2(y[2]/sm)*y[2]/sm << ' ';
		}
		cout << endl;
	}
	cout << endl;
}