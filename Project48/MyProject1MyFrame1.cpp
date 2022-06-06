#include "MyProject1MyFrame1.h"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>

MyProject1MyFrame1::MyProject1MyFrame1(wxWindow *parent)
	: MyFrame1(parent)
{
	wxImage::AddHandler(new wxJPEGHandler);
}

void MyProject1MyFrame1::on_update(wxUpdateUIEvent &event)
{
	wxClientDC dc(this->img_panel);
	wxBufferedDC mdc(&dc);

	if (!this->bitmaps.empty())
	{
		mdc.DrawBitmap(this->bitmaps[0], 0, 0);

		if (mode == 1)
		{
			mdc.SetBrush(*wxTRANSPARENT_BRUSH);
			mdc.SetPen(*wxGREEN_PEN);
			mdc.DrawPolygon(positions.size(), positions.data(), 0, 0);
		}
	}
}

void MyProject1MyFrame1::patch_click(wxCommandEvent &event)
{
  if (this->bitmaps.empty()) {
    wxMessageBox("Can'\t patch on the blank image", "An error has occured", wxICON_ERROR);
    return;
  }

	switch (mode)
	{
	case 0:
		nowBitmap = this->bitmaps[0];
		mode++;
		break;
	default:
		iteratePoints(nowBitmap, this->bitmaps[0]);
		swap(currentBitmap);
		this->bitmaps[0] = nowBitmap;
		mode = 0;
		this->Update();
		break;
	}
}

void MyProject1MyFrame1::swap(int ind)
{
	currentBitmap = ind;
	int newIndex = ind;

	wxBitmap first = this->bitmaps[0];
	std::tuple<double, double> firstSize = this->originalSizes[0];

	this->bitmaps[0] = this->bitmaps[newIndex];
	this->bitmaps[newIndex] = first;

	this->originalSizes[0] = this->originalSizes[newIndex];
	this->originalSizes[newIndex] = firstSize;
	bitmapsC[0]->SetBitmap(wxBitmap(this->bitmaps[0].ConvertToImage().Scale(std::get<0>(this->originalSizes[0]) / 50, std::get<1>(this->originalSizes[0]) / 50)));

	bitmapsC[newIndex]->SetBitmap(wxBitmap(this->bitmaps[newIndex].ConvertToImage().Scale(std::get<0>(this->originalSizes[newIndex]) / 50, std::get<1>(this->originalSizes[newIndex]) / 50)));
	this->Update();
}

void MyProject1MyFrame1::org_size_click(wxCommandEvent &event)
{
	if (this->bitmaps.empty()) return;

	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(std::get<0>(this->originalSizes[0]), std::get<1>(this->originalSizes[0])));
}

void MyProject1MyFrame1::width_size_click(wxCommandEvent &event)
{
	if (this->bitmaps.empty()) return;

	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(this->img_panel->GetSize().GetWidth(), std::get<1>(this->originalSizes[0])));
}

void MyProject1MyFrame1::height_size_click(wxCommandEvent &event)
{
	if (this->bitmaps.empty()) return;

	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(std::get<0>(this->originalSizes[0]), this->img_panel->GetSize().GetHeight()));
}

void MyProject1MyFrame1::fit_click(wxCommandEvent &event)
{
	if (this->bitmaps.empty()) return;

	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(this->img_panel->GetSize().GetWidth(), this->img_panel->GetSize().GetHeight()));
}

void MyProject1MyFrame1::open_file_open_event(wxCommandEvent &event)
{
	wxFileDialog files(this, _("Choose images"), "", "", "*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (files.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	if (this->bitmaps.size() >= 5)
	{
		wxMessageBox("Maximum images count exceeded", "Error", wxICON_ERROR);
          return;
    }

    wxImage img(files.GetPath());
    wxBitmap bmp = wxBitmap(img);
    originalSizes.emplace_back(
        std::make_tuple(img.GetWidth(), img.GetHeight()));
    bitmaps.emplace_back(bmp);
    bitmapsC[current]->SetBitmap(
        wxBitmap(img.Scale(img.GetWidth() / 50, img.GetHeight() / 50)));
    current += 1;
}

void MyProject1MyFrame1::save_file_save_event(wxCommandEvent &event)
{
	try
	{
		if (nowBitmap.IsOk())
		{
			nowBitmap.SaveFile("image.bmp", wxBitmapType::wxBITMAP_TYPE_BMP);
		}
		wxMessageBox("Image has been saved", "File saved", wxICON_INFORMATION);
	}
	catch (std::exception &ex)
	{
		wxMessageBox("Error while saving patched image!", "Error", wxICON_ERROR);
	}
}

void MyProject1MyFrame1::about_menu_authors_open(wxCommandEvent &event)
{
	wxMessageBox("Ignacy,Piotr,Szymon", "Authors", wxICON_INFORMATION);
}

void MyProject1MyFrame1::m_bitmap1_click(wxMouseEvent &event)
{
	swap(0);
}

void MyProject1MyFrame1::m_bitmap2_click(wxMouseEvent &event)
{
	swap(1);
}

void MyProject1MyFrame1::m_bitmap3_click(wxMouseEvent &event)
{
	swap(2);
}

void MyProject1MyFrame1::m_bitmap4_click(wxMouseEvent &event)
{
	swap(3);
}

void MyProject1MyFrame1::m_bitmap5_click(wxMouseEvent &event)
{
	swap(4);
}

void MyProject1MyFrame1::mouse_point_click(wxMouseEvent &event)
{
	if (mode == 1)
	{
		if (positions.size() == 0)
		{
			positions.emplace_back(wxPoint(event.GetX(), event.GetY()));
			positions.emplace_back(wxPoint(event.GetX(), event.GetY()));
		}
		else
		{
			positions.insert(std::begin(positions) + positions.size() - 2, wxPoint(event.GetX(), event.GetY()));
		}
	}
}

void MyProject1MyFrame1::clear_pts_event(wxCommandEvent &event)
{
	positions.clear();
	wxMessageBox("Points cleared", "Points cleared successfully");
}

void MyProject1MyFrame1::iteratePoints(wxBitmap &bmp, wxBitmap &other)
{
	if (!positions.empty())
	{
		auto pixels = bmp.ConvertToImage();
		auto pixelsNew = other.ConvertToImage();

		for (int i = 0; i < pixels.GetWidth(); i++)
		{
			for (int j = 0; j < pixels.GetHeight(); j++)
			{
				if (isInside(positions, 5, wxPoint(i, j)))
				{
					pixels.SetRGB(i, j, pixelsNew.GetRed(i, j), pixelsNew.GetGreen(i, j), pixelsNew.GetBlue(i, j));
				}
			}
		}
		bmp = wxBitmap(pixels);
	}
}

// from:https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool MyProject1MyFrame1::onSegment(wxPoint &p, wxPoint &q, wxPoint &r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int MyProject1MyFrame1::orientation(wxPoint &p, wxPoint &q, wxPoint &r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return 0;			  // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool MyProject1MyFrame1::doIntersect(wxPoint &p1, wxPoint &q1, wxPoint &p2, wxPoint &q2)
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

// Returns true if the point p lies inside the polygon[] with n vertices
bool MyProject1MyFrame1::isInside(std::vector<wxPoint> polygon, int n, wxPoint &p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3)
		return false;

	// Create a point for line segment from p to infinite
	wxPoint extreme(5000, p.y);

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
