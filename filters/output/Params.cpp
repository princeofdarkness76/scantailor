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

#include "Params.h"
#include "ColorGrayscaleOptions.h"
#include "BlackWhiteOptions.h"
#include "XmlMarshaller.h"
#include "XmlUnmarshaller.h"
#include "CommandLine.h"
#include <QDomDocument>
#include <QDomElement>
#include <QByteArray>
#include <QString>

namespace output
{

Params::Params()
<<<<<<< HEAD
<<<<<<< HEAD
:	m_dpi(600, 600),
	m_despeckleLevel(DESPECKLE_CAUTIOUS),
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
//begin of modified by monday2000
//Picture_Shape
	m_pictureShape(FREE_SHAPE)
//end of modified by monday2000
=======
	m_pictureShape(FREE_SHAPE)
>>>>>>> scantailor/tiff
=======
	m_pictureShape(FREE_SHAPE)
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
=======
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
	m_pictureShape(FREE_SHAPE)
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	m_pictureShape(FREE_SHAPE)
>>>>>>> scantailor/tiff
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
	m_pictureShape(FREE_SHAPE)
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
	m_pictureShape(FREE_SHAPE)
>>>>>>> pod/tiff
=======
:	m_dpi(CommandLine::get().getDefaultOutputDpi()),
	m_despeckleLevel(DESPECKLE_CAUTIOUS),
	m_pictureShape(FREE_SHAPE)
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
:	m_dpi(CommandLine::get().getDefaultOutputDpi()),
	m_despeckleLevel(DESPECKLE_CAUTIOUS),
	m_pictureShape(FREE_SHAPE)
>>>>>>> origin/enhanced
=======
	m_pictureShape(FREE_SHAPE)
>>>>>>> pod/tiff
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
{
}

Params::Params(QDomElement const& el)
:	m_dpi(XmlUnmarshaller::dpi(el.namedItem("dpi").toElement())),
	m_distortionModel(el.namedItem("distortion-model").toElement()),
	m_depthPerception(el.attribute("depthPerception")),
	m_dewarpingMode(el.attribute("dewarpingMode")),
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
//begin of modified by monday2000
//Picture_Shape
	//m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel")))
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
//end of modified by monday2000
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> scantailor/tiff
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
=======
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> scantailor/tiff
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
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
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> pod/tiff
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> origin/enhanced
=======
	m_despeckleLevel(despeckleLevelFromString(el.attribute("despeckleLevel"))),
	m_pictureShape((PictureShape)(el.attribute("pictureShape").toInt()))
>>>>>>> pod/tiff
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
{
	QDomElement const cp(el.namedItem("color-params").toElement());
	m_colorParams.setColorMode(parseColorMode(cp.attribute("colorMode")));
	m_colorParams.setColorGrayscaleOptions(
		ColorGrayscaleOptions(
			cp.namedItem("color-or-grayscale").toElement()
		)
	);
	m_colorParams.setBlackWhiteOptions(
		BlackWhiteOptions(cp.namedItem("bw").toElement())
	);
}

QDomElement
Params::toXml(QDomDocument& doc, QString const& name) const
{
	XmlMarshaller marshaller(doc);
	
	QDomElement el(doc.createElement(name));
	el.appendChild(m_distortionModel.toXml(doc, "distortion-model"));
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
//begin of modified by monday2000
//Picture_Shape
	el.setAttribute("pictureShape", (int)m_pictureShape);
//end of modified by monday2000
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> scantailor/tiff
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
=======
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> scantailor/tiff
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
	el.setAttribute("pictureShape", (int)m_pictureShape);
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
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> pod/tiff
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> origin/enhanced
=======
	el.setAttribute("pictureShape", (int)m_pictureShape);
>>>>>>> pod/tiff
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
	el.setAttribute("depthPerception", m_depthPerception.toString());
	el.setAttribute("dewarpingMode", m_dewarpingMode.toString());
	el.setAttribute("despeckleLevel", despeckleLevelToString(m_despeckleLevel));
	el.appendChild(marshaller.dpi(m_dpi, "dpi"));
	
	QDomElement cp(doc.createElement("color-params"));
	cp.setAttribute(
		"colorMode",
		formatColorMode(m_colorParams.colorMode())
	);
	
	cp.appendChild(
		m_colorParams.colorGrayscaleOptions().toXml(
			doc, "color-or-grayscale"
		)
	);
	cp.appendChild(m_colorParams.blackWhiteOptions().toXml(doc, "bw"));
	
	el.appendChild(cp);
	
	return el;
}

ColorParams::ColorMode
Params::parseColorMode(QString const& str)
{
	if (str == "bw") {
		return ColorParams::BLACK_AND_WHITE;
	} else if (str == "bitonal") {
		// Backwards compatibility.
		return ColorParams::BLACK_AND_WHITE;
	} else if (str == "colorOrGray") {
		return ColorParams::COLOR_GRAYSCALE;
	} else if (str == "mixed") {
		return ColorParams::MIXED;
	} else {
		return ColorParams::DefaultColorMode();
	}
}

QString
Params::formatColorMode(ColorParams::ColorMode const mode)
{
	char const* str = "";
	switch (mode) {
		case ColorParams::BLACK_AND_WHITE:
			str = "bw";
			break;
		case ColorParams::COLOR_GRAYSCALE:
			str = "colorOrGray";
			break;
		case ColorParams::MIXED:
			str = "mixed";
			break;
	}
	return QString::fromLatin1(str);
}

} // namespace output
