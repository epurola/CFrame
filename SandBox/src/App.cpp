#include <CFrame.h>
#include "ServerInfoBox.h"


class SandBox : public CFrame::Application 
{
public:
	SandBox() : CFrame::Application(2000, 1500)
	{
		CFrame::VBox* vbox        = new CFrame::VBox();
		CFrame::HBox* header      = new CFrame::HBox(-1, 75);
		CFrame::HBox* content     = new CFrame::HBox();
		CFrame::VBox* sideBar     = new CFrame::VBox(150,-1);
		CFrame::VBox* friendList  = new CFrame::VBox(-1,-1);
		CFrame::VBox* messageBox  = new CFrame::VBox(-1, -1);
		CFrame::HBox* contentLeft = new CFrame::HBox(500,-1);
		ServerInfoBox* info       = new ServerInfoBox(20, 20, -1, -1); //H = 120;
		info->SetMargin(0,20,0,0);
		info->SetPositionAbsolute(true);
		info->SetAnchorPoint(CFrame::PositionMode::BottomLeft); // Set the origin where absolute positioning is calculated from
	                                                            //BottomLeft allows it to stay 20px (x) 20px(y) from the bottom
		                                                        //even when window size changes
		contentLeft->AddChild(sideBar);
		contentLeft->AddChild(friendList);
		content->AddChild(contentLeft);
		content->AddChild(messageBox);
		content->ToFront(contentLeft);

		vbox->AddChild(header);
		vbox->AddChild(content);
	
		
		
		contentLeft->SetMaxWidth(800);
		contentLeft->SetColor(Color::DarkGray);
		contentLeft->SetDragToResize(true); //Some other layer handles the event before so this does not currently work
		
		contentLeft->AddChild(info);
		
		content->SetColor(Color::DarkGray);

		CFrame::Button* button = new CFrame::Button(90, 90);
		                button->SetText("S");
						button->SetFont(CFrame::Font::Arial);
						button->setTextOpacity(0.8);
						button->SetFontSize(34.0);
		                button->SetMargin(0, 0, 50, 0);				 
		                button->SetRadius(20,20,20,20);
						
						button->SetOnLeave([button]() {
							button->SetColor(Color::Gray);
						});
						button->SetOnHover([button]() {
							button->SetColor({ 100, 100, 100, 255 });
						});
		CFrame::Button* button1 = new CFrame::Button(90, 90);
						button1->SetText("Wz");
						button1->SetFont(CFrame::Font::Arial);
						button1->SetFontSize(34.0);
		                button1->SetRadius(20, 20, 20, 20);
						button1->SetOnLeave([button1]() {
							button1->SetColor(Color::Gray);
							});
						button1->SetOnHover([button1]() {
							button1->SetColor({ 100, 100, 100, 255 });
							});
		CFrame::Button* button2 = new CFrame::Button(90, 90);
						button2->SetText("\x14");
						button2->SetFont(CFrame::Font::SegoeMDL2Assets);
						button2->SetFontSize(44.0);
		                button2->SetRadius(20,20,20,20);
						button2->SetOnLeave([button2]() {
							button2->SetColor(Color::Gray);
						});
						button2->SetOnHover([button2]() {
							button2->SetColor({ 100, 100, 100, 255 });
						});
		CFrame::Button* button3 = new CFrame::Button(90, 90);
						button3->SetText("\x55");
						button3->SetFont(CFrame::Font::SegoeMDL2Assets);
						button3->SetFontSize(44.0);
		                button3->SetRadius(20,20,20,20);
						button3->SetOnLeave([button3]() {
							button3->SetColor(Color::Gray);
						});
						button3->SetOnHover([button3]() {
							button3->SetColor({ 100, 100, 100, 255 });
						});
						
		CFrame::Button* button4 = new CFrame::Button(90, 90);
						button4->SetFontSize(34.0);
						button4->SetText("E.m");
		                button4->SetRadius(20,20,20,20);
						button4->SetOnLeave([button4]() {
							button4->SetColor(Color::Gray);
						});
						button4->SetOnHover([button4]() {
							button4->SetColor({ 100, 100, 100, 255 });
						});
	    CFrame::Button* button45 = new CFrame::Button(90, 90);
						button45->SetText("Il");
						button45->SetFontSize(34.0);
		                button45->SetRadius(20,20,20,20);
						button45->SetOnLeave([button45, friendList,content]() {
							button45->SetColor(Color::Gray);
							
						});
						button45->SetOnClick([friendList, content, messageBox]() {
							bool currentVisibility = friendList->IsVisible();
							friendList->SetVisibility(!currentVisibility);
							content->UpdateChildSizes();
							if (!currentVisibility) {
								messageBox->SetRadius(0, 0, 0, 0);
								messageBox->SetBorder(2, 0, 0, 0);
							}
							else {
								messageBox->SetRadius(15, 0, 0, 0);
								messageBox->SetBorder(2, 0, 2, 0); //Wrong order in the function
							}
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
		sideBar->SetScrollEnabled(true);
		

		CFrame::Button* button5 = new CFrame::Button(-1, 75);
						button5->SetTextColor(Color::Cyan, Color::Red);
						button5->SetText("Kaverit");
						button5->SetOverflow(true);
						button5->SetPadding(20);
						button5->SetTextAlign(CFrame::TextAlign::Start);
						button5->SetOnLeave([button5]() { 
							button5->SetBorder(0.0f);
							button5->SetColor(Color::DarkGray);
						});
						button5->SetOnClick([info, contentLeft]() {
							bool isExpanded = info->GetHeight() == 120 ? true : false;
							if (!isExpanded) {
								info->SetHeight(110);
							}
							else {
								info->SetHeight(300);
							}
							contentLeft->UpdateChildSizes();
							});
						button5->SetOnHover([button5]() {
							button5->SetBorder(2.5f);
						    button5->SetBorderColor(Color::Cyan, Color::Red);
						    button5->AnimateGradient(3.0);
							button5->SetOpacity(0.2);
							button5->SetColor(Color::Gray);
						});
						
		CFrame::Button* button6  = new CFrame::Button(-1, 75);
						button6->SetText("Kirjasto");
						button6->SetAngle(25.0);
		                button6->SetColor(Color::Gray);
						button6->SetPadding(20);
						button6->SetTextAlign(CFrame::TextAlign::Start);
						button6->SetOnLeave([button6]() { 
							button6->SetBorder(0.0f);
							button6->SetColor(Color::DarkGray);
						});
						button6->SetOnHover([button6]() {
							button6->SetBorder(2.5f);
							button6->SetBorderColor(Color::Cyan, Color::Red);
							button6->AnimateGradient(3.0);
							button6->SetOpacity(0.2);
							button6->SetColor(Color::Gray);
						});
						
		CFrame::Button* button7  = new CFrame::Button(-1, 75);
						button7->SetText("Nitro");
						button7->SetTextAlign(CFrame::TextAlign::Start);
						button7->SetPadding(20);
						button7->SetColor(Color::DarkGray);
						button7->SetOnLeave([button7]() { 
							button7->SetBorder(0.0f);
							button7->SetColor(Color::DarkGray);
						});
						button7->SetOnHover([button7]() {
							button7->SetBorder(2.5f);
							button7->SetBorderColor(Color::Cyan, Color::Red);
							button7->AnimateGradient(3.0);
							button7->SetOpacity(0.2);
							button7->SetColor(Color::Gray);
						});
		CFrame::Button* button8  = new CFrame::Button(-1, 75);
	                    button8->SetText("Kauppa");
						button8->SetTextAlign(CFrame::TextAlign::Start);
						button8->SetPadding(20);
						button8->SetColor(Color::DarkGray);						
						button8->SetOnLeave([button8]() { 
							button8->SetBorder(0.0f);
							button8->SetColor(Color::DarkGray);
							});
						button8->SetOnHover([button8]() {
							button8->SetBorder(2.5f);
							button8->SetBorderColor(Color::Cyan, Color::Red);
							button8->AnimateGradient(3.0);
							button8->SetOpacity(0.2);
							button8->SetColor(Color::Gray);
						});
						button8->SetOpacity(0.5);
		CFrame::Button* button9 = new CFrame::Button(-1, 75);
		                button9->SetColor(Color::Gray);
						button9->SetTextAlign(CFrame::TextAlign::Start);
						button9->SetPadding(20);
						button9->SetOnLeave([button9, friendList]() { 
							button9->SetBorder(0.0f);
							
						});
						button9->SetOnHover([button9]() {
							button9->SetBorder(2.5f);
							button9->SetBorderColor(Color::Cyan, Color::Red);
							button9->AnimateGradient(3.0);
						});
						button9->SetOpacity(0.5);
	  
						
						

		friendList->AddChild(button5);
		friendList->AddChild(button6);
		friendList->AddChild(button7);
		friendList->AddChild(button8);
		friendList->AddChild(button9);

		friendList->SetSpacing(25);
		friendList->SetPadding(15);
		friendList->SetRadius(20, 0, 0, 0);
		friendList->SetColor(Color::DarkGray);
		friendList->SetBorder(0.7);
		friendList->SetBorderColor(Color::Gray);
		friendList->SetBorder(2,0,2,2);
		

		CFrame::Button* button10 = new CFrame::Button(50, 50);
						button10->SetText("-");
						button10->SetFontSize(34);
		                button10->SetColor(Color::Gray);
		CFrame::Button* button11 = new CFrame::Button(50, 50);
						button11->SetText("×");
						button11->SetFontSize(24);
		                button11->SetColor(Color::Gray);
		CFrame::Button* button12 = new CFrame::Button(50, 50);
		                button12->SetText("X");
						button12->SetFont(CFrame::Font::VerdanaBold);
						button12->SetFontSize(24);
		                button12->SetColor(Color::Gray);
		

		header->AddChild(button10);
		header->AddChild(button11);
		header->AddChild(button12);
		
		header->SetSpacing(15);
		header->SetPadding(10);
		header->SetColor(Color::DarkGray);
		header->SetAlignment(CFrame::AlignItems::End, CFrame::AlignItems::Center);
		

		//messageBox->SetColor(Color::DarkGray);
		messageBox->SetBorder(2, 0, 0, 0);
		messageBox->SetBorderColor(Color::Gray);
		CFrame::Button* button16 = new CFrame::Button(300, 300);
		button16->SetColor(Color::Gold);
		button16->SetMargin(20, 20, 20, 20);
		messageBox->AddChild(button16);
		messageBox->SetOpacity(0.3);
		
		
		rootContainer->SetColor(Color::Red);
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
