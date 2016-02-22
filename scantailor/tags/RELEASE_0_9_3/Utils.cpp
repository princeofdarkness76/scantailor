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

#include "Utils.h"
#include <QString>
#include <QByteArray>
#include <QFile>
#include <Qt>
#include <QTextDocument> // Qt::escape() is actually declare there.

#ifdef Q_WS_WIN
#include <windows.h>
#else
#include <stdio.h>
#endif

bool
Utils::overwritingRename(QString const& from, QString const& to)
{
#ifdef Q_WS_WIN
	return MoveFileExW(
		(WCHAR*)from.utf16(), (WCHAR*)to.utf16(),
		MOVEFILE_REPLACE_EXISTING
	) != 0;
#else
	return rename(
		QFile::encodeName(from).data(),
		QFile::encodeName(to).data()
	) == 0;
#endif
}

QString
Utils::richTextForLink(
	QString const& label, QString const& target)
{
	return QString::fromAscii(
		"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\""
		"\"http://www.w3.org/TR/REC-html40/strict.dtd\">"
		"<html><head><meta name=\"qrichtext\" content=\"1\" />"
		"</head><body><p style=\"margin-top:0px; margin-bottom:0px;"
		"margin-left:0px; margin-right:0px; -qt-block-indent:0;"
		"text-indent:0px;\"><a href=\"%1\">%2</a></p></body></html>"
	).arg(Qt::escape(target), Qt::escape(label));
}
