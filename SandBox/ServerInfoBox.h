#pragma once
#include "CFrame/UIElements/UIElement.h"
#include "CFrame/UIElements/Container.h"
#include "CFrame/UIElements/VBox.h"
#include "CFrame/UIElements/HBox.h"
#include "CFrame/UIElements/Button.h"
#include "CFrame/Log.h"

class ServerInfoBox : public CFrame::VBox
{
public:
	ServerInfoBox(int x , int y , int w, int h);
	

private:
	CFrame::HBox* topPart;
	CFrame::HBox* bottomPart;

};