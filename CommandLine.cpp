/*    Scan Tailor - Interactive post-processing tool for scanned pages.

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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	opts << "force-disable-page-detection";
>>>>>>> origin/enhanced
=======
	opts << "force-disable-page-detection";
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	opts << "force-disable-page-detection";
>>>>>>> enhanced
=======
	opts << "force-disable-page-detection";
>>>>>>> pod/translations
	opts << "content-detection";
	opts << "content-box";
	opts << "content-deviation";
	opts << "enable-auto-margins";
	opts << "margins";
	opts << "margins-left";
	opts << "margins-right";
	opts << "margins-top";
	opts << "margins-bottom";
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	opts << "match-layout";
	opts << "match-layout-tolerance";
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	opts << "default-margins";
	opts << "default-margins-left";
	opts << "default-margins-right";
	opts << "default-margins-top";
	opts << "default-margins-bottom";
	opts << "match-layout";
	opts << "match-layout-tolerance";
	opts << "match-layout-default";
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
	opts << "match-layout";
	opts << "match-layout-tolerance";
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
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
	opts << "picture-shape";
 	opts << "language";
	opts << "disable-content-text-mask";
	opts << "window-title";
	opts << "page-detection-box";
	opts << "page-detection-tolerance";
	opts << "page-borders";
	opts << "page-borders-left";
	opts << "page-borders-top";
	opts << "page-borders-right";
	opts << "page-borders-bottom";
	opts << "disable-check-output";
	opts << "default-output-dpi";
	opts << "default-color-mode";
	opts << "tiff-force-rgb";
	opts << "tiff-force-grayscale";
	opts << "tiff-force-keep-color-space";
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

	QMap<QString, QString> shortMap;
	shortMap["h"] = "help";
	shortMap["help"] = "help";
	shortMap["v"] = "verbose";
	shortMap["l"] = "layout";
	shortMap["ld"] = "layout-direction";
	shortMap["o"] = "output-project";

	// skip first argument (scantailor)
	for (int i=1; i<argv.size(); i++) {
#ifdef DEBUG
	std::cout << "arg[" << i << "]=" << argv[i].toAscii().constData() << std::endl;
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
					std::cout << "Error: Last argument must be an existing directory" << std::endl;
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

#ifdef DEBUG
	QStringList params = m_options.keys();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options.value(params[i]).toAscii().constData() << "\n"; }
	std::cout << "Images: " << CommandLine::m_images.size() << "\n";
=======
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options[params[i]].toAscii().constData() << std::endl; }
	std::cout << "Images: " << CommandLine::m_images.size() << std::endl;
>>>>>>> origin/enhanced
=======
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options[params[i]].toAscii().constData() << std::endl; }
	std::cout << "Images: " << CommandLine::m_images.size() << std::endl;
>>>>>>> origin/enhanced
=======
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options[params[i]].toAscii().constData() << std::endl; }
	std::cout << "Images: " << CommandLine::m_images.size() << std::endl;
=======
=======
<<<<<<< HEAD
<<<<<<< HEAD
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options[params[i]].toAscii().constData() << std::endl; }
	std::cout << "Images: " << CommandLine::m_images.size() << std::endl;
=======
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> pod/translations
=======
>>>>>>> scantailor/master
	for (int i=0; i<params.size(); i++) { std::cout << params[i].toAscii().constData() << "=" << m_options.value(params[i]).toAscii().constData() << "\n"; }
	std::cout << "Images: " << CommandLine::m_images.size() << "\n";
>>>>>>> scantailor/master
<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations
#endif

	return m_error;
}

void
CommandLine::addImage(QString const& path)
{
	QFileInfo file(path);
	m_files.push_back(file);
}

void
CommandLine::setup()
{
    // setup parameters
	m_outputProjectFile = fetchOutputProjectFile();
	m_layoutType = fetchLayoutType();
	m_layoutDirection = fetchLayoutDirection();
	m_colorMode = fetchColorMode();
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
	m_pictureShape = fetchPictureShape();
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
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
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
	m_pictureShape = fetchPictureShape();
>>>>>>> pod/tiff
=======
	m_defaultColorMode = fetchDefaultColorMode();
	m_pictureShape = fetchPictureShape();
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	m_defaultColorMode = fetchDefaultColorMode();
	m_pictureShape = fetchPictureShape();
>>>>>>> origin/enhanced
=======
	m_pictureShape = fetchPictureShape();
>>>>>>> pod/tiff
=======
	m_defaultColorMode = fetchDefaultColorMode();
	m_pictureShape = fetchPictureShape();
>>>>>>> enhanced
=======
	m_defaultColorMode = fetchDefaultColorMode();
	m_pictureShape = fetchPictureShape();
>>>>>>> pod/translations
	m_dpi = fetchDpi();
	m_outputDpi = fetchDpi("output-dpi");
    m_defaultOutputDpi = fetchDpi("default-output-dpi");
	m_margins = fetchMargins();
	m_defaultMargins = fetchMargins("default-margins");
    m_pageBorders = fetchPageBorders();
	m_alignment = fetchAlignment();
	m_contentDetection = fetchContentDetection();
	m_contentRect = fetchContentRect();
	m_contentDeviation = fetchContentDeviation();
	m_orientation = fetchOrientation();
	m_threshold = fetchThreshold();
	m_deskewAngle = fetchDeskewAngle();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	m_deskewMode = fetchDeskewMode();
>>>>>>> origin/enhanced
=======
	m_deskewMode = fetchDeskewMode();
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
	m_deskewMode = fetchDeskewMode();
>>>>>>> enhanced
=======
	m_deskewMode = fetchDeskewMode();
>>>>>>> pod/translations
	m_skewDeviation = fetchSkewDeviation();
	m_startFilterIdx = fetchStartFilterIdx();
	m_endFilterIdx = fetchEndFilterIdx();
	m_matchLayoutTolerance = fetchMatchLayoutTolerance();
	m_dewarpingMode = fetchDewarpingMode();
	m_compression = fetchCompression();
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
	m_language = fetchLanguage();
	m_windowTitle = fetchWindowTitle();
	m_pageDetectionBox = fetchPageDetectionBox();
	m_pageDetectionTolerance = fetchPageDetectionTolerance();
    m_defaultNull = fetchDefaultNull();

	QRegExp exp(".*(tif|tiff|jpg|jpeg|bmp|gif|png|pbm|pgm|ppm|xbm|xpm)$", Qt::CaseInsensitive);
	// setup images
	for (int i=0; i<m_files.size(); ++i) {
		if (! exp.exactMatch(m_files[i].filePath())) {
#ifdef DEBUG
			std::cout << "Skipping file: " << m_files[i].filePath().toStdString() << std::endl;
#endif
			continue;
		}
		// create ImageFileInfo and push to images
		ImageId const image_id(m_files[i].filePath());
		ImageMetadata metadata;
		metadata.setDpi(m_dpi);
		std::vector<ImageMetadata> vMetadata;
		vMetadata.push_back(metadata);
		ImageFileInfo image_info(m_files[i], vMetadata);
		m_images.push_back(image_info);
	}
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
}


void
CommandLine::printHelp()
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
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
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> pod/tiff
>>>>>>> pod/scantailor-filters.h
=======
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << "\n";
>>>>>>> pod/tiff
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
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	std::cout << std::endl;
	std::cout << "Scan Tailor is a post-processing tool for scanned pages." << std::endl;    
	std::cout << "Version: " << VERSION << std::endl;
	std::cout << std::endl;
	std::cout << "ScanTailor usage: " << std::endl;
	std::cout << "\t1) scantailor" << std::endl;
	std::cout << "\t2) scantailor <project_file>" << std::endl;
	std::cout << "\t3) scantailor-cli [options] <images|directory|-> <output_directory>" << std::endl;
	std::cout << "\t4) scantailor-cli [options] <project_file> [output_directory]" << std::endl;
	std::cout << std::endl;
	std::cout << "1)" << std::endl;
	std::cout << "\tstart ScanTailor's GUI interface" << std::endl;
	std::cout << "2)" << std::endl;
	std::cout << "\tstart ScanTailor's GUI interface and load project file" << std::endl;
	std::cout << "3)" << std::endl;
	std::cout << "\tbatch processing images from command line; no GUI" << std::endl;
	std::cout << "\tfile names are collected from arguments, input directory or stdin (-)" << std::endl;
	std::cout << "4)" << std::endl;
	std::cout << "\tbatch processing project from command line; no GUI" << std::endl;
	std::cout << "\tif output_directory is specified as last argument, it overwrites the one in project file" << std::endl;
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t--help, -h" << std::endl;
	std::cout << "\t--verbose, -v" << std::endl;
	std::cout << "\t--languge=<cs|de|...>\t-- default: system language" << std::endl;
	std::cout << "\t--layout=, -l=<0|1|1.5|2>\t\t-- default: 0" << std::endl;
	std::cout << "\t\t\t  0: auto detect" << std::endl;
	std::cout << "\t\t\t  1: one page layout" << std::endl;
	std::cout << "\t\t\t1.5: one page layout but cutting is needed" << std::endl;
	std::cout << "\t\t\t  2: two page layout" << std::endl;
	std::cout << "\t--layout-direction=, -ld=<lr|rl>\t-- default: lr" << std::endl;
	std::cout << "\t--orientation=<left|right|upsidedown|none>\n\t\t\t\t\t\t-- default: none" << std::endl;
	std::cout << "\t--rotate=<0.0...360.0>\t\t\t-- it also sets deskew to manual mode" << std::endl;
	std::cout << "\t--deskew=<auto|manual>\t\t\t-- default: auto" << std::endl;
	std::cout << "\t--skew-deviation=<0.0...)\t\t-- default: 5.0; pages with bigger skew deviation will be painted in red" << std::endl;
	std::cout << "\t--disable-content-detection\t\t-- default: enabled" << std::endl;
	std::cout << "\t--enable-page-detection\t\t\t-- default: disabled" << std::endl;
	std::cout << "\t--enable-fine-tuning\t\t\t-- default: disabled; if page detection enabled it moves edges while corners are in black" << std::endl;
	std::cout << "\t--force-disable-page-detection\t\t-- switch page detection from page project off if enabled and set content detection to manual mode" << std::endl;
	std::cout << "\t--disable-content-text-mask\n\t\t\t\t\t\t-- disable using text mask to estimate a content box" << std::endl;
	std::cout << "\t--content-detection=<cautious|normal|aggressive>\n\t\t\t\t\t\t-- default: normal" << std::endl;
	std::cout << "\t--content-deviation=<0.0...)\t\t-- default: 1.0; pages with bigger content deviation will be painted in red" << std::endl;
	std::cout << "\t--content-box=<<left_offset>x<top_offset>:<width>x<height>>" << std::endl;
	std::cout << "\t\t\t\t\t\t-- if set the content detection is se to manual mode" << std::endl;
	std::cout << "\t\t\t\t\t\t   example: --content-box=100x100:1500x2500" << std::endl;
	std::cout << "\t--enable-auto-margins\t\t\t-- sets the margins to original ones (based on detected page or image size)" << std::endl;
	std::cout << "\t--margins=<number>\t\t\t-- sets left, top, right and bottom margins to same number." << std::endl;
	std::cout << "\t\t--margins-left=<number>" << std::endl;
	std::cout << "\t\t--margins-right=<number>" << std::endl;
	std::cout << "\t\t--margins-top=<number>" << std::endl;
	std::cout << "\t\t--margins-bottom=<number>" << std::endl;
	std::cout << "\t--default-margins=<number>\t\t\t-- sets left, top, right and bottom margins, for new pages, to same number." << std::endl;
	std::cout << "\t\t--default-margins-left=<number>" << std::endl;
	std::cout << "\t\t--default-margins-right=<number>" << std::endl;
	std::cout << "\t\t--default-margins-top=<number>" << std::endl;
	std::cout << "\t\t--default-margins-bottom=<number>" << std::endl;
	std::cout << "\t--match-layout=<true|false>\t\t-- default: true" << std::endl;
	std::cout << "\t--match-layout-tolerance=<0.0...)\t-- default: off" << std::endl;
	std::cout << "\t--match-layout-default=<true|false>\t-- default: true" << std::endl;
	std::cout << "\t--alignment=<center|original|auto>\t-- sets vertical to original and horizontal to center" << std::endl;
	std::cout << "\t\t--alignment-vertical=<top|center|bottom|original>" << std::endl;
	std::cout << "\t\t--alignment-horizontal=<left|center|right|original>" << std::endl;
	std::cout << "\t--alignment-tolerance=<float>\t\t-- sets tolerance for auto alignment" << std::endl;
	std::cout << "\t--dpi=<number>\t\t\t\t-- sets x and y dpi. default: 600" << std::endl;
	std::cout << "\t\t--dpi-x=<number>" << std::endl;
	std::cout << "\t\t--dpi-y=<number>" << std::endl;
	std::cout << "\t--output-dpi=<number>\t\t\t-- sets x and y output dpi. default: 600" << std::endl;
	std::cout << "\t\t--output-dpi-x=<number>" << std::endl;
	std::cout << "\t\t--output-dpi-y=<number>" << std::endl;
	std::cout << "\t--default-output-dpi=<number>\t\t-- default output dpi for pages created by split filter in gui" << std::endl;
	std::cout << "\t--color-mode=<black_and_white|color_grayscale|mixed>\n\t\t\t\t\t\t-- default: black_and_white" << std::endl;
	std::cout << "\t--default-color-mode=<...>\t\t-- sets default value for new images created by split filter" << std::endl;
	std::cout << "\t--picture-shape=<free|rectangular>\n\t\t\t\t\t\t-- default: free" << std::endl;
	std::cout << "\t--white-margins\t\t\t\t-- default: false" << std::endl;
	std::cout << "\t--normalize-illumination\t\t-- default: false" << std::endl;
	std::cout << "\t--threshold=<n>\t\t\t\t-- n<0 thinner, n>0 thicker; default: 0" << std::endl;
	std::cout << "\t--despeckle=<off|cautious|normal|aggressive>\n\t\t\t\t\t\t-- default: normal" << std::endl;
	std::cout << "\t--dewarping=<off|auto>\t\t\t-- default: off" << std::endl;
	std::cout << "\t--depth-perception=<1.0...3.0>\t\t-- default: 2.0" << std::endl;
	std::cout << "\t--start-filter=<1...6>\t\t\t-- default: 4" << std::endl;
	std::cout << "\t--end-filter=<1...6>\t\t\t-- default: 6" << std::endl;
	std::cout << "\t--output-project=, -o=<project_name>" << std::endl;
	std::cout << "\t--tiff-compression=<lzw|deflate|packbits|jpeg|none>\t-- default: lzw" << std::endl;
	std::cout << "\t--tiff-force-rgb\t\t\t-- all output tiffs will be rgb" << std::endl;
	std::cout << "\t--tiff-force-grayscale\t\t\t-- all output tiffs will be grayscale" << std::endl;
	std::cout << "\t--tiff-force-keep-color-space\t\t-- output tiffs will be in original color space" << std::endl;
	std::cout << "\t--window-title=WindowTitle\t\t-- default: project name" << std::endl;
	std::cout << "\t--page-detection-box=<widthxheight>\t\t-- in mm" << std::endl;
	std::cout << "\t\t--page-detection-tolerance=<0.0..1.0>\t-- default: 0.1" << std::endl;
    std::cout << "\t--disable-check-output\t\t\t-- don't check if page is valid when switching to step 6";
	std::cout << std::endl;
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	QString cm = m_options.value("color-mode").toLower();
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/translations
	if (! hasColorMode())
		return output::ColorParams::BLACK_AND_WHITE;
	
	QString cm = m_options["color-mode"].toLower();
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
	
	if (cm == "color_grayscale")
		return output::ColorParams::COLOR_GRAYSCALE;
	else if (cm == "mixed")
		return output::ColorParams::MIXED;

	return output::ColorParams::BLACK_AND_WHITE;
}

<<<<<<< HEAD
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
=======
output::ColorParams::ColorMode
CommandLine::fetchDefaultColorMode()
{
	if (! hasDefaultColorMode())
		return output::ColorParams::BLACK_AND_WHITE;
	
	QString cm = m_options["default-color-mode"].toLower();
=======
=======
	QString cm = m_options.value("color-mode").toLower();
>>>>>>> scantailor/master
=======
	QString cm = m_options.value("color-mode").toLower();
>>>>>>> scantailor/master
=======
	QString cm = m_options.value("color-mode").toLower();
>>>>>>> scantailor/master
>>>>>>> pod/translations
	
	if (cm == "color_grayscale")
		return output::ColorParams::COLOR_GRAYSCALE;
	else if (cm == "mixed")
		return output::ColorParams::MIXED;

	return output::ColorParams::BLACK_AND_WHITE;
}
<<<<<<< HEAD
>>>>>>> origin/enhanced

output::PictureShape
CommandLine::fetchPictureShape()
{
<<<<<<< HEAD
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
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
output::PictureShape
CommandLine::fetchPictureShape()
{
=======
	if (! hasPictureShape())
		return output::FREE_SHAPE;
	
>>>>>>> origin/enhanced
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

	return output::FREE_SHAPE;
}


<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
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
=======
>>>>>>> pod/translations

output::ColorParams::ColorMode
CommandLine::fetchDefaultColorMode()
{
	if (! hasDefaultColorMode())
		return output::ColorParams::BLACK_AND_WHITE;
	
	QString cm = m_options["default-color-mode"].toLower();
=======
<<<<<<< HEAD
=======
=======
>>>>>>> pod/translations
	QString cm = m_options.value("color-mode").toLower();
>>>>>>> scantailor/master
=======
	QString cm = m_options.value("color-mode").toLower();
>>>>>>> scantailor/master
<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations
	
	if (cm == "color_grayscale")
		return output::ColorParams::COLOR_GRAYSCALE;
	else if (cm == "mixed")
		return output::ColorParams::MIXED;

	return output::ColorParams::BLACK_AND_WHITE;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/translations
output::PictureShape
CommandLine::fetchPictureShape()
{
	if (! hasPictureShape())
		return output::FREE_SHAPE;
	
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;
<<<<<<< HEAD
=======

	return output::FREE_SHAPE;
}

>>>>>>> pod/translations

<<<<<<< HEAD
=======
output::PictureShape
CommandLine::fetchPictureShape()
{
=======
output::ColorParams::ColorMode
CommandLine::fetchDefaultColorMode()
{
	if (! hasDefaultColorMode())
		return output::ColorParams::BLACK_AND_WHITE;
	
	QString cm = m_options["default-color-mode"].toLower();
	
	if (cm == "color_grayscale")
		return output::ColorParams::COLOR_GRAYSCALE;
	else if (cm == "mixed")
		return output::ColorParams::MIXED;

	return output::ColorParams::BLACK_AND_WHITE;
}

output::PictureShape
CommandLine::fetchPictureShape()
{
	if (! hasPictureShape())
		return output::FREE_SHAPE;
	
>>>>>>> enhanced
	QString ps = m_options["picture-shape"].toLower();
	
	if (ps == "rectangular")
		return output::RECTANGULAR_SHAPE;

<<<<<<< HEAD
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
	return output::FREE_SHAPE;
}


<<<<<<< HEAD
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
>>>>>>> pod/tiff
>>>>>>> pod/scantailor-filters.h
=======
>>>>>>> pod/tiff
Margins
CommandLine::fetchMargins(QString base, Margins def)
{
	Margins margins(def);

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	if (m_options.contains("margins")) {
		double m = m_options.value("margins").toDouble();
=======
	if (m_options.contains(base)) {
		double m = m_options[base].toDouble();
>>>>>>> origin/enhanced
=======
	if (m_options.contains(base)) {
		double m = m_options[base].toDouble();
>>>>>>> origin/enhanced
=======
=======
>>>>>>> pod/translations
	if (m_options.contains(base)) {
		double m = m_options[base].toDouble();
=======
	if (m_options.contains("margins")) {
		double m = m_options.value("margins").toDouble();
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> enhanced
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> pod/translations
		margins.setTop(m);
		margins.setBottom(m);
		margins.setLeft(m);
		margins.setRight(m);
	}
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> pod/translations
    
    QString lstr = base + "-left",
            tstr = base + "-top",
            rstr = base + "-right",
            bstr = base + "-bottom";
    

	if (m_options.contains(lstr))
		margins.setLeft(m_options[lstr].toFloat());
	if (m_options.contains(rstr))
		margins.setRight(m_options[rstr].toFloat());
	if (m_options.contains(tstr))
		margins.setTop(m_options[tstr].toFloat());
	if (m_options.contains(bstr))
		margins.setBottom(m_options[bstr].toFloat());
=======
<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations

	if (m_options.contains("margins-left"))
		margins.setLeft(m_options.value("margins-left").toFloat());
	if (m_options.contains("margins-right"))
		margins.setRight(m_options.value("margins-right").toFloat());
	if (m_options.contains("margins-top"))
		margins.setTop(m_options.value("margins-top").toFloat());
	if (m_options.contains("margins-bottom"))
		margins.setBottom(m_options.value("margins-bottom").toFloat());
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/enhanced
    
    QString lstr = base + "-left",
            tstr = base + "-top",
            rstr = base + "-right",
            bstr = base + "-bottom";
    

	if (m_options.contains(lstr))
		margins.setLeft(m_options[lstr].toFloat());
	if (m_options.contains(rstr))
		margins.setRight(m_options[rstr].toFloat());
	if (m_options.contains(tstr))
		margins.setTop(m_options[tstr].toFloat());
	if (m_options.contains(bstr))
		margins.setBottom(m_options[bstr].toFloat());
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
<<<<<<< HEAD
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> enhanced
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> pod/translations

	return margins;
}


page_layout::Alignment
CommandLine::fetchAlignment()
{
	page_layout::Alignment alignment(page_layout::Alignment::TOP, page_layout::Alignment::HCENTER);

	if (m_options.contains("match-layout")) {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		if (m_options["match-layout"] == "false") alignment.setNull(true);
		if (m_options["match-layout"] == "true") alignment.setNull(false);
=======
=======
>>>>>>> origin/enhanced
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
        m_defaultNull = false;
		if (m_options["match-layout"] == "false") alignment.setNull(true);
		if (m_options["match-layout"] == "true") {
            alignment.setNull(false);
            m_defaultNull = true;
        }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
>>>>>>> origin/enhanced
=======
		if (m_options["match-layout"] == "false") alignment.setNull(true);
		if (m_options["match-layout"] == "true") alignment.setNull(false);
>>>>>>> pod/tiff
=======
>>>>>>> enhanced
=======
>>>>>>> pod/translations
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

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
=======
=======
>>>>>>> origin/enhanced
	if (hasContentDetection()) {
		QString cm = m_options["content-detection"].toLower();
>>>>>>> origin/enhanced
=======
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/translations
	if (hasContentDetection()) {
		QString cm = m_options["content-detection"].toLower();
=======
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
>>>>>>> scantailor/master
=======
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
>>>>>>> scantailor/master
<<<<<<< HEAD
>>>>>>> enhanced
=======
=======
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
>>>>>>> scantailor/master
=======
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
>>>>>>> scantailor/master
=======
	if (m_options.value("content-detection") != "") {
		QString cm = m_options.value("content-detection").toLower();
>>>>>>> scantailor/master
>>>>>>> pod/translations
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

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
=======
	std::cout << "invalid --content-box=" << m_options["content-box"].toAscii().constData() << std::endl;
>>>>>>> origin/enhanced
=======
	std::cout << "invalid --content-box=" << m_options["content-box"].toAscii().constData() << std::endl;
>>>>>>> origin/enhanced
=======
	std::cout << "invalid --content-box=" << m_options["content-box"].toLocal8Bit().constData() << "\n";
>>>>>>> origin/qt5
=======
	std::cout << "invalid --content-box=" << m_options["content-box"].toAscii().constData() << std::endl;
=======
<<<<<<< HEAD
	std::cout << "invalid --content-box=" << m_options["content-box"].toAscii().constData() << std::endl;
=======
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
>>>>>>> scantailor/master
>>>>>>> pod/translations
=======
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
	std::cout << "invalid --content-box=" << m_options.value("content-box").toAscii().constData() << "\n";
>>>>>>> scantailor/master
<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
=======
		std::cout << "Wrong orientation " << m_options["orientation"].toAscii().constData() << std::endl;
>>>>>>> origin/enhanced
=======
		std::cout << "Wrong orientation " << m_options["orientation"].toAscii().constData() << std::endl;
>>>>>>> origin/enhanced
=======
		std::cout << "Wrong orientation " << m_options["orientation"].toLocal8Bit().constData() << "\n";
>>>>>>> origin/qt5
=======
		std::cout << "Wrong orientation " << m_options["orientation"].toAscii().constData() << std::endl;
=======
<<<<<<< HEAD
		std::cout << "Wrong orientation " << m_options["orientation"].toAscii().constData() << std::endl;
=======
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
>>>>>>> scantailor/master
>>>>>>> pod/translations
=======
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
>>>>>>> scantailor/master
=======
		std::cout << "Wrong orientation " << m_options.value("orientation").toAscii().constData() << "\n";
>>>>>>> scantailor/master
<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
}

AutoManualMode CommandLine::fetchDeskewMode()
{
	if (!hasDeskew())
		return MODE_AUTO;
	return (m_options["deskew"].toLower() == "manual") ? MODE_MANUAL : MODE_AUTO;
}

double
CommandLine::fetchSkewDeviation()
{
	if (!hasSkewDeviation())
		return 5.0;

	return m_options["skew-deviation"].toDouble();
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
=======
>>>>>>> scantailor/master
>>>>>>> pod/translations
}

double
CommandLine::fetchSkewDeviation()
{
	if (!hasSkewDeviation())
		return 0.0;

	return m_options["skew-deviation"].toDouble();
}

<<<<<<< HEAD
AutoManualMode CommandLine::fetchDeskewMode()
{
	if (!hasDeskew())
		return MODE_AUTO;
	return (m_options["deskew"].toLower() == "manual") ? MODE_MANUAL : MODE_AUTO;
}

double
CommandLine::fetchSkewDeviation()
{
	if (!hasSkewDeviation())
		return 5.0;

	return m_options["skew-deviation"].toDouble();
=======
<<<<<<< HEAD
>>>>>>> enhanced
}

AutoManualMode CommandLine::fetchDeskewMode()
{
	if (!hasDeskew())
		return MODE_AUTO;
	return (m_options["deskew"].toLower() == "manual") ? MODE_MANUAL : MODE_AUTO;
}

double
CommandLine::fetchSkewDeviation()
{
	if (!hasSkewDeviation())
		return 5.0;

	return m_options["skew-deviation"].toDouble();
<<<<<<< HEAD
=======
=======
>>>>>>> scantailor/master
>>>>>>> enhanced
}

=======
>>>>>>> pod/tiff
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/translations
}

float
CommandLine::fetchMatchLayoutTolerance()
{
<<<<<<< HEAD
	if (!m_options.contains("match-layout-tolerance"))
		return 0.2;

	return m_options["match-layout-tolerance"].toFloat();
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
float
CommandLine::fetchMatchLayoutTolerance()
{
	if (! hasMatchLayoutTolerance())
		return 0.2;

	return m_options["match-layout-tolerance"].toFloat();
}

<<<<<<< HEAD
>>>>>>> origin/enhanced
=======
float
CommandLine::fetchMatchLayoutTolerance()
{
	if (! hasMatchLayoutTolerance())
		return 0.2;

	return m_options["match-layout-tolerance"].toFloat();
}

>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======
}

float
CommandLine::fetchMatchLayoutTolerance()
{
=======
>>>>>>> pod/translations
	if (! hasMatchLayoutTolerance())
		return 0.2;

	return m_options["match-layout-tolerance"].toFloat();
}

<<<<<<< HEAD
>>>>>>> enhanced
=======
>>>>>>> pod/translations

bool
CommandLine::hasMargins(QString base) const
{
	return(
		m_options.contains(base) ||
		m_options.contains(base+"-left") ||
		m_options.contains(base+"-right") ||
		m_options.contains(base+"-top") ||
		m_options.contains(base+"-bottom")
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
<<<<<<< HEAD
=======
}

bool CommandLine::hasLanguage() const
{
	return m_options.contains("language");
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

QString CommandLine::fetchLanguage() const
{
	if (hasLanguage()) {
		return m_options["language"];
	}
    
    return "untranslated";
}

QString CommandLine::fetchWindowTitle() const
{
    if (hasWindowTitle()) {
        return m_options["window-title"];
    }
    
    return "";
}

QSizeF CommandLine::fetchPageDetectionBox() const
{
    if (! hasPageDetectionBox()) {
        return QSizeF();
    }
    
    QRegExp rx("([\\d\\.]+)x([\\d\\.]+)");
	if (rx.exactMatch(m_options["page-detection-box"])) {
		return QSizeF(rx.cap(1).toFloat(), rx.cap(2).toFloat());
	}
    
    std::cout << "invalid --page-detection-box=" << m_options["page-detection-box"].toAscii().constData() << std::endl;
    exit(1);    
}

double CommandLine::fetchPageDetectionTolerance() const
{
    if (hasPageDetectionTolerance()) {
        return m_options["page-detection-tolerance"].toFloat();
    }
    
    return 0.1;
}

bool CommandLine::fetchDefaultNull() 
{
    m_defaultNull = false;
    
    if (contains("match-layout-default") && m_options["match-layout-default"] == "false") {
        m_defaultNull = true;
    }
    
    return m_defaultNull;
>>>>>>> pod/translations
}

bool CommandLine::hasLanguage() const
{
	return m_options.contains("language");
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
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

QString CommandLine::fetchLanguage() const
{
	if (hasLanguage()) {
		return m_options["language"];
	}
    
    return "untranslated";
}

QString CommandLine::fetchWindowTitle() const
{
    if (hasWindowTitle()) {
        return m_options["window-title"];
    }
    
    return "";
}

QSizeF CommandLine::fetchPageDetectionBox() const
{
    if (! hasPageDetectionBox()) {
        return QSizeF();
    }
    
    QRegExp rx("([\\d\\.]+)x([\\d\\.]+)");
	if (rx.exactMatch(m_options["page-detection-box"])) {
		return QSizeF(rx.cap(1).toFloat(), rx.cap(2).toFloat());
	}
    
    std::cout << "invalid --page-detection-box=" << m_options["page-detection-box"].toAscii().constData() << std::endl;
    exit(1);    
}

double CommandLine::fetchPageDetectionTolerance() const
{
    if (hasPageDetectionTolerance()) {
        return m_options["page-detection-tolerance"].toFloat();
    }
    
    return 0.1;
}

bool CommandLine::fetchDefaultNull() 
{
    m_defaultNull = false;
    
    if (contains("match-layout-default") && m_options["match-layout-default"] == "false") {
        m_defaultNull = true;
    }
    
    return m_defaultNull;
>>>>>>> enhanced
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

QString CommandLine::fetchLanguage() const
{
	if (hasLanguage()) {
		return m_options["language"];
	}
    
    return "untranslated";
}

QString CommandLine::fetchWindowTitle() const
{
    if (hasWindowTitle()) {
        return m_options["window-title"];
    }
    
    return "";
}

QSizeF CommandLine::fetchPageDetectionBox() const
{
    if (! hasPageDetectionBox()) {
        return QSizeF();
    }
    
    QRegExp rx("([\\d\\.]+)x([\\d\\.]+)");
	if (rx.exactMatch(m_options["page-detection-box"])) {
		return QSizeF(rx.cap(1).toFloat(), rx.cap(2).toFloat());
	}
    
    std::cout << "invalid --page-detection-box=" << m_options["page-detection-box"].toAscii().constData() << std::endl;
    exit(1);    
}

double CommandLine::fetchPageDetectionTolerance() const
{
    if (hasPageDetectionTolerance()) {
        return m_options["page-detection-tolerance"].toFloat();
    }
    
    return 0.1;
}

bool CommandLine::fetchDefaultNull() 
{
    m_defaultNull = false;
    
    if (contains("match-layout-default") && m_options["match-layout-default"] == "false") {
        m_defaultNull = true;
    }
    
    return m_defaultNull;
>>>>>>> origin/enhanced
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
<<<<<<< HEAD
    throw("Unknown compression");
}

QString CommandLine::fetchLanguage() const
{
	if (hasLanguage()) {
		return m_options["language"];
	}
    
    return "untranslated";
}

QString CommandLine::fetchWindowTitle() const
{
    if (hasWindowTitle()) {
        return m_options["window-title"];
    }
    
    return "";
}

QSizeF CommandLine::fetchPageDetectionBox() const
{
    if (! hasPageDetectionBox()) {
        return QSizeF();
    }
    
    QRegExp rx("([\\d\\.]+)x([\\d\\.]+)");
	if (rx.exactMatch(m_options["page-detection-box"])) {
		return QSizeF(rx.cap(1).toFloat(), rx.cap(2).toFloat());
	}
    
    std::cout << "invalid --page-detection-box=" << m_options["page-detection-box"].toAscii().constData() << std::endl;
    exit(1);    
}

double CommandLine::fetchPageDetectionTolerance() const
{
    if (hasPageDetectionTolerance()) {
        return m_options["page-detection-tolerance"].toFloat();
    }
    
    return 0.1;
}

bool CommandLine::fetchDefaultNull() 
{
    m_defaultNull = false;
    
    if (contains("match-layout-default") && m_options["match-layout-default"] == "false") {
        m_defaultNull = true;
    }
    
    return m_defaultNull;
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
=======
>>>>>>> pod/tiff
	throw("Unknown compression");
}