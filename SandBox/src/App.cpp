#include <CFrame.h>

class SandBox : public CFrame::Application 
{
public:
	SandBox() : CFrame::Application(1000, 1000)
	{
		CFrame::HBox* hbox = new CFrame::HBox();
		CFrame::VBox* vbox = new CFrame::VBox();
		CFrame::VBox* vbox1 = new CFrame::VBox();
		vbox->SetPadding(20);

		CFrame::Button* button = new CFrame::Button(150,100,150, 75);
		CFrame::Button* button1 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button2 = new CFrame::Button(100, 100, 150, 75);

		button->SetColor(Color::Red);
		

		CFrame::Button* button3 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button4 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button5 = new CFrame::Button(100, 100, 150, 75);
		button5->SetScale(1.5f, 1.5f);

		vbox->SetAlignment(CFrame::AlignItems::Center, CFrame::AlignItems::Start);
		vbox1->SetAlignment(CFrame::AlignItems::Center, CFrame::AlignItems::Center);

		vbox->AddChild(button);
		vbox->AddChild(button1);
		vbox->AddChild(button2);
		
		vbox1->AddChild(button3);
		vbox1->AddChild(button4);
		vbox1->AddChild(button5);

		hbox->AddChild(vbox);
		hbox->AddChild(vbox1);
		hbox->UpdateChildSizes();
		
		//addElement(hbox);
		rootContainer->AddChild(hbox);
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
