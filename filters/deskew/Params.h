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

#ifndef DESKEW_PARAMS_H_
#define DESKEW_PARAMS_H_

#include "Dependencies.h"
#include "AutoManualMode.h"
#include <QString>
#include <cmath>
#include <algorithm>
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

#include "CommandLine.h"
class CommandLine;
>>>>>>> origin/enhanced
=======

#include "CommandLine.h"
class CommandLine;
>>>>>>> origin/enhanced
=======
>>>>>>> pod/tiff
=======

#include "CommandLine.h"
class CommandLine;
>>>>>>> enhanced
=======

#include "CommandLine.h"
class CommandLine;
>>>>>>> pod/translations

class QDomDocument;
class QDomElement;

namespace deskew
{

class Params
{
public:
	// Member-wise copying is OK.
	
	Params(double deskew_angle_deg,
		Dependencies const& deps, AutoManualMode mode);
	
	Params(QDomElement const& deskew_el); 
	
	~Params();
	
	double deskewAngle() const { return m_deskewAngleDeg; }

	double deviation() const { return m_deviation; }
	void computeDeviation(double avg) { m_deviation = avg - m_deskewAngleDeg; }
	// check if skew is too large
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	bool isDeviant(double std, double max_dev=1.0) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
=======
	bool isDeviant(double std, double max_dev=CommandLine::get().getSkewDeviation()) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
>>>>>>> origin/enhanced
=======
	bool isDeviant(double std, double max_dev=CommandLine::get().getSkewDeviation()) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
>>>>>>> origin/enhanced
=======
	bool isDeviant(double std, double max_dev=1.0) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
>>>>>>> pod/tiff
=======
	bool isDeviant(double std, double max_dev=CommandLine::get().getSkewDeviation()) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
>>>>>>> enhanced
=======
	bool isDeviant(double std, double max_dev=CommandLine::get().getSkewDeviation()) const { return std::max(1.5*std, max_dev) < fabs(m_deviation); }
>>>>>>> pod/translations
	
	Dependencies const& dependencies() const { return m_deps; }
	
	AutoManualMode mode() const { return m_mode; }
	
	QDomElement toXml(QDomDocument& doc, QString const& name) const;
private:
	double m_deskewAngleDeg;
	Dependencies m_deps;
	AutoManualMode m_mode;
	double m_deviation;
};

} // namespace deskew

#endif
