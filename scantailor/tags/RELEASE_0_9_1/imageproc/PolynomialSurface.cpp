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
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "PolynomialSurface.h"
#include "LeastSquaresFit.h"
#include "BinaryImage.h"
#include "Grayscale.h"
#include "BitOps.h"
#include <QImage>
#include <QDebug>
#include <stdexcept>
#include <algorithm>
#include <math.h>
#include <stdint.h>
#include <assert.h>

namespace imageproc
{

PolynomialSurface::PolynomialSurface(
	int const hor_degree, int const vert_degree, QImage const& src)
:	m_horDegree(hor_degree),
	m_vertDegree(vert_degree)
{
	// Note: m_horDegree and m_vertDegree may still change!
	
	if (hor_degree < 0) {
		throw std::invalid_argument("PolynomialSurface: horizontal degree is invalid");
	}
	if (vert_degree < 0) {
		throw std::invalid_argument("PolynomialSurface: vertical degree is invalid");
	}
	
	if (src.format() != QImage::Format_Indexed8
			|| src.numColors() != 256 || !src.allGray()) {
		throw std::invalid_argument("PolynomialSurface: not grayscale");
	}
	
	int const num_data_points = src.width() * src.height();
	if (num_data_points == 0) {
		m_horDegree = 0;
		m_vertDegree = 0;
		m_coeffs.push_back(0.0);
		return;
	}
	
	maybeReduceDegrees(num_data_points);
	
	int const num_terms = calcNumTerms();
	QSize const dimensions(num_terms, num_data_points);
	std::vector<double> equations;
	std::vector<double> data_points;
	equations.reserve(dimensions.width() * dimensions.height());
	data_points.reserve(dimensions.height());
	m_coeffs.resize(dimensions.width());
	
	prepareEquationsAndDataPoints(src, equations, data_points);
	assert(equations.size() == dimensions.width() * dimensions.height());
	assert(data_points.size() == num_terms);
	
	leastSquaresFit(dimensions, &equations[0], &m_coeffs[0], &data_points[0]);
}

PolynomialSurface::PolynomialSurface(
	int const hor_degree, int const vert_degree,
	QImage const& src, BinaryImage const& mask)
:	m_horDegree(hor_degree),
	m_vertDegree(vert_degree)
{
	// Note: m_horDegree and m_vertDegree may still change!
	
	if (hor_degree < 0) {
		throw std::invalid_argument("PolynomialSurface: horizontal degree is invalid");
	}
	if (vert_degree < 0) {
		throw std::invalid_argument("PolynomialSurface: vertical degree is invalid");
	}
	
	if (src.format() != QImage::Format_Indexed8
			|| src.numColors() != 256 || !src.allGray()) {
		throw std::invalid_argument("PolynomialSurface: not grayscale");
	}
	
	if (src.size() != mask.size()) {
		throw std::invalid_argument("PolynomialSurface: image and mask have different sizes");
	}
	
	int const num_data_points = mask.countBlackPixels();
	if (num_data_points == 0) {
		m_horDegree = 0;
		m_vertDegree = 0;
		m_coeffs.push_back(0.0);
		return;
	}
	
	maybeReduceDegrees(num_data_points);
	
	int const num_terms = calcNumTerms();
	QSize const dimensions(num_terms, num_data_points);
	
	std::vector<double> equations;
	std::vector<double> data_points;
	equations.reserve(dimensions.width() * dimensions.height());
	data_points.reserve(dimensions.height());
	m_coeffs.resize(dimensions.width());
	
	prepareEquationsAndDataPoints(src, mask, equations, data_points);
	assert(equations.size() == dimensions.width() * dimensions.height());
	assert(data_points.size() == num_terms);
	
	leastSquaresFit(dimensions, &equations[0], &m_coeffs[0], &data_points[0]);
}

QImage
PolynomialSurface::render(QSize const& size) const
{
	if (size.isEmpty()) {
		return QImage();
	}
	
	QImage image(size, QImage::Format_Indexed8);
	image.setColorTable(createGrayscalePalette());
	int const width = size.width();
	int const height = size.height();
	unsigned char* line = image.bits();
	int const bpl = image.bytesPerLine();
	
	
	// Pretend that both x and y positions of pixels
	// lie in range of [1, 2].
	double const xscale = calcScale(width);
	double const yscale = calcScale(height);
	
	for (int y = 0; y < height; ++y, line += bpl) {
		double const y_adjusted = 1.0 + y * yscale;
		for (int x = 0; x < width; ++x) {
			double const x_adjusted = 1.0 + x * xscale;
			int pos = 0;
			double sum = 0.5; // for rounding purposes
			double pow1 = 1.0;
			for (int i = 0; i <= m_vertDegree; ++i) {
				double pow2 = pow1;
				for (int j = 0; j <= m_horDegree; ++j, ++pos) {
					sum += m_coeffs[pos] * pow2;
					pow2 *= x_adjusted;
				}
				pow1 *= y_adjusted;
			}
			int const isum = (int)sum;
			line[x] = static_cast<unsigned char>(qBound(0, isum, 255));
		}
	}
	
	return image;
}

void
PolynomialSurface::maybeReduceDegrees(int const num_data_points)
{
	assert(num_data_points > 0);
	
	while (num_data_points < calcNumTerms()) {
		if (m_horDegree > m_vertDegree) {
			--m_horDegree;
		} else {
			--m_vertDegree;
		}
	}
}

int
PolynomialSurface::calcNumTerms() const
{
	return (m_horDegree + 1) * (m_vertDegree + 1);
}

double
PolynomialSurface::calcScale(int const dimension)
{
	if (dimension <= 1) {
		return 0.0;
	} else {
		return 1.0 / (dimension - 1);
	}
}

void
PolynomialSurface::prepareEquationsAndDataPoints(
	QImage const& image,
	std::vector<double>& equations,
	std::vector<double>& data_points) const
{
	int const width = image.width();
	int const height = image.height();
	
	uint8_t const* line = image.bits();
	int const bpl = image.bytesPerLine();
	
	// Pretend that both x and y positions of pixels
	// lie in range of [1, 2].
	double const xscale = calcScale(width);
	double const yscale = calcScale(height);
	
	for (int y = 0; y < height; ++y, line += bpl) {
		double const y_adjusted = 1.0 + yscale * y;
		
		for (int x = 0; x < width; ++x) {
			double const x_adjusted = 1.0 + xscale * x;
			
			data_points.push_back(line[x]);
			
			double pow1 = 1.0;
			for (int i = 0; i <= m_vertDegree; ++i) {
				double pow2 = pow1;
				for (int j = 0; j <= m_horDegree; ++j) {
					equations.push_back(pow2);
					pow2 *= x_adjusted;
				}
				pow1 *= y_adjusted;
			}
		}
	}
}

void
PolynomialSurface::prepareEquationsAndDataPoints(
	QImage const& image, BinaryImage const& mask,
	std::vector<double>& equations,
	std::vector<double>& data_points) const
{
	int const width = image.width();
	int const height = image.height();
	
	double const xscale = calcScale(width);
	double const yscale = calcScale(height);
	
	uint8_t const* image_line = image.bits();
	int const image_bpl = image.bytesPerLine();
	
	uint32_t const* mask_line = mask.data();
	int const mask_wpl = mask.wordsPerLine();
	int const last_word_idx = (width - 1) >> 5;
	int const last_word_mask = ~uint32_t(0) << (31 - ((width - 1) & 31));
	
	for (int y = 0; y < height; ++y) {
		double const y_adjusted = 1.0 + y * yscale;
		int idx = 0;
		
		// Full words.
		for (; idx < last_word_idx; ++idx) {
			processMaskWord(
				image_line, mask_line[idx], idx, y,
				y_adjusted, xscale, equations, data_points
			);
		}
		
		// Last word.
		processMaskWord(
			image_line, mask_line[idx] & last_word_mask,
			idx, y, y_adjusted, xscale, equations, data_points
		);
		
		image_line += image_bpl;
		mask_line += mask_wpl;
	}
}

void
PolynomialSurface::processMaskWord(
	uint8_t const* const image_line,
	uint32_t word, int const word_idx, int const y,
	double const y_adjusted, double const xscale,
	std::vector<double>& equations,
	std::vector<double>& data_points) const
{
	uint32_t const msb = uint32_t(1) << 31;
	int const xbase = word_idx << 5;
	
	int x = xbase;
	uint32_t mask = msb;
	
	for (; word; word &= ~mask, mask >>= 1, ++x) {
		if (!(word & mask)) {
			// Skip a group of zero bits.
			int const offset = countMostSignificantZeroes(word);
			x = xbase + offset;
			mask = msb >> offset;
			assert(word & mask);
		}
		
		data_points.push_back(image_line[x]);
		
		double const x_adjusted = 1.0 + xscale * x;
		double pow1 = 1.0;
		for (int i = 0; i <= m_vertDegree; ++i) {
			double pow2 = pow1;
			
			for (int j = 0; j <= m_horDegree; ++j) {
				equations.push_back(pow2);
				pow2 *= x_adjusted;
			}
			
			pow1 *= y_adjusted;
		}
	}
}

}
