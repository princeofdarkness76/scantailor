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

#include <cstdlib>
#include <assert.h>
#include <iostream>
#include <tiff.h>

#include <QDir>
#include <QMap>
#include <QRegExp>
#include <QStringList>

#include "Dpi.h"
#include "ImageId.h"
#include "version.h"
#include "CommandLine.h"
#include "ImageFileInfo.h"
#include "ImageMetadata.h"
#include "filters/page_split/LayoutType.h"
#include "filters/page_layout/Settings.h"
#include "Margins.h"
#include "Despeckle.h"


CommandLine CommandLine::m_globalInstance;


void
CommandLine::set(CommandLine const& cl)
{
	assert(!m_globalInstance.isGlobal());

	m_globalInstance = cl;
	m_globalInstance.setGlobal();
}


bool
CommandLine::parseCli(QStringList const& argv)
{
	QRegExp rx("^--([^=]+)=(.*)$");
	QRegExp rx_switch("^--([^=]+)$");
	QRegExp rx_short("^-([^=]+)=(.*)$");
	QRegExp rx_short_switch("^-([^=]+)$");
	QRegExp rx_project(".*\\.ScanTailor$", Qt::CaseInsensitive);

	QList<QString> opts;
	opts << "help";
	opts << "verbose";
	opts << "layout";
	opts << "layout-direction";
	opts << "orientation";
	opts << "rotate";
	opts << "deskew";
	opts << "skew-deviation";
	opts << "disable-content-detection";
	opts << "enable-page-detection";
	opts << "enable-fine-tuning";
	opts << "content-detection";
	opts << "content-box";
	opts << "content-deviation";
	opts << "enable-auto-margins";
	opts << "margins";
	opts << "margins-left";
	opts << "margins-right";
	opts << "margins-top";
	opts << "margins-bottom";
	opts << "match-layout";
	opts << "match-layout-tolerance";
	opts << "alignment";
	opts << "alignment-vertical";
	opts << "alignment-horizontal";
	opts << "alignment-tolerance";
	opts << "dpi";
	opts << "output-dpi";
	opts << "dpi-x";
	opts << "dpi-y";
	opts << "output-dpi-x";
	opts << "output-dpi-y";
	opts << "color-mode";
	opts << "white-margins";
	opts << "normalize-illumination";
	opts << "threshold";
	opts << "despeckle";
	opts << "dewarping";
	opts << "depth-perception";
	opts << "start-filter";
	opts << "end-filter";
	opts << "output-project";
	opts << "tiff-compression";

	QMap<QString, QString> shortMap;
	shortMap["h"] = "help";
	shortMap["help"] = "help";
	shortMap["v"] = "verbose";
	shortMap["l"] = "layout";
	shortMap["ld"] = "layout-direction";
	shortMap["o"] = "output-project";

	// skip first argument (scantailor)
	for (int i=1; i<argv.size(); i++) {
#ifdef DEBUG_CLI
	std::cout << "arg[" << i << "]=" << argv[i].toAscii().constData() << "\n";
#endif
		if (rx.exactMatch(argv[i])) {
			// option with a value
			QString key = rx.cap(1);
			if (! opts.contains(key)) {
				m_error = true;
				std::cout << "Unknown option '" << key.toStdString() << "'" << std::endl;
				continue;
			}
			m_options[key] = rx.cap(2);
		} else if (rx_switch.exactMatch(argv[i])) {
			// option without value
			QString key = rx_switch.cap(1);
			if (! opts.contains(key)) {
				m_error = true;
				std::cout << "Unknown switch '" << key.toStdString() << "'" << std::endl;
				continue;
			}
			m_options[key] = "true";
		} else if (rx_short.exactMatch(argv[i])) {
			// option with a value
			QString key = shortMap[rx_short.cap(1)];
			if (key == "") {
				std::cout << "Unknown option: '" << rx_short.cap(1).toStdString() << "'" << std::endl;
				m_error = true;
				continue;
			}
			m_options[key] = rx_short.cap(2);
		} else if (rx_short_switch.exactMatch(argv[i])) {
			QString key = shortMap[rx_short_switch.cap(1)];
			if (key == "") {
				std::cout << "Unknown switch: '" << rx_short_switch.cap(1).toStdString() << "'" << std::endl;
				m_error = true;
				continue;
			}
			m_options[key] = "true";
		} else if (rx_project.exactMatch(argv[i])) {
			// project file
			CommandLine::m_projectFile = argv[i];
		} else {
			// handle input images and output directory
			QFileInfo file(argv[i]);
			if (i==(argv.size()-1)) {
				// output directory
				if (file.isDir()) {
					CommandLine::m_outputDirectory = file.filePath();
				} else {
					std::cout << "Error: Last argument must be an existing directory" << "\n";
					exit(1);
				}
			} else if (file.filePath() == "-") {
				// file names from stdin
				std::string fname;
				while (! std::cin.eof()) {
					std::cin >> fname;
					addImage(fname.c_str());
				}
			} else if (file.isDir()) {
				// add all files from given directory as images
				QDir dir(argv[i]);
				QStringList files = dir.entryList(QDir::Files, QDir::Name);
				for (int f=0; f<files.count(); f++) {
					addImage(dir.filePath(files[f]));
				}
			} else {
				// argument is image
				addImage(file.filePath());
			}
		}
	}

	setup();

#ifdef DEBUG_CLI
	QStringList params = m_options.keys();
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options.value(params[i]).toAscii().constData() << "\n"; }
	std::cout << "Images: " << CommandLine::m_images.size() << "\n";
