/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

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

#include "virtual_binary.h"
#include <supla/time.h>

namespace Supla {
namespace Sensor {

VirtualBinary::VirtualBinary() : state(false), lastReadTime(0) {
  channel.setType(SUPLA_CHANNELTYPE_SENSORNO);
}

bool VirtualBinary::getValue() {
  return state;
}

void VirtualBinary::iterateAlways() {
  if (millis() - lastReadTime > 100) {
    lastReadTime = millis();
    channel.setNewValue(getValue());
  }
}

void VirtualBinary::onInit() {
  channel.setNewValue(getValue());
}

void VirtualBinary::handleAction(int event, int action) {
  (void)(event);
  switch (action) {
    case SET: {
      state = true;
      break;
    }
    case CLEAR: {
      state = false;
      break;
    }
    case TOGGLE: {
      state = !state;
      break;
    }
  }
}

};  // namespace Sensor
};  // namespace Supla
