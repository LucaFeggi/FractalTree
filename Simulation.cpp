#include "Simulation.hpp"
#include "DrawingFunctions.hpp"

#include <iostream>
#include <cmath>

inline int SDL_GetWindowRefreshRate(SDL_Window *Window){
    SDL_DisplayMode Mode;
    int DisplayIndex = SDL_GetWindowDisplayIndex(Window);
    int DefaultRefreshRate = 60;
    if(SDL_GetDesktopDisplayMode(DisplayIndex, &Mode) != 0){
        return DefaultRefreshRate;
    }
    if(Mode.refresh_rate == 0){
        return DefaultRefreshRate;
    }
    return Mode.refresh_rate;
}

Simulation::Simulation() : WindowWidth(1280), WindowHeight(720), SmallestBranchDimension(1){
	SDL_Init(SDL_INIT_VIDEO);
	Window = SDL_CreateWindow("Fractal Tree", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	Surface = SDL_GetWindowSurface(Window);
	FPS = SDL_GetWindowRefreshRate(Window);
	Quit = false;
	Angle = M_PI/3.0f;
	this->CreateTree();
	SDL_UpdateWindowSurface(Window);
}

Simulation::~Simulation(){
	SDL_FreeSurface(Surface);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void Simulation::GetCommands(){
	while(SDL_WaitEvent(&Event)){
		if(Event.type == SDL_QUIT){
			Quit = true;
			break;
		}
		if(Event.key.state == SDL_PRESSED){
			if(Event.key.keysym.sym == SDLK_ESCAPE){
				Quit = true;
				break;
			}
		}
		if(Event.type == SDL_MOUSEWHEEL){
			if(Event.wheel.y > 0){	//scroll up
				Angle += 0.01f;
			}
			else if(Event.wheel.y < 0){	//scroll down
				Angle -= 0.01f;
			}
			if(Angle > 2*M_PI)
				Angle = Angle/(2*M_PI) - 1.0f;
			if(Angle < -(2*M_PI))
				Angle = -Angle/(2*M_PI) - 1.0f;
			this->ClearSurface();
			this->CreateTree();
			SDL_UpdateWindowSurface(Window);
		}
	}
}

void Simulation::CreateBranch(Branch ParentBranch, float Length, float Alfa, float Beta){
	if(Length < SmallestBranchDimension)
		return;
	Branch ThisBranch(ParentBranch.x, ParentBranch.y, Length, Alfa);
	DrawLine(ParentBranch.x, ParentBranch.y, ThisBranch.x, ThisBranch.y, Surface, WindowWidth, White);
	this->CreateBranch(ThisBranch, Length*0.67f, Alfa-Beta, Beta);
	this->CreateBranch(ThisBranch, Length*0.67f, Alfa-Beta, -Beta);
}

void Simulation::CreateTree(){
	float InitialLength = WindowHeight/5;
	int InitialX = WindowWidth/2;
	int InitialY = WindowHeight*2/3;
	Branch FirstBranch(InitialX, InitialY, InitialLength, 0.0f);
	DrawLine(InitialX, InitialY, FirstBranch.x, FirstBranch.y, Surface, WindowWidth, White);
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(j == 0 || (i == 0 && j == 0))
				continue;
			this->CreateBranch(FirstBranch, InitialLength*0.67f, i*Angle, j*Angle/2.0f);
		}
	}
}

void Simulation::ClearSurface(){
	SDL_FillRect(Surface, NULL, 0x000000);
}

void Simulation::Cycle(){
	while (!Quit){
		double IterationStart = SDL_GetPerformanceCounter();
		this->GetCommands();
		if(Quit)
			break;
		double IterationEnd = SDL_GetPerformanceCounter();
		double ElapsedSeconds = (IterationEnd-IterationStart) / (double)SDL_GetPerformanceFrequency();
		double Delay =  (1000.0/(double)FPS) - (ElapsedSeconds*1000.0);
		if(Delay > 0)
			SDL_Delay(std::max(0, (int)round(Delay)));
	}
}
