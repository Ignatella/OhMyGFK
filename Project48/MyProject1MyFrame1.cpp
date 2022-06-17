#include "MyProject1MyFrame1.h"
#include <algorithm>

MyProject1MyFrame1::MyProject1MyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	wxImage::AddHandler(new wxJPEGHandler);
}

void MyProject1MyFrame1::switch_images(size_t new_image) {
	currently_edited = new_image;
	org_size_click(wxCommandEvent());
}

void MyProject1MyFrame1::apply_click(wxCommandEvent& event)
{
	if (all_polygons.empty()) return;
	if (no_images == 1) return;

	images[0] = images[1].Copy();
	for (auto& poly : all_polygons) {
		iteratePoints(poly.first, poly.second);
	}

	switch_images(0);
	this->Update();
}

void MyProject1MyFrame1::move_graphics_key_down(wxKeyEvent& event)
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

void MyProject1MyFrame1::on_update(wxUpdateUIEvent& event)
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

void MyProject1MyFrame1::open_file_open_event(wxCommandEvent& event)
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

void MyProject1MyFrame1::save_file_save_event(wxCommandEvent& event)
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

void MyProject1MyFrame1::clear_pts_event(wxCommandEvent& event)
{
	polygon.clear();
	wxMessageBox("Points cleared", "Points cleared successfully");
}

void MyProject1MyFrame1::about_menu_authors_open(wxCommandEvent& event)
{
	wxMessageBox("Ignacy, Piotr, Szymon", "Authors", wxICON_INFORMATION);
}

void MyProject1MyFrame1::patch_click(wxCommandEvent& event)
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

void MyProject1MyFrame1::org_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	current_bitmap = wxBitmap(images[currently_edited]);
}

void MyProject1MyFrame1::width_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	wxSize panel_size{ img_panel->GetSize() };
	wxSize img_size{ images[currently_edited].GetSize() };
	double ratio{ img_size.x / static_cast<double>(img_size.y) };
	current_bitmap = wxBitmap(images[currently_edited].Scale(panel_size.x, static_cast<int>(panel_size.x / ratio)));
}

void MyProject1MyFrame1::height_size_click(wxCommandEvent& event)
{
	if (no_images == 1) return;

	wxSize panel_size{ img_panel->GetSize() };
	wxSize img_size{ images[currently_edited].GetSize() };
	double ratio{ img_size.x / static_cast<double>(img_size.y) };
	current_bitmap = wxBitmap(images[currently_edited].Scale(static_cast<int>(panel_size.y * ratio), panel_size.y));
}

void MyProject1MyFrame1::fit_click(wxCommandEvent& event)
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

void MyProject1MyFrame1::m_bitmap1_click(wxMouseEvent& event) {
	switch_images(1);
}

void MyProject1MyFrame1::m_bitmap2_click(wxMouseEvent& event) {
	switch_images(2);
}

void MyProject1MyFrame1::m_bitmap3_click(wxMouseEvent& event) {
	switch_images(3);
}

void MyProject1MyFrame1::m_bitmap4_click(wxMouseEvent& event) {
	switch_images(4);
}

void MyProject1MyFrame1::m_bitmap5_click(wxMouseEvent& event) {
	switch_images(5);
}

void MyProject1MyFrame1::mouse_point_click(wxMouseEvent& event)
{
	if (patch_mode == 0) return;

	double ratio{ static_cast<double>(images[currently_edited].GetWidth()) / current_bitmap.GetWidth() };

	if (polygon.size() == 0) {
		polygon.emplace_back(event.GetX(), event.GetY(), ratio);
		polygon.emplace_back(event.GetX(), event.GetY(), ratio);
	}
	else {
		polygon.emplace_back(event.GetX(), event.GetY(), ratio);
	}
}

void MyProject1MyFrame1::movePositions(int shift, bool direction)
{
	for (auto& pt : polygon) {
		pt.y += direction ? shift : 0;
		pt.x += direction ? shift : 0;
	}
}


// Returns true if the point p lies inside the polygon[] with n vertices
bool MyProject1MyFrame1::isInside(std::vector<Vertex> polygon, int n, Vertex& p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3)
		return false;

	// Create a point for line segment from p to infinite
	Vertex extreme{ 5000, p.y };

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1; // Same as (count%2 == 1)
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int MyProject1MyFrame1::orientation(Vertex& p, Vertex& q, Vertex& r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return 0;			  // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool MyProject1MyFrame1::doIntersect(Vertex& p1, Vertex& q1, Vertex& p2, Vertex& q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1))
		return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1))
		return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2))
		return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2))
		return true;

	return false; // Doesn't fall in any of the above cases
}


// from:https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool MyProject1MyFrame1::onSegment(Vertex& p, Vertex& q, Vertex& r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

void MyProject1MyFrame1::iteratePoints(std::vector<Vertex>& pos, size_t img)
{
	if (pos.empty()) return;

	auto& pixels = images[0];
	auto& pixelsNew = images[img];

	for (int i = 0; i < pixels.GetWidth(); i++) {
		for (int j = 0; j < pixels.GetHeight(); j++) {
			if (isInside(pos, pos.size(), Vertex(i, j))) {
				pixels.SetRGB(i, j, pixelsNew.GetRed(i, j), pixelsNew.GetGreen(i, j), pixelsNew.GetBlue(i, j));
			}
		}
	}
}
