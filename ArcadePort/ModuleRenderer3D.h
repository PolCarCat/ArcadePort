#pragma once
#include "Module.h"
#include "Globals.h"


#include <list>
#include <vector>





class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();



public:


	SDL_GLContext context;



};