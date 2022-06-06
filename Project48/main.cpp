#include <wx/wxprec.h>
#include "MyProject1MyFrame1.h"
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyProject1MyFrame1* frame = new MyProject1MyFrame1(NULL);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
