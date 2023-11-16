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
#include "Core/MainEngineUI.h"
#include "Core/EngineUI/EngineUIFunctionPointers.h"
#include "Core/Rendering.h"
#include "Core/Display.h"
#include "Core/Engine.h"

int main()
{
	CLoader Loader;
	CDisplay Display("Trident Engine (OpenGL 4.5)", 1024, 780);
	CRenderer Renderer(&Display, &Loader);

	CEngine TridentEngine;
	TridentEngine.InitCore(&Renderer, &Display);

	CEngineUI* engineUI = TridentEngine.createEngineUI();
	TridentEngine.MakeUIFloats(engineUI);
	Renderer.SetUI(engineUI);

	while (!glfwWindowShouldClose(Display.GetWindow()))
	{
		TridentEngine.Update(engineUI);

		glfwSwapBuffers(Display.GetWindow());
		glfwPollEvents();
	}

	TridentEngine.Close(engineUI);

	glfwTerminate();
	return 0;
}