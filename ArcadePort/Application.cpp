#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);

	renderer3D = new ModuleRenderer3D(this);
	imgui = new ModuleGui(this);
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(input);
	AddModule(imgui);


	// Renderer last!
	AddModule(renderer3D);



}

Application::~Application()
{
	for (list<Module*>::reverse_iterator it = list_modules.rbegin(); !list_modules.empty() && it != list_modules.rend(); ++it)
		delete (*it);

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && ret; ++it)
		ret = (*it)->Init();

	// After all Init calls we call Start() in all modules

	VSLOG("Application Start --------------");
	
	for (list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && ret; ++it)
		ret = (*it)->Start();



	return ret;
}



// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate(dt);

	for (list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update(dt);

	for (list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate(dt);

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = list_modules.rbegin(); !list_modules.empty() && it != list_modules.rend(); ++it)
		ret = (*it)->CleanUp();

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

