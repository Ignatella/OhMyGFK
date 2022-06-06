#include "MyProject1MyFrame1.h"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>

MyProject1MyFrame1::MyProject1MyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	wxImage::AddHandler(new wxJPEGHandler);
}

void MyProject1MyFrame1::on_update(wxUpdateUIEvent& event)
{
	wxClientDC dc(this->img_panel);
	wxBufferedDC mdc(&dc);

	if (!this->bitmaps.empty()) {
		mdc.DrawBitmap(this->bitmaps[0], 0, 0);
	}
}

void MyProject1MyFrame1::patch_click(wxCommandEvent& event)
{
	// TODO: Implement patch_click
	//nowBitmap = &this->bitmaps[0];
}

void MyProject1MyFrame1::swap(int ind)
{
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

void MyProject1MyFrame1::org_size_click(wxCommandEvent& event)
{
	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(std::get<0>(this->originalSizes[0]), std::get<1>(this->originalSizes[0])));
}

void MyProject1MyFrame1::width_size_click(wxCommandEvent& event)
{
	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(this->img_panel->GetSize().GetWidth(), std::get<1>(this->originalSizes[0])));
}

void MyProject1MyFrame1::height_size_click(wxCommandEvent& event)
{
	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(std::get<0>(this->originalSizes[0]), this->img_panel->GetSize().GetHeight()));

}

void MyProject1MyFrame1::fit_click(wxCommandEvent& event)
{
	this->bitmaps[0] = wxBitmap(this->bitmaps[0].ConvertToImage().Scale(this->img_panel->GetSize().GetWidth(), this->img_panel->GetSize().GetHeight()));

}

void MyProject1MyFrame1::open_file_open_event(wxCommandEvent& event)
{
	wxFileDialog files(this, _("Choose images"), "", "", "*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (files.ShowModal() == wxID_CANCEL) {
		return;
	}


	if (this->bitmaps.size() < 5) {
		wxImage img(files.GetPath());
		wxBitmap bmp = wxBitmap(img);
		originalSizes.emplace_back(std::make_tuple(img.GetWidth(), img.GetHeight()));
		bitmaps.emplace_back(bmp);
		bitmapsC[current]->SetBitmap(wxBitmap(img.Scale(img.GetWidth() / 50, img.GetHeight() / 50)));
		current += 1;
	}
	else {
		wxMessageBox("Maximum images count exceeded", "Error", wxICON_ERROR);
	}
}

void MyProject1MyFrame1::save_file_save_event(wxCommandEvent& event)
{
	try {
		if (nowBitmap && nowBitmap->IsOk()) {
			nowBitmap->SaveFile("image.bmp", wxBitmapType::wxBITMAP_TYPE_BMP);
		}
		wxMessageBox("Image has been saved", "File saved", wxICON_INFORMATION);
	}
	catch (std::exception& ex) {
		wxMessageBox("Error while saving patched image!", "Error", wxICON_ERROR);
	}
}

void MyProject1MyFrame1::about_menu_authors_open(wxCommandEvent& event)
{
	wxMessageBox("Ignacy,Piotr,Szymon", "Authors", wxICON_INFORMATION);
}

void MyProject1MyFrame1::m_bitmap1_click(wxMouseEvent& event)
{
	swap(0);
}

void MyProject1MyFrame1::m_bitmap2_click(wxMouseEvent& event)
{
	swap(1);
}

void MyProject1MyFrame1::m_bitmap3_click(wxMouseEvent& event)
{
	swap(2);
}

void MyProject1MyFrame1::m_bitmap4_click(wxMouseEvent& event)
{
	swap(3);
}

void MyProject1MyFrame1::m_bitmap5_click(wxMouseEvent& event)
{
	swap(4);
}