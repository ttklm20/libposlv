/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "visualization/IMUControl.h"

#include "visualization/ReadThread.h"
#include "types/TimeTaggedIMUData.h"
#include "ui_IMUControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IMUControl::IMUControl() :
  mpUi(new Ui_IMUControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[0] = "OK";
  mStatusMsg[1] = "1 bad raw IMU frame";
  mStatusMsg[2] = "2 bad raw IMU frames";
  mStatusMsg[3] = "3 bad raw IMU frames";
}

IMUControl::~IMUControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void IMUControl::groupRead(const Group* group) {
  if (group->instanceOf<TimeTaggedIMUData>() == true) {
    const TimeTaggedIMUData& msg = group->typeCast<TimeTaggedIMUData>();
    mpUi->typeSpinBox->setValue(msg.mIMUType);
    size_t dataRate;
    switch (msg.mIMUType) {
      case 1:case 2: case 7:
        dataRate = 200;
        break;
      case 17:
        dataRate = 100;
        break;
      default:
        break;
    }
    mpUi->rateSpinBox->setValue(dataRate);
    size_t msgIdx = 0;
    (msg.mDataStatus & 0x01) ? msgIdx = 1 : msgIdx = 0;
    ((msg.mDataStatus >> 1) & 0x01) ? msgIdx = 2 : msgIdx = 0;
    ((msg.mDataStatus >> 1) & 0x01) ? msgIdx = 3 : msgIdx = 0;
    mpUi->statusText->setText(mStatusMsg[msgIdx].c_str());
  }
}