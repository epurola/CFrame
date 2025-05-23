#include "ChessPiece.h"
#include "CFrame/Animator/Bounce.h"

ChessPiece::ChessPiece( std::string path)
	:Image(path)
{
	SetBorder(2);
	SetBorderColor(Color::Gold);
	SetRadius(2, 2, 2, 2);
	SetColor(Color::Blue);

	SetOpacity(0);

}

ChessPiece::~ChessPiece()
{

}

bool ChessPiece::MouseMoveEvent(CFrame::MouseMovedEvent& event)
{
	//this->StartAnimation<CFrame::Bounce>();
	return false;
}
