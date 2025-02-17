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

#ifndef PAGE_RANGE_H_
#define PAGE_RANGE_H_

#include "PageId.h"
#include <vector>

class PageRange
{
public:
	/**
	 * \brief Ordered list of consecutive pages.
	 */
	std::vector<PageId> pages;
	
	/**
	 * \brief The index of the first page in the global page sequence.
	 */
	int firstPageIdx;
	
	PageRange() : firstPageIdx(-1) {}
};

#endif
