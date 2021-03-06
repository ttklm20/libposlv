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

#include "visualization/GeneralInstallProcessParamsTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/GeneralInstallProcessParams.h"
#include "base/Factory.h"

#include "ui_GeneralInstallProcessParamsTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeneralInstallProcessParamsTab::GeneralInstallProcessParamsTab() :
    mUi(new Ui_GeneralInstallProcessParamsTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

GeneralInstallProcessParamsTab::~GeneralInstallProcessParamsTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GeneralInstallProcessParamsTab::enableFields(bool enable) {
  mUi->refIMUXSpinBox->setEnabled(enable);
  mUi->refIMUYSpinBox->setEnabled(enable);
  mUi->refIMUZSpinBox->setEnabled(enable);
  mUi->refPrimGPSXSpinBox->setEnabled(enable);
  mUi->refPrimGPSYSpinBox->setEnabled(enable);
  mUi->refPrimGPSZSpinBox->setEnabled(enable);
  mUi->xIMURefMountingAngleSpinBox->setEnabled(enable);
  mUi->yIMURefMountingAngleSpinBox->setEnabled(enable);
  mUi->zIMURefMountingAngleSpinBox->setEnabled(enable);
  mUi->xRefVehicMountingAngleSpinBox->setEnabled(enable);
  mUi->yRefVehicMountingAngleSpinBox->setEnabled(enable);
  mUi->zRefVehicMountingAngleSpinBox->setEnabled(enable);
  mUi->pos1TimeRadioButton->setEnabled(enable);
  mUi->gps1TimeRadioButton->setEnabled(enable);
  mUi->utc1TimeRadioButton->setEnabled(enable);
  mUi->pos2TimeRadioButton->setEnabled(enable);
  mUi->gps2TimeRadioButton->setEnabled(enable);
  mUi->utc2TimeRadioButton->setEnabled(enable);
  mUi->userTimeRadioButton->setEnabled(enable);
  mUi->posDistanceRadioButton->setEnabled(enable);
  mUi->dmiDistanceRadioButton->setEnabled(enable);
  mUi->disabledRadioButton->setEnabled(enable);
  mUi->enabledRadioButton->setEnabled(enable);
  mUi->lowRadioButton->setEnabled(enable);
  mUi->mediumRadioButton->setEnabled(enable);
  mUi->highRadioButton->setEnabled(enable);
}

void GeneralInstallProcessParamsTab::setReadOnlyFields(bool readonly) {
  mUi->refIMUXSpinBox->setReadOnly(readonly);
  mUi->refIMUYSpinBox->setReadOnly(readonly);
  mUi->refIMUZSpinBox->setReadOnly(readonly);
  mUi->refPrimGPSXSpinBox->setReadOnly(readonly);
  mUi->refPrimGPSYSpinBox->setReadOnly(readonly);
  mUi->refPrimGPSZSpinBox->setReadOnly(readonly);
  mUi->xIMURefMountingAngleSpinBox->setReadOnly(readonly);
  mUi->yIMURefMountingAngleSpinBox->setReadOnly(readonly);
  mUi->zIMURefMountingAngleSpinBox->setReadOnly(readonly);
  mUi->xRefVehicMountingAngleSpinBox->setReadOnly(readonly);
  mUi->yRefVehicMountingAngleSpinBox->setReadOnly(readonly);
  mUi->zRefVehicMountingAngleSpinBox->setReadOnly(readonly);
}

void GeneralInstallProcessParamsTab::applyPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(20));
  GeneralInstallProcessParams& msg =
    packet->messageCast().typeCast<GeneralInstallProcessParams>();
  msg.mRefIMUX = mUi->refIMUXSpinBox->value();
  msg.mRefIMUY = mUi->refIMUYSpinBox->value();
  msg.mRefIMUZ = mUi->refIMUZSpinBox->value();
  msg.mRefPrimGPSX = mUi->refPrimGPSXSpinBox->value();
  msg.mRefPrimGPSY = mUi->refPrimGPSYSpinBox->value();
  msg.mRefPrimGPSZ = mUi->refPrimGPSZSpinBox->value();
  msg.mXIMURefMountingAngle = mUi->xIMURefMountingAngleSpinBox->value();
  msg.mYIMURefMountingAngle = mUi->yIMURefMountingAngleSpinBox->value();
  msg.mZIMURefMountingAngle = mUi->zIMURefMountingAngleSpinBox->value();
  msg.mXRefVehicleMountingAngle = mUi->xRefVehicMountingAngleSpinBox->value();
  msg.mYRefVehicleMountingAngle = mUi->yRefVehicMountingAngleSpinBox->value();
  msg.mZRefVehicleMountingAngle = mUi->zRefVehicMountingAngleSpinBox->value();
  if (mUi->lowRadioButton->isChecked())
    msg.mMultipathEnvironment = 0;
  else if (mUi->mediumRadioButton->isChecked())
    msg.mMultipathEnvironment = 1;
  else if (mUi->highRadioButton->isChecked())
    msg.mMultipathEnvironment = 2;
  if (mUi->posDistanceRadioButton->isChecked())
    msg.mDistanceType = 1;
  else if (mUi->dmiDistanceRadioButton->isChecked())
    msg.mDistanceType = 2;
  if (mUi->disabledRadioButton->isChecked())
    msg.mAutoStart = 0;
  else if (mUi->enabledRadioButton->isChecked())
    msg.mAutoStart = 1;
  msg.mTimeTypes = 0;
  if (mUi->pos1TimeRadioButton->isChecked())
    msg.mTimeTypes |= 0 & 0x0f;
  else if (mUi->gps1TimeRadioButton->isChecked())
    msg.mTimeTypes |= 1 & 0x0f;
  else if (mUi->utc1TimeRadioButton->isChecked())
    msg.mTimeTypes |= 2 & 0x0f;
  if (mUi->pos2TimeRadioButton->isChecked())
    msg.mTimeTypes |= (0 << 4) & 0xf0;
  else if (mUi->gps2TimeRadioButton->isChecked())
    msg.mTimeTypes |= (1 << 4) & 0xf0;
  else if (mUi->utc2TimeRadioButton->isChecked())
    msg.mTimeTypes |= (2 << 4) & 0xf0;
  else if (mUi->userTimeRadioButton->isChecked())
    msg.mTimeTypes |= (3 << 4) & 0xf0;
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
}

