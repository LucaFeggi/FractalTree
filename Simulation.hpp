#pragma once

#include "Branch.hpp"

#include <SDL.h>

class Simulation{
	public:
		Simulation();
		~Simulation();
		void GetCommands();
		void CreateTree();
		void CreateBranch(Branch ParentBranch, float Length, float Alfa, float Beta);
		void ClearSurface();
		void Cycle();
	private:
		const int WindowWidth, WindowHeight;
		const int SmallestBranchDimension;
		int FPS;
		SDL_Window *Window = nullptr;
		SDL_Surface *Surface = nullptr;
		SDL_Event Event;
		bool Quit;
		float Angle;
};
