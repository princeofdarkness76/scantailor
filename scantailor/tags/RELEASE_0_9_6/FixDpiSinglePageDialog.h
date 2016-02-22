/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2009  Joseph Artsimovich <joseph_a@mail.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FIX_DPI_SINGLE_PAGE_DIALOG_H_
#define FIX_DPI_SINGLE_PAGE_DIALOG_H_

#include "ui_FixDpiSinglePageDialog.h"
#include "Dpi.h"
#include "ImageMetadata.h"
#include <QPalette>

class QPushButton;
class ImageId;

class FixDpiSinglePageDialog : public QDialog
{
	Q_OBJECT
public:
	FixDpiSinglePageDialog(
		ImageId const& image_id, ImageMetadata const& image_metadata,
		bool is_multipage_file, QWidget* parent = 0);
	
	Dpi const& dpi() const { return m_metadata.dpi(); }
private slots:
	void dpiComboChangedByUser(int idx);
	
	void dpiValueChanged();
private:
	void decorateDpiInputField(QLineEdit* field, ImageMetadata::DpiStatus dpi_status) const;
	
	Ui::FixDpiSinglePageDialog ui;
	ImageMetadata m_metadata;
	QPalette m_normalPalette;
	QPalette m_errorPalette;
	QPushButton* m_pOkBtn;
};

#endif
