#ifdef ENGINEUI_EXPORTS
#define ENGINEUI_API __declspec(dllexport)
#else
#define ENGINEUI_API __declspec(dllimport)
#endif

typedef std::unordered_map<String, float*> FPMap;
typedef std::unordered_map<String, uint32*> UIPMap;

class ENGINEUI_API CEngineUI
{
private:
	FPMap* FloatUIElements;
	UIPMap* UnsignedIntegerUIElements;
	String* FileRetrieved;

public:
	virtual void InitializeIMGUI(GLFWwindow* window);

	virtual void CreateUIFrame();
	virtual void Render(const String& Name, GLFWwindow* window);

	virtual void CleanUpUI();

	virtual void AddFloatUIElement(const String& Name, float* Element);
	virtual void AddIntegerUIElement(const String& Name, uint32* Element);

	virtual FPMap* GetFloatUIElements();
	virtual UIPMap* GetUnsignedUIElements();

	virtual void SetFloatUIElements(FPMap* Map);
	virtual void SetUnsignedUIElements(UIPMap* Map);

	virtual String* GetFileDialogResult();

public: // ImGUI interfacing
	virtual void BeginImGUI(const String& WindowName);

	virtual void AddTextIMGUI(const String& Text, ...);

	virtual void EndImGUI();

private:
	virtual String* OpenFileDialog(GLFWwindow* window);
};

// ** Normal Functions**
extern "C"
{
	ENGINEUI_API CEngineUI* createUI();
}