#endif

	return m_error;
}

void
CommandLine::addImage(QString const& path)
{
	QFileInfo file(path);

	// create ImageFileInfo and push to images
	ImageId const image_id(file.filePath());
	ImageMetadata metadata;
	metadata.setDpi(fetchDpi());
	std::vector<ImageMetadata> vMetadata;
	vMetadata.push_back(metadata);
	ImageFileInfo image_info(file, vMetadata);
	m_images.push_back(image_info);
	m_files.push_back(file);
}

void
CommandLine::setup()
{
	m_outputProjectFile = fetchOutputProjectFile();
	m_layoutType = fetchLayoutType();
	m_layoutDirection = fetchLayoutDirection();
	m_colorMode = fetchColorMode();
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	m_pictureShape = fetchPictureShape();
//end of modified by monday2000
=======
	m_pictureShape = fetchPictureShape();
>>>>>>> scantailor/tiff
=======
	m_pictureShape = fetchPictureShape();
>>>>>>> scantailor/tiff
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	m_pictureShape = fetchPictureShape();
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
	m_pictureShape = fetchPictureShape();
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
	m_dpi = fetchDpi();
	m_outputDpi = fetchDpi("output-dpi");
	m_margins = fetchMargins();
	m_alignment = fetchAlignment();
	m_contentDetection = fetchContentDetection();
	m_contentRect = fetchContentRect();
	m_contentDeviation = fetchContentDeviation();
	m_orientation = fetchOrientation();
	m_threshold = fetchThreshold();
	m_deskewAngle = fetchDeskewAngle();
	m_skewDeviation = fetchSkewDeviation();
	m_startFilterIdx = fetchStartFilterIdx();
	m_endFilterIdx = fetchEndFilterIdx();
	m_matchLayoutTolerance = fetchMatchLayoutTolerance();
	m_dewarpingMode = fetchDewarpingMode();
	m_compression = fetchCompression();
}


