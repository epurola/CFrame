#include "ChessPiece.h"

ChessPiece::ChessPiece(int width, int height, std::string path)
	:Image(width, height, path)
{
	SetBorder(5);
	SetBorderColor(Color::Blue);
	SetRadius(5, 5, 5, 5);
	SetColor(Color::Blue);
	//SetAngle(20);
}

ChessPiece::~ChessPiece()
{

}
