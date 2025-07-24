#pragma once
#include <wx/wx.h>
#include <wx/datetime.h>
class MainFrame;  
class GoalPanel : public wxPanel {
public:
    GoalPanel(wxWindow* parent, const wxString& goalText, int days, MainFrame* parentFrame);
    wxString GetGoalText() const;
    int GetDaysToDue() const;
    void OnDelete(wxCommandEvent& event);
    void OnEdit(wxCommandEvent& event);
    void SetGoalText(const wxString& newText);
private:
    MainFrame* parentFrame;
    wxTextCtrl* label;
    wxStaticText* dueLabel;
    wxButton* edit;
    wxButton* del;

    int storedDays;
    wxString GetDueDateString(int days);
};