void
CommandLine::printHelp()
{
	std::cout << "\n";
	std::cout << "Scan Tailor is a post-processing tool for scanned pages." << "\n";
	std::cout << "Version: " << VERSION << "\n";
	std::cout << "\n";
	std::cout << "ScanTailor usage: " << "\n";
	std::cout << "\t1) scantailor" << "\n";
	std::cout << "\t2) scantailor <project_file>" << "\n";
	std::cout << "\t3) scantailor-cli [options] <images|directory|-> <output_directory>" << "\n";
	std::cout << "\t4) scantailor-cli [options] <project_file> [output_directory]" << "\n";
	std::cout << "\n";
	std::cout << "1)" << "\n";
	std::cout << "\tstart ScanTailor's GUI interface" << "\n";
	std::cout << "2)" << "\n";
	std::cout << "\tstart ScanTailor's GUI interface and load project file" << "\n";
	std::cout << "3)" << "\n";
	std::cout << "\tbatch processing images from command line; no GUI" << "\n";
	std::cout << "\tfile names are collected from arguments, input directory or stdin (-)" << "\n";
	std::cout << "4)" << "\n";
	std::cout << "\tbatch processing project from command line; no GUI" << "\n";
	std::cout << "\tif output_directory is specified as last argument, it overwrites the one in project file" << "\n";
	std::cout << "\n";
	std::cout << "Options:" << "\n";
	std::cout << "\t--help, -h" << "\n";
	std::cout << "\t--verbose, -v" << "\n";
	std::cout << "\t--layout=, -l=<0|1|1.5|2>\t\t-- default: 0" << "\n";
	std::cout << "\t\t\t  0: auto detect" << "\n";
	std::cout << "\t\t\t  1: one page layout" << "\n";
	std::cout << "\t\t\t1.5: one page layout but cutting is needed" << "\n";
	std::cout << "\t\t\t  2: two page layout" << "\n";
	std::cout << "\t--layout-direction=, -ld=<lr|rl>\t-- default: lr" << "\n";
	std::cout << "\t--orientation=<left|right|upsidedown|none>\n\t\t\t\t\t\t-- default: none" << "\n";
	std::cout << "\t--rotate=<0.0...360.0>\t\t\t-- it also sets deskew to manual mode" << "\n";
	std::cout << "\t--deskew=<auto|manual>\t\t\t-- default: auto" << "\n";
	std::cout << "\t--skew-deviation=<0.0...)\t\t\t-- default: 1.0; pages with bigger skew deviation will be painted in red" << "\n";
	std::cout << "\t--disable-content-detection\t\t\t-- default: enabled" << "\n";
	std::cout << "\t--enable-page-detection\t\t\t-- default: disabled" << "\n";
	std::cout << "\t--enable-fine-tuning\t\t\t-- default: disabled; if page detection enabled it moves edges while corners are in black" << "\n";
	std::cout << "\t--content-detection=<cautious|normal|aggressive>\n\t\t\t\t\t\t-- default: normal" << "\n";
	std::cout << "\t--content-deviation=<0.0...)\t\t\t-- default: 2.0; pages with bigger content deviation will be painted in red" << "\n";
	std::cout << "\t--content-box=<<left_offset>x<top_offset>:<width>x<height>>" << "\n";
	std::cout << "\t\t\t\t\t\t-- if set the content detection is se to manual mode" << "\n";
	std::cout << "\t\t\t\t\t\t   example: --content-box=100x100:1500x2500" << "\n";
	std::cout << "\t--enable-auto-margins\t\t\t-- sets the margins to original ones (based on detected page or image size)" << "\n";
	std::cout << "\t--margins=<number>\t\t\t-- sets left, top, right and bottom margins to same number." << "\n";
	std::cout << "\t\t--margins-left=<number>" << "\n";
	std::cout << "\t\t--margins-right=<number>" << "\n";
	std::cout << "\t\t--margins-top=<number>" << "\n";
	std::cout << "\t\t--margins-bottom=<number>" << "\n";
	std::cout << "\t--match-layout=<true|false>\t\t-- default: true" << "\n";
	std::cout << "\t--match-layout-tolerance=<0.0...)\t-- default: off" << "\n";
	std::cout << "\t--alignment=<center|original|auto>\t-- sets vertical to original and horizontal to center" << "\n";
	std::cout << "\t\t--alignment-vertical=<top|center|bottom|original>" << "\n";
	std::cout << "\t\t--alignment-horizontal=<left|center|right|original>" << "\n";
	std::cout << "\t--alignment-tolerance=<float>\t\t-- sets tolerance for auto alignment" << "\n";
	std::cout << "\t--dpi=<number>\t\t\t\t-- sets x and y dpi. default: 600" << "\n";
	std::cout << "\t\t--dpi-x=<number>" << "\n";
	std::cout << "\t\t--dpi-y=<number>" << "\n";
	std::cout << "\t--output-dpi=<number>\t\t\t-- sets x and y output dpi. default: 600" << "\n";
	std::cout << "\t\t--output-dpi-x=<number>" << "\n";
	std::cout << "\t\t--output-dpi-y=<number>" << "\n";
	std::cout << "\t--color-mode=<black_and_white|color_grayscale|mixed>\n\t\t\t\t\t\t-- default: black_and_white" << "\n";
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << std::endl;
//end of modified by monday2000
=======
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> scantailor/tiff
=======
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> scantailor/tiff
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
	std::cout << "\t--white-margins\t\t\t\t-- default: false" << "\n";
	std::cout << "\t--normalize-illumination\t\t-- default: false" << "\n";
	std::cout << "\t--threshold=<n>\t\t\t\t-- n<0 thinner, n>0 thicker; default: 0" << "\n";
	std::cout << "\t--despeckle=<off|cautious|normal|aggressive>\n\t\t\t\t\t\t-- default: normal" << "\n";
	std::cout << "\t--dewarping=<off|auto>\t\t\t-- default: off" << "\n";
	std::cout << "\t--depth-perception=<1.0...3.0>\t\t-- default: 2.0" << "\n";
	std::cout << "\t--start-filter=<1...6>\t\t\t-- default: 4" << "\n";
	std::cout << "\t--end-filter=<1...6>\t\t\t-- default: 6" << "\n";
	std::cout << "\t--output-project=, -o=<project_name>" << "\n";
	std::cout << "\t--tiff-compression=<lzw|deflate|packbits|jpeg|none>\t-- default: lzw" << "\n";
	std::cout << "\n";
}


