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

#ifndef PAGE_LAYOUT_OPTIONSWIDGET_H_
#define PAGE_LAYOUT_OPTIONSWIDGET_H_

#include "ui_PageLayoutOptionsWidget.h"
#include "FilterOptionsWidget.h"
#include "IntrusivePtr.h"
#include "Margins.h"
#include "Alignment.h"
#include "Scope.h"
#include <QIcon>
#include <memory>
#include <map>

class QToolButton;
class PageSequence;

namespace page_layout
{

class Settings;

class OptionsWidget :
	public FilterOptionsWidget,
	public Ui::PageLayoutOptionsWidget
{
	Q_OBJECT
public:
	OptionsWidget(
		IntrusivePtr<Settings> const& settings,
		IntrusivePtr<PageSequence> const& page_sequence);
	
	virtual ~OptionsWidget();
	
	void preUpdateUI(Margins const& margins_mm, Alignment const& alignment);
	
	void postUpdateUI();
	
	bool leftRightLinked() const { return m_leftRightLinked; }
	
	bool topBottomLinked() const { return m_topBottomLinked; }
	
	Margins const& marginsMM() const { return m_marginsMM; }
	
	Alignment const& alignment() const { return m_alignment; }
signals:
	void leftRightLinkToggled(bool linked);
	
	void topBottomLinkToggled(bool linked);
	
	void alignmentChanged(Alignment const& alignment);
	
	void marginsSetLocally(Margins const& margins_mm);
	
	void aggregateHardSizeChanged();
public slots:
	void marginsSetExternally(Margins const& margins_mm);
private slots:
	void unitsChanged(int idx);
	
	void horMarginsChanged(double val);
	
	void vertMarginsChanged(double val);
	
	void topBottomLinkClicked();
	
	void leftRightLinkClicked();
	
	void alignWithOthersToggled();
	
	void alignmentButtonClicked();
	
	void goToWidestPage();
	
	void goToTallestPage();
	
	void showApplyMarginsDialog();
	
	void showApplyAlignmentDialog();
	
	void applyMargins(Scope scope);
	
	void applyAlignment(Scope scope);
private:
	typedef std::map<QToolButton*, Alignment> AlignmentByButton;
	
	void updateMarginsDisplay();
	
	void updateLinkDisplay(QToolButton* button, bool linked);
	
	void enableDisableAlignmentButtons();
	
	IntrusivePtr<Settings> m_ptrSettings;
	IntrusivePtr<PageSequence> m_ptrPageSequence;
	QIcon m_chainIcon;
	QIcon m_brokenChainIcon;
	AlignmentByButton m_alignmentByButton;
	double m_mmToUnit;
	double m_unitToMM;
	Margins m_marginsMM;
	Alignment m_alignment;
	int m_ignoreMarginChanges;
	bool m_leftRightLinked;
	bool m_topBottomLinked;
};

} // namespace page_layout

#endif
