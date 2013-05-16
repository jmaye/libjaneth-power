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

#include "sensor/PowerControl.h"

#include <sstream>

#include "com/SerialConnection.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

/******************************************************************************/
/* Static members initialization                                              */
/******************************************************************************/

const std::string PowerControl::cmd = "#";
const std::string PowerControl::ack = "ACK";
const std::string PowerControl::nack = "NACK";
const std::string PowerControl::on = "I";
const std::string PowerControl::off = "O";
const std::string PowerControl::state = "S";

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PowerControl::PowerControl(SerialConnection& serialConnection) :
    mSerialConnection(serialConnection) {
}

PowerControl::~PowerControl() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

SerialConnection& PowerControl::getConnection() {
  return mSerialConnection;
}

size_t PowerControl::getRelayNumMax() const {
  return maxRelayNum;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PowerControl::switchRelay(size_t num, bool state) {
  if (!isRelay(num))
    throw OutOfBoundException<size_t>(num,
      "PowerControl::switchRelay(): inexistent relay",
      __FILE__, __LINE__);
  std::stringstream commandString;
  commandString << cmd;
  if (num < 10)
    commandString << '0' << num;
  else
    commandString << num;
  if (state)
    commandString << on;
  else
    commandString << off;
  mSerialConnection.write(reinterpret_cast<const char*>(
    commandString.str().c_str()),
    commandString.str().size());
  char buffer[80];
  mSerialConnection.read(buffer, 4);
  if (buffer[1] == 'N') {
    mSerialConnection.read(&buffer[4], 1);
    buffer[5] = 0;
  }
  else
    buffer[4] = 0;
  const std::string response(buffer);
  if (response == nack)
    throw InvalidOperationException("PowerControl::switchRelay(): "
      "protocol violation");
}

void PowerControl::switchRelays(bool state) {
  std::stringstream commandString;
  commandString << cmd << maxRelayNum + 1;
  if (state)
    commandString << on;
  else
    commandString << off;
  mSerialConnection.write(reinterpret_cast<const char*>(
    commandString.str().c_str()),
    commandString.str().size());
  char buffer[80];
  mSerialConnection.read(buffer, 4);
  if (buffer[1] == 'N') {
    mSerialConnection.read(&buffer[4], 1);
    buffer[5] = 0;
  }
  else
    buffer[4] = 0;
  const std::string response(buffer);
  if (response == nack)
    throw InvalidOperationException("PowerControl::switchRelays(): "
      "protocol violation");
}

bool PowerControl::getRelayState(size_t num) {
  if (!isRelay(num))
    throw OutOfBoundException<size_t>(num,
      "PowerControl::getRelayState(): inexistent relay",
      __FILE__, __LINE__);
  std::stringstream commandString;
  commandString << cmd;
  if (num < 10)
    commandString << '0' << num;
  else
    commandString << num;
  commandString << state;
  mSerialConnection.write(reinterpret_cast<const char*>(
    commandString.str().c_str()),
    commandString.str().size());
  char buffer[80];
  mSerialConnection.read(buffer, 4);
  if (buffer[1] == 'N') {
    mSerialConnection.read(&buffer[4], 1);
    buffer[5] = 0;
  }
  else
    buffer[4] = 0;
  const std::string response(buffer);
  if (response == nack)
    throw InvalidOperationException("PowerControl::switchRelays(): "
      "protocol violation");
  if (buffer[3] == 'O')
    return false;
  else
    return true;
}

bool PowerControl::isRelay(size_t num) const {
  return num <= maxRelayNum;
}
