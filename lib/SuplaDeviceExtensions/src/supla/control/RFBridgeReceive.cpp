/*
  Copyright (C) krycha88

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "RFBridgeReceive.h"

namespace Supla {
namespace Control {
RFBridgeReceive::RFBridgeReceive(int receivePin) : RFBridge() {
  mySwitch->enableReceive(receivePin);
}

void RFBridgeReceive::onTimer() {
  if (mySwitch->available()) {
    int code = mySwitch->getReceivedValue();
    if (code == codeON) {
      Serial.print("Received code ON ");
      Serial.println(code);

      runAction(Supla::TURN_ON);
      mySwitch->resetAvailable();
    }

    if (code == codeOFF) {
      Serial.print("Received code OFF ");
      Serial.println(code);

      runAction(Supla::TURN_OFF);
      mySwitch->resetAvailable();
    }
  }
}

}  // namespace Control
}  // namespace Supla