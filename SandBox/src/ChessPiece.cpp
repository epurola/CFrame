#include "ChessPiece.h"

ChessPiece::ChessPiece( std::string path)
	:Image(path)
{
	SetBorder(2);
	SetBorderColor(Color::Gold);
	SetRadius(2, 2, 2, 2);
	//SetColor(Color::Blue);
	SetAngle(20);
	SetOpacity(0);
}

ChessPiece::~ChessPiece()
{

}
