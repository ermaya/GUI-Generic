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

#ifndef _device_status_led_h
#define _device_status_led_h

#include "../element.h"

namespace Supla {

  enum LedState { NOT_INITIALIZED, ON, OFF };

  enum LedMode {
    LED_ON_WHEN_CONNECTED /* default */,
    LED_OFF_WHEN_CONNECTED,
    LED_ALWAYS_OFF
  };

  enum LedSequence {
    NETWORK_CONNECTING /* initial state 2000/2000 ms */,
    SERVER_CONNECTING /* flashing 500/500 ms */,
    REGISTERED_AND_READY /* stable ON or OFF depending on config */,
    CONFIG_MODE /* quick flashing 100/100 ms */,
    SW_DOWNLOAD /* very fast flashing 20/20 ms */,
    PACZKOW_WE_HAVE_A_PROBLEM /* some problem 500/500 ms */,
    CUSTOM_SEQUENCE /* values set manually, state changes ignored */
  };

  namespace Device {
    class StatusLed : public Element {
      public:
        StatusLed(uint8_t outPin, bool invert = false);

        void onInit() override;
        void iterateAlways() override;
        void onTimer() override;

        // Use inverted logic for GPIO output, when:
        // false -> HIGH=ON,  LOW=OFF
        // true  -> HIGH=OFF, LOW=ON
        void setInvertedLogic(bool invertedLogic);

        // Enables custom LED sequence based on given durations.
        // Automatic sequence change will be disabled.
        void setCustomSequence(int onDurationMs, int offDurationMs);

        // Restores automatic LED sequence change based on device state.
        // It is enabled by default, so if it wasn't disabled by calling
        // setCustomSequence, then there is no need to call it.
        void setAutoSequence();

        // Sets status LED mode
        void setMode(LedMode newMode);

      protected:
        void updatePin();
        void turnOn();
        void turnOff();

        uint8_t outPin;
        bool invert;
        unsigned int onDuration = 0;
        unsigned int offDuration = 1000;
        unsigned long lastUpdate = 0;
        LedState state = NOT_INITIALIZED;
        int lastDeviceStatus = -1;
        LedSequence currentSequence = NETWORK_CONNECTING;
        LedMode ledMode = LED_ON_WHEN_CONNECTED;
    };

  };  // namespace Device
};  // namespace Supla

#endif
