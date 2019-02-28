#include "ModuleGui.h"
#include "Application.h"
#include <gl/GL.h>
#include <windows.h>


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl2.h"

ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGui::~ModuleGui()
{
}


bool ModuleGui::Start()
{
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL2_Init();


	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	

	char buf[256];
	GetCurrentDirectoryA(256, buf);
	directory = std::string(buf) + '\\';

	Game* test1 = new Game();
	test1->name = "Parallax Paradox";
	test1->description = "2D Plataformer";
	test1->directory = "Games\\ParallaxParadox\\ParallaxParadox.exe";

	games.push_back(test1);

	Game* test2 = new Game();
	test2->name = "Other boring game";
	test2->description = "meh";
	test2->directory = "xdd/arallax Paradox.exe";

	games.push_back(test2);

	Game* test3 = new Game();
	test3->name = "Other boring game";
	test3->description = "meh";
	test3->directory = "xdd/arallax Paradox.exe";

	games.push_back(test3);


	test1->focus = true;

	return true;
}

update_status ModuleGui::PreUpdate(float dt)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();



	UpdateDockSpace();
	ShowMenuBar();

	UpdateInput();
	UpdateMainWindow();

	for (uint i = 0; i < 135; i++)
	{
		if (App->input->GetKey(i))
		{
			currKey = std::to_string(i);
			break;
		}
	}


	return UPDATE_CONTINUE;
}



update_status ModuleGui::Update(float dt)
{
	return UPDATE_CONTINUE;
}


update_status ModuleGui::PostUpdate(float dt)
{
	update_status status = UPDATE_CONTINUE;

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	if (quit)
		status = UPDATE_STOP;

	return status;
}

bool ModuleGui::CleanUp()
{
	//ImGui_ImplSdl_Shutdown();

	VSLOG("Cleaning UP IMGUI Module")
		bool ret = true;

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}



void ModuleGui::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Text("Hello");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}


void ModuleGui::UpdateDockSpace()
{
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;



	if (opt_flags & ImGuiDockNodeFlags_RenderWindowBg)
		ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool b = true;
	ImGui::Begin("DockSpace Demo", &b, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);


	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}

	opt_flags |= ImGuiDockNodeFlags_PassthruInEmptyNodes;
	opt_flags |= ImGuiDockNodeFlags_RenderWindowBg;



	ImGui::End();
}

void ModuleGui::UpdateMainWindow()
{
	ImGui::Begin("");
	//Returns true if an objcet has been clicked
	bool ret = false;
	int n = 0;

	for (std::list<Game*>::iterator item = games.begin(); item != games.end(); item++)
	{
		ImGui::PushID(n);

		Game* game = *item;

		//Change color for selected item
		if (game->focus)
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));

		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

		ImGui::TreeNodeEx(game->name.c_str(), node_flags);


		//Reset color
		if (game->focus)
			ImGui::PopStyleColor();


		if (ImGui::IsItemClicked())
		{
			VSLOG("2");
		}


		ImGui::PopID();
		n++;
	}

	ImGui::Separator();

	ImGui::Text(currKey.c_str());

	ImGui::End();

}

void ModuleGui::ReadInput(SDL_Event * e) const
{
	ImGui_ImplSDL2_ProcessEvent(e);
}

void ModuleGui::UpdateInput()
{

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		SwitchFocusDown();

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		SwitchFocusUp();
	

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		ExecuteFocus();

}

void ModuleGui::SwitchFocusDown()
{

	for (std::list<Game*>::iterator item = games.begin(); item != games.end();)
	{
		if ((*item)->focus)
		{
			(*item)->focus = false;

			item++;

			if (item == games.end())
				(*games.front()).focus = true;
			else
				(*item)->focus = true;

			break;
		}
		else
			item++;
	}

}

void ModuleGui::SwitchFocusUp()
{
	for (std::list<Game*>::iterator item = games.begin(); item != games.end();)
	{
		if ((*item)->focus)
		{
			(*item)->focus = false;


			if (item == games.begin())
				(*--games.end())->focus = true;
			else
				(*--item)->focus = true;

			break;
		}
		else
			item++;
	}
}

void ModuleGui::ExecuteFocus()
{
	Game* game = nullptr;

	for (std::list<Game*>::iterator item = games.begin(); item != games.end(); item++)
	{
		if ((*item)->focus)
		{
			game = (*item);
			break;
		}
	}

	if (game != nullptr)
	{				
	ShellExecute(NULL, "open", (directory + game->directory).c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}
}
