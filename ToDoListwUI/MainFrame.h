#pragma once
#include <wx/wx.h>
#include <wx/popupwin.h>


class GoalPanel;
class MainFrame : public wxFrame
{
public:
	void RemoveGoal(GoalPanel* goal);
	void EditGoal(GoalPanel* goal);
	MainFrame(const wxString& title);

private:
	void OnAddGoalClicked(wxCommandEvent& event);
	void OnLogClicked(wxCommandEvent& event);
	void OnGitClicked(wxCommandEvent& event);
	void OnSliderChange(wxCommandEvent& event);
	void LoadGoalsFromFile();
	void SaveGoalsToFile();
	

	wxButton* logButton;
	wxPanel* logInfo;
	wxStaticText* logText;
	wxButton* gitButton;
	wxPanel* gitInfo;
	wxStaticText* gitText;
	wxSlider* sliderDays;
	wxStaticText* sliderInfo;
	wxStaticText* savedGoal;
	wxTextCtrl* inputGoal;
	wxStaticText* savedDate;
	wxStaticText* finDate;
	wxButton* addButton;
	wxScrolledWindow* goalList;
	wxBoxSizer* goalListSizer;


	void editSub() {
		wxString currentGoal = savedGoal->GetLabel();
		savedGoal->Hide();
		savedDate->Hide();
		inputGoal->Show();
		sliderDays->Show();
		sliderInfo->Show();
		addButton->SetLabel("Save goal");
	}
	void savedSub() {
		wxString newGoal = inputGoal->GetValue();
		inputGoal->Hide();
		savedDate->Show();
		savedGoal->SetLabel(newGoal);
		savedGoal->Show();
		sliderDays->Hide();
		sliderInfo->Hide();
		addButton->SetLabel("Add goal");
	}
};

