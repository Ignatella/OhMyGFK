#include "AppFrame.h"
#include "Vertex.h"
#include "Polygon.h"

AppFrame::AppFrame(wxWindow* parent) : BaseFrame(parent)
{
	wxImage::AddHandler(new wxJPEGHandler);
}

void AppFrame::switch_images(size_t new_image) {
	currently_edited = new_image;
	org_size_click(wxCommandEvent());
}

void AppFrame::apply_click(wxCommandEvent& event)
{
	if (all_polygons.empty()) return;
	if (no_images == 1) return;

	wxProgressDialog progress_dialog{ "Patching...", "Wait until patching is completed",
		static_cast<int>(all_polygons.size()), this,
		wxPD_APP_MODAL | wxPD_SMOOTH | wxPD_AUTO_HIDE };

	images[0] = images[1].Copy();
	// i want to use for(int value{}; auto& poly : all_polygons) {} :(
	int value{};
	for (auto& poly : all_polygons) {
		iteratePoints(poly.first, poly.second);
		progress_dialog.Update(++value);
	}
	switch_images(0);
	images[1] = images[0];
	this->Update();
}

void AppFrame::move_graphics_key_down(wxKeyEvent& event)
{
	switch (event.GetKeyCode()) {
	case wxKeyCode::WXK_UP:
		movePositions(-1, 0);
		break;
	case wxKeyCode::WXK_DOWN:
		movePositions(1, 0);
		break;
	case wxKeyCode::WXK_LEFT:
		movePositions(-1, 1);
		break;
	case wxKeyCode::WXK_RIGHT:
		movePositions(1, 1);
		break;
	default:
		break;
	}
	event.Skip();
}

void AppFrame::on_update(wxUpdateUIEvent& event)
{
	if (no_images == 1) return;

	wxClientDC dc(this->img_panel);
	wxBufferedDC mdc(&dc);
	mdc.Clear();

	img_panel->DoPrepareDC(mdc);
	img_panel->SetVirtualSize(current_bitmap.GetSize());
	mdc.DrawBitmap(current_bitmap, wxPoint());

	if (patch_mode == 1) {
		mdc.SetBrush(*wxTRANSPARENT_BRUSH);
		mdc.SetPen(*wxGREEN_PEN);

		double ratio{ static_cast<double>(images[currently_edited].GetWidth()) / current_bitmap.GetWidth() };

		// vector of scaled polygon points, static to save on allocation
		static std::vector<wxPoint> tmp;
		tmp.reserve(polygon.size());
		std::transform(polygon.begin(), polygon.end(), std::back_inserter(tmp), [ratio](const Vertex& pt) {
			return wxPoint{
				static_cast<int>(pt.x / ratio),
				static_cast<int>(pt.y / ratio) };
			});

		mdc.DrawPolygon(tmp.size(), tmp.data());
		tmp.clear();
	}
}

void AppFrame::open_file_open_event(wxCommandEvent& event)
{
	if (no_images > 6) {
		wxMessageBox("Maximum images count exceeded", "Error", wxICON_ERROR);
		return;
	}

	wxFileDialog files(this, _("Choose images"), "", "", "*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (files.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxImage img(files.GetPath());
	images[no_images] = img; // shallow copy

	wxSize size{ img.GetSize() };
	double ratio{ size.x / static_cast<double>(size.y) };
	miniatures[no_images - 1]->SetBitmap(wxBitmap(img.Scale(static_cast<int>(50 * ratio), 50))); // Scale return new wxImage

	++no_images;
	switch_images(no_images - 1);

	Layout();
}

void AppFrame::save_file_save_event(wxCommandEvent& event)
{
	try
	{
		if (current_bitmap.IsOk())
		{
			current_bitmap.SaveFile("image.bmp", wxBitmapType::wxBITMAP_TYPE_BMP);
		}
		wxMessageBox("Image has been saved", "File saved", wxICON_INFORMATION);
	}
	catch (std::exception&)
	{
		wxMessageBox("Error while saving patched image!", "Error", wxICON_ERROR);
	}
}

void AppFrame::clear_pts_event(wxCommandEvent& event)
{
	polygon.clear();
	wxMessageBox("Points cleared", "Points cleared successfully");
}

void AppFrame::about_menu_authors_open(wxCommandEvent& event)
{
	wxMessageBox("Szymon Antkowiak\nIhnatsi Yermakovich\nPiotr Ptak", "Authors", wxICON_INFORMATION);
}

void AppFrame::patch_click(wxCommandEvent& event)
{
	if (no_images == 1) {
		wxMessageBox("Can't patch on the blank image", "An error has occured", wxICON_ERROR);
		return;
	}

	if (patch_mode) {
		all_polygons.emplace_back(polygon, currently_edited);
		polygon.clear();
		apply_button->Enable();
		patch_mode = false;
	}
	else {
		apply_button->Disable();
		patch_mode = true;
	}
}

void AppFrame::org_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	current_bitmap = wxBitmap(images[currently_edited]);
}

