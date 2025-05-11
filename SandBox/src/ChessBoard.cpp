#include "ChessBoard.h"

ChessBoard::ChessBoard(int w, int h)
	:Grid(w, h)
{
	InitializeBoard();
}

ChessBoard::~ChessBoard()
{

}

bool ChessBoard::MousePressEvent(CFrame::MouseButtonDownEvent& event)
{
	selectedPiece = nullptr;
	float x = event.GetX();
	float y = event.GetY();

	int localX = x - GetX() ;
	int localY = y -GetY() ;

	cellWidth = GetWidth() / 8;
	cellHeight = GetHeight() / 8;

	int col = localX / cellWidth;
	int row = localY / cellHeight;
    index = row * 8 + col;

    selectedPiece = static_cast<ChessPiece*>(GetChild(index));
	
	return true;
}

bool ChessBoard::MouseMoveEvent(CFrame::MouseMovedEvent& event)
{
	if (selectedPiece) 
	{
		int x = event.GetX();
		int y = event.GetY();

		selectedPiece->SetY(y - (cellWidth / 2));
		selectedPiece->SetX(x - (cellHeight / 2));
		selectedPiece->UpdateVertices();
		return true;
	}
	return false;
}

bool ChessBoard::MouseReleaseEvent(CFrame::MouseButtonReleasedEvent& event)
{
	if (selectedPiece) 
	{
		RemoveChild(index); //Won't delete the child
		int x = event.GetX();
		int y = event.GetY();

		int localX = x - GetX();
		int localY = y - GetY();

		int cellWidth = GetWidth() / 8;
		int cellHeight = GetHeight() / 8;

		int col = localX / cellWidth;
		int row = localY / cellHeight;
		int toIndex = row * 8 + col;
		//This can be used to place an child to a different cell after it was removed.
		if (static_cast<ChessPiece*>(GetChild(toIndex)) == nullptr) {
			InsertChild(selectedPiece, toIndex); //Do not use AddChild() since it will also add to the child list
		}
		else {
			InsertChild(selectedPiece, index); //Put it back if the cell is already in use
		}
		
		UpdateChildSizes();
		selectedPiece = nullptr;
		return true;
	}
	return false;
}

void ChessBoard::InitializeBoard()
{
	ChessPiece* b1 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-rook.png");
	ChessPiece* b2 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-knight.png");
	ChessPiece* b3 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-bishop.png");
	ChessPiece* b4 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-queen.png");
	ChessPiece* b5 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-king.png");
	ChessPiece* b6 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-bishop.png");
	ChessPiece* b7 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-knight.png");
	ChessPiece* b8 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-rook.png");
	ChessPiece* b9 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/black-pawn.png");

	ChessPiece* w1 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-rook.png");
	ChessPiece* w2 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-knight.png");
	ChessPiece* w3 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-bishop.png");
	ChessPiece* w4 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-queen.png");
	ChessPiece* w5 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-king.png");
	ChessPiece* w6 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-bishop.png");
	ChessPiece* w7 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-knight.png");
	ChessPiece* w8 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-rook.png");
	ChessPiece* w9 = new ChessPiece( "C:/dev/CFrame/SandBox/src/Images/white-pawn.png");

	SetLayout(8, 8);
	SetBackgroundImage("C:/dev/CFrame/SandBox/src/Images/board.png");
	SetColor(Color::Blue);
	AddChild(b1, 0);
	AddChild(b2, 1);
	AddChild(b3, 2);
	AddChild(b4, 3);
	AddChild(b5, 4);
	AddChild(b6, 5);
	AddChild(b7, 6);
	AddChild(b8, 7);
	AddChild(b9, 8);

	AddChild(w1, 63);
	AddChild(w2, 62);
	AddChild(w3, 61);
	AddChild(w4, 60);
	AddChild(w5, 59);
	AddChild(w6, 58);
	AddChild(w7, 57);
	AddChild(w8, 56);
	AddChild(w9, 55);
}
