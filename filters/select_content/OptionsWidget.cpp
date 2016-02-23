/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

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

#include "OptionsWidget.h"
#include "OptionsWidget.moc"
#include "ApplyDialog.h"
#include "Settings.h"
#include "Params.h"
#include "ScopedIncDec.h"
#ifndef Q_MOC_RUN
#include <boost/foreach.hpp>
#endif
<<<<<<< HEAD
=======
<<<<<<< HEAD

#include <iostream>
=======
>>>>>>> scantailor/master
>>>>>>> enhanced

#include <iostream>

<<<<<<< HEAD
#include <iostream>

#include <iostream>

=======
>>>>>>> pod/tiff
namespace select_content
{

OptionsWidget::OptionsWidget(
	IntrusivePtr<Settings> const& settings,
	PageSelectionAccessor const& page_selection_accessor)
:	m_ptrSettings(settings),
	m_pageSelectionAccessor(page_selection_accessor),
	m_ignoreAutoManualToggle(0)
{
	setupUi(this);
	
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	connect(autoBtn, SIGNAL(toggled(bool)), this, SLOT(modeChanged(bool)));
<<<<<<< HEAD
=======
	connect(autoBtn, SIGNAL(pressed()), this, SLOT(autoMode()));
	connect(manualBtn, SIGNAL(pressed()), this, SLOT(manualMode()));
>>>>>>> origin/enhanced
=======
	connect(autoBtn, SIGNAL(pressed()), this, SLOT(autoMode()));
	connect(manualBtn, SIGNAL(pressed()), this, SLOT(manualMode()));
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	connect(autoBtn, SIGNAL(pressed()), this, SLOT(autoMode()));
	connect(manualBtn, SIGNAL(pressed()), this, SLOT(manualMode()));
>>>>>>> enhanced
	connect(disableBtn, SIGNAL(pressed()), this, SLOT(contentDetectionDisabled()));
	connect(pageDetectAutoBtn, SIGNAL(pressed()), this, SLOT(pageDetectionEnabled()));
	connect(pageDetectDisableBtn, SIGNAL(pressed()), this, SLOT(pageDetectionDisabled()));
	connect(applyToBtn, SIGNAL(clicked()), this, SLOT(showApplyToDialog()));
	connect(fineTuneBtn, SIGNAL(toggled(bool)), this, SLOT(fineTuningChanged(bool)));
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
    
    connect(leftBorder, SIGNAL(valueChanged(double)), this, SLOT(borderChanged()));
    connect(rightBorder, SIGNAL(valueChanged(double)), this, SLOT(borderChanged()));
    connect(topBorder, SIGNAL(valueChanged(double)), this, SLOT(borderChanged()));
    connect(bottomBorder, SIGNAL(valueChanged(double)), this, SLOT(borderChanged()));
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
}

OptionsWidget::~OptionsWidget()
{
}

void
OptionsWidget::preUpdateUI(PageId const& page_id)
{
	ScopedIncDec<int> guard(m_ignoreAutoManualToggle);
	
	m_pageId = page_id;
	autoBtn->setChecked(true);
	autoBtn->setEnabled(false);
	manualBtn->setEnabled(false);
	disableBtn->setEnabled(false);
	pageDetectAutoBtn->setEnabled(false);
	pageDetectDisableBtn->setEnabled(false);
}

void
OptionsWidget::postUpdateUI(UiData const& ui_data)
{
    Margins m = ui_data.pageBorders();
    
	m_uiData = ui_data;
    
    leftBorder->setValue(m.left());
    topBorder->setValue(m.top());
    rightBorder->setValue(m.right());
    bottomBorder->setValue(m.bottom());
    
	updateModeIndication(ui_data.mode());
	fineTuneBtn->setChecked(ui_data.fineTuning());
	pageDetectAutoBtn->setChecked(ui_data.pageDetection());
	pageDetectDisableBtn->setChecked(!ui_data.pageDetection());
	autoBtn->setEnabled(true);
	manualBtn->setEnabled(true);
	disableBtn->setEnabled(true);
	pageDetectAutoBtn->setEnabled(true);
	pageDetectDisableBtn->setEnabled(true);
	fineTuneBtn->setEnabled(true);
}

void
OptionsWidget::manualContentRectSet(QRectF const& content_rect)
{
	m_uiData.setContentRect(content_rect);
	m_uiData.setMode(MODE_MANUAL);
	m_uiData.setContentDetection(true);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
    m_uiData.setPageDetection(false);
>>>>>>> origin/enhanced
=======
    m_uiData.setPageDetection(false);
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
    m_uiData.setPageDetection(false);
>>>>>>> enhanced
	updateModeIndication(MODE_MANUAL);
	commitCurrentParams();
	
	emit invalidateThumbnail(m_pageId);
	emit reloadRequested();
}

void
OptionsWidget::modeChanged(bool const auto_mode)
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	if (m_ignoreAutoManualToggle) {
		return;
	}
<<<<<<< HEAD
=======
	//if (m_ignoreAutoManualToggle) {
	//	return;
	//}
>>>>>>> origin/enhanced
=======
	//if (m_ignoreAutoManualToggle) {
	//	return;
	//}
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	//if (m_ignoreAutoManualToggle) {
	//	return;
	//}
>>>>>>> enhanced