void AppFrame::width_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	wxSize panel_size{ img_panel->GetSize() };
	wxSize img_size{ images[currently_edited].GetSize() };
	double ratio{ img_size.x / static_cast<double>(img_size.y) };
	current_bitmap = wxBitmap(images[currently_edited].Scale(panel_size.x, static_cast<int>(panel_size.x / ratio)));
}

void AppFrame::height_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	wxSize panel_size{ img_panel->GetSize() };
	wxSize img_size{ images[currently_edited].GetSize() };
	double ratio{ img_size.x / static_cast<double>(img_size.y) };
	current_bitmap = wxBitmap(images[currently_edited].Scale(static_cast<int>(panel_size.y * ratio), panel_size.y));
}

void AppFrame::fit_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	wxSize panel_size{ img_panel->GetSize() };
	wxSize img_size{ images[currently_edited].GetSize() };
	double ratio{ img_size.x / static_cast<double>(img_size.y) };

	if (img_size.x * panel_size.y > img_size.y * panel_size.x)
		width_size_click(event);
	else
		height_size_click(event);
}

void AppFrame::m_bitmap1_click(wxMouseEvent& event) {
	switch_images(1);
}

void AppFrame::m_bitmap2_click(wxMouseEvent& event) {
	switch_images(2);
}

void AppFrame::m_bitmap3_click(wxMouseEvent& event) {
	switch_images(3);
}

void AppFrame::m_bitmap4_click(wxMouseEvent& event) {
	switch_images(4);
}

void AppFrame::m_bitmap5_click(wxMouseEvent& event) {
	switch_images(5);
}

void AppFrame::mouse_point_click(wxMouseEvent& event)
{
	if (patch_mode == 0) return;

	double ratio{ static_cast<double>(images[currently_edited].GetWidth()) / current_bitmap.GetWidth() };

	polygon.emplace_back(event.GetX(), event.GetY(), ratio);
}

void AppFrame::movePositions(int shift, bool direction)
{
	for (auto& pt : polygon) {
		pt.y += direction ? shift : 0;
		pt.x += direction ? shift : 0;
	}
}


void AppFrame::iteratePoints(std::vector<Vertex>& pos, size_t img)
{
	if (pos.empty()) return;

	const int x_min{ static_cast<int>(std::min_element(pos.begin(), pos.end(), Vertex::less_in_x)->x) - 1 };
	const int y_min{ static_cast<int>(std::min_element(pos.begin(), pos.end(), Vertex::less_in_y)->y) - 1 };
	const int x_max{ static_cast<int>(std::min_element(pos.begin(), pos.end(), Vertex::greater_in_x)->x) + 1 };
	const int y_max{ static_cast<int>(std::min_element(pos.begin(), pos.end(), Vertex::greater_in_y)->y) + 1 };

	auto& pixels = images[0];
	auto& pixelsNew = images[img];

#pragma omp parallel
	for (int i = x_min; i < x_max; i++) {
		for (int j = y_min; j < y_max; j++) {
			if (Polygon::isInside(pos, pos.size(), Vertex(i, j))) {
				pixels.SetRGB(i, j, pixelsNew.GetRed(i, j), pixelsNew.GetGreen(i, j), pixelsNew.GetBlue(i, j));
			}
		}
	}
}

void AppFrame::panel_right_click(wxMouseEvent& event) {
	if (!polygon.empty()) {
		polygon.pop_back();
	}
}
