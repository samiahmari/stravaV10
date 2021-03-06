/*
 * VueGPS.cpp
 *
 *  Created on: 27 f�vr. 2018
 *      Author: Vincent
 */

#include <VueGPS.h>
#include "Screenutils.h"
#include "Model.h"

#define VUE_GPS_NB_LINES    7

VueGPS::VueGPS() : Adafruit_GFX(0, 0) {

}

void VueGPS::displayGPS() {

	vue.setCursor(20,20);
	vue.setTextSize(2);

	if (gps_mgmt.isEPOUpdating()) {
		locator.displayGPS2();
	} else {
		vue.println("EPO update in progress");
//		vue.println("EPO update in progress...");
	}

	this->cadranH(6, VUE_GPS_NB_LINES, "Time", _timemkstr(att.date, ':'), NULL);

	this->cadran(7, VUE_GPS_NB_LINES, 1, "STC", _imkstr((int)stc.getCurrent()), "mA");
	this->cadran(7, VUE_GPS_NB_LINES, 2, "SOC", _imkstr(percentageBatt(stc.getVoltage(), stc.getCurrent())), "%");

}
