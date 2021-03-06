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

/** \file TCPCom.h
    \brief This file defines the TCPCom class which handles TCP communication
           with the Applanix.
  */

#ifndef TCPCOM_H
#define TCPCOM_H

#include <memory>

#include <QtCore/QObject>

class POSLVComTCP;
class Packet;

/** The TCPCom class handles TCP communication with the Applanix.
    \brief TCP Communication with Applanix.
  */
class TCPCom :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  TCPCom(const TCPCom& other);
  /// Assignment operator
  TCPCom& operator = (const TCPCom& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  TCPCom(POSLVComTCP& device, double pollingTime = 1);
  /// Destructor
  virtual ~TCPCom();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the polling time
  double getPollingTime() const;
  /// Sets the polling time
  void setPollingTime(double pollingTime);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Device
  POSLVComTCP& mDevice;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Connect to the Applanix
  void connect(bool connect);
  /// Send a packet to the Applanix
  void writePacket(std::shared_ptr<Packet> packet);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Packet read
  void readPacket(std::shared_ptr<Packet> packet);
  /// Device connected
  void deviceConnected(bool connected);
  /// Com connection
  void comException(const std::string& msg);
  /** @}
    */

};

#endif // TCPCOM_H
