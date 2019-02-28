#pragma once
#include "Module.h"
#include "Globals.h"
#include <list>
#include <string>


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl2.h"

class Game
{

public:
	std::string name;
	std::string directory;
	std::string description;

	bool focus = false;
};

class ModuleGui :
	public Module
{
public:
	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

	bool Start();

	update_status PreUpdate(float dt);

	update_status Update(float dt);

	update_status PostUpdate(float dt);

	bool CleanUp();
	void ShowMenuBar();
	void UpdateDockSpace();
	void UpdateMainWindow();
	void ReadInput(SDL_Event * e) const;
	void UpdateInput();


private:
	bool quit = false;
	std::list<Game*> games;

	void SwitchFocusDown();
	void SwitchFocusUp();
	void ExecuteFocus();

	std::string directory;
	std::string currKey;

};