void GeneralInstallProcessParamsTab::readPacket(std::shared_ptr<Packet>
    packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<GeneralInstallProcessParams>()) {
      enableFields(true);
      const GeneralInstallProcessParams& msg =
        message.typeCast<GeneralInstallProcessParams>();
      switch (msg.mTimeTypes & 0x0F) {
        case 0:
          mUi->pos1TimeRadioButton->setChecked(true);
          break;
        case 1:
          mUi->gps1TimeRadioButton->setChecked(true);
          break;
        case 2:
          mUi->utc1TimeRadioButton->setChecked(true);
          break;
        default:
          break;
      }
      switch ((msg.mTimeTypes >> 4) & 0x0F) {
        case 0:
          mUi->pos2TimeRadioButton->setChecked(true);
          break;
        case 1:
          mUi->gps2TimeRadioButton->setChecked(true);
          break;
        case 2:
          mUi->utc2TimeRadioButton->setChecked(true);
          break;
        case 3:
          mUi->userTimeRadioButton->setChecked(true);
        default:
          break;
      }
      switch (msg.mDistanceType) {
        case 1:
          mUi->posDistanceRadioButton->setChecked(true);
          break;
        case 2:
          mUi->dmiDistanceRadioButton->setChecked(true);
          break;
        default:
          break;
      }
      switch (msg.mAutoStart) {
        case 0:
          mUi->disabledRadioButton->setChecked(true);
          break;
        case 1:
          mUi->enabledRadioButton->setChecked(true);
          break;
        default:
          break;
      }
      mUi->refIMUXSpinBox->setValue(msg.mRefIMUX);
      mUi->refIMUYSpinBox->setValue(msg.mRefIMUY);
      mUi->refIMUZSpinBox->setValue(msg.mRefIMUZ);
      mUi->refPrimGPSXSpinBox->setValue(msg.mRefPrimGPSX);
      mUi->refPrimGPSYSpinBox->setValue(msg.mRefPrimGPSY);
      mUi->refPrimGPSZSpinBox->setValue(msg.mRefPrimGPSZ);
      mUi->xIMURefMountingAngleSpinBox->setValue(msg.mXIMURefMountingAngle);
      mUi->yIMURefMountingAngleSpinBox->setValue(msg.mYIMURefMountingAngle);
      mUi->zIMURefMountingAngleSpinBox->setValue(msg.mZIMURefMountingAngle);
      mUi->xRefVehicMountingAngleSpinBox->setValue(
        msg.mXRefVehicleMountingAngle);
      mUi->yRefVehicMountingAngleSpinBox->setValue(
        msg.mYRefVehicleMountingAngle);
      mUi->zRefVehicMountingAngleSpinBox->setValue(
        msg.mZRefVehicleMountingAngle);
      switch (msg.mMultipathEnvironment) {
        case 0:
          mUi->lowRadioButton->setChecked(true);
          break;
        case 1:
          mUi->mediumRadioButton->setChecked(true);
          break;
        case 2:
          mUi->highRadioButton->setChecked(true);
          break;
        default:
          break;
      }
    }
  }
}

void GeneralInstallProcessParamsTab::deviceConnected(bool connected) {
  if (connected) {
    setReadOnlyFields(false);
    mControlMode = true;
    mUi->applyButton->setEnabled(true);
  }
  else {
    setReadOnlyFields(true);
    mControlMode = false;
    mUi->applyButton->setEnabled(false);
  }
}
