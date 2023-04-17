#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_mainWindow = new MainWindow("Conway's Game of Life", wxDefaultPosition, wxSize(800, 600));
    m_mainWindow->Show();

    return true;
}