	if (auto_mode) {
		//m_ptrSettings->clearPageParams(m_pageId);
		m_uiData.setMode(MODE_AUTO);
		m_uiData.setContentDetection(true);
		commitCurrentParams();
		emit reloadRequested();
	} else {
        m_uiData.setPageDetection(false);
		m_uiData.setMode(MODE_MANUAL);
		m_uiData.setContentDetection(true);
		commitCurrentParams();
		emit reloadRequested();
	}
}

void OptionsWidget::autoMode()
{
	modeChanged(true);
}

void OptionsWidget::manualMode()
{
	modeChanged(false);
}

void
OptionsWidget::fineTuningChanged(bool checked)
{
	m_uiData.setFineTuneCorners(checked);
	commitCurrentParams();
	if (m_uiData.pageDetection()) {
		emit reloadRequested();
	}
}

void
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/tiff
OptionsWidget::fineTuningChanged(bool checked)
{
	m_uiData.setFineTuneCorners(checked);
	commitCurrentParams();
	if (m_uiData.pageDetection()) {
		emit reloadRequested();
	}
}

void
<<<<<<< HEAD
=======
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
OptionsWidget::contentDetectionDisabled(void)
{
	bool old = m_ignoreAutoManualToggle;
	m_ignoreAutoManualToggle = true;

	m_uiData.setContentDetection(false);
	commitCurrentParams();
	autoBtn->setChecked(false);
	manualBtn->setChecked(false);
	disableBtn->setChecked(true);
	emit reloadRequested();

	m_ignoreAutoManualToggle = old;
}

void
OptionsWidget::pageDetectionDisabled(void)
{
	m_uiData.setPageDetection(false);
	pageDetectAutoBtn->setChecked(false);
	pageDetectDisableBtn->setChecked(true);
	commitCurrentParams();
	emit reloadRequested();
}

void
OptionsWidget::pageDetectionEnabled(void)
{
	m_uiData.setPageDetection(true);
	pageDetectAutoBtn->setChecked(true);
	pageDetectDisableBtn->setChecked(false);
	commitCurrentParams();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	emit reloadRequested();
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
    emit reloadRequested();
}

void OptionsWidget::borderChanged()
{
    m_uiData.setPageBorders(leftBorder->value(), topBorder->value(), rightBorder->value(), bottomBorder->value());
    commitCurrentParams();
    emit reloadRequested();
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
	emit reloadRequested();
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
}

void
OptionsWidget::updateModeIndication(AutoManualMode const mode)
{
	ScopedIncDec<int> guard(m_ignoreAutoManualToggle);
	
	if (! m_uiData.contentDetection()) {
		disableBtn->setChecked(true);
		autoBtn->setChecked(false);
		manualBtn->setChecked(false);
	} else {
		disableBtn->setChecked(false);
		if (mode == MODE_AUTO) {
			autoBtn->setChecked(true);
			manualBtn->setChecked(false);
		} else {
			autoBtn->setChecked(false);
			manualBtn->setChecked(true);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
            pageDetectDisableBtn->setChecked(true);
            pageDetectAutoBtn->setChecked(false);
>>>>>>> origin/enhanced
=======
            pageDetectDisableBtn->setChecked(true);
            pageDetectAutoBtn->setChecked(false);
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
            pageDetectDisableBtn->setChecked(true);
            pageDetectAutoBtn->setChecked(false);
>>>>>>> enhanced
		}
	}
}

void
OptionsWidget::commitCurrentParams()
{
	Params params(
		m_uiData.contentRect(), m_uiData.contentSizeMM(),
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
	);
=======
		//m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
		Dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
	);
	params.setPageRect(m_uiData.pageRect());
    params.setPageBorders(m_uiData.pageBorders());
