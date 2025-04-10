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

	CFrame::Button* button20 = new CFrame::Button(90, 90);

	
	button20->SetRadius(20, 20, 20, 20);
	button20->SetOnLeave([button20]() {
		button20->SetColor(Color::Gray);
		});
	button20->SetOnHover([button20]() {
		button20->SetColor({ 100, 100, 100, 255 });
		
		});

	topPart->AddChild(button20);
	topPart->SetAlignment(CFrame::AlignItems::Start, CFrame::AlignItems::Start);
	
	
	
	SetRadius(20,20,20,20);
	SetBorder(2);
	AddChild(topPart);
	AddChild(bottomPart);
	SetColor(Color::Red);
}





