#include "frame.hpp"

enum {
  ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
   EVT_MENU(ID_Hello, MyFrame::OnHello)
   EVT_MENU(wxID_EXIT, MyFrame::OnExit)
   EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title,
		 const wxPoint& pos,
		 const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello... \tCtrl-H",
		   "Help String shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  this->SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Welcome to ZKProg");

  // Core of the window
  wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);


}

void MyFrame::OnHello(wxCommandEvent& event)
{
  wxLogMessage("Hello world from wxWidgets");
}


void MyFrame::OnExit(wxCommandEvent& event)
{
  this->Close(true);
}


void MyFrame::OnAbout(wxCommandEvent& event)
{
  wxMessageBox("This is the message of the message box",
	       "This is the title",
	       wxOK | wxICON_INFORMATION);
}
