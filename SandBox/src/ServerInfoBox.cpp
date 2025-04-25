#include "ServerInfoBox.h"

ServerInfoBox::ServerInfoBox(int x, int y, int w, int h)
	:VBox(x,y,w,h)
{
	isWidthResizable = true;
	topPart = new CFrame::HBox(-1, -1);
	topPart->SetRadius(20,20,0,0);
	topPart->SetBorder(2, 0, 2, 2);
	topPart->SetBorderColor(Color::Gray);
	topPart->SetColor(Color::DarkGray);
	topPart->SetPadding(20);

	bottomPart = new CFrame::HBox(-1, -1);
	bottomPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Center);
	bottomPart->SetColor(Color::LightGray);
	bottomPart->SetRadius(20, 20, 20, 20);
	bottomPart->SetPadding(10);
	bottomPart->SetSpacing(10);

	CFrame::Button* button20 = new CFrame::Button(10,10,100, 100);
	CFrame::Button* button21 = new CFrame::Button(55,10, 300, 100);
	button21->SetWidthResizable(true);
	 
	CFrame::Button* logo  = new CFrame::Button( 55, 55);
	logo->SetIcon(0xE74F);
	logo->SetFontSize(44);
	logo->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo->SetTextColor(Color::Red);
	logo->SetColor(Color::LightGray);
	logo->SetOnLeave([logo]() {
		logo->SetColor(Color::LightGray);
		});
	logo->SetOnHover([logo]() {
		logo->SetColor({ 100, 100, 100, 255 });
		});
	CFrame::Button* logo1 = new CFrame::Button( 55, 55);
	//logo1->SetAngle(45.0);
	logo1->SetIcon(0xE720);
	logo1->SetFontSize(44);
	logo1->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo1->SetColor(Color::LightGray);
	logo1->SetTextColor(Color::Red);
	logo1->SetOnLeave([logo1]() {
		logo1->SetColor(Color::LightGray);
		});
	logo1->SetOnHover([logo1]() {
		logo1->SetColor({ 100, 100, 100, 255 });
		});
	CFrame::Button* logo2 = new CFrame::Button( 55, 55);
	//logo2->SetAngle(45.0);
	logo2->SetIcon(0xE713);
	logo2->SetFontSize(34);
	logo2->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo2->SetColor(Color::LightGray);
	logo2->SetOnLeave([logo2]() {
		logo2->SetColor(Color::LightGray);
		});
	logo2->SetOnHover([logo2]() {
		logo2->SetColor({ 100, 100, 100, 255 });
		});
	
	
	button20->SetRadius(55, 55, 55, 55);
	button20->SetBackgroundImage("C:/Users/eelip/Pictures/aaaaaaaape.jpg");
	button20->SetAnchorPoint(CFrame::PositionMode::BottomLeft);
	button20->SetPositionAbsolute(true);
	button20->SetBorderColor(Color::Green);
	//button20->SetBorder(2);
	button20->SetText("");
	

	button21->SetOnLeave([button21]() {
		button21->SetColor(Color::LightGray);
		});
	button21->SetOnHover([button21]() {
		button21->SetColor({ 100, 100, 100, 255 });
		});

	
	button21->SetText("aefootballclub45");
	button21->SetColor(Color::LightGray);
	button21->SetTextAlign(CFrame::TextAlign::Start);
	button21->SetFontSize(20);
	button21->SetMargin(50,0,0,0);


	button21->SetPadding(60);
	button21->SetAnchorPoint(CFrame::PositionMode::BottomLeft);
	
	
	topPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Start);
	
	SetRadius(20,20,20,20);
	SetBorder(2);
	
	//SetPadding(10);
	bottomPart->AddChild(button21);
	bottomPart->AddChild(button20);
	bottomPart->AddChild(logo);
	bottomPart->AddChild(logo1);
	bottomPart->AddChild(logo2);
	bottomPart->ToFront(logo1);
	SetMinHeight(120);
	AddChild(topPart);
	topPart->SetVisibility(false);
	AddChild(bottomPart);
	SetColor(Color::LightGray);
	SetPadding(2);
}





