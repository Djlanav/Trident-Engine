#include "Core/CommonHeaders.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/EditorUI.h"
#include "Core/Display.h"
#include "Core/Rendering.h"
#include "Core/Engine.h"

CEngine::CEngine(CRenderer& Renderer)
	: EngineRenderer(Renderer), EngineLoader(EngineRenderer.GetLoader()), EngineShaderProgram(EngineRenderer.GetShaderProgram())
{
	EngineDisplay.CreateDisplay();

	EngineRenderer.InitializeMeshData();
	EngineMesh = EngineLoader.LoadMeshFromVao(EngineRenderer.GetMeshData());

	EngineRenderer.InitializeShaders();
}

void CEngine::MakeUIFloats()
{
	EditorUI.InitializeIMGUI(EngineDisplay.GetWindow());

	std::shared_ptr<float[]> color(new float[4]);
	color[0] = 0.4f;
	color[1] = 0.6f;
	color[2] = 0.3f;
	color[3] = 1.0f;

	FloatPointerContainer.AddToBuffer("ColorData", color);
	EditorUI.AddFloatUIElement("Color", color);
}

TUIDataContainer<std::shared_ptr<float[]>>& CEngine::GetFloatPointerContainer()
{
	return FloatPointerContainer;
}

void CEngine::ProccessInput(GLFWwindow* Window)
{
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, true);
	}
	else if (glfwGetKey(Window, GLFW_KEY_R) == GLFW_PRESS)
	{
		EngineRenderer.SetIsWireframeEnabled(true);
	}
	else if (glfwGetKey(Window, GLFW_KEY_T) == GLFW_PRESS)
	{
		EngineRenderer.SetIsWireframeEnabled(false);
	}
}

void CEngine::Update()
{
	std::shared_ptr<float[]> color = FloatPointerContainer.GetDataFromBuffer("ColorData");

	ProccessInput(EngineDisplay.GetWindow());

	EditorUI.CreateUIFrame();
	EngineRenderer.ClearScreen();

	EngineShaderProgram.StartShaderProgram();
	EngineShaderProgram.SetFourVectorUniform("uniform_color",
			color[0],
			color[1],
			color[2],
			color[3]
		);
	
	EngineRenderer.Render(EngineMesh);
	EngineRenderer.Interface();
	EditorUI.Render();

	EngineShaderProgram.StopShaderProgram();
}

void CEngine::Close()
{
	EngineRenderer.GetShaderProgram().CleanShaderProgram();
	EngineLoader.CleanUp();

	EditorUI.CleanUpUI();

	// Free All DLLs
	FreeAll();
}