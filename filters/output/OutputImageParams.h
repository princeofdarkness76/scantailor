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

#ifndef OUTPUT_OUTPUT_IMAGE_PARAMS_H_
#define OUTPUT_OUTPUT_IMAGE_PARAMS_H_

#include "Dpi.h"
#include "ColorParams.h"
#include "Params.h"
#include "DewarpingMode.h"
#include "dewarping/DistortionModel.h"
#include "DepthPerception.h"
#include "DespeckleLevel.h"
#include <QSize>
#include <QRect>
//begin of modified by monday2000
//Picture_Shape
#include "Params.h"
//end of modified by monday2000

class ImageTransformation;
class QDomDocument;
class QDomElement;
class QTransform;

namespace output
{

/**
 * \brief Parameters of the output image used to determine if we need to re-generate it.
 */
class OutputImageParams
{
public:
	OutputImageParams(QSize const& out_image_size,
		QRect const& content_rect, ImageTransformation xform,
		Dpi const& dpi, ColorParams const& color_params,
		DewarpingMode const& dewarping_mode,
		dewarping::DistortionModel const& distortion_model,
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
		//DepthPerception const& depth_perception, DespeckleLevel despeckle_level);
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level,
		PictureShape picture_shape);
//end of modified by monday2000
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> scantailor/tiff
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
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
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> scantailor/tiff
=======
>>>>>>> master
=======
>>>>>>> master
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
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
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> pod/tiff
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> origin/enhanced
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> pod/tiff
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> enhanced
=======
		DepthPerception const& depth_perception, DespeckleLevel despeckle_level, PictureShape picture_shape);
>>>>>>> pod/translations
	
//begin of modified by monday2000
//Picture_Shape_Bug	
	//explicit OutputImageParams(QDomElement const& el);
	explicit OutputImageParams(QDomElement const& el, int picture_shape_int=0);
//end of modified by monday2000

	DewarpingMode const& dewarpingMode() const { return m_dewarpingMode; }

	dewarping::DistortionModel const& distortionModel() const { return m_distortionModel; }

	void setDistortionModel(dewarping::DistortionModel const& model) { m_distortionModel = model; }

	DepthPerception const& depthPerception() const { return m_depthPerception; }

	DespeckleLevel despeckleLevel() const { return m_despeckleLevel; }
	
	QDomElement toXml(QDomDocument& doc, QString const& name) const;
	
	/**
	 * \brief Returns true if two sets of parameters are close enough
	 *        to avoid re-generating the output image.
	 */
	bool matches(OutputImageParams const& other) const;
private:
	class PartialXform
	{
	public:
		PartialXform();

		PartialXform(QTransform const& xform);
		
		PartialXform(QDomElement const& el);
		
		QDomElement toXml(QDomDocument& doc, QString const& name) const;
		
		bool matches(PartialXform const& other) const;
	private:
		static bool closeEnough(double v1, double v2);
		
		double m_11;
		double m_12;
		double m_21;
		double m_22;
	};
	
	static bool colorParamsMatch(
		ColorParams const& cp1, DespeckleLevel dl1,
		ColorParams const& cp2, DespeckleLevel dl2);
	
	/** Pixel size of the output image. */
	QSize m_size;
	
	/** Content rectangle in output image coordinates. */
	QRect m_contentRect;
	
	/**
	 * Some parameters from the transformation matrix that maps
	 * source image coordinates to unscaled (disregarding dpi changes)
	 * output image coordinates.
	 */
	PartialXform m_partialXform;
	
	/** DPI of the output image. */
	Dpi m_dpi;
	
	/** Non-geometric parameters used to generate the output image. */
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
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
//end of modified by monday2000
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> scantailor/tiff
=======
	/** Shape of the pictures in image */
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
	/** Shape of the pictures in image */
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
	/** Shape of the pictures in image */
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
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
>>>>>>> pod/scantailor-filters.h
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> origin/enhanced
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> pod/tiff
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> enhanced
=======
	/** Shape of the pictures in image */
	PictureShape m_pictureShape;
>>>>>>> pod/translations

	/** Two curves and two lines connecting their endpoints.  Used for dewarping. */
	dewarping::DistortionModel m_distortionModel;

	/** \see imageproc::CylindricalSurfaceDewarper */
	DepthPerception m_depthPerception;

	/** Off / Auto / Manual */
	DewarpingMode m_dewarpingMode;

	/** Despeckle level of the output image. */
	DespeckleLevel m_despeckleLevel;
};

} // namespace output

#endif
