/*
    Scan Tailor - Interactive post-processing tool for scanned pages.

    CommandLine - Interface for ScanTailor's parameters provided on CL.
    Copyright (C) 2011 Petr Kovar <pejuko@gmail.com>

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

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include <QMap>
#include <QRectF>
#include <QStringList>
#include <iostream>

#include "Dpi.h"
#include "filters/page_split/LayoutType.h"
#include "filters/output/ColorParams.h"
#include "filters/output/Params.h"
#include "filters/output/DespeckleLevel.h"
#include "filters/output/DewarpingMode.h"
#include "filters/output/DepthPerception.h"
#include "filters/page_layout/Settings.h"
#include "filters/page_layout/Alignment.h"
#include "ImageFileInfo.h"
#include "AutoManualMode.h"
#include "Margins.h"
#include "Despeckle.h"
//begin of modified by monday2000
//Picture_Shape
#include "filters/output/Params.h"
#include "filters/page_layout/Settings.h"
//end of modified by monday2000

namespace page_layout {
    class Alignment;
}

namespace page_layout {
    class Alignment;
}

namespace page_layout {
    class Alignment;
}

namespace page_layout {
    class Alignment;
}

/**
 * CommandLine is a singleton simulation.
 * use CommandLine::get() to get access to global class
 * use CommandLine::set(CommandLine const&) to set the global class
 */
class CommandLine
{
	// Member-wise copying is OK.
public:
	enum Orientation {TOP, LEFT, RIGHT, UPSIDEDOWN};

	static CommandLine const& get() { return m_globalInstance; }
	static void set(CommandLine const& cl);

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false) { CommandLine::parseCli(argv); }
=======
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false), m_defaultNull(false) { CommandLine::parseCli(argv); }
>>>>>>> origin/enhanced
=======
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false), m_defaultNull(false) { CommandLine::parseCli(argv); }
>>>>>>> origin/enhanced
=======
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false) { CommandLine::parseCli(argv); }
>>>>>>> pod/tiff
=======
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false), m_defaultNull(false) { CommandLine::parseCli(argv); }
>>>>>>> enhanced
=======
	CommandLine(QStringList const& argv, bool g=true) : m_error(false), m_gui(g), m_global(false), m_defaultNull(false) { CommandLine::parseCli(argv); }
>>>>>>> pod/translations

	bool isGui() const { return m_gui; }
	bool isVerbose() const { return contains("verbose"); }
	bool isError() const { return m_error; }

	std::vector<ImageFileInfo> const& images() const { return m_images; }
	QString const& outputDirectory() const { return m_outputDirectory; }
	QString const& projectFile() const { return m_projectFile; }
	QString const& outputProjectFile() const { return m_outputProjectFile; }

	bool isContentDetectionEnabled() const { return !contains("disable-content-detection"); };
	bool isPageDetectionEnabled() const { return contains("enable-page-detection"); };
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/tiff
	bool isFineTuningEnabled() const { return contains("enable-fine-tuning"); };
	bool isAutoMarginsEnabled() const { return contains("enable-auto-margins"); };

	bool hasMargins() const;
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	bool isForcePageDetectionDisabled() const { return contains("force-disable-page-detection"); };
	bool isFineTuningEnabled() const { return contains("enable-fine-tuning"); };
	bool isAutoMarginsEnabled() const { return contains("enable-auto-margins"); };

	bool hasMargins(QString base="margins") const;
    bool hasPageBorders() const { return hasMargins("page-borders"); };
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	bool hasAlignment() const;
	bool hasOutputDpi() const;
	bool hasLanguage() const;

	bool hasHelp() const { return contains("help"); }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	bool hasOutputProject() const { return contains("output-project"); }
	bool hasLayout() const { return contains("layout"); }
	bool hasLayoutDirection() const { return contains("layout-direction"); }
	bool hasStartFilterIdx() const { return contains("start-filter"); }
	bool hasEndFilterIdx() const { return contains("end-filter"); }
	bool hasOrientation() const { return contains("orientation"); }
	bool hasDeskewAngle() const { return contains("rotate"); }
	bool hasDeskew() const { return contains("deskew"); }
	bool hasSkewDeviation() const { return contains("skew-deviation"); }
	bool hasContentRect() const { return contains("content-box"); }
	bool hasContentDeviation() const { return contains("content-deviation"); }
	bool hasColorMode() const { return contains("color-mode"); }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
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
	bool hasPictureShape() const { return contains("picture-shape") && !m_options["picture-shape"].isEmpty(); }
