/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2008  Joseph Artsimovich <joseph_a@mail.ru>

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

#ifndef FILTERDATA_H_
#define FILTERDATA_H_

#include "imageproc/BinaryThreshold.h"
#include "ImageTransformation.h"
#include <QImage>

class FilterData
{
	// Member-wise copying is OK.
public:
	FilterData(QImage const& image);
	
	FilterData(FilterData const& other, ImageTransformation const& xform);
		
	imageproc::BinaryThreshold bwThreshold() const { return m_bwThreshold; }
	
	ImageTransformation const& xform() const { return m_xform; }

	QImage const& origImage() const {return m_origImage;}

	QImage const& grayImage() const {return m_grayImage;}
private:
	QImage m_origImage;
	QImage m_grayImage;
	ImageTransformation m_xform;
	imageproc::BinaryThreshold m_bwThreshold;
};

#endif
