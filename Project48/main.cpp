#include <wx/wxprec.h>
#include "AppFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	AppFrame* frame = new AppFrame(NULL);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