page_split::LayoutType
CommandLine::fetchLayoutType()
{
	page_split::LayoutType lt = page_split::AUTO_LAYOUT_TYPE;

	if (!hasLayout())
		return lt;

	if (m_options.value("layout") == "1")
		lt = page_split::SINGLE_PAGE_UNCUT;
	else if (m_options.value("layout") == "1.5")
		lt = page_split::PAGE_PLUS_OFFCUT;
	else if (m_options.value("layout") == "2")
		lt = page_split::TWO_PAGES;

	return lt;
}

Qt::LayoutDirection
CommandLine::fetchLayoutDirection()
{
	Qt::LayoutDirection l = Qt::LeftToRight;
	if (!hasLayoutDirection())
		return l;

	QString ld = m_options.value("layout-direction").toLower();
	if (ld == "rl")
		l = Qt::RightToLeft;

	return l;
}

Dpi
CommandLine::fetchDpi(QString oname)
{
	int xdpi=600;
	int ydpi=600;

	if (m_options.contains(oname+"-x")) {
		xdpi = m_options.value(oname+"-x").toInt();
	}
	if (m_options.contains(oname+"-y")) {
		ydpi = m_options.value(oname+"-y").toInt();
	}
	if (m_options.contains(oname)) {
		xdpi = m_options.value(oname).toInt();
		ydpi = m_options.value(oname).toInt();
	}

	return Dpi(xdpi, ydpi);
}

output::ColorParams::ColorMode
CommandLine::fetchColorMode()
{
	QString cm = m_options.value("color-mode").toLower();
	
	if (cm == "color_grayscale")
		return output::ColorParams::COLOR_GRAYSCALE;
	else if (cm == "mixed")
		return output::ColorParams::MIXED;

	return output::ColorParams::BLACK_AND_WHITE;
}

//begin of modified by monday2000
//Picture_Shape
output::PictureShape
CommandLine::fetchPictureShape()
{
	if (! hasPictureShape())
		return output::FREE_SHAPE;
	
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}
//end of modified by monday2000

output::PictureShape
CommandLine::fetchPictureShape()
{
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}


