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

#include "Params.h"
#include "XmlMarshaller.h"
#include "XmlUnmarshaller.h"
#include <QDomDocument>
#include <QDomElement>
#include <QString>

namespace page_layout
{

Params::Params(
	Margins const& hard_margins_mm, QRectF const& content_rect, QRectF const& page_rect,
	QSizeF const& content_size_mm, Alignment const& alignment)
:	m_hardMarginsMM(hard_margins_mm),
	m_pageRect(page_rect),
	m_contentRect(content_rect),
	m_contentSizeMM(content_size_mm),
	m_alignment(alignment)
{
}

Params::Params(QDomElement const& el)
:	m_hardMarginsMM(
		XmlUnmarshaller::margins(
			el.namedItem("hardMarginsMM").toElement()
		)
	),
	m_pageRect(
		XmlUnmarshaller::rectF(
			el.namedItem("pageRect").toElement()
		)
	),
	m_contentRect(
		XmlUnmarshaller::rectF(
			el.namedItem("contentRect").toElement()
		)
	),
	m_contentSizeMM(
		XmlUnmarshaller::sizeF(
			el.namedItem("contentSizeMM").toElement()
		)
	),
	m_alignment(el.namedItem("alignment").toElement())
{
}

QDomElement
Params::toXml(QDomDocument& doc, QString const& name) const
{
	XmlMarshaller marshaller(doc);
	
	QDomElement el(doc.createElement(name));
	el.appendChild(marshaller.margins(m_hardMarginsMM, "hardMarginsMM"));
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	el.appendChild(marshaller.rectF(m_pageRect, "pageRect"));
>>>>>>> origin/enhanced
=======
	el.appendChild(marshaller.rectF(m_pageRect, "pageRect"));
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	el.appendChild(marshaller.rectF(m_pageRect, "pageRect"));
>>>>>>> enhanced
=======
	el.appendChild(marshaller.rectF(m_pageRect, "pageRect"));
>>>>>>> pod/translations
	el.appendChild(marshaller.rectF(m_contentRect, "contentRect"));
	el.appendChild(marshaller.sizeF(m_contentSizeMM, "contentSizeMM"));
	el.appendChild(m_alignment.toXml(doc, "alignment"));
	return el;
}

} // namespace page_layout