>>>>>>> origin/enhanced
=======
=======
>>>>>>> enhanced
		//m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
		Dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
	);
	params.setPageRect(m_uiData.pageRect());
    params.setPageBorders(m_uiData.pageBorders());
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
		m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
	);
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
	params.computeDeviation(m_ptrSettings->avg());
	m_ptrSettings->setPageParams(m_pageId, params);
}

void
OptionsWidget::showApplyToDialog()
{
	ApplyDialog* dialog = new ApplyDialog(
		this, m_pageId, m_pageSelectionAccessor
	);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	connect(
		dialog, SIGNAL(applySelection(std::set<PageId> const&, bool)),
		this, SLOT(applySelection(std::set<PageId> const&, bool))
	);
	dialog->show();
}

void
OptionsWidget::applySelection(std::set<PageId> const& pages, bool apply_content_box)
{
	if (pages.empty()) {
		return;
	}

	Dependencies deps;
	Params params(
		m_uiData.contentRect(), m_uiData.contentSizeMM(),
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
=======
		deps, m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
>>>>>>> origin/enhanced
=======
		deps, m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
>>>>>>> origin/enhanced
=======
		m_uiData.dependencies(), m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
>>>>>>> pod/tiff
=======
		deps, m_uiData.mode(), m_uiData.contentDetection(), m_uiData.pageDetection(), m_uiData.fineTuning()
>>>>>>> enhanced
	);

	BOOST_FOREACH(PageId const& page_id, pages) {
		std::auto_ptr<Params> old_params = m_ptrSettings->getPageParams(page_id);

		if (old_params.get()) {
			if (!apply_content_box) {
				params.setContentRect(old_params->contentRect());
				params.setContentSizeMM(old_params->contentSizeMM());
			}
			params.setPageRect(old_params->pageRect());
		}
		params.setPageBorders( Margins(leftBorder->value(), topBorder->value(), rightBorder->value(), bottomBorder->value()) );

		m_ptrSettings->setPageParams(page_id, params);
		//emit invalidateThumbnail(page_id);
	}
    emit invalidateAllThumbnails();
    emit reloadRequested();
}

/*========================= OptionsWidget::UiData ======================*/

OptionsWidget::UiData::UiData()
:	m_mode(MODE_AUTO),
	m_contentDetection(true),
	m_pageDetection(false),
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	m_fineTuneCorners(false)
=======
	m_fineTuneCorners(false),
    m_borders(0,0,0,0)
>>>>>>> origin/enhanced
=======
	m_fineTuneCorners(false),
    m_borders(0,0,0,0)
>>>>>>> origin/enhanced
=======
	m_fineTuneCorners(false)
>>>>>>> pod/tiff
=======
	m_fineTuneCorners(false),
    m_borders(0,0,0,0)
>>>>>>> enhanced
{
}

OptionsWidget::UiData::~UiData()
{
}

void
OptionsWidget::UiData::setSizeCalc(PhysSizeCalc const& calc)
{
	m_sizeCalc = calc;
}

void
OptionsWidget::UiData::setContentRect(QRectF const& content_rect)
{
	m_contentRect = content_rect;
}

QRectF const&
OptionsWidget::UiData::contentRect() const
{
	return m_contentRect;
}

void
OptionsWidget::UiData::setPageRect(QRectF const& page_rect)
{
	m_pageRect = page_rect;
}

QRectF const&
OptionsWidget::UiData::pageRect() const
{
	return m_pageRect;
}

QSizeF
OptionsWidget::UiData::contentSizeMM() const
{
	return m_sizeCalc.sizeMM(m_contentRect);
}

void
OptionsWidget::UiData::setDependencies(Dependencies const& deps)
{
	m_deps = deps;
}

Dependencies const&
OptionsWidget::UiData::dependencies() const
{
	return m_deps;
}

void
OptionsWidget::UiData::setMode(AutoManualMode const mode)
{
	m_mode = mode;
}

AutoManualMode
OptionsWidget::UiData::mode() const
{
	return m_mode;
}

void
OptionsWidget::UiData::setContentDetection(bool detect)
{
	m_contentDetection = detect;
}

void
OptionsWidget::UiData::setPageDetection(bool detect)
{
	m_pageDetection = detect;
}

void
OptionsWidget::UiData::setFineTuneCorners(bool fine_tune)
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	m_fineTuneCorners = fine_tune;
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
    m_fineTuneCorners = fine_tune;
}

void OptionsWidget::UiData::setPageBorders(double left, double top, double right, double bottom)
{
    m_borders.setLeft(left);
    m_borders.setTop(top);
    m_borders.setRight(right);
    m_borders.setBottom(bottom);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
	m_fineTuneCorners = fine_tune;
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
}


} // namespace select_content
