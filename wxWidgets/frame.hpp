#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>

#include <GL/glew.h>
#include <wx/glcanvas.h>

using std::cout;
using std::cend;

class MyFrame : public wxFrame
{
public:
  MyFrame(const wxString& title,
	  const wxPoint& pos,
	  const wxSize& size);
private:
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};