//end of modified by monday2000
=======
	bool hasPictureShape() const { return contains("picture-shape"); }
>>>>>>> scantailor/tiff
=======
	bool hasPictureShape() const { return contains("picture-shape"); }
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
	bool hasPictureShape() const { return contains("picture-shape"); }
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	bool hasPictureShape() const { return contains("picture-shape"); }
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
	bool hasPictureShape() const { return contains("picture-shape"); }
>>>>>>> pod/tiff
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	bool hasOutputProject() const { return contains("output-project") && !m_options["output-project"].isEmpty(); }
	bool hasLayout() const { return contains("layout") && !m_options["layout"].isEmpty(); }
	bool hasLayoutDirection() const { return contains("layout-direction") && !m_options["layout-direction"].isEmpty(); }
	bool hasStartFilterIdx() const { return contains("start-filter") && !m_options["start-filter"].isEmpty(); }
	bool hasEndFilterIdx() const { return contains("end-filter") && !m_options["end-filter"].isEmpty(); }
	bool hasOrientation() const { return contains("orientation") && !m_options["orientation"].isEmpty(); }
	bool hasDeskewAngle() const { return contains("rotate") && !m_options["rotate"].isEmpty(); }
	bool hasDeskew() const { return contains("deskew") && !m_options["deskew"].isEmpty(); }
	bool hasSkewDeviation() const { return contains("skew-deviation") && !m_options["skew-deviation"].isEmpty(); }
	bool hasContentRect() const { return contains("content-box") && !m_options["content-box"].isEmpty(); }
	bool hasContentDeviation() const { return contains("content-deviation") && !m_options["content-deviation"].isEmpty(); }
	bool hasContentDetection() const { return ! contains("disable-content-detection"); }
	bool hasContentText() const { return !contains("disable-content-text-mask"); }
	bool hasColorMode() const { return contains("color-mode") && !m_options["color-mode"].isEmpty(); }
	bool hasDefaultColorMode() const { return contains("default-color-mode") && !m_options["default-color-mode"].isEmpty(); }
	bool hasPictureShape() const { return contains("picture-shape") && !m_options["picture-shape"].isEmpty(); }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
>>>>>>> origin/enhanced
=======
	bool hasPictureShape() const { return contains("picture-shape"); }
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	bool hasWhiteMargins() const { return contains("white-margins"); }
	bool hasNormalizeIllumination() const { return contains("normalize-illumination"); }
	bool hasThreshold() const { return contains("threshold") && !m_options["threshold"].isEmpty(); }
	bool hasDespeckle() const { return contains("despeckle") && !m_options["despeckle"].isEmpty(); }
	bool hasDewarping() const { return contains("dewarping"); }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	bool hasMatchLayoutTolerance() const { return contains("match-layout-tolerance"); }
	bool hasDepthPerception() const { return contains("depth-perception"); }
	bool hasTiffCompression() const { return contains("tiff-compression"); }
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	bool hasMatchLayoutTolerance() const { return contains("match-layout-tolerance") && !m_options["match-layout-tolerance"].isEmpty(); }
	bool hasDepthPerception() const { return contains("depth-perception") && !m_options["depth-perception"].isEmpty(); }
	bool hasTiffCompression() const { return contains("tiff-compression") && !m_options["tiff-compression"].isEmpty(); }
	bool hasTiffForceRGB() const { return contains("tiff-force-rgb"); }
	bool hasTiffForceGrayscale() const { return contains("tiff-force-grayscale"); }
	bool hasTiffForceKeepColorSpace() const { return contains("tiff-force-keep-color-space"); }
	bool hasWindowTitle() const { return contains("window-title") && !m_options["window-title"].isEmpty(); }
	bool hasPageDetectionBox() const { return contains("page-detection-box") && !m_options["page-detection-box"].isEmpty(); }
	bool hasPageDetectionTolerance() const { return contains("page-detection-tolerance") && !m_options["page-detection-tolerance"].isEmpty(); }
 	bool hasDisableCheckOutput() const { return contains("disable-check-output"); }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
	bool hasMatchLayoutTolerance() const { return contains("match-layout-tolerance"); }
	bool hasDepthPerception() const { return contains("depth-perception"); }
	bool hasTiffCompression() const { return contains("tiff-compression"); }
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations

	page_split::LayoutType getLayout() const { return m_layoutType; }
	Qt::LayoutDirection getLayoutDirection() const { return m_layoutDirection; }
	output::ColorParams::ColorMode getColorMode() const { return m_colorMode; }
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
	output::PictureShape getPictureShape() const { return m_pictureShape; }
