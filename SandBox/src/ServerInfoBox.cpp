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
	bottomPart->SetBorder(0, 2, 2, 2);
	bottomPart->SetBorderColor(Color::Gray);
	bottomPart->SetColor(Color::DarkGray);
	bottomPart->SetRadius(0, 0, 20, 20);

	CFrame::Button* button20 = new CFrame::Button(10,10,100, 100);
	CFrame::Button* button21 = new CFrame::Button(55,10, -1, 100);

	
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
	button21->SetPositionAbsolute(true);
	button21->SetPadding(60);
	button21->SetAnchorPoint(CFrame::PositionMode::BottomLeft);
	
	
	topPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Start);
	
	SetRadius(20,20,20,20);
	SetBorder(2);
	SetBorderColor(Color::Gray);
	SetPadding(10);
	AddChild(button21);
	AddChild(button20);
	SetMinHeight(120);
	
	SetColor(Color::DarkGray);
}