output::PictureShape
CommandLine::fetchPictureShape()
{
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}


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
<<<<<<< HEAD
<<<<<<< HEAD
output::PictureShape
CommandLine::fetchPictureShape()
{
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}


<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/filters.cpp
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
output::PictureShape
CommandLine::fetchPictureShape()
{
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}


>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
Margins
CommandLine::fetchMargins()
{
	Margins margins(page_layout::Settings::defaultHardMarginsMM());

	if (m_options.contains("margins")) {
		double m = m_options.value("margins").toDouble();
		margins.setTop(m);
		margins.setBottom(m);
		margins.setLeft(m);
		margins.setRight(m);
	}

	if (m_options.contains("margins-left"))
		margins.setLeft(m_options.value("margins-left").toFloat());
	if (m_options.contains("margins-right"))
		margins.setRight(m_options.value("margins-right").toFloat());
	if (m_options.contains("margins-top"))
		margins.setTop(m_options.value("margins-top").toFloat());
	if (m_options.contains("margins-bottom"))
		margins.setBottom(m_options.value("margins-bottom").toFloat());

	return margins;
}

page_layout::Alignment
CommandLine::fetchAlignment()
{
	page_layout::Alignment alignment(page_layout::Alignment::TOP, page_layout::Alignment::HCENTER);

	if (m_options.contains("match-layout")) {
		if (m_options["match-layout"] == "false") alignment.setNull(true);
		if (m_options["match-layout"] == "true") alignment.setNull(false);
	}

	if (m_options.contains("alignment-tolerance")) {
		alignment.setTolerance(m_options["alignment-tolerance"].toFloat());
	}

	if (m_options.contains("alignment")) {
		if (m_options["alignment"] == "original")
			alignment.setVertical(page_layout::Alignment::VORIGINAL);
		else if (m_options["alignment"] == "auto")
			alignment.setVertical(page_layout::Alignment::VAUTO);
		else
			alignment.setVertical(page_layout::Alignment::VCENTER);
		alignment.setHorizontal(page_layout::Alignment::HCENTER);
	}

	if (m_options.contains("alignment-vertical")) {
		QString a = m_options.value("alignment-vertical").toLower();
		if (a == "top") alignment.setVertical(page_layout::Alignment::TOP);
		if (a == "center") alignment.setVertical(page_layout::Alignment::VCENTER);
		if (a == "bottom") alignment.setVertical(page_layout::Alignment::BOTTOM);
		if (a == "original") alignment.setVertical(page_layout::Alignment::VORIGINAL);
		if (a == "auto") alignment.setVertical(page_layout::Alignment::VAUTO);
	}

	if (m_options.contains("alignment-horizontal")) {
		QString a = m_options.value("alignment-horizontal").toLower();
		if (a == "left") alignment.setHorizontal(page_layout::Alignment::LEFT);
		if (a == "center") alignment.setHorizontal(page_layout::Alignment::HCENTER);
		if (a == "right") alignment.setHorizontal(page_layout::Alignment::RIGHT);
		if (a == "original") alignment.setHorizontal(page_layout::Alignment::HORIGINAL);
		if (a == "auto") alignment.setHorizontal(page_layout::Alignment::HAUTO);
	}

	alignment.setAutoMargins(isAutoMarginsEnabled());

	return alignment;
}

Despeckle::Level
CommandLine::fetchContentDetection()
{
	Despeckle::Level level = Despeckle::NORMAL;

	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
		if (cm == "cautious")
			level = Despeckle::CAUTIOUS;
		else if (cm == "aggressive")
			level = Despeckle::AGGRESSIVE;
	}

	return level;
}


QRectF
CommandLine::fetchContentRect()
{
	if (!hasContentRect())
		return QRectF();

	QRegExp rx("([\\d\\.]+)x([\\d\\.]+):([\\d\\.]+)x([\\d\\.]+)");

	if (rx.exactMatch(m_options.value("content-box"))) {
		return QRectF(rx.cap(1).toFloat(), rx.cap(2).toFloat(), rx.cap(3).toFloat(), rx.cap(4).toFloat());
	}

	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
	exit(1);
}


