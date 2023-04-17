#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include <vector>
#include "DrawingPanel.h"



class MainWindow : public wxFrame {
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    int GetLivingCount() const;
private:
    void OnQuit(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnTick(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnTrash(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void NextGeneration();
    int CountNeighbors(int row, int col);
    void UpdateStatusText();
    void StopSimulation();
    void ClearBoard();

    int m_generation;
    std::vector<std::vector<bool>> m_gameBoard;
    DrawingPanel* drawingPanel;
    wxTimer* m_pTimer;
    int m_interval = 50;
    wxDECLARE_EVENT_TABLE();
};

#endif 


//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H
//
//#include <wx/wx.h>
//
//class MainWindow : public wxFrame
//{
//public:
//    MainWindow();
//    virtual ~MainWindow();
//
//private:
//    void OnQuit(wxCommandEvent& event);
//    void OnAbout(wxCommandEvent& event);
//    void OnNew(wxCommandEvent& event);
//    void OnOpen(wxCommandEvent& event);
//    void OnSave(wxCommandEvent& event);
//    void OnStep(wxCommandEvent& event);
//    void OnPlay(wxCommandEvent& event);
//    void OnStop(wxCommandEvent& event);
//    void OnClear(wxCommandEvent& event);
//    void UpdateStatusBar();
//    
//    wxMenu* fileMenu;
//    wxMenu* editMenu;
//    wxMenu* helpMenu;
//    wxToolBar* toolBar;
//    wxStatusBar* statusBar;
//    wxPanel* panel;
//    
//    int generation;
//    int livingCells;
//    
//    DECLARE_EVENT_TABLE()
//};
//
//#endif // MAINWINDOW_H





