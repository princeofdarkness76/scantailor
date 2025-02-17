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

#include "Filter.h"
#include "FilterUiInterface.h"
#include "OptionsWidget.h"
#include "Settings.h"
#include "Task.h"
#include "CacheDrivenTask.h"
#include "OrthogonalRotation.h"
#include "PageId.h"
#include "ImageId.h"
#include "PageSequence.h"
#include "ProjectReader.h"
#include "ProjectWriter.h"
#include "XmlMarshaller.h"
#include "XmlUnmarshaller.h"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <QString>
#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

namespace fix_orientation
{

Filter::Filter(
	IntrusivePtr<PageSequence> const& page_sequence)
:	m_ptrPages(page_sequence),
	m_ptrSettings(new Settings(page_sequence))
{
	m_ptrOptionsWidget.reset(new OptionsWidget(m_ptrSettings, page_sequence));
}

Filter::~Filter()
{
}

QString
Filter::getName() const
{
	return QObject::tr("Fix Orientation");
}

PageSequence::View
Filter::getView() const
{
	return PageSequence::IMAGE_VIEW;
}

void
Filter::preUpdateUI(FilterUiInterface* ui, PageId const& page_id)
{
	if (m_ptrOptionsWidget.get()) {
		OrthogonalRotation const rotation(
			m_ptrSettings->getRotationFor(page_id.imageId())
		);
		m_ptrOptionsWidget->preUpdateUI(
			rotation, m_ptrPages->numImages(),
			m_ptrPages->curImageIdx()
		);
		ui->setOptionsWidget(m_ptrOptionsWidget.get(), ui->KEEP_OWNERSHIP);
	}
}

QDomElement
Filter::saveSettings(
	ProjectWriter const& writer, QDomDocument& doc) const
{
	using namespace boost::lambda;
	
	QDomElement filter_el(doc.createElement("fix-orientation"));
	writer.enumImages(
		bind(
			&Filter::writeImageSettings,
			this, boost::ref(doc), var(filter_el), _1, _2
		)
	);
	
	return filter_el;
}

void
Filter::loadSettings(ProjectReader const& reader, QDomElement const& filters_el)
{
	m_ptrSettings->clear();
	
	QDomElement filter_el(filters_el.namedItem("fix-orientation").toElement());
	
	QString const image_tag_name("image");
	QDomNode node(filter_el.firstChild());
	for (; !node.isNull(); node = node.nextSibling()) {
		if (!node.isElement()) {
			continue;
		}
		if (node.nodeName() != image_tag_name) {
			continue;
		}
		QDomElement el(node.toElement());
		
		bool ok = true;
		int const id = el.attribute("id").toInt(&ok);
		if (!ok) {
			continue;
		}
		
		ImageId const image_id(reader.imageId(id));
		if (image_id.isNull()) {
			continue;
		}
		
		OrthogonalRotation const rotation(
			XmlUnmarshaller::rotation(
				el.namedItem("rotation").toElement()
			)
		);
		
		m_ptrSettings->applyRule(image_id, rotation);
	}
}

IntrusivePtr<Task>
Filter::createTask(
	PageId const& page_id,
	IntrusivePtr<page_split::Task> const& next_task,
	bool const batch_processing)
{
	return IntrusivePtr<Task>(
		new Task(
			page_id.imageId(), IntrusivePtr<Filter>(this),
			m_ptrSettings, next_task, batch_processing
		)
	);
}

IntrusivePtr<CacheDrivenTask>
Filter::createCacheDrivenTask(
	IntrusivePtr<page_split::CacheDrivenTask> const& next_task)
{
	return IntrusivePtr<CacheDrivenTask>(
		new CacheDrivenTask(m_ptrSettings, next_task)
	);
}

void
Filter::writeImageSettings(
	QDomDocument& doc, QDomElement& filter_el,
	ImageId const& image_id, int const numeric_id) const
{
	OrthogonalRotation const rotation(m_ptrSettings->getRotationFor(image_id));
	if (rotation.toDegrees() == 0) {
		return;
	}
	
	XmlMarshaller marshaller(doc);
	
	QDomElement image_el(doc.createElement("image"));
	image_el.setAttribute("id", numeric_id);
	image_el.appendChild(marshaller.rotation(rotation, "rotation"));
	filter_el.appendChild(image_el);
}

} // namespace fix_orientation
