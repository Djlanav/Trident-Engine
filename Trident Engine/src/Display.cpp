#include "Plugins/imgui/imgui.h"
#include "Plugins/imgui/imgui_impl_glfw.h"
#include "Plugins/imgui/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "Core/Typedefs.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/Rendering.h"
#include "Core/Display.h"

void framebuffer_size_call_back(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

CDisplay::CDisplay(const String& DisplayTitle, int32 DisplayWidth, int32 DisplayHeight)
{
	ELogStatus glfwStatus;

	if (!glfwInit())
	{
		std::exit(-1);
	}
	else
	{
		glfwStatus = SUCCESS;
		this->DisplayTitle = DisplayTitle;
		this->DisplayHeight = DisplayHeight;
		this->DisplayWidth = DisplayWidth;

		CLogger::Log("GLFW Init Status:", &glfwStatus, nullptr);
	}
}

void CDisplay::SetGlfwHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void CDisplay::CreateDisplay()
{
	ELogStatus windowStatus;

	SetGlfwHints();

	window = glfwCreateWindow(DisplayWidth, DisplayHeight, DisplayTitle.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::exit(-1);
	}
	else
	{
		windowStatus = SUCCESS;
		CLogger::Log("Window Creation Status:", &windowStatus, nullptr);
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	LoadGLAD();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_call_back);
}

void CDisplay::LoadGLAD()
{
	ELogStatus gladStatus;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		gladStatus = FAILURE;
		CLogger::Log("GLAD Status:", &gladStatus, nullptr);
	}
	else
	{
		gladStatus = SUCCESS;
		CLogger::Log("GLAD Status:", &gladStatus, nullptr);
	}
}

GLFWwindow* CDisplay::GetWindow()
{
	return window;
}