#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/datetime.h>
#include "GoalPanel.h"
#include <wx/file.h>


enum IDs {
	BUTTON_ID = 2,
	LOGBUTTON_ID,
	SLIDER_ID,
	GITBUTTON_ID,
	EDIT_ID,
	DEL_ID,
	
};



GoalPanel::GoalPanel(wxWindow* parent, const wxString& goalText, int days, MainFrame* parentFrame)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 70), wxBORDER_SIMPLE),
	storedDays(days), parentFrame(parentFrame)
	// wiêkszy height
{

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* topRowSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetBackgroundColour(wxColour(90, 90, 90));

	label = new wxTextCtrl(this, wxID_ANY, goalText,wxDefaultPosition, wxSize(200, -1), wxTE_MULTILINE|wxTE_WORDWRAP| wxBORDER_NONE);
	label->SetEditable(false);
	label->SetScrollbar(wxVERTICAL,0,0,0);
	label->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	label->SetForegroundColour(wxColour(44, 44, 44));
	label->SetBackgroundColour(wxColour(90, 90, 90));
	label->SetMinSize(wxSize(200, -1));  

	edit = new wxButton(this, EDIT_ID, "Edit");
	edit->SetBackgroundColour(wxColour(33, 33, 33));
	edit->SetForegroundColour(wxColour(222, 222, 222));

	del = new wxButton(this, DEL_ID, "Delete");
	del->SetBackgroundColour(wxColour(33, 33, 33));
	del->SetForegroundColour(wxColour(222, 222, 222));

	del->Bind(wxEVT_BUTTON, &GoalPanel::OnDelete, this);
	edit->Bind(wxEVT_BUTTON, &GoalPanel::OnEdit, this);


	topRowSizer->Add(label, 1, wxEXPAND | wxALIGN_TOP | wxLEFT, 2);
	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxVERTICAL); 

	buttonsSizer->Add(edit, 0, wxBOTTOM, 2);  
	buttonsSizer->Add(del, 0);

	topRowSizer->Add(buttonsSizer, 0, wxALIGN_TOP | wxRIGHT, 5);

	dueLabel = new wxStaticText(this, wxID_ANY, GetDueDateString(days));
	dueLabel->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	dueLabel->SetForegroundColour(wxColour(33, 33, 33));
	dueLabel->SetMinSize(wxSize(-1, 15));

	mainSizer->Add(topRowSizer, 0, wxEXPAND | wxTOP, 2); 
	mainSizer->Add(dueLabel, 0, wxLEFT|wxTOP, 3);              

	SetSizer(mainSizer);
	Layout();
}

void GoalPanel::OnDelete(wxCommandEvent& event) {
	if (parentFrame) {
		parentFrame->RemoveGoal(this);
	}
}
void GoalPanel::OnEdit(wxCommandEvent& event) {
	if (parentFrame) {
		label->SetEditable(!label->IsEditable());
	}
}

wxString GoalPanel::GetDueDateString(int days) {
	wxDateTime due = wxDateTime::Now().Add(wxTimeSpan::Days(days));
	return "Due: " + due.Format("%d %B %Y %H:%M");
}

MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(mainSizer);
	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);


	wxStaticText* titleText = new wxStaticText(panel, wxID_ANY, "ToDoList v.0.4");
	titleText->SetFont(wxFont(25, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	titleText->SetForegroundColour(wxColour(33, 33, 33));
	titleText->SetBackgroundColour(wxColour(77, 77, 77));
	wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);


	logButton = new wxButton(panel, LOGBUTTON_ID, "Log", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	logButton->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	logButton->SetForegroundColour(wxColour(200, 200, 200));
	logButton->SetBackgroundColour(wxColour(77, 77, 77));

	logInfo = new wxPanel(panel, wxID_ANY, wxPoint(80, 80), wxSize(230, 230), wxBORDER_SUNKEN);
	logInfo->SetBackgroundColour(wxColor(80, 80, 80));
	logInfo->Hide();
	logText = new wxStaticText(logInfo, wxID_ANY, "v.0.4 Update log\n -Added goal editing\n -Added logs", wxPoint(10, 30));
	logText->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	logText->SetForegroundColour(wxColour(33, 33, 33));
	
	gitButton = new wxButton(panel, GITBUTTON_ID, "Socials", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	gitButton->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	gitButton->SetForegroundColour(wxColour(200, 200, 200));
	gitButton->SetBackgroundColour(wxColour(77, 77, 77));


	gitInfo = new wxPanel(panel, wxID_ANY, wxPoint(75, 80), wxSize(230, 90), wxBORDER_SUNKEN);
	gitInfo->SetBackgroundColour(wxColor(80, 80, 80));
	gitInfo->Hide();
	gitText = new wxStaticText(gitInfo, wxID_ANY, "github.com/Kuz03d\nartstation.com/kuzu3d\nlinkedin.com/in/kuzo3d", wxPoint(5, 10));
	gitText->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	gitText->SetForegroundColour(wxColour(33, 33, 33));


	wxDateTime now = wxDateTime::Now();
	wxString formatted = now.Format("%d %B %Y\n %H:%M ");
	savedDate = new wxStaticText(panel, wxID_ANY, "Created: "+formatted, wxPoint(20, 155), wxSize(110, 15), wxALIGN_CENTER);
	savedDate->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	savedDate->SetForegroundColour(wxColour(44, 44, 44));
	savedDate->SetBackgroundColour(wxColour(80, 80, 80));
	savedDate->Hide();

	goalList = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 200), wxVSCROLL);
	goalList->SetScrollRate(0, 10);
	goalList->SetBackgroundColour(wxColour(70, 70, 70));
	goalListSizer = new wxBoxSizer(wxVERTICAL);
	goalList->SetSizer(goalListSizer);

	inputGoal = new wxTextCtrl(panel, wxID_ANY, "Your goal, ex. Learn C++");
	inputGoal->SetSize(wxSize(270, 50));
	inputGoal->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	inputGoal->SetForegroundColour(wxColour(66, 66, 66));
	inputGoal->SetBackgroundColour(wxColour(90, 90, 90));

	
	sliderDays = new wxSlider(panel, SLIDER_ID, 1, 1, 30, wxDefaultPosition, wxSize(200,30), wxSL_HORIZONTAL | wxSL_LABELS);
	sliderDays->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	sliderDays->SetForegroundColour(wxColour(80, 80, 80));
	sliderInfo = new wxStaticText(panel, wxID_ANY, "DAYS TO DUE DATE:",wxDefaultPosition, wxSize(180, 20));
	sliderInfo->SetFont(wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	sliderInfo->SetForegroundColour(wxColour(80, 80, 80));



	finDate = new wxStaticText(panel, wxID_ANY, "Due: N/A",wxDefaultPosition,wxDefaultSize, wxALIGN_CENTER);
	finDate -> SetMinSize(wxSize(130,40));
	finDate->SetMaxSize(wxSize(130, 40));

	finDate->SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
	finDate->SetForegroundColour(wxColour(44, 44, 44));
	finDate->SetBackgroundColour(wxColour(80, 80, 80));

	savedGoal = new wxStaticText(panel, wxID_ANY, "Your goal, ex. Learn C++", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	savedGoal->SetMaxSize(wxSize(270, 50));
	savedGoal->SetFont(wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	savedGoal->SetForegroundColour(wxColour(44, 44, 44));
	savedGoal->SetBackgroundColour(wxColour(90, 90, 90));
	savedGoal->Hide();

	addButton = new wxButton(panel, BUTTON_ID, "Save goal", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	addButton->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	addButton->SetForegroundColour(wxColour(222, 222, 222));
	addButton->SetBackgroundColour(wxColour(33, 33, 33));

	wxBoxSizer* sliderRowSizer = new wxBoxSizer(wxHORIZONTAL);

	inputSizer->Add(inputGoal, 1, wxEXPAND | wxALL, 1);
	inputSizer->Add(addButton, 0, wxALL, 1);
	mainSizer->Add(titleText, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 8);
	headerSizer->Add(logButton, 0, wxALL, 1);
	headerSizer->Add(gitButton, 0, wxALL, 1);
	mainSizer->Add(headerSizer, 0,wxALIGN_CENTER);
	mainSizer->Add(inputSizer, 0, wxEXPAND | wxLEFT | wxRIGHT , 2);
	mainSizer->Add(sliderInfo, 0, wxLEFT | wxTOP, 10);
	

	sliderRowSizer->Add(sliderDays, 1,  wxLEFT|wxBOTTOM ,5);
	sliderRowSizer->Add(finDate, 0, wxRIGHT|wxLEFT| wxALIGN_LEFT, 30);
	mainSizer->Add(sliderRowSizer,0,wxTOP,1);
	mainSizer->Add(goalList, 1, wxEXPAND | wxTOP, 5);

	Bind(wxEVT_BUTTON, &MainFrame::OnAddGoalClicked, this, BUTTON_ID);
	Bind(wxEVT_BUTTON,  &MainFrame::OnLogClicked,this,LOGBUTTON_ID);
	Bind(wxEVT_BUTTON, &MainFrame::OnGitClicked, this, GITBUTTON_ID);
	Bind(wxEVT_SLIDER, &MainFrame::OnSliderChange,this,SLIDER_ID);

	LoadGoalsFromFile();






}

void MainFrame::OnAddGoalClicked(wxCommandEvent& event)
{
	wxString goalText = inputGoal->GetValue();
	int days = sliderDays->GetValue();

	if (goalText.IsEmpty()) return;

	GoalPanel* goalPanel = new GoalPanel(goalList, goalText, days, this);

	goalListSizer->Add(goalPanel, 0, wxEXPAND | wxALL, 6);
	goalListSizer->Layout();
	goalList->FitInside(); 
	goalList->SetScrollRate(0, 10);

	inputGoal->SetValue("");
	sliderDays->SetValue(1);
	finDate->SetLabel("Due: N/A");
	SaveGoalsToFile();
	Layout();


}

wxString EscapeText(const wxString& text) {
	wxString safe = text;
	safe.Replace("|", "[PIPE]");
	safe.Replace("\n", "[NL]");
	return safe;
}

wxString UnescapeText(const wxString& text) {
	wxString raw = text;
	raw.Replace("[PIPE]", "|");
	raw.Replace("[NL]", "\n");
	return raw;
}

void MainFrame::OnLogClicked(wxCommandEvent& event) {
	logInfo->Show(!logInfo->IsShown());
	gitButton->Enable(!gitButton->IsEnabled());
	addButton->Enable(!addButton->IsEnabled());
	sliderDays->Show(!sliderDays->IsShown());
	inputGoal->SetEditable(!inputGoal->IsEditable());

	Layout(); 
}
void MainFrame::OnGitClicked(wxCommandEvent& event) {
	gitInfo->Show(!gitInfo->IsShown());
	logButton->Enable(!logButton->IsEnabled());
	addButton->Enable(!addButton->IsEnabled());
	sliderDays->Show(!sliderDays->IsShown());
	inputGoal->SetEditable(!inputGoal->IsEditable());
	Layout();
}

void MainFrame::RemoveGoal(GoalPanel* goal) {
	goalListSizer->Detach(goal);  
	goal->Destroy();              
	goalListSizer->Layout();      
	goalList->FitInside();
	SaveGoalsToFile();           
}
void MainFrame::OnSliderChange(wxCommandEvent& event) {
	int days = sliderDays->GetValue();

	wxDateTime now = wxDateTime::Now();
	wxDateTime dueDate = now.Add(wxTimeSpan::Days(days));
	wxString formattedFin = dueDate.Format("%d %B %Y\n %H:%M ");
	finDate->SetLabel("Due: " + formattedFin);
};

void MainFrame::SaveGoalsToFile() {
	wxFile file("goals.txt", wxFile::write);
	if (!file.IsOpened()) return;

	for (size_t i = 0; i < goalListSizer->GetChildren().GetCount(); ++i) {
		wxSizerItem* item = goalListSizer->GetChildren()[i];
		GoalPanel* goalPanel = dynamic_cast<GoalPanel*>(item->GetWindow());
		if (goalPanel) {
			wxString text = EscapeText(goalPanel->GetGoalText());
			int days = goalPanel->GetDaysToDue();
			wxString line = text + "|" + wxString::Format("%d", days) + "\n";			
			file.Write(line);
		}
	}
	file.Close();
}

void MainFrame::LoadGoalsFromFile() {
	wxFile file("goals.txt", wxFile::read);
	if (!file.IsOpened()) return;

	wxString data;
	file.ReadAll(&data);

	wxArrayString lines = wxSplit(data, '\n');
	for (const wxString& line : lines) {
		if (line.IsEmpty()) continue;
		wxArrayString parts = wxSplit(line, '|');
		if (parts.GetCount() == 2) {
			wxString goalText = UnescapeText(parts[0]);
			long days = 1;
			parts[1].ToLong(&days);
			GoalPanel* goalPanel = new GoalPanel(goalList, goalText, days, this);
			goalListSizer->Add(goalPanel, 0, wxEXPAND | wxALL, 6);
		}
	}
	goalListSizer->Layout();
	goalList->FitInside();
	file.Close();
}
wxString GoalPanel::GetGoalText() const {
	return label->GetLabel();
}

int GoalPanel::GetDaysToDue() const {
	return storedDays;
}
