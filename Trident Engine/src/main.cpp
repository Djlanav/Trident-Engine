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
#include "Core/Rendering.h"
#include "Core/Display.h"
#include "Core/Engine.h"

// Entry point
int main()
{
	CEditorUI EditorUI;
	CLoader Loader;
	CDisplay Display("Trident Engine (OpenGL 4.5)", 1024, 780);

	CRenderer Renderer(Display, Loader, EditorUI);

	CEngine TridentEngine(Renderer);

	TridentEngine.MakeUIFloats();

	while (!glfwWindowShouldClose(Display.GetWindow()))
	{
		TridentEngine.Update();

		glfwSwapBuffers(Display.GetWindow());
		glfwPollEvents();
	}

	TridentEngine.Close();

	glfwTerminate();
	return 0;
}