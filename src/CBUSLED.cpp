
/*

  Copyright (C) Duncan Greenwood 2017 (duncan_greenwood@hotmail.com)

  This work is licensed under the:
      Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit:
      http://creativecommons.org/licenses/by-nc-sa/4.0/
   or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

   License summary:
    You are free to:
      Share, copy and redistribute the material in any medium or format
      Adapt, remix, transform, and build upon the material

    The licensor cannot revoke these freedoms as long as you follow the license terms.

    Attribution : You must give appropriate credit, provide a link to the license,
                  and indicate if changes were made. You may do so in any reasonable manner,
                  but not in any way that suggests the licensor endorses you or your use.

    NonCommercial : You may not use the material for commercial purposes. **(see note below)

    ShareAlike : If you remix, transform, or build upon the material, you must distribute
                 your contributions under the same license as the original.

    No additional restrictions : You may not apply legal terms or technological measures that
                                 legally restrict others from doing anything the license permits.

   ** For commercial use, please contact the original copyright holder(s) to agree licensing terms

    This software is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE

*/

#include "CBUSLED.h"

//
/// class for individual LED with non-blocking control
//

// constructors

CBUSLED::CBUSLED() {

  _state = LOW;
  _blink = false;
  _pulse = false;
}

CBUSLED::CBUSLED(const byte pin) : _pin(pin) {

  _state = LOW;
  _blink = false;
  _pulse = false;
  pinMode(_pin, OUTPUT);
}

// set the pin for this LED

void CBUSLED::setPin(const byte pin) {

  _pin = pin;
  pinMode(_pin, OUTPUT);
}

// return the current state, on or off

bool CBUSLED::getState() {

  return _state;
}

// turn LED state on

void CBUSLED::on(void) {

  _state = HIGH;
  _blink = false;
  _pulse = false;
  _update();
}

// turn LED state off

void CBUSLED::off(void) {

  _state = LOW;
  _blink = false;
  _pulse = false;
  _update();
}

// toggle LED state from on to off or vv

void CBUSLED::toggle(void) {

  _state = !_state;
  _update();
}

// blink the LED

void CBUSLED::blink(const unsigned int rate) {          // note default paramater value

  _blink = true;
  _pulse = false;
  _blink_rate = rate;
  _state = LOW;
  _timer_start = 0;    // timer will expire immediately and illumiate LED
}

// pulse the LED

void CBUSLED::pulse(const unsigned int duration) {      // note default paramater value

  _pulse = true;
  _blink = false;
  _state = HIGH;
  _pulse_duration = duration;
  _update();
  _timer_start = millis();    // the LED will illuminate now and then toggle once the timer expires
}

// actually operate the LED dependent upon its current state
// must be called frequently from loop() if the LED is set to blink or pulse

void CBUSLED::run(void) {

  // blinking - toggle each time timer expires
  if (_blink) {
    if ((millis() - _timer_start) >= _blink_rate) {
      toggle();
      _timer_start = millis();
    }
  }

  // single pulse - switch off after timer expires
  if (_pulse) {
    if (millis() - _timer_start >= PULSE_ON_TIME) {
      _pulse = false;
      _state = LOW;
      _update();
    }
  }

}

// write to the physical pin

void CBUSLED::_update(void) {

  digitalWrite(_pin, _state);
}

