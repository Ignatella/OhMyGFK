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
#include <functional>

#include "BaseFrame.h"
#include "Vertex.h"

class AppFrame : public BaseFrame
{
protected:
	/**
	 * @brief event handler for keyboard keys (moving shapes)
	 *
	 * @param event
	 */
	void move_graphics_key_down(wxKeyEvent& event);
	/**
	 * @brief method that fires on each update
	 *
	 * @param event
	 */
	void on_update(wxUpdateUIEvent& event);
	/**
	 * @brief method that handles the open file event (loads up to 5 images in jpeg format)
	 *
	 * @param event
	 */
	void open_file_open_event(wxCommandEvent& event);
	/**
	 * @brief method that saves the image as image.bmp file
	 *
	 * @param event
	 */
	void save_file_save_event(wxCommandEvent& event);
	/**
	 * @brief method that clears points from the currently edited polygon
	 *
	 * @param event
	 */
	void clear_pts_event(wxCommandEvent& event);
	/**
	 * @brief method that handles about menu submenu click (displays wxMessageBox with authors of the app)
	 *
	 * @param event
	 */
	void about_menu_authors_open(wxCommandEvent& event);
	/**
	 * @brief method that restores the patched image to its initial state
	 *
	 * @param event
	 */
	void restore_img_click(wxCommandEvent& event);
	/**
	 * @brief method that is used to stage the patched polygon
	 *
	 * @param event
	 */
	void patch_click(wxCommandEvent& event);
	/**
	 * @brief method that applies all changes to the first bitmap
	 *
	 * @param event
	 */
	void apply_click(wxCommandEvent& event);
	/**
	 * @brief method that restores image to its initial dimensions
	 *
	 * @param event
	 */
	void org_size_click(wxCommandEvent& event);
	/**
	 * @brief method that fits the width of the image to the width of the panel (preserves scale)
	 *
	 * @param event
	 */
	void width_size_click(wxCommandEvent& event);
	/**
	 * @brief method that fits the height of the image to the height of the panel (preserves scale)
	 *
	 * @param event
	 */
	void height_size_click(wxCommandEvent& event);
	/**
	 * @brief method that fits image to the dimensions of the wxPanel
	 *
	 * @param event
	 */
	void fit_click(wxCommandEvent& event);
	/**
	 * @brief method that handles the change to the first bitmap (from the left) (react to the KeyUp event on the wxStaticBitmap)
	 *
	 * @param event
	 */
	void m_bitmap1_click(wxMouseEvent& event);
	/**
	 * @brief method that handles the change to the second bitmap (from the left) (react to the KeyUp event on the wxStaticBitmap)
	 *
	 * @param event
	 */
	void m_bitmap2_click(wxMouseEvent& event);
	/**
	 * @brief method that handles the change to the third bitmap (from the left) (react to the KeyUp event on the wxStaticBitmap)
	 *
	 * @param event
	 */
	void m_bitmap3_click(wxMouseEvent& event);
	/**
	 * @brief method that handles the change to the fourth bitmap (from the left) (react to the KeyUp event on the wxStaticBitmap)
	 *
	 * @param event
	 */
	void m_bitmap4_click(wxMouseEvent& event);
	/**
	 * @brief method that handles the change to the fifth bitmap (from the left) (react to the KeyUp event on the wxStaticBitmap)
	 *
	 * @param event
	 */
	void m_bitmap5_click(wxMouseEvent& event);
	/**
	 * @brief method that handles left mouse click on the img panel
	 *
	 * @param event
	 */
	void mouse_point_click(wxMouseEvent& event);
	/**
	 * @brief method that handles right mouse click on the img panel
	 *
	 * @param event
	 */
	void panel_right_click(wxMouseEvent& event);

public:
	AppFrame(wxWindow* parent);

private:
	/**
	 * @brief method used to switch images
	 *
	 * @param new_image
	 */
	void switch_images(size_t new_image);

	/**
	 * @brief method that iterates throught the points of the vector of positions in order to apply changes to the background images
	 *
	 * @param pos
	 * @param img
	 */
	void iteratePoints(std::vector<Vertex>& pos, size_t img);

	/**
	 * @brief function that is used to move points of the currently edited polygon
	 *
	 * @param shift
	 * @param direction
	 */
	void movePositions(int shift, bool direction = false);

	// holds original images (first is patched img)
	std::array<wxImage, 6> images;
	// number of correct elements in images array (first is patched img)
	size_t no_images{ 1 };
	// variable that stores the index of the currently edited image
	size_t currently_edited{};
	// array that stores all the miniatures
	std::array<wxStaticBitmap*, 5> miniatures = { m_bitmap1, m_bitmap2, m_bitmap3, m_bitmap4, m_bitmap5 };
	// bitmap of currently displayed image
	wxBitmap current_bitmap;
	// bitmap that acts like the background for patch process
	wxBitmap bg_bitmap;
	// stores original image
	wxImage original_image;
	// variable that determines whether the app is in the patch mode or not
	bool patch_mode{ false };
	// vector of points that make polygon
	std::vector<Vertex> polygon;
	// vector of all polygons (polygon, src image number)
	std::vector<std::pair<std::vector<Vertex>, size_t>> all_polygons;
	// variable that detemines current display mode
	enum class display_modes {
		original, heigh, width, fit
	} display_mode{ display_modes::original };
};
