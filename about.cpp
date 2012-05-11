/*
 * This file is part of the sigrok project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

extern "C" {
#include <sigrokdecode.h>
}

#include <QTextDocument>

#include "about.h"
#include "ui_about.h"

extern "C" {
/* __STDC_FORMAT_MACROS is required for PRIu64 and friends (in C++). */
#define __STDC_FORMAT_MACROS
#include <glib.h>
#include <libsigrok/libsigrok.h>
}

About::About(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::About)
{
	GSList *l;
	struct sr_dev_driver **drivers;
	struct sr_input_format **inputs;
	struct sr_output_format **outputs;
	struct srd_decoder *dec;
	QString s;

	ui->setupUi(this);

	/* Setup the version field */
	ui->versionInfo->setText(tr("%1 %2<br />%3<br /><a href=\"%4\">%4</a>")
				 .arg(QApplication::applicationName())
				 .arg(QApplication::applicationVersion())
				 .arg(tr("GNU GPL, version 2 or later"))
				 .arg(QApplication::organizationDomain()));

	/* Set up the supported field */
	s.append("<b>" + tr("Supported hardware drivers:") + "</b><table>");
	drivers = sr_driver_list();
	for (int i = 0; drivers[i]; ++i) {
		s.append(QString("<tr><td><i>%1</i></td><td>%2</td></tr>")
			 .arg(QString(drivers[i]->name))
			 .arg(QString(drivers[i]->longname)));
	}
	s.append("</table><p>");

	s.append("<b>" + tr("Supported input formats:") + "</b><table>");
	inputs = sr_input_list();
	for (int i = 0; inputs[i]; ++i) {
		s.append(QString("<tr><td><i>%1</i></td><td>%2</td></tr>")
			 .arg(QString(inputs[i]->id))
			 .arg(QString(inputs[i]->description)));
	}
	s.append("</table><p>");

	s.append("<b>" + tr("Supported output formats:") + "</b><table>");
	outputs = sr_output_list();
	for (int i = 0; outputs[i]; ++i) {
		s.append(QString("<tr><td><i>%1</i></td><td>%2</td></tr>")
			.arg(QString(outputs[i]->id))
			.arg(QString(outputs[i]->description)));
	}
	s.append("</table><p>");

	s.append("<b>" + tr("Supported protocol decoders:") + "</b><table>");
	for (l = srd_decoder_list(); l; l = l->next) {
		dec = (struct srd_decoder *)l->data;
		s.append(QString("<tr><td><i>%1</i></td><td>%2</td></tr>")
			 .arg(QString(dec->id))
			 .arg(QString(dec->longname)));
	}
	s.append("</table>");

	supportedDoc.reset(new QTextDocument(this));
	supportedDoc->setHtml(s);
	ui->supportList->setDocument(supportedDoc.get());
}

About::~About()
{
	delete ui;
}