double
CommandLine::fetchContentDeviation()
{
	if (!hasContentDeviation())
		return 1.0;

	return m_options["content-deviation"].toDouble();
}

CommandLine::Orientation
CommandLine::fetchOrientation()
{
	if (!hasOrientation())
		return TOP;

	Orientation orient;
	QString cli_orient = m_options.value("orientation");

	if (cli_orient == "left") {
		orient = LEFT;
	} else if (cli_orient == "right") {
		orient = RIGHT;
	} else if (cli_orient == "upsidedown") {
		orient = UPSIDEDOWN;
	} else {
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
		exit(1);
	}

	return orient;
}


QString
CommandLine::fetchOutputProjectFile()
{
	if (!hasOutputProject())
		return QString();

	return m_options.value("output-project");
}

int
CommandLine::fetchThreshold()
{
	if (!hasThreshold())
		return 0;

	return m_options.value("threshold").toInt();
}

double
CommandLine::fetchDeskewAngle()
{
	if (!hasDeskewAngle())
		return 0.0;

	return m_options.value("rotate").toDouble();
}

double
CommandLine::fetchSkewDeviation()
{
	if (!hasSkewDeviation())
		return 0.0;

	return m_options["skew-deviation"].toDouble();
}

int
CommandLine::fetchStartFilterIdx()
{
	if (!hasStartFilterIdx())
		return 0;

	return m_options.value("start-filter").toInt() - 1;
}

int
CommandLine::fetchEndFilterIdx()
{
	if (!hasEndFilterIdx())
		return 5;

	return m_options.value("end-filter").toInt() - 1;
}

output::DewarpingMode
CommandLine::fetchDewarpingMode()
{
	if (!hasDewarping())
		return output::DewarpingMode::OFF;

	return output::DewarpingMode(m_options.value("dewarping").toLower());
}

output::DespeckleLevel
CommandLine::fetchDespeckleLevel()
{
	if (!hasDespeckle())
		return output::DESPECKLE_NORMAL;

	return output::despeckleLevelFromString(m_options.value("despeckle"));
}

output::DepthPerception
CommandLine::fetchDepthPerception()
{
	if (!hasDepthPerception())
		return output::DepthPerception();

	return output::DepthPerception(m_options.value("depth-perception"));
}

float
CommandLine::fetchMatchLayoutTolerance()
{
	if (!m_options.contains("match-layout-tolerance"))
		return 0.2;

	return m_options["match-layout-tolerance"].toFloat();
}


bool
CommandLine::hasMargins() const
{
	return(
		m_options.contains("margins") ||
		m_options.contains("margins-left") ||
		m_options.contains("margins-right") ||
		m_options.contains("margins-top") ||
		m_options.contains("margins-bottom")
	);
}

bool
CommandLine::hasAlignment() const
{
	return(
		hasMatchLayoutTolerance() ||
		m_options.contains("alignment") ||
		m_options.contains("alignment-vertical") ||
		m_options.contains("alignment-horizontal") ||
		isAutoMarginsEnabled()
	);
}

bool
CommandLine::hasOutputDpi() const
{
	return(
		m_options.contains("output-dpi") ||
		m_options.contains("output-dpi-x") ||
		m_options.contains("output-dpi-y")
	);
}

int
CommandLine::fetchCompression() const
{
	if (!m_options.contains("tiff-compression"))
	    return COMPRESSION_LZW;
	
	QString c(m_options["tiff-compression"].toLower());
	if (c == "lzw")
	    return COMPRESSION_LZW;
	else if (c == "none")
	    return COMPRESSION_NONE;
	else if (c == "jpeg")
	    return COMPRESSION_JPEG;	
	else if (c == "deflate")
	    return COMPRESSION_DEFLATE;	
	else if (c == "packbits")
	    return COMPRESSION_PACKBITS;
	
	std::cout << "Unknown compression" << std::endl;
	throw("Unknown compression");
}