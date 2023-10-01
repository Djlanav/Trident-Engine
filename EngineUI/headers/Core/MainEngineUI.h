#ifdef ENGINEUI_EXPORTS
#define ENGINEUI_API __declspec(dllexport)
#else
#define ENGINEUI_API __declspec(dllimport)
#endif

typedef std::unordered_map<String, float*> FPMap;
typedef std::unordered_map<String, uint32*> UIPMap;

class ENGINEUI_API CUI
{
public:
	virtual void InitializeIMGUI(GLFWwindow* window) = 0;

	virtual void CreateUIFrame() = 0;

	virtual void Render(const String& Name) = 0;

	virtual void CleanUpUI() = 0;
};

class ENGINEUI_API CEngineUI : public CUI 
{
private:
	FPMap* FloatUIElements;
	UIPMap* UnsignedIntegerUIElements;

public:
	void InitializeIMGUI(GLFWwindow* window) override;

	void CreateUIFrame() override;

	void AddFloatUIElement(const String& Name, float* Element);
	void AddIntegerUIElement(const String& Name, uint32* Element);

	void Render(const String& Name) override;

	void CleanUpUI() override;

	FPMap* GetFloatUIElements();
	UIPMap* GetUnsignedUIElements();

	void SetFloatUIElements(FPMap* Map);
	void SetUnsignedUIElements(UIPMap* Map);
};

// ** Normal Functions**
extern "C"
{
	ENGINEUI_API CEngineUI* createUI();
	ENGINEUI_API FPMap* GetFloatUIElements(CEngineUI* UI);
	ENGINEUI_API UIPMap* GetUnsignedUIElements(CEngineUI* UI);

	ENGINEUI_API void SetFloatUIElements(CEngineUI* UI, FPMap* Map);
	ENGINEUI_API void SetUnsignedUIElements(CEngineUI* UI, UIPMap* Map);

	ENGINEUI_API void AddFloatUIElement(CEngineUI* UI, const String& Name, float* Element);
	ENGINEUI_API void AddIntegerUIElement(CEngineUI* UI, const String& Name, uint32* Element);
}