#include "ServerInfoBox.h"

ServerInfoBox::ServerInfoBox(int x, int y, int w, int h)
	:VBox(x,y,w,h)
{
	topPart = new CFrame::HBox(-1, -1);
	topPart->SetRadius(20,20,0,0);
	topPart->SetBorder(2, 0, 2, 2);
	topPart->SetBorderColor(Color::Gray);
	topPart->SetColor(Color::DarkGray);
	topPart->SetPadding(20);

	bottomPart = new CFrame::HBox(-1, -1);
	bottomPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Center);
	bottomPart->SetColor(Color::DarkGray);
	bottomPart->SetRadius(20, 20, 20, 20);
	bottomPart->SetPadding(10);

	CFrame::Button* button20 = new CFrame::Button(10,10,100, 100);
	CFrame::Button* button21 = new CFrame::Button(55,10, -1, 100);
	 
	CFrame::Button* logo  = new CFrame::Button( 55, 55);
	logo->SetText("\x2B");
	logo->SetMargin(30, 0, 0, 0);
	logo->SetFontSize(44);
	logo->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo->SetColor(Color::DarkGray);
	CFrame::Button* logo1 = new CFrame::Button( 55, 55);
	logo1->SetAngle(45.0);
	logo1->SetText("\x0D");
	logo1->SetFontSize(44);
	logo1->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo1->SetColor(Color::Gray);
	CFrame::Button* logo2 = new CFrame::Button( 55, 55);
	logo2->SetAngle(45.0);
	logo2->SetText("\x12");
	logo2->SetFontSize(44);
	logo2->SetFont(CFrame::Font::SegoeMDL2Assets);
	logo2->SetColor(Color::DarkGray);

	
	button20->SetRadius(55, 55, 55, 55);
	button20->SetBackgroundImage("C:/Users/eelip/Pictures/aaaaaaaape.jpg");
	button20->SetAnchorPoint(CFrame::PositionMode::BottomLeft);
	button20->SetPositionAbsolute(true);
	button20->SetBorderColor(Color::Green);
	//button20->SetBorder(2);
	button20->SetText("");
	

	button21->SetOnLeave([button21]() {
		button21->SetColor(Color::DarkGray);
		});
	button21->SetOnHover([button21]() {
		button21->SetColor({ 100, 100, 100, 255 });

		});

	
	button21->SetText("aefootballclub45");
	button21->SetColor(Color::DarkGray);
	button21->SetTextAlign(CFrame::TextAlign::Start);
	button21->SetFontSize(20);
	button21->SetMargin(50, 0,0,0);

	button21->SetPadding(60);
	button21->SetAnchorPoint(CFrame::PositionMode::BottomLeft);
	
	
	topPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Start);
	
	SetRadius(20,20,20,20);
	SetBorder(2);
	SetBorderColor(Color::Gray);
	//SetPadding(10);
	bottomPart->AddChild(button21);
	bottomPart->AddChild(button20);
	bottomPart->AddChild(logo);
	bottomPart->AddChild(logo1);
	bottomPart->AddChild(logo2);
	SetMinHeight(120);
	AddChild(topPart);
	topPart->SetVisibility(false);
	AddChild(bottomPart);
	SetColor(Color::DarkGray);
	SetPadding(2);
}





