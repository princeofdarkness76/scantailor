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

#ifndef OUTPUT_OPTIONSWIDGET_H_
#define OUTPUT_OPTIONSWIDGET_H_

#include "ui_OutputOptionsWidget.h"
#include "FilterOptionsWidget.h"
#include "IntrusivePtr.h"
#include "PageId.h"
#include "PageSelectionAccessor.h"
#include "ColorParams.h"
#include "DewarpingMode.h"
#include "DepthPerception.h"
#include "DespeckleLevel.h"
#include "Dpi.h"
#include "ImageViewTab.h"
#include "Params.h"
#include <set>
//begin of modified by monday2000
//Picture_Shape
#include "Params.h"
//end of modified by monday2000

namespace dewarping
{
	class DistortionModel;
}

namespace output
{

class Settings;
class DewarpingParams;

class OptionsWidget
	: public FilterOptionsWidget, private Ui::OutputOptionsWidget
{
	Q_OBJECT
public:
	OptionsWidget(IntrusivePtr<Settings> const& settings,
		PageSelectionAccessor const& page_selection_accessor);
	
	virtual ~OptionsWidget();
	
	void preUpdateUI(PageId const& page_id);
	
	void postUpdateUI();

	ImageViewTab lastTab() const { return m_lastTab; }

    DepthPerception const& depthPerception() const { return m_depthPerception; }
signals:
	void despeckleLevelChanged(DespeckleLevel level, bool* handled);

	void depthPerceptionChanged(double val);
public slots:
	void tabChanged(ImageViewTab tab);

	void distortionModelChanged(dewarping::DistortionModel const& model);
private slots:
	void changeDpiButtonClicked();
	
	void applyColorsButtonClicked();
	
	void dpiChanged(std::set<PageId> const& pages, Dpi const& dpi);

	void applyColorsConfirmed(std::set<PageId> const& pages);

	void colorModeChanged(int idx);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/filters.cpp
=======
=======
<<<<<<< HEAD
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	void pictureShapeChanged(int idx);
//end of modified by monday2000	
=======

	void pictureShapeChanged(int idx);
=======

	void pictureShapeChanged(int idx);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> pod/filters.cpp
=======
=======
<<<<<<< HEAD
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
<<<<<<< HEAD
=======

	void pictureShapeChanged(int idx);
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/homebrew-formulae
<<<<<<< HEAD
=======

	void pictureShapeChanged(int idx);
>>>>>>> pod/scantailor-filters.h
=======

	void pictureShapeChanged(int idx);
=======

	void pictureShapeChanged(int idx);
=======

	void pictureShapeChanged(int idx);
=======

	void pictureShapeChanged(int idx);
=======

	void pictureShapeChanged(int idx);
	
	void tiffCompressionChanged(int idx);
>>>>>>> pod/translations
	
	void tiffCompressionChanged(int idx);
>>>>>>> enhanced
	
	void tiffCompressionChanged(int idx);
>>>>>>> pod/tiff
	
	void tiffCompressionChanged(int idx);
>>>>>>> origin/enhanced
	
	void tiffCompressionChanged(int idx);
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
<<<<<<< HEAD
>>>>>>> pod/filters.cpp
=======
>>>>>>> origin/enhanced
	
	void tiffCompressionChanged(int idx);
>>>>>>> pod/tiff
>>>>>>> pod/scantailor-filters.h
	
	void tiffCompressionChanged(int idx);
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
	
	void tiffCompressionChanged(int idx);
>>>>>>> scantailor/tiff
	
	void tiffCompressionChanged(int idx);
	
>>>>>>> scantailor/tiff
	void whiteMarginsToggled(bool checked);
	
	void equalizeIlluminationToggled(bool checked);
	
	void setLighterThreshold();
	
	void setDarkerThreshold();
	
	void setNeutralThreshold();
	
	void bwThresholdChanged();

	void despeckleOffSelected();

	void despeckleCautiousSelected();

	void despeckleNormalSelected();

	void despeckleAggressiveSelected();

	void applyDespeckleButtonClicked();

	void applyDespeckleConfirmed(std::set<PageId> const& pages);

	void changeDewarpingButtonClicked();

	void dewarpingChanged(std::set<PageId> const& pages, DewarpingMode const& mode);

	void applyDepthPerceptionButtonClicked();

	void applyDepthPerceptionConfirmed(std::set<PageId> const& pages);

	void depthPerceptionChangedSlot(int val);
private:
	void handleDespeckleLevelChange(DespeckleLevel level);

	void reloadIfNecessary();

	void updateDpiDisplay();

	void updateColorsDisplay();

	void updateDewarpingDisplay();
	
	IntrusivePtr<Settings> m_ptrSettings;
	PageSelectionAccessor m_pageSelectionAccessor;
	PageId m_pageId;
	Dpi m_outputDpi;
	ColorParams m_colorParams;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/filters.cpp
=======
=======
<<<<<<< HEAD
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	PictureShape m_pictureShape;
//end of modified by monday2000
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> pod/filters.cpp
=======
=======
<<<<<<< HEAD
>>>>>>> pod/homebrew-formulae
=======
=======
<<<<<<< HEAD
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
<<<<<<< HEAD
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
=======
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> enhanced
=======
	PictureShape m_pictureShape;
>>>>>>> pod/translations
	DepthPerception m_depthPerception;
	DewarpingMode m_dewarpingMode;
	DespeckleLevel m_despeckleLevel;
	ImageViewTab m_lastTab;
	int m_ignoreThresholdChanges;
};

} // namespace output

#endif
