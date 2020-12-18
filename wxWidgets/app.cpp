#include "app.hpp"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  MyFrame *frame = new MyFrame("Hello World",
			       wxPoint(50, 50),
			       wxSize(800, 600));

  frame->Show(true);
  return true;
}