//end of modified by monday2000
=======
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> scantailor/tiff
=======
	output::PictureShape getPictureShape() const { return m_pictureShape; }
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
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	output::PictureShape getPictureShape() const { return m_pictureShape; }
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
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode getDefaultColorMode() const { return m_defaultColorMode; }
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	output::ColorParams::ColorMode getDefaultColorMode() const { return m_defaultColorMode; }
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> origin/enhanced
=======
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode getDefaultColorMode() const { return m_defaultColorMode; }
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> enhanced
=======
	output::ColorParams::ColorMode getDefaultColorMode() const { return m_defaultColorMode; }
	output::PictureShape getPictureShape() const { return m_pictureShape; }
>>>>>>> pod/translations
	Dpi getInputDpi() const { return m_dpi; }
	Dpi getOutputDpi() const { return m_outputDpi; }
    Dpi getDefaultOutputDpi() const { return m_defaultOutputDpi; }
	Margins getMargins() const { return m_margins; }
	Margins getDefaultMargins() const { return m_defaultMargins; }
    Margins getPageBorders() const { return m_pageBorders; }
	page_layout::Alignment getAlignment() const { return m_alignment; }
	Despeckle::Level getContentDetection() const { return m_contentDetection; }
	QRectF getContentRect() const { return m_contentRect; }
	double getContentDeviation() const { return m_contentDeviation; }
	Orientation getOrientation() const { return m_orientation; }
	int getThreshold() const { return m_threshold; }
	double getDeskewAngle() const { return m_deskewAngle; }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	AutoManualMode getDeskewMode() const { return m_deskewMode; }
>>>>>>> origin/enhanced
=======
	AutoManualMode getDeskewMode() const { return m_deskewMode; }
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	AutoManualMode getDeskewMode() const { return m_deskewMode; }
>>>>>>> enhanced
=======
	AutoManualMode getDeskewMode() const { return m_deskewMode; }
>>>>>>> pod/translations
	double getSkewDeviation() const { return m_skewDeviation; }
	int getStartFilterIdx() const { return m_startFilterIdx; }
	int getEndFilterIdx() const { return m_endFilterIdx; }
	output::DewarpingMode getDewarpingMode() const { return m_dewarpingMode; }
	output::DespeckleLevel getDespeckleLevel() const { return m_despeckleLevel; }
	output::DepthPerception getDepthPerception() const { return m_depthPerception; }
	float getMatchLayoutTolerance() const { return m_matchLayoutTolerance; }
	int getTiffCompression() const { return m_compression; }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	QString getLanguage() const { return m_language; }
	QString getWindowTitle() const { return m_windowTitle; }
	QSizeF getPageDetectionBox() const { return m_pageDetectionBox; }
	double getPageDetectionTolerance() const { return m_pageDetectionTolerance; }
    bool getDefaultNull() const { return m_defaultNull; }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations

	bool help() { return m_options.contains("help"); }
	void printHelp();
    
private:
	CommandLine() : m_gui(true), m_global(false) {}

	static CommandLine m_globalInstance;
	bool m_error;
	bool m_gui;
	bool m_global;
	QString m_language;
	QString m_windowTitle;
	QSizeF m_pageDetectionBox;
	double m_pageDetectionTolerance;
    bool m_defaultNull;

	bool isGlobal() { return m_global; }
	void setGlobal() { m_global = true; }

	bool contains(QString const& key) const { return m_options.contains(key); }

	QMap<QString, QString> m_options;
	QString m_projectFile;
	QString m_outputProjectFile;
	std::vector<QFileInfo> m_files;
	std::vector<ImageFileInfo> m_images;
	QString m_outputDirectory;

	page_split::LayoutType m_layoutType;
	Qt::LayoutDirection m_layoutDirection;
	output::ColorParams::ColorMode m_colorMode;
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
	output::PictureShape m_pictureShape;
