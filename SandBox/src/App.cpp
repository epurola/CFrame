#include <CFrame.h>

class SandBox : public CFrame::Application 
{
public:
	SandBox() 
	{

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