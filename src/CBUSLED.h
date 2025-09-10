
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

//
//
//

#pragma once

#define BLINK_RATE 500         // default - flash at 1Hz, 500mS on, 500mS off
#define PULSE_ON_TIME 10       // default pulseon time

#include <Arduino.h>           // for definition of byte datatype

//
/// class to encapsulate a non-blocking LED
//

/// virtual methods specified so that a super class could use different IO technology, e.g. an I2C expander

class CBUSLED {

public:
  CBUSLED();
  CBUSLED(const byte pin);

  virtual void setPin(const byte pin);
  bool getState(void);
  void on(void);
  void off(void);
  void toggle(void);
  void blink(const unsigned int rate = BLINK_RATE);                 // note default paramater value
  void pulse(const unsigned int duration = PULSE_ON_TIME);          // note default paramater value
  virtual void run(void);

protected:
  byte _pin;
  bool _state;
  bool _blink;
  bool _pulse;
  unsigned int _blink_rate, _pulse_duration;
  unsigned long _timer_start;
  virtual void _update(void);
};

