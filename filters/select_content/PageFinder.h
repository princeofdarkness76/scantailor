/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2009  Joseph Artsimovich <joseph_a@mail.ru>
    Copyright (C) 2012  Petr Kovar <pejuko@gmail.com>

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

#ifndef SELECT_CONTENT_PAGEFINDER_H_
#define SELECT_CONTENT_PAGEFINDER_H_

#include "imageproc/BinaryThreshold.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "Margins.h"
>>>>>>> origin/enhanced
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
#include "Margins.h"
>>>>>>> origin/enhanced
=======
#include "Margins.h"
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
#include "Margins.h"
>>>>>>> pod/translations

#include <Qt>

class TaskStatus;
class DebugImages;
class FilterData;
class QImage;
class QRect;
class QRectF;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
<<<<<<< HEAD
>>>>>>> master
=======
class QSizeF;
class QSize;
>>>>>>> origin/enhanced
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
=======
class QSizeF;
class QSize;
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
class QSizeF;
class QSize;
>>>>>>> pod/translations

namespace imageproc
{
	class BinaryImage;
}

namespace select_content
{

class PageFinder
{
public:
	static QRectF findPageBox(
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/tiff
>>>>>>> master
=======
<<<<<<< HEAD
=======
>>>>>>> pod/tiff
>>>>>>> master
		TaskStatus const& status, FilterData const& data, bool fine_tune=false,
		DebugImages* dbg = 0);
private:
	static QRect detectBorders(QImage const& img);
	static int detectEdge(QImage const& img, int start, int end, int inc, int mid, Qt::Orientation orient);
	static void fineTuneCorners(QImage const& img, QRect &rect);
	static void fineTuneCorner(QImage const& img, int &x, int &y, int inc_x, int inc_y);
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/enhanced
>>>>>>> master
=======
>>>>>>> origin/enhanced
>>>>>>> master
=======
>>>>>>> pod/translations
        TaskStatus const& status, FilterData const& data, bool fine_tune, QSizeF const& box, double tolerance, Margins borders, DebugImages* dbg = 0);
private:
	static QRect detectBorders(QImage const& img);
	static int detectEdge(QImage const& img, int start, int end, int inc, int mid, Qt::Orientation orient);
	static void fineTuneCorners(QImage const& img, QRect &rect, QSize const& size, double tolerance);
	static bool fineTuneCorner(QImage const& img, int &x, int &y, int max_x, int max_y, int inc_x, int inc_y, QSize const& size, double tolerance);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
>>>>>>> master
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
>>>>>>> master
=======
>>>>>>> pod/translations
};

} // namespace select_content

#endif
