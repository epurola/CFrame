#include <CFrame.h>

class SandBox : public CFrame::Application 
{
public:
	SandBox() : CFrame::Application(2000, 1500)
	{
		CFrame::VBox* vbox = new CFrame::VBox();
		CFrame::HBox* header = new CFrame::HBox(-1, 75);
		CFrame::HBox* content = new CFrame::HBox();
		CFrame::VBox* sideBar = new CFrame::VBox(150,-1);
		CFrame::VBox* friendList = new CFrame::VBox(500,-1);
		CFrame::VBox* messageBox = new CFrame::VBox(-1, -1);
		
		content->AddChild(sideBar);
		content->AddChild(friendList);
		content->AddChild(messageBox);
		vbox->AddChild(header);
		vbox->AddChild(content);

		content->SetColor(Color::DarkGray);

		CFrame::Button* button  = new CFrame::Button(90, 90);
		                button->SetMargin(0, 0, 50, 0);				 
		                button->SetRadius(20,20,20,20);
						button->SetOnLeave([button]() {
							button->SetColor(Color::Gray);
						});
						button->SetOnHover([button]() {
							button->SetColor({ 100, 100, 100, 255 });
						});
		CFrame::Button* button1 = new CFrame::Button(90, 90);
		                button1->SetRadius(20, 20, 20, 20);
						button1->SetOnLeave([button1]() {
							button1->SetColor(Color::Gray);
							});
						button1->SetOnHover([button1]() {
							button1->SetColor({ 100, 100, 100, 255 });
							});
		CFrame::Button* button2 = new CFrame::Button(90, 90);
		                button2->SetRadius(20,20,20,20);
						button2->SetOnLeave([button2]() {
							button2->SetColor(Color::Gray);
						});
						button2->SetOnHover([button2]() {
							button2->SetColor({ 100, 100, 100, 255 });
						});
		CFrame::Button* button3 = new CFrame::Button(90, 90);
		                button3->SetRadius(20,20,20,20);
						button3->SetOnLeave([button3]() {
							button3->SetColor(Color::Gray);
						});
						button3->SetOnHover([button3]() {
							button3->SetColor({ 100, 100, 100, 255 });
						});
		CFrame::Button* button4 = new CFrame::Button(90, 90);
		                button4->SetRadius(20,20,20,20);
						button4->SetOnLeave([button4]() {
							button4->SetColor(Color::Gray);
						});
						button4->SetOnHover([button4]() {
							button4->SetColor({ 100, 100, 100, 255 });
						});
	    CFrame::Button* button45 = new CFrame::Button(90, 90);
		                button45->SetRadius(20,20,20,20);
						button45->SetOnLeave([button45]() {
							button45->SetColor(Color::Gray);
						});
						button45->SetOnHover([button45]() {
							button45->SetColor({ 100, 100, 100, 255 });
						});
						

		sideBar->AddChild(button);
		sideBar->AddChild(button1);
		sideBar->AddChild(button2);
		sideBar->AddChild(button3);
		sideBar->AddChild(button4);
		sideBar->AddChild(button45);
		sideBar->SetSpacing(20);
		sideBar->SetAlignment(CFrame::AlignItems::Center, CFrame::AlignItems::Start);
		sideBar->SetColor(Color::DarkGray);

		CFrame::Button* button5 = new CFrame::Button(-1, 75);
		                button5->SetColor(Color::DarkGray);
						button5->SetOnLeave([button5]() { 
							button5->SetBorder(0.0f);
						});
						button5->SetOnHover([button5]() {
							button5->SetBorder(1.5f);
						    button5->SetBorderGradient(Color::Cyan, Color::Red);
						    button5->AnimateGradient(3.0);
						});
						button5->SetOnClick([button5](){
							button5->SetScale(1.5f, 1.5f); 
							button5->StartAnimation();
						});
		CFrame::Button* button6  = new CFrame::Button(-1, 75);
		                button6->SetColor(Color::DarkGray);
						button6->SetOnLeave([button6]() { 
							button6->SetBorder(0.0f);
						});
						button6->SetOnHover([button6]() {
							button6->SetBorder(1.5f);
							button6->SetBorderGradient(Color::Cyan, Color::Red);
							button6->AnimateGradient(3.0);
						});
		CFrame::Button* button7  = new CFrame::Button(-1, 75);
		                button7->SetColor(Color::DarkGray);
						button7->SetOnLeave([button7]() { 
							button7->SetBorder(0.0f);
						});
						button7->SetOnHover([button7]() {
							button7->SetBorder(1.5f);
							button7->SetBorderGradient(Color::Cyan, Color::Red);
							button7->AnimateGradient(3.0);
						});
		CFrame::Button* button8  = new CFrame::Button(-1, 75);
	                    button8->SetColor(Color::DarkGray); 
						button8->SetOnLeave([button8]() { 
							button8->SetBorder(0.0f);
							});
						button8->SetOnHover([button8]() {
							button8->SetBorder(1.5f);
							button8->SetBorderGradient(Color::Cyan, Color::Red);
							button8->AnimateGradient(3.0);
						});
						button8->SetOpacity(0.5);
		CFrame::Button* button9 = new CFrame::Button(-1, 75);
		                button9->SetColor(Color::DarkGray);
						button9->SetOnLeave([button9]() { 
							button9->SetBorder(0.0f);
						});
						button9->SetOnHover([button9]() {
							button9->SetBorder(1.5f);
							button9->SetBorderGradient(Color::Cyan, Color::Red);
							button9->AnimateGradient(3.0);
						});
						button9->SetOpacity(0.5);
	  
      CFrame::Button* button15 = new CFrame::Button(-1, 3);
	                  button15->SetColor(Color::DarkGray);
					  button15->SetMargin(20, 20, 20, 20);
						
						

		friendList->AddChild(button5);
		friendList->AddChild(button6);
		friendList->AddChild(button7);
		friendList->AddChild(button15);
		friendList->AddChild(button8);
		friendList->AddChild(button9);

		friendList->SetSpacing(25);
		friendList->SetPadding(15);
		friendList->SetRadius(20, 0, 0, 0);
		friendList->SetColor(Color::Gray);
		friendList->SetDragToResize(true);
		friendList->SetMaxWidth(600);

		CFrame::Button* button10 = new CFrame::Button(50, 50);
		                button10->SetColor(Color::Gray);
		CFrame::Button* button11 = new CFrame::Button(50, 50);
		                button11->SetColor(Color::Gray);
		CFrame::Button* button12 = new CFrame::Button(50, 50);
		                button12->SetColor(Color::Gray);
		

		header->AddChild(button10);
		header->AddChild(button11);
		header->AddChild(button12);
		header->SetAlignment(CFrame::AlignItems::End, CFrame::AlignItems::Center);
		header->SetSpacing(15);
		header->SetPadding(10);
		header->SetColor(Color::DarkGray);

		messageBox->SetColor(Color::LightGray);
		
		rootContainer->SetColor(Color::White);
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
