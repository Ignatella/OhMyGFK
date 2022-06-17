#pragma once



#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/rawbmp.h>
#include <wx/progdlg.h>

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>
#include <array>

#include "BaseFrame.h"
#include "Vertex.h"

class AppFrame : public BaseFrame
{
protected:
	void move_graphics_key_down(wxKeyEvent& event);
	void on_update(wxUpdateUIEvent& event);
	void open_file_open_event(wxCommandEvent& event);
	void save_file_save_event(wxCommandEvent& event);
	void clear_pts_event(wxCommandEvent& event);
	void about_menu_authors_open(wxCommandEvent& event);
	void patch_click(wxCommandEvent& event);
	void apply_click(wxCommandEvent& event);
	void org_size_click(wxCommandEvent& event);
	void width_size_click(wxCommandEvent& event);
	void height_size_click(wxCommandEvent& event);
	void fit_click(wxCommandEvent& event);
	void m_bitmap1_click(wxMouseEvent& event);
	void m_bitmap2_click(wxMouseEvent& event);
	void m_bitmap3_click(wxMouseEvent& event);
	void m_bitmap4_click(wxMouseEvent& event);
	void m_bitmap5_click(wxMouseEvent& event);
	void mouse_point_click(wxMouseEvent& event);
	void panel_right_click(wxMouseEvent& event);

public:
	AppFrame(wxWindow* parent);
private:

	void switch_images(size_t new_image);

	void iteratePoints(std::vector<Vertex>& pos, size_t img);

	void movePositions(int shift, bool direction = false);

	// holds original images (first is patched img)
	std::array<wxImage, 6> images;
	// number of correct elements in images array (first is patched img)
	size_t no_images{ 1 };
	size_t currently_edited{};
	std::array<wxStaticBitmap*, 5> miniatures = { m_bitmap1, m_bitmap2, m_bitmap3, m_bitmap4, m_bitmap5 };

	// bitmap of currently displayed image
	wxBitmap current_bitmap;
	// bitmap that acts like the background for patch process
	wxBitmap bg_bitmap;

	bool patch_mode{ false };

	// vector of points that make polygon
	std::vector<Vertex> polygon;
	// vector of all polygons (polygon, src image number)
	std::vector<std::pair<std::vector<Vertex>, size_t>> all_polygons;
};
