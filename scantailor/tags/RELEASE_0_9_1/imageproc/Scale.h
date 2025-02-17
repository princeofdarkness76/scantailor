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

#ifndef IMAGEPROC_SCALE_H_
#define IMAGEPROC_SCALE_H_

class QImage;
class QSize;

namespace imageproc
{

/**
 * \brief Converts an image to grayscale and scales it to dst_size.
 *
 * \param src The source image.
 * \param dst_size The size to scale the image to.
 * \return The scaled image. The image format will be
 *         QImage::Format_Indexed8 with a grayscale palette.
 *
 * This function is a faster replacement for QImage::scaled(), when
 * dealing with grayscale images.
 */
QImage scaleToGray(QImage const& src, QSize const& dst_size);

} // namespace imageproc

#endif
