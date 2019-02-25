#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleGui.h"
#include <list>

using namespace std;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleGui* imgui;



public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();


private:

	float	dt;
	list<Module*> list_modules;



private:

	void AddModule(Module* mod);


};