#pragma once

#include "CFrame/UIElements/Image.h"
#include "CFrame/UIElements/UIElement.h"

class ChessPiece : public CFrame::Image 
{
public:
	ChessPiece(int width, int height, std::string path);
	~ChessPiece();


private:

};