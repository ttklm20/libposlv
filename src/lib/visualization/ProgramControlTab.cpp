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

#include "visualization/ProgramControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/ProgramControl.h"
#include "base/Factory.h"

#include "ui_ProgramControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ProgramControlTab::ProgramControlTab() :
    mUi(new Ui_ProgramControlTab()) {
  mUi->setupUi(this);
  QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
  mTimer.setInterval(10000);
}

ProgramControlTab::~ProgramControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ProgramControlTab::connectPressed() {
  emit connect(true);
}

void ProgramControlTab::disconnectPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(90));
  ProgramControl& msg = packet->messageCast().typeCast<ProgramControl>();
  msg.mControl = 1;
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
  emit connect(false);
}

void ProgramControlTab::resetPOSPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(90));
  ProgramControl& msg = packet->messageCast().typeCast<ProgramControl>();
  msg.mControl = 101;
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
}

void ProgramControlTab::resetGAMSPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(90));
  ProgramControl& msg = packet->messageCast().typeCast<ProgramControl>();
  msg.mControl = 100;
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
}

void ProgramControlTab::shutdownPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(90));
  ProgramControl& msg = packet->messageCast().typeCast<ProgramControl>();
  msg.mControl = 102;
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
}

void ProgramControlTab::deviceConnected(bool connected) {
  if (connected) {
    mUi->connectButton->setEnabled(false);
    mUi->disconnectButton->setEnabled(true);
    mUi->resetPOSButton->setEnabled(true);
    mUi->resetGAMSButton->setEnabled(true);
    mUi->shutdownButton->setEnabled(true);
    mTimer.start();
  }
  else {
    mUi->connectButton->setEnabled(true);
    mUi->disconnectButton->setEnabled(false);
    mUi->resetPOSButton->setEnabled(false);
    mUi->resetGAMSButton->setEnabled(false);
    mUi->shutdownButton->setEnabled(false);
    mTimer.stop();
  }
}

void ProgramControlTab::timerTimeout() {
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(90));
  ProgramControl& msg = packet->messageCast().typeCast<ProgramControl>();
  msg.mControl = 0;
  emit writePacket(packet);
}
