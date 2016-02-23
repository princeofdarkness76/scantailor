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

#ifndef OUTPUT_PARAMS_H_
#define OUTPUT_PARAMS_H_

#include "Dpi.h"
#include "ColorParams.h"
#include "DewarpingMode.h"
#include "dewarping/DistortionModel.h"
#include "DepthPerception.h"
#include "DespeckleLevel.h"

class QDomDocument;
class QDomElement;

namespace output
{
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
<<<<<<< HEAD
=======
>>>>>>> master
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
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE, 
//Quadro_Zoner		
		QUADRO_SHAPE };
//end of modified by monday2000
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> scantailor/tiff
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
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
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
>>>>>>> master
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> pod/tiff
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> origin/enhanced
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
>>>>>>> pod/scantailor-filters.h
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> origin/enhanced
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> pod/tiff
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> pod/translations
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> pod/tiff

class Params
{
public:
	Params();
	
	Params(QDomElement const& el);
	
	Dpi const& outputDpi() const { return m_dpi; }

	void setOutputDpi(Dpi const& dpi) { m_dpi = dpi; }
	
	ColorParams const& colorParams() const { return m_colorParams; }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
//begin of modified by monday2000
//Picture_Shape
	PictureShape pictureShape() const { return m_pictureShape; }
	void setPictureShape(PictureShape ps) { m_pictureShape = ps; }
//end of modified by monday2000
=======
=======
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
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
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
>>>>>>> master
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
>>>>>>> pod/tiff
=======
>>>>>>> origin/enhanced
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> pod/scantailor-filters.h
>>>>>>> master
=======
>>>>>>> pod/scantailor-filters.h
>>>>>>> master

	PictureShape pictureShape() const { return m_pictureShape; }
	void setPictureShape(PictureShape ps) { m_pictureShape = ps; }

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
=======
<<<<<<< HEAD
=======
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
>>>>>>> scantailor/tiff
=======
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/scantailor-filters.h
>>>>>>> scantailor/tiff
=======
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
>>>>>>> scantailor/tiff
=======
>>>>>>> master
>>>>>>> scantailor/tiff
=======
>>>>>>> pod/tiff
=======
>>>>>>> origin/enhanced
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/scantailor-filters.h
>>>>>>> scantailor/tiff
=======
=======
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
>>>>>>> scantailor/tiff
=======
>>>>>>> scantailor/tiff
=======
>>>>>>> pod/tiff
=======
>>>>>>> origin/enhanced
>>>>>>> master
=======
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> pod/translations
=======
>>>>>>> pod/tiff
	void setColorParams(ColorParams const& params) { m_colorParams = params; }

	DewarpingMode const& dewarpingMode() const { return m_dewarpingMode; }

	void setDewarpingMode(DewarpingMode const& mode) { m_dewarpingMode = mode; }

	dewarping::DistortionModel const& distortionModel() const { return m_distortionModel; }

	void setDistortionModel(dewarping::DistortionModel const& model) { m_distortionModel = model; }

	DepthPerception const& depthPerception() const { return m_depthPerception; }

	void setDepthPerception(DepthPerception depth_perception) {
		m_depthPerception = depth_perception;
	}

	DespeckleLevel despeckleLevel() const { return m_despeckleLevel; }

	void setDespeckleLevel(DespeckleLevel level) { m_despeckleLevel = level; }
	
	QDomElement toXml(QDomDocument& doc, QString const& name) const;
private:
	static ColorParams::ColorMode parseColorMode(QString const& str);
	
	static QString formatColorMode(ColorParams::ColorMode mode);
	
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
<<<<<<< HEAD
=======
>>>>>>> master
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
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> master
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> pod/filters.coo
=======
=======
>>>>>>> pod/homebrew-formulae
=======
>>>>>>> pod/scantailor-filters.h
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp

	Dpi m_dpi;
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> master
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
>>>>>>> master
=======
>>>>>>> master
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
=======
<<<<<<< HEAD
=======
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
>>>>>>> pod/filters.cpp
=======
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
>>>>>>> pod/scantailor-filters.h
=======
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
=======
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
=======
	PictureShape m_pictureShape;
>>>>>>> pod/translations
=======
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
	dewarping::DistortionModel m_distortionModel;
	DepthPerception m_depthPerception;
	DewarpingMode m_dewarpingMode;
	DespeckleLevel m_despeckleLevel;	
//begin of modified by monday2000
//Picture_Shape
	PictureShape m_pictureShape;
//end of modified by monday2000	
};

} // namespace output

#endif