//end of modified by monday2000
=======
	output::PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
	output::PictureShape m_pictureShape;
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
	output::PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	output::PictureShape m_pictureShape;
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
	output::PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode m_defaultColorMode;
	output::PictureShape m_pictureShape;
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	output::ColorParams::ColorMode m_defaultColorMode;
	output::PictureShape m_pictureShape;
>>>>>>> origin/enhanced
=======
	output::PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode m_defaultColorMode;
	output::PictureShape m_pictureShape;
>>>>>>> enhanced
=======
	output::ColorParams::ColorMode m_defaultColorMode;
	output::PictureShape m_pictureShape;
>>>>>>> pod/translations
	Dpi m_dpi;
	Dpi m_outputDpi;
    Dpi m_defaultOutputDpi;
	Margins m_margins;
	Margins m_defaultMargins;
    Margins m_pageBorders;
	page_layout::Alignment m_alignment;
	Despeckle::Level m_contentDetection;
	QRectF m_contentRect;
	double m_contentDeviation;
	Orientation m_orientation;
	int m_threshold;
	double m_deskewAngle;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	AutoManualMode m_deskewMode;
>>>>>>> origin/enhanced
=======
	AutoManualMode m_deskewMode;
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	AutoManualMode m_deskewMode;
>>>>>>> enhanced
=======
	AutoManualMode m_deskewMode;
>>>>>>> pod/translations
	double m_skewDeviation;
	int m_startFilterIdx;
	int m_endFilterIdx;
	output::DewarpingMode m_dewarpingMode;
	output::DespeckleLevel m_despeckleLevel;
	output::DepthPerception m_depthPerception;
	float m_matchLayoutTolerance;
	int  m_compression;

	bool parseCli(QStringList const& argv);
	void addImage(QString const& path);
	void setup();
	page_split::LayoutType fetchLayoutType();
	output::ColorParams::ColorMode fetchColorMode();
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
	output::PictureShape fetchPictureShape();
//end of modified by monday2000
=======
	output::PictureShape fetchPictureShape();
>>>>>>> scantailor/tiff
=======
	output::PictureShape fetchPictureShape();
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
	output::PictureShape fetchPictureShape();
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	output::PictureShape fetchPictureShape();
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
	output::PictureShape fetchPictureShape();
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode fetchDefaultColorMode();
	output::PictureShape fetchPictureShape();
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	output::ColorParams::ColorMode fetchDefaultColorMode();
	output::PictureShape fetchPictureShape();
>>>>>>> origin/enhanced
=======
	output::PictureShape fetchPictureShape();
>>>>>>> pod/tiff
=======
	output::ColorParams::ColorMode fetchDefaultColorMode();
	output::PictureShape fetchPictureShape();
>>>>>>> enhanced
=======
	output::ColorParams::ColorMode fetchDefaultColorMode();
	output::PictureShape fetchPictureShape();
>>>>>>> pod/translations
	Qt::LayoutDirection fetchLayoutDirection();
	Dpi fetchDpi(QString oname="dpi");
	Margins fetchMargins(QString base="margins", Margins def=Margins(10.0, 5.0, 10.0, 5.0));
    Margins fetchPageBorders() { return fetchMargins("page-borders", Margins(0,0,0,0)); }
	page_layout::Alignment fetchAlignment();
	Despeckle::Level fetchContentDetection();
	QRectF fetchContentRect();
	double fetchContentDeviation();
	Orientation fetchOrientation();
	QString fetchOutputProjectFile();
	int fetchThreshold();
	double fetchDeskewAngle();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	AutoManualMode fetchDeskewMode();
>>>>>>> origin/enhanced
=======
	AutoManualMode fetchDeskewMode();
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	AutoManualMode fetchDeskewMode();
>>>>>>> enhanced
=======
	AutoManualMode fetchDeskewMode();
>>>>>>> pod/translations
	double fetchSkewDeviation();
	int fetchStartFilterIdx();
	int fetchEndFilterIdx();
	output::DewarpingMode fetchDewarpingMode();
	output::DespeckleLevel fetchDespeckleLevel();
	output::DepthPerception fetchDepthPerception();
	float fetchMatchLayoutTolerance();
	int fetchCompression() const;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	QString fetchLanguage() const;
	QString fetchWindowTitle() const;
	QSizeF fetchPageDetectionBox() const;
	double fetchPageDetectionTolerance() const;
    bool fetchDefaultNull();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
};

#endif
