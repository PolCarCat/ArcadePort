#include "WinConfig.h"
#include "Application.h"
#include "ImGui/imgui.h"

WinConfig::WinConfig(Application* parent, bool start_enabled) : WinBase(parent, start_enabled) 
{
};

WinConfig::~WinConfig()
{
}

bool WinConfig::Update()
{
	ImGui::Begin("Configuration");


	ImGui::End();

	return true;
}

