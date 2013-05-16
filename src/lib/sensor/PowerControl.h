/******************************************************************************
 * Copyright (C) 2013 by Jerome Maye                                          *
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

/** \file PowerControl.h
    \brief This file defines the PowerControl class, which is the interface
           for controlling the power board.
  */

#ifndef POWERCONTROL_H
#define POWERCONTROL_H

#include <string>

class SerialConnection;

/** The class PowerControl represents the interface for controlling the
    power board of JanETH.
    \brief Power board control
  */
class PowerControl {
public:
  /** \name Types definitions
    @{
    */
  /// Self type
  typedef PowerControl Self;
  /** @}
    */

  /** \name Constants
    @{
    */
  /// Command string
  static const std::string cmd;
  /// Ack string
  static const std::string ack;
  /// Nack string
  static const std::string nack;
  /// On string
  static const std::string on;
  /// Off string
  static const std::string off;
  /// State string
  static const std::string state;
  /// Max relay number
  static const size_t maxRelayNum = 23;
  /** @}
    */

  /** \name Constructors/Destructor
    @{
    */
  /// Constructs object from serial connection
  PowerControl(SerialConnection& serialConnection);
  /// Copy constructor
  PowerControl(const Self& other) = delete;
  /// Copy assignment operator
  PowerControl& operator = (const Self& other) = delete;
  /// Move constructor
  PowerControl(Self&& other) = delete;
  /// Move assignment operator
  PowerControl& operator = (Self&& other) = delete;
   /// Destructor
  virtual ~PowerControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the serial connection
  SerialConnection& getConnection();
  /// Returns the maximum relay number
  size_t getRelayNumMax() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Switch the state of a relay
  void switchRelay(size_t num, bool state);
  /// Switch the state of all relays
  void switchRelays(bool state);
  /// Check the state of a relay
  bool getRelayState(size_t num);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Checks if a relay number exist
  bool isRelay(size_t num) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Serial connection to the power board
  SerialConnection& mSerialConnection;
  /** @}
    */

};

#endif // POWERCONTROL_H
