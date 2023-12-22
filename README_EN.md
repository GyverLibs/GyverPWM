This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverpwm
Library for expanded generation of PWM on Atmega328 (Arduino Uno/Nano/Pro mini ...)
- hardware generation of PWM of customized frequency and discharge

## compatibility
Arduino UNO/Nano/Pro mini

### Documentation
There is [extended documentation] to the library (https://alexgyver.ru/gyverpwm/)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverpwm ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverpwm/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
No

<a id="usage"> </a>
## Usage
`` `CPP
// =====ward
// these functions remove one PWM output from 8 bit timers, leaving us shim pins D3, D5, D9 and D10 on Atmega328
VOID PWM_FREQUENCY (Byte PIN, LONG FreQ, Modes Correct);
/* Pwm_freqency (pin, frequency, mode) - start the shim with the selected frequency
 - Pins: D3 (timer 2), d5 (timer 0 - will break millis/delay), D9 and D10 (timer 1)
 - mode: 0 (fast_pwm), 1 (Correct_PWM)
 - Frequency: 250-200'000 Hz for all timers
 - To change the filling, use pwm_se
  - The bit in this mode is given to 8 bits, in fact, the steps of the change are different!
*/
VOID PWM_RESOLUTION (Byte PIN, Byte Res, Modes Correct);
/* Pwm_resolution (pin, discharge, mode) - start the PWM with the selected bit
 - Pins: D3 (timer 2), d5 (timer 0 - will break millis/delay), D9 and D10 (timer 1)
 - mode: 0 (fast_pwm), 1 (Correct_PWM)
 -Resolution: D3 (4-8 bits), D5 (4-8 bits), D9 and D10 (4-16 bits)
 - the frequency in this mode is automatically maximum according to the capabilities of the timer (see table)
 - To change the filling, use pwm_se
  - the limits of filling for different discharge are indicated in the table
*/
VOID PWM_SET (Byte PIN, UNSIGNED inti);
/* Pwm_seet (pin, filling) - change the filling on the selected pin
 - PIN: D3, D5, D6,D9, D10, D11
 - Filling: depends on the permission and the regime (see table)
  - when using pwm_frequency, the discharge is 8 bits (0-255)
  - When using PWM_Resolution Max.The value of the filling is equal (2^discharge - 1), also look at the table
*/
VOID pwm_detach (byte pin);// Disaches the PWM on the selected pin (allows you to use digital read/WRITE)
VOID pwm_attach (byte pin);// connects Shim on the selected pin (with the last settings)
VOID pwm_default (byte pin);// Reset settings corresponding to Pin Tiemer on "Standard" for Arduino
VOID PWM_16KHZ_D3 (Byte Duty);
/* Launch PWM with a frequency of 16 kHz on pin D3
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 8 bits (filling 0-255)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_20KHZ_D3 (Byte Duty);
/* Launch of PWM with a frequency of 20 kHz on pin D3
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 8 bits (filling 0-255)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_16KHZ_D5 (Byte Duty);
/* Launch PWM with a frequency of 16 kHz on pin D5
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 8 bits (filling 0-255)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_20KHZ_D5 (Byte Duty);
/* Launch PWM with a frequency of 20 kHz on pin D5
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 8 bits (filling 0-255)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_16KHZ_D9 (inti);
/* Launch of PWM with a frequency of 16 kHz (15.6 kHz) on pin D9
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - Disgusting of exactly 10 bits (filling 0-1023)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_20KHZ_D9 (inti);
/* Launch PWM with a frequency of 20 kHz on pin D9
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 10 bits (filling 0-1023)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_16KHZ_D10 (inti);
/* Launch of PWM with a frequency of 16 kHz (15.6 kHz) on pin D10
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - Disgusting of exactly 10 bits (filling 0-1023)
 - Filling changes itself (you do not need to call pwm_seet) */
VOID PWM_20KHZ_D10 (inti);
/* Launch PWM with a frequency of 20 kHz on pin D10
 - cancels PWM_FREQUENCY/PWM_RESOLATION settings
 - discharge is given to 10 bits (filling 0-1023)
 - Filling changes itself (you do not need to call pwm_seet) */
 
Float PWM_SQUARE_D9 (Float Frequency);
/* Meander generator (square wave) on pin D9
 Frequency from 2 Hz to 8 MHz, the frequency step depends on the frequency
 (Starting from 0.01 Hz and ending with dozens of kHz !!!)
 You can turn off by calling pwm_detach (9);
 To reset the timer into a default mode - pwm_default (9);
 Returns the established frequency in Herza!
 
 Frequency error
 300 Hz 0.01 Hz
 700 Hz 0.05 Hz
 900 Hz 0.1 Hz
 2 kHz 0.5 Hz
 3 kHz 1 Hz
 4 kHz 2 Hz
 9 kHz 10 Hz
 20 kHz 50 Hz
 30 kHz 110 Hz
 63 kHz 500 Hz
 90 kHz 1000 Hz
*/
/*
 ==========ward
 _____________________________________________________________________________________________________________
| Disgusting, bit | 4 | 5 | 6 | 7 | 8 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
| ___________________ | _______ | _______ | _______ | _______ | ______ | ________ | ________ | _______ | _______ | _______ | ______ | ______ | ______ |
| Max.Duty value | 15 | 31 | 63 | 127 | 255 | 511 | 1023 | 2047 | 4095 | 8191 | 16383 | 32767 | 65535 |
| ___________________ | _______ | _______ | _______ | _______ | ______ | ________ | ________ | _______ | _______ | _______ | ______ | ______ | ______ |
| Fast |Pins 3, 5 | 1 MHz | 516 kHz | 254 kHz | 126 kHz | 63 kHz |- |- |- |- |- |- |- |- |
| Pwm |9, 10 | 1 MHz | 516 kHz | 254 kHz | 126 kHz | 63 kHz | 31.2 kHz | 15.6 kHz | 7.8 kHz | 3.9 kHz | 1.9 kHz | 980 Hz | 488 Hz |244 Hz |
| _______ | ___________ | _______ | _______ | _______ | _______ | ______ | ________ | ________ | _______ | _______ | _______ | ______ | ______ | ______ |
| Correct |Pines 3, 5 | 571 kHz | 266 kHz | 129 kHz | 63 kHz | 32 kHz |- |- |- |- |- |- |- |- |
| Pwm |9, 10 | 571 kHz | 266 kHz | 129 kHz | 63 kHz | 32 kHz | 15.7 kHz | 7.8 kHz | 3.9 kHz | 1.9 kHz | 976 Hz | 488 Hz | 244 Hz | 122 Hz |
| _______ | ___________ | _______ | _______ | _______ | _______ | ______ | ________ | ________ | _______ | _______ | _______ | ______ | ______ | ______ |
*/
// ==ward
// These functions do not remove one PWM output from 8 bit timers, you can use all 6 PIM Pinov with a configured frequency!See table.
VOID PWM_PRESCALER (Byte PIN, Byte Mode);
/* PWM_PRESCALER (PIN, mode) - set the Tiemer Premier (changes the frequency of PWM)
 - PIN: D3, D5, D6, D9, D10, D11
 - mode: 1-7, see the frequency table
*/
VOID pwm_mode (byte pin, modes mode);
/* Pwm_mode (pin, mode) - set the generation mode of the PWM
 - PIN: D3, D5, D6, D9, D10, D11
 - mode: 0 - Fastpwm, 1 - Phase -Correct, see the frequency table
*/
VOID PWM_TMR1_8BIT ();// Install the timer 1 (PWM on D9 and D10) in mode 8 bits.See the frequency table
VOID PWM_TMR1_10BIT ();// Install the timer 1 (Shim on D9 and D10) in mode 10 bits.See the frequency table
/*
 =======ward
 
 Timer 0 by default operates in FAST PWM mode
 Timer 1 and 2 by default work in Phase-Correct mode
 _______________________________________________________________________________________
||Timer0 (Pines 5 and 6) 8 Bit |Timer 1 (Pines 9 and 10) 10 Bit |Timer2 (Pins 3 and 11) 8 Bit |
||Timer1 (Pins 9 and 10) 8 Bit |||
|| ________________ (
| Mode |Phase-Correct |FAST PWM |Phase-Correct |FAST PWM |Phase-Correct |FAST PWM |
| _______ | _______________ | ___________ | _____________________ | _____________ | _________________ | ___________ |
| 1 |31.4 khz |62.5 KHZ |7.8 khz |15.6 khz |31.4 khz |62.5 KHZ |
| 2 |4 khz |7.8 khz |977 Hz |2 khz |4 khz |8 khz |
| 3 |490 Hz |976 Hz |122 Hz |244 Hz |980 Hz |2 khz |
| 4 |122 Hz |244 Hz |30 Hz |61 Hz |490 Hz |980 Hz |
| 5 |30 Hz |61 Hz |7.6 Hz |15 Hz |245 Hz |490 Hz |
| 6 |- |- |- |- |122 Hz |244 Hz |
| 7 |- |- |- |- |30 Hz |60 Hz |
| _______ | _______________ | ___________ | _____________________ | _____________ | _________________ | ___________ |
*/
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include <gyverpwm.h>

VOID setup () {
  Pinmode (3, output);
  Pinmode (5, output);
  Pinmode (9, output);
  Pinmode (10, output);

  // these functions remove one PWM output from 8 bit timers, leaving us shim pins D3, D5, D9 and D10 on Atmega328

  PWM_16KHZ_D3 (30);// SHIM 16 kHz on pin D3, filling 30 out of 255
  PWM_20KHZ_D5 (50);// PWM 20 kHz on pin D5, filling 50 out of 255. Millis () and delay () will break!
  PWM_16KHZ_D9 (760);// SHIM 16 kHz on pin D9, filling 760 out of 1023
  PWM_16KHZ_D10 (800);// SHIM 16 kHz on pin D10, filling 800 out of 1023
  // Pins 9 and 10 work at the same frequency, starting on different ones will not work
}

VOID loop () {
}
`` `

<a id="versions"> </a>
## versions
- V1.4
- V1.5 - Small corrections and optimization
- V1.6 - support atmega168

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


Under the messageCranberries about bugs or incorrect work of the library must be indicated:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code