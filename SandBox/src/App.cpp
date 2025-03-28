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
		hbox->SetColor(Color::DarkGray);

		CFrame::Button* button = new CFrame::Button(150,100,150, 75);
		CFrame::Button* button1 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button2 = new CFrame::Button(100, 100, 150, 75);

		button2->SetOnHover([button2]() {button2->SetScale(1.1, 1.1);});
		button2->SetOnLeave([button2]() {button2->SetScale(1.0, 1.0);});

		button->SetColor(Color::Red);

		CFrame::Button* button3 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button4 = new CFrame::Button(100, 100, 150, 75);
		CFrame::Button* button5 = new CFrame::Button(100,100);
		button5->SetScale(1.5f, 1.5f, 1.0f);

		vbox->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Start);
		vbox->SetColor(Color::Navy);
		vbox1->SetAlignment(CFrame::AlignItems::Center, CFrame::AlignItems::Center);
		vbox1->SetColor(Color::Gold);

		CFrame::HBox* hbox2 = new CFrame::HBox(-1, 100);
		CFrame::Button* button6 = new CFrame::Button(50, 50);
		CFrame::Button* button7 = new CFrame::Button(50, 50);
		CFrame::Button* button8 = new CFrame::Button(50, 50);
		hbox2->AddChild(button6);
		hbox2->AddChild(button7);
		hbox2->AddChild(button8);
		hbox2->SetAlignment(CFrame::AlignItems::Center, CFrame::AlignItems::Center);
		hbox2->SetRadius(15);
		hbox2->SetSpacing(50);
		hbox2->SetMargin(0,0,100,0);
		

		vbox->AddChild(button);
		vbox->AddChild(button1);
		vbox->AddChild(button2);
		vbox->AddChild(hbox2);
		
		vbox1->AddChild(button3);
		vbox1->AddChild(button4);
		vbox1->AddChild(button5);

		hbox->AddChild(vbox);
		hbox->AddChild(vbox1);
		hbox->UpdateChildSizes();
		
		//addElement(hbox);
		rootContainer->SetPadding(30);
		rootContainer->SetColor(Color::White);
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
