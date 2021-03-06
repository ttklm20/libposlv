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

/** \file COMPortParameters.h
    \brief This file defines the COMPortParameters class, which defines the
           parameters for COM ports
  */

#ifndef COMPORTPARAMETERS_H
#define COMPORTPARAMETERS_H

#include "base/Serializable.h"

class BinaryReader;
class BinaryWriter;

/** The class COMPortParameters represents the COM ports parameters for the
    Applanix.
    \brief COM port parameters
  */
class COMPortParameters :
  public virtual Serializable {
  /// Stream operator for reading from a connection
  friend BinaryReader& operator >> (BinaryReader& stream,
    COMPortParameters& obj);
  /// Stream operator for writing to a connection
  friend BinaryWriter& operator << (BinaryWriter& stream, const
    COMPortParameters& obj);
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  COMPortParameters();
  /// Copy constructor
  COMPortParameters(const COMPortParameters& other);
  /// Assignement operator
  COMPortParameters& operator = (const COMPortParameters& other);
  /// Destructor
  virtual ~COMPortParameters();
  /** @}
    */

  /** \name Members
    @{
    */
  /// RS-232/422 port baud rate
  uint8_t mBaudrate;
  /// Parity
  uint8_t mParity;
  /// Data/Stop Bits
  uint8_t mDataStopBits;
  /// Flow Control
  uint8_t mFlowControl;
  /// Input select
  uint16_t mInputSelect;
  /// Output select
  uint16_t mOutputSelect;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /// Reads from the network
  virtual void read(BinaryReader& stream);
  /// Writes to the network
  virtual void write(BinaryWriter& stream) const;
  /** @}
    */

};

#endif // COMPORTPARAMETERS_H
