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
	virtual void Render();

	virtual void CleanUpUI();

	virtual void AddFloatUIElement(const String& Name, float* Element);
	virtual void AddIntegerUIElement(const String& Name, uint32* Element);

	virtual FPMap* GetFloatUIElements();
	virtual UIPMap* GetUnsignedUIElements();

	virtual void SetFloatUIElements(FPMap* Map);
	virtual void SetUnsignedUIElements(UIPMap* Map);

	virtual String* OpenFileDialog(GLFWwindow* window);
	virtual void SetFileRetrieved(String* retrieved);
	virtual String* GetFileDialogResult();

public: // ImGUI interfacing
	virtual void UIBegin(const String& WindowName);

	virtual bool UIButton(const String& Text);

	virtual void UIEnd();
};

// ** Normal Functions**
extern "C"
{
	ENGINEUI_API CEngineUI* createUI();
}