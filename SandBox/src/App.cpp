#include <CFrame.h>

class SandBox : public CFrame::Application 
{
public:
	SandBox() : CFrame::Application(1000, 1000)
	{
		CFrame::VBox* vbox = new CFrame::VBox();
		CFrame::Button* button = new CFrame::Button(100,100,200, 200);
		vbox->AddChild(button);
		vbox->UpdateChildSizes();
		addElement(vbox);
		rootContainer->AddChild(vbox);
	}
	~SandBox() 
	{
		
	}

};

/*Client implementasion of CreateApplication returns a new instance of users application
* that inherits from CFrame::Application */
CFrame::Application* CFrame::CreateApplication()
{
	return new SandBox();
}

