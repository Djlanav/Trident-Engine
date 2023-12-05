#pragma once

class CRenderer;
struct GLFWwindow;

class CDisplay
{
private:
	GLFWwindow* window;

	String DisplayTitle;
	int32 DisplayWidth;
	int32 DisplayHeight;

private:
	void SetGlfwHints();

public:
	CDisplay();
	CDisplay(const String& DisplayTitle, int32 DisplayWidth, int32 DisplayHeight);

	void CreateDisplay();
	void LoadGLAD();
	
	GLFWwindow* GetWindow();
};