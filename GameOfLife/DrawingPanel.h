#pragma once
#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H


#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/timer.h>
#include <vector>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxFrame* parent); 
    void OnPaint(wxPaintEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnResize(wxSizeEvent& event);
    void SetGridSize(int gridSize);
    void SetGameBoard(std::vector<std::vector<bool>>& gameBoard);

private:
    wxGraphicsContext* graphicsContext;
  
    int gridSize = 15;
    int cellSize = 10;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> tempGrid;
    bool isDrawing = false;
    int mouseX = -1;
    int mouseY = -1;

    std::vector<std::vector<bool>>* m_gameBoard;
    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H

