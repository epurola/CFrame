#pragma once
#include "CFrame/UIElements/UIElement.h"
#include "CFrame/UIElements/Grid.h"
#include "CFrame/Animator/Bounce.h"
#include "ChessPiece.h"
#include "CFrame/CFrameEvent/CFrameEvent.h"


class ChessBoard : public CFrame::Grid 
{
public:
	ChessBoard(int w, int h);
	~ChessBoard();

	bool MousePressEvent(CFrame::MouseButtonDownEvent& event);
	bool MouseMoveEvent(CFrame::MouseMovedEvent& event);
	bool MouseReleaseEvent(CFrame::MouseButtonReleasedEvent& event);

private:
	void InitializeBoard();

	ChessPiece* selectedPiece = nullptr;
	int index = -1;
	int cellWidth = 0;
	int cellHeight = 0;
};