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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file getRelayState.cpp
    \brief This file returns the state of a relay number.
  */

#include <cstdlib>

#include <iostream>

#include "com/SerialConnection.h"
#include "sensor/PowerControl.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <device> <relay>" << std::endl;
    return -1;
  }
  SerialConnection serialConnection(argv[1]);
  PowerControl powerControl(serialConnection);
  const int relayNum = atoi(argv[2]);
  if (powerControl.getRelayState(relayNum))
    std::cout << "relay: " << relayNum << " state: on" << std::endl;
  else
    std::cout << "relay: " << relayNum << " state: off" << std::endl;
}
