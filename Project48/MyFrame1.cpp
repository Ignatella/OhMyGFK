///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyFrame1.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(500, 350), wxDefaultSize);

	m_menubar1 = new wxMenuBar(0);
	file_menu = new wxMenu();
	wxMenuItem* file_menu_open_file;
	file_menu_open_file = new wxMenuItem(file_menu, wxID_ANY, wxString(wxT("Open File")) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL);
	file_menu->Append(file_menu_open_file);

	wxMenuItem* file_menu_save_file;
	file_menu_save_file = new wxMenuItem(file_menu, wxID_ANY, wxString(wxT("Save")) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL);
	file_menu->Append(file_menu_save_file);

	wxMenuItem* file_menu_clear_pts;
	file_menu_clear_pts = new wxMenuItem(file_menu, wxID_ANY, wxString(wxT("Clear Points")) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL);
	file_menu->Append(file_menu_clear_pts);

	m_menubar1->Append(file_menu, wxT("File"));

	about_menu = new wxMenu();
	wxMenuItem* about_menu_authors;
	about_menu_authors = new wxMenuItem(about_menu, wxID_ANY, wxString(wxT("Authors")) + wxT('\t') + wxT("Ctrl+A"), wxEmptyString, wxITEM_NORMAL);
	about_menu->Append(about_menu_authors);

	m_menubar1->Append(about_menu, wxT("About"));

	this->SetMenuBar(m_menubar1);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	patch_button = new wxButton(this, wxID_ANY, wxT("Patch"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(patch_button, 0, wxALL | wxEXPAND, 5);

	apply_button = new wxButton(this, wxID_ANY, wxT("Apply changes"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(apply_button, 0, wxALL | wxEXPAND, 5);

	org_size_button = new wxButton(this, wxID_ANY, wxT("Original Size"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(org_size_button, 0, wxALL | wxEXPAND, 5);

	width_size_button = new wxButton(this, wxID_ANY, wxT("Fit Width"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(width_size_button, 0, wxALL | wxEXPAND, 5);

	height_button = new wxButton(this, wxID_ANY, wxT("Fit Height"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(height_button, 0, wxALL | wxEXPAND, 5);

	fit_button = new wxButton(this, wxID_ANY, wxT("Fit to Screen"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(fit_button, 0, wxALL | wxEXPAND, 5);


	bSizer1->Add(bSizer4, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	bSizer2->SetMinSize(wxSize(-1, 60));
	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(0, 0), wxDefaultSize, 0);
	bSizer2->Add(m_bitmap1, 0, wxALL, 5);


	bSizer2->Add(20, 0, 0, wxEXPAND, 5);

	m_bitmap2 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(80, 0), wxDefaultSize, 0);
	bSizer2->Add(m_bitmap2, 0, wxALL, 5);

	m_bitmap3 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(160, 80), wxDefaultSize, 0);
	bSizer2->Add(m_bitmap3, 0, wxALL, 5);

	m_bitmap4 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(240, 0), wxDefaultSize, 0);
	bSizer2->Add(m_bitmap4, 0, wxALL, 5);

	m_bitmap5 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(360, 0), wxDefaultSize, 0);
	bSizer2->Add(m_bitmap5, 0, wxALL, 5);


	bSizer3->Add(bSizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	img_panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	img_panel->SetScrollRate(5, 5);
	img_panel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	bSizer5->Add(img_panel, 1, wxEXPAND | wxALL, 5);


	bSizer3->Add(bSizer5, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_CHAR_HOOK, wxKeyEventHandler(MyFrame1::move_graphics_key_down));
	this->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::on_update));
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::open_file_open_event), this, file_menu_open_file->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::save_file_save_event), this, file_menu_save_file->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::clear_pts_event), this, file_menu_clear_pts->GetId());
	about_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::about_menu_authors_open), this, about_menu_authors->GetId());
	patch_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::patch_click), NULL, this);
	apply_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::apply_click), NULL, this);
	org_size_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::org_size_click), NULL, this);
	width_size_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::width_size_click), NULL, this);
	height_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::height_size_click), NULL, this);
	fit_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::fit_click), NULL, this);
	m_bitmap1->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap1_click), NULL, this);
	m_bitmap2->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap2_click), NULL, this);
	m_bitmap3->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap3_click), NULL, this);
	m_bitmap4->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap4_click), NULL, this);
	m_bitmap5->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap5_click), NULL, this);
	img_panel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::mouse_point_click), NULL, this);
	img_panel->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MyFrame1::panel_right_click), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect(wxEVT_CHAR_HOOK, wxKeyEventHandler(MyFrame1::move_graphics_key_down));
	this->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::on_update));
	patch_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::patch_click), NULL, this);
	apply_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::apply_click), NULL, this);
	org_size_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::org_size_click), NULL, this);
	width_size_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::width_size_click), NULL, this);
	height_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::height_size_click), NULL, this);
	fit_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::fit_click), NULL, this);
	m_bitmap1->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap1_click), NULL, this);
	m_bitmap2->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap2_click), NULL, this);
	m_bitmap3->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap3_click), NULL, this);
	m_bitmap4->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap4_click), NULL, this);
	m_bitmap5->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::m_bitmap5_click), NULL, this);
	img_panel->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MyFrame1::mouse_point_click), NULL, this);
	img_panel->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(MyFrame1::panel_right_click), NULL, this);

}
