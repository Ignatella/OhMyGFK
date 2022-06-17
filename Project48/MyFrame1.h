///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxMenuBar* m_menubar1;
	wxMenu* file_menu;
	wxMenu* about_menu;
	wxButton* patch_button;
	wxButton* apply_button;
	wxButton* org_size_button;
	wxButton* width_size_button;
	wxButton* height_button;
	wxButton* fit_button;
	wxStaticBitmap* m_bitmap1;
	wxStaticBitmap* m_bitmap2;
	wxStaticBitmap* m_bitmap3;
	wxStaticBitmap* m_bitmap4;
	wxStaticBitmap* m_bitmap5;
	wxScrolledWindow* img_panel;

	// Virtual event handlers, override them in your derived class
	virtual void move_graphics_key_down(wxKeyEvent& event) { event.Skip(); }
	virtual void on_update(wxUpdateUIEvent& event) { event.Skip(); }
	virtual void open_file_open_event(wxCommandEvent& event) { event.Skip(); }
	virtual void save_file_save_event(wxCommandEvent& event) { event.Skip(); }
	virtual void clear_pts_event(wxCommandEvent& event) { event.Skip(); }
	virtual void about_menu_authors_open(wxCommandEvent& event) { event.Skip(); }
	virtual void patch_click(wxCommandEvent& event) { event.Skip(); }
	virtual void apply_click(wxCommandEvent& event) { event.Skip(); }
	virtual void org_size_click(wxCommandEvent& event) { event.Skip(); }
	virtual void width_size_click(wxCommandEvent& event) { event.Skip(); }
	virtual void height_size_click(wxCommandEvent& event) { event.Skip(); }
	virtual void fit_click(wxCommandEvent& event) { event.Skip(); }
	virtual void m_bitmap1_click(wxMouseEvent& event) { event.Skip(); }
	virtual void m_bitmap2_click(wxMouseEvent& event) { event.Skip(); }
	virtual void m_bitmap3_click(wxMouseEvent& event) { event.Skip(); }
	virtual void m_bitmap4_click(wxMouseEvent& event) { event.Skip(); }
	virtual void m_bitmap5_click(wxMouseEvent& event) { event.Skip(); }
	virtual void mouse_point_click(wxMouseEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

