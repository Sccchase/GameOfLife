#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include <wx/wx.h>



wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnResize)
EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
EVT_MENU(10001, MainWindow::OnStart)
EVT_MENU(10002, MainWindow::OnStop)
EVT_MENU(10003, MainWindow::OnTick)
EVT_MENU(10004, MainWindow::OnClear)
EVT_MENU(10005, MainWindow::OnPlay)
EVT_MENU(10006, MainWindow::OnPause)
EVT_MENU(10007, MainWindow::OnNext)
EVT_MENU(10008, MainWindow::OnTrash)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), drawingPanel(new DrawingPanel(this))
    , m_pTimer(new wxTimer(this, wxID_ANY)), m_interval(50)

{


    // Create a menu bar
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "&Quit");
    wxMenu* gameMenu = new wxMenu;
    gameMenu->Append(10001, "&Start\tSpace", "Start or Resume the Game");
    gameMenu->Append(10002, "&Stop\tEscape", "Stop the Game");
    gameMenu->Append(10003, "&Tick\tEnter", "Advance One Generation");
    gameMenu->Append(10004, "&Clear", "Clear the Game Board");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(gameMenu, "&Game");
    SetMenuBar(menuBar);

  

    wxToolBar* toolbar = CreateToolBar();
    toolbar->AddTool(10005,"play", wxBitmap(play_xpm));
    toolbar->AddTool(10006, "Pause", wxBitmap(pause_xpm));
    toolbar->AddTool(10007, "Next", wxBitmap(next_xpm));
    toolbar->AddTool(10008, "Trash", wxBitmap(trash_xpm));
    toolbar->Realize();

    // Create a status bar
    CreateStatusBar();
    SetStatusText("Welcome to the Game of Life!");

    // Create the game board
    m_gameBoard = std::vector<std::vector<bool>>(50, std::vector<bool>(50));




    // Bind menu events to event handlers
    Bind(wxEVT_MENU, &MainWindow::OnQuit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnStart, this, 10001);
    Bind(wxEVT_MENU, &MainWindow::OnStop, this, 10002);
    Bind(wxEVT_MENU, &MainWindow::OnTick, this, 10003);
    Bind(wxEVT_MENU, &MainWindow::OnClear, this, 10004);
    Bind(wxEVT_MENU, &MainWindow::OnPlay, this, 10005);
    Bind(wxEVT_MENU, &MainWindow::OnPause, this, 10006);
    Bind(wxEVT_MENU, &MainWindow::OnNext, this, 10007);
    Bind(wxEVT_MENU, &MainWindow::OnTrash, this, 10008);

 
  


}


void MainWindow::OnQuit(wxCommandEvent& event) {
    Close(true);
}

void MainWindow::OnStart(wxCommandEvent& event) {
   SetStatusText("Starting the Game...");
   
}


void MainWindow::OnStop(wxCommandEvent& event) {
    SetStatusText("Stopping the Game...");
    
}

void MainWindow::OnTick(wxCommandEvent& event) {
    SetStatusText("Advancing One Generation...");
}


void MainWindow::OnClear(wxCommandEvent& event) {
    SetStatusText("Clearing the Game Board...");
    ClearBoard();
}

void MainWindow::OnResize(wxSizeEvent& event) {
    if (drawingPanel) {
        drawingPanel->SetSize(event.GetSize());
        drawingPanel->Refresh();
    }
    event.Skip();
}


void MainWindow::OnPlay(wxCommandEvent& event) {
    m_pTimer->Start(m_interval);
}

void MainWindow::OnPause(wxCommandEvent& event) {
    m_pTimer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& WXUNUSED(event)) {
    NextGeneration();
}


void MainWindow::OnTrash(wxCommandEvent& event) {
    ClearBoard();
}

void MainWindow::OnTimer(wxTimerEvent& event){
    NextGeneration();
}


int MainWindow::CountNeighbors(int row, int col)
{
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < m_gameBoard.size() && j >= 0 && j < m_gameBoard[0].size() && (i != row || j != col))
            {
                if (m_gameBoard[i][j])
                {
                    count++;
                }
            }
        }
    }
    return count;
}

void MainWindow::NextGeneration() {
    // Create a sandbox with the same dimensions as the game board
    std::vector<std::vector<bool>> sandbox(m_gameBoard.size(), std::vector<bool>(m_gameBoard[0].size(), false));

    // Iterate through the game board
    int livingCount = 0;
    for (int i = 0; i < m_gameBoard.size(); i++) {
        for (int j = 0; j < m_gameBoard[i].size(); j++) {
            // Count the number of living neighbors
            int neighborCount = CountNeighbors(i, j);

            // Determine whether the current cell should be alive or dead in the next generation
            if (m_gameBoard[i][j] == true && neighborCount < 2) {
                sandbox[i][j] = false;  // Die of loneliness
            } else if (m_gameBoard[i][j] == true && neighborCount > 3) {
                sandbox[i][j] = false;  // Die of overpopulation
            } else if (m_gameBoard[i][j] == true && (neighborCount == 2 || neighborCount == 3)) {
                sandbox[i][j] = true;  // Live on
                livingCount++;
            } else if (m_gameBoard[i][j] == false && neighborCount == 3) {
                sandbox[i][j] = true;  // Resurrect
                livingCount++;
            }
        }
    }

    // Copy the sandbox to the game board
    m_gameBoard.swap(sandbox);

    // Update the generation count, status text, and drawing panel
    m_generation++;
    UpdateStatusText();
    drawingPanel->Refresh();

    // If all cells are dead, stop the simulation
    if (livingCount == 0) {
        StopSimulation();
    }
}
void MainWindow::UpdateStatusText() {
    wxString statusText;
    statusText << "Generation: " << m_generation << "  Living: " << GetLivingCount();
    SetStatusText(statusText);
}
void MainWindow::StopSimulation() {
    if (m_pTimer->IsRunning()) {
        m_pTimer->Stop();
    }
}


int MainWindow::GetLivingCount() const
{
    int count = 0;
    for (const auto& row : m_gameBoard) {
        for (const auto& cell : row) {
            if (cell) {
                count++;
            }
        }
    }
    return count;
}
void MainWindow::ClearBoard()
{
    // Set all cells to false
    for (int i = 0; i < m_gameBoard.size(); i++) {
        for (int j = 0; j < m_gameBoard[i].size(); j++) {
            m_gameBoard[i][j] = false;
        }
    }

    // Reset generation count
    m_generation = 0;

    // Update status text
    wxString statusText;
    statusText << "Generation: " << m_generation << "   Living Cells: " << GetLivingCount();
    UpdateStatusText();

    // Refresh drawing panel
    drawingPanel->Refresh();
}







