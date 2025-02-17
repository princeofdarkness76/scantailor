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

#include "PolygonUtils.h"
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <boost/foreach.hpp>
#include <algorithm>
#include <stddef.h>
#include <math.h>
#include <assert.h>

namespace imageproc
{

double const PolygonUtils::ROUNDING_MULTIPLIER = 1 << 12;
double const PolygonUtils::ROUNDING_RECIP_MULTIPLIER = 1.0 / ROUNDING_MULTIPLIER;

class PolygonUtils::Before
{
public:
	bool operator()(QPointF const& lhs, QPointF const& rhs) const {
		return compare(lhs, rhs) < 0;
	}
	
	bool operator()(QLineF const& lhs, QLineF const& rhs) {
		int comp = compare(lhs.p1(), rhs.p1());
		if (comp != 0) {
			return comp;
		}
		return compare(lhs.p2(), rhs.p2());
	}
private:
	static int compare(QPointF const& lhs, QPointF const& rhs) {
		double const dx = lhs.x() - rhs.x();
		double const dy = lhs.y() - rhs.y();
		if (fabs(dx) > fabs(dy)) {
			if (dx < 0.0) {
				return -1;
			} else if (dx > 0.0) {
				return 1;
			}
		} else {
			if (dy < 0.0) {
				return -1;
			} else if (dy > 0.0) {
				return 1;
			}
		}
		return 0;
	}
};


QPolygonF
PolygonUtils::round(QPolygonF const& poly)
{
	QPolygonF rounded;
	rounded.reserve(poly.size());
	
	BOOST_FOREACH (QPointF const& p, poly) {
		rounded.push_back(roundPoint(p));
	}
	
	return rounded;
}

bool
PolygonUtils::fuzzyCompare(QPolygonF const& poly1, QPolygonF const& poly2)
{
	if (poly1.size() < 2 && poly2.size() < 2) {
		return true;
	} else if (poly1.size() < 2 || poly2.size() < 2) {
		return false;
	}
	
	assert(poly1.size() >= 2 && poly2.size() >= 2);
	
	QPolygonF closed1(poly1);
	QPolygonF closed2(poly2);
	
	// Close if necessary.
	if (closed1.back() != closed1.front()) {
		closed1.push_back(closed1.front());
	}
	if (closed2.back() != closed2.front()) {
		closed2.push_back(closed2.front());
	}
	
	std::vector<QLineF> edges1(extractAndNormalizeEdges(closed1));
	std::vector<QLineF> edges2(extractAndNormalizeEdges(closed2));
	
	if (edges1.size() != edges2.size()) {
		return false;
	}
	
	std::sort(edges1.begin(), edges1.end(), Before());
	std::sort(edges2.begin(), edges2.end(), Before());
	
	return fuzzyCompareImpl(edges1, edges2);
}

QPointF
PolygonUtils::roundPoint(QPointF const& p)
{
	return QPointF(roundValue(p.x()), roundValue(p.y()));
}

double
PolygonUtils::roundValue(double const val)
{
	return floor(val * ROUNDING_MULTIPLIER + 0.5) * ROUNDING_RECIP_MULTIPLIER;
}

std::vector<QLineF>
PolygonUtils::extractAndNormalizeEdges(QPolygonF const& poly)
{
	std::vector<QLineF> edges;
	
	int const num_edges = poly.size();
	if (num_edges > 1) {
		for (int i = 1; i < num_edges; ++i) {
			maybeAddNormalizedEdge(edges, poly[i - 1], poly[i]);
		}
		maybeAddNormalizedEdge(edges, poly[num_edges - 1], poly[0]);
	}
	
	return edges;
}

void
PolygonUtils::maybeAddNormalizedEdge(
	std::vector<QLineF>& edges, QPointF const& p1, QPointF const& p2)
{
	if (fuzzyCompareImpl(p1, p2)) {
		return;
	}
	
	if (Before()(p2, p1)) {
		edges.push_back(QLineF(p2, p1));
	} else {
		edges.push_back(QLineF(p1, p2));
	}
}

bool
PolygonUtils::fuzzyCompareImpl(
	std::vector<QLineF> const& lines1,
	std::vector<QLineF> const& lines2)
{
	assert(lines1.size() == lines2.size());
	size_t const size = lines1.size();
	for (size_t i = 0; i < size; ++i) {
		if (!fuzzyCompareImpl(lines1[i], lines2[i])) {
			return false;
		}
	}
	return true;
}

bool
PolygonUtils::fuzzyCompareImpl(QLineF const& line1, QLineF const& line2)
{
	return fuzzyCompareImpl(line1.p1(), line2.p1()) &&
			fuzzyCompareImpl(line1.p2(), line2.p2());
}

bool
PolygonUtils::fuzzyCompareImpl(QPointF const& p1, QPointF const& p2)
{
	double const dx = fabs(p1.x() - p2.x());
	double const dy = fabs(p1.y() - p2.y());
	return dx <= ROUNDING_RECIP_MULTIPLIER && dy <= ROUNDING_RECIP_MULTIPLIER;
}

} // namespace imageproc
