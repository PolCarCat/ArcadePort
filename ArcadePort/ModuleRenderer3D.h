#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

#include <list>
#include <vector>



#define MAX_LIGHTS 8



class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	void OnResize(int width, int height);


public:


	SDL_GLContext context;



};