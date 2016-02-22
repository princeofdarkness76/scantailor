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
=======
>>>>>>> master
=======
>>>>>>> master
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
=======
	enum PictureShape { FREE_SHAPE, RECTANGULAR_SHAPE };
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master

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
>>>>>>> master
=======
>>>>>>> master
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
=======
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master

	PictureShape pictureShape() const { return m_pictureShape; }
	void setPictureShape(PictureShape ps) { m_pictureShape = ps; }

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> scantailor/tiff
=======
=======
>>>>>>> master
=======
>>>>>>> master
>>>>>>> scantailor/tiff
=======
>>>>>>> scantailor/tiff
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
=======
>>>>>>> master
=======
>>>>>>> master

	Dpi m_dpi;
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
<<<<<<< HEAD
<<<<<<< HEAD
=======
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
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
