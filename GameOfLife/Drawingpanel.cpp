#include "DrawingPanel.h"
#include <wx/dcbuffer.h>

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent)
    : wxPanel(parent), gridSize(30), m_gameBoard(nullptr)
{
}

void DrawingPanel::SetGridSize(int gridSize)
{
    gridSize = gridSize;
}

void DrawingPanel::SetGameBoard(std::vector<std::vector<bool>>& gameBoard)
{
    m_gameBoard = &gameBoard;
}

void DrawingPanel::OnPaint(wxPaintEvent&)
{
    if (m_gameBoard == nullptr)
        return;

    wxAutoBufferedPaintDC dc(this);

    int width, height;
    GetClientSize(&width, &height);

    int cellWidth = width / gridSize;
    int cellHeight = height / gridSize;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            wxBrush brush((*m_gameBoard)[row][col] ? *wxLIGHT_GREY_BRUSH : *wxWHITE_BRUSH);
            dc.SetBrush(brush);

            int x = col * cellWidth;
            int y = row * cellHeight;

            dc.DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    int width, height;
    GetClientSize(&width, &height);

    int cellWidth = width;
}
