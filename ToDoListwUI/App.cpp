#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App :: OnInit() {
	MainFrame* mainFrame = new MainFrame("ToDoList");
	mainFrame->SetBackgroundColour(wxColour(44,44,44));
	mainFrame->Refresh();
	mainFrame->SetClientSize(400,800);
	mainFrame->SetMaxSize(wxSize(400,800));
	mainFrame->SetMinSize(wxSize(400, 800));
	mainFrame->Centre();
	mainFrame->Show();

	return true;
}
