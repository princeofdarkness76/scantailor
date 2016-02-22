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

#ifndef SELECT_CONTENT_PARAMS_H_
#define SELECT_CONTENT_PARAMS_H_

#include "Dependencies.h"
#include "AutoManualMode.h"
#include <QRectF>

class QDomDocument;
class QDomElement;
class QString;

namespace select_content
{

class Params
{
public:
	// Member-wise copying is OK.
	
	Params(QRectF const& rect, Dependencies const& deps, AutoManualMode mode);
	
	Params(QDomElement const& filter_el);
	
	~Params();
	
	QRectF const& contentRect() const { return m_contentRect; }
	
	Dependencies const& dependencies() const { return m_deps; }
	
	AutoManualMode mode() const { return m_mode; }
	
	QDomElement toXml(QDomDocument& doc, QString const& name) const;
private:
	QRectF m_contentRect;
	Dependencies m_deps;
	AutoManualMode m_mode;
};

} // namespace select_content

#endif
