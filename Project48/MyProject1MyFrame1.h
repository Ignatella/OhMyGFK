#ifndef __MyProject1MyFrame1__
#define __MyProject1MyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "MyFrame1.h"

//// end generated include

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/rawbmp.h>

#include <string>
#include <tuple>
#include <vector>
#include <array>
/** Implementing MyFrame1 */
class MyProject1MyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void move_graphics_key_down( wxKeyEvent& event );
		void on_update( wxUpdateUIEvent& event );
		void open_file_open_event( wxCommandEvent& event );
		void save_file_save_event( wxCommandEvent& event );
		void clear_pts_event( wxCommandEvent& event );
		void about_menu_authors_open( wxCommandEvent& event );
		void patch_click( wxCommandEvent& event );
		void org_size_click( wxCommandEvent& event );
		void width_size_click( wxCommandEvent& event );
		void height_size_click( wxCommandEvent& event );
		void fit_click( wxCommandEvent& event );
		void m_bitmap1_click( wxMouseEvent& event );
		void m_bitmap2_click( wxMouseEvent& event );
		void m_bitmap3_click( wxMouseEvent& event );
		void m_bitmap4_click( wxMouseEvent& event );
		void m_bitmap5_click( wxMouseEvent& event );
		void mouse_point_click( wxMouseEvent& event );
	public:
		/** Constructor */
		MyProject1MyFrame1( wxWindow* parent );
	//// end generated class members
private:
	void swap(int ind = 0);

	void iteratePoints(wxBitmap& bmp, wxBitmap& other);

	void movePositions(int shift, int y = 0);

	bool onSegment(wxPoint& p, wxPoint& q, wxPoint& r);

	int orientation(wxPoint& p, wxPoint& q, wxPoint& r);

	bool isInside(std::vector<wxPoint> polygon, int n, wxPoint& p);

	bool doIntersect(wxPoint& p1, wxPoint& q1, wxPoint& p2, wxPoint& q2);

	// holds original images
	std::array<wxImage, 5> images;
	// number of correct elements in images
	size_t no_images{ 0 };
	size_t currently_edited{ 0 };
	std::array<wxStaticBitmap*, 5> miniatures = { m_bitmap1, m_bitmap2, m_bitmap3, m_bitmap4, m_bitmap5 };

	// bitmap of currently displayed image
	wxBitmap current_bitmap;

	int mode = 0;
	//int current = 0;
	//int currentBitmap = 0;

	std::vector<wxPoint> positions;





};

#endif // __MyProject1MyFrame1__
