This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverPWM
Library for extended PWM generation on ATmega328 (Arduino UNO/Nano/Pro Mini...)
- Hardware generation of PWM with adjustable frequency and bit depth

### Compatibility
Arduino UNO/Nano/Pro Mini

### Documentation
The library has [extended documentation](https://alexgyver.ru/GyverPWM/)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverPWM** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/GyverPWM/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
Not

<a id="usage">Cranberry</a>
## Usage
```cpp
// ============== Functions for advanced PWM signal generation ==============
// These functions remove one PWM output from 8-bit timers, leaving us with PWM pins D3, D5, D9 and D10 on the ATmega328
void PWM_frequency(byte pin, long freq, modes correct);
/* PWM_freqency(pin, frequency, mode) - run the PWM at the selected frequency
 - Pins: D3 (timer 2), D5 (timer 0 - break millis/delay), D9 and D10 (timer 1)
 - Mode: 0 (FAST_PWM), 1 (CORRECT_PWM)
 - Frequency: 250-200'000 Hz for all timers
 - To change padding use PWM_set
  - The bit depth in this mode is reduced to 8 bits, in fact, the change steps are different!
*/
void PWM_resolution(byte pin, byte res, modes correct);
/* PWM_resolution(pin, bit width, mode) - run PWM with selected bit width
 - Pins: D3 (timer 2), D5 (timer 0 - break millis/delay), D9 and D10 (timer 1)
 - Mode: 0 (FAST_PWM), 1 (CORRECT_PWM)
 - Resolution: D3 (4-8 bits), D5 (4-8 bits), D9 and D10 (4-16 bits)
 - The frequency in this mode is automatically selected maximum according to the capabilities of the timer (see table)
 - To change padding use PWM_set
  - The filling limits for different bit depths are indicated in the table
*/
void PWM_set(byte pin, unsigned int duty);
/* PWM_set(pin, padding) - change the padding on the selected pin
 - Pin: D3, D5, D6, D9, D10, D11
 - Padding: depends on resolution and mode (see table)
  - When using PWM_frequency, the bit width is 8 bits (0-255)
  - When using PWM_resolution max. padding value is (2^bit - 1), also see table
*/
void PWM_detach(byte pin); // disables PWM on selected pin (allows digital Read/Write)
void PWM_attach(byte pin); // enable PWM on selected pin (with latest settings)
void PWM_default(byte pin); // reset the settings of the timer corresponding to the pin to "standard" for Arduino
void PWM_16KHZ_D3(byte duty);
/* Run PWM at 16kHz on pin D3
 - Cancels P settingsWM_frequency/PWM_resolution
 - Bit depth adjusted to 8 bits (padding 0-255)
 - Padding changes itself (no need to call PWM_set) */
void PWM_20KHZ_D3(byte duty);
/* Run PWM at 20kHz on pin D3
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit depth adjusted to 8 bits (padding 0-255)
 - Padding changes itself (no need to call PWM_set) */
void PWM_16KHZ_D5(byte duty);
/* Run PWM at 16kHz on pin D5
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit depth adjusted to 8 bits (padding 0-255)
 - Padding changes itself (no need to call PWM_set) */
void PWM_20KHZ_D5(byte duty);
/* Run PWM at 20kHz on pin D5
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit depth adjusted to 8 bits (padding 0-255)
 - Padding changes itself (no need to call PWM_set) */
void PWM_16KHZ_D9(int duty);
/* Run PWM at 16kHz (15.6kHz) on pin D9
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit width exactly 10 bits (padding 0-1023)
 - Padding changes itself (no need to call PWM_set) */
void PWM_20KHZ_D9(int duty);
/* Run PWM at 20kHz on pin D9
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit depth adjusted to 10 bits (padding 0-1023)
 - Padding changes itself (no need to call PWM_set) */
void PWM_16KHZ_D10(int duty);
/* Run PWM at 16kHz (15.6kHz) on pin D10
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit width exactly 10 bits (padding 0-1023)
 - Padding changes itself (no need to call PWM_set) */
void PWM_20KHZ_D10(int duty);
/* Run PWM at 20kHz on pin D10
 - Overrides PWM_frequency/PWM_resolution settings
 - Bit depth adjusted to 10 bits (padding 0-1023)
 - Padding changes itself (no need to call PWM_set) */
 
float PWM_square_D9(float frequency);
/* Square wave generator on pin D9
 Frequency 2Hz to 8MHz, frequency step depends on frequency
 (starting at 0.01 Hz and ending at tenkami kHz!!!)
 You can disable it by calling PWM_detach(9);
 To reset the timer to default mode - PWM_default(9);
 Returns the set frequency in hertz!
 
 Frequency Accuracy
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
 ============= Table #1 of frequencies for extended PWM generation (PWM_resolution) =============
 _________________________________________________________________________________________________________________________________
| Bit depth | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|______|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
|Max. duty value|15 |31 |63 |127 |255 |511 |1023 |2047 |4095 |8191 |16383 |32767 |65535 |
|______|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
| Fast | Pins 3, 5 |1 MHz |516 kHz|254 kHz|126 kHz|63 kHz|- |- |- |- |- |- |- |- |
|PWM| 9, 10 |1 MHz |516 kHz|254 kHz|126 kHz|63 kHz|31.2 kHz|15.6 kHz|7.8 kHz|3.9 kHz|1.9 kHz|980 Hz|488 Hz|244 Hz|
|_______|___________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
|Correct| Pins 3, 5 |571kHz|266kHz|129kHz|63kHz |32kHz|- |- |- |- |- |- |- |- |
|PWM| 9, 10 |571 kHz|266 kHz|129 kHz|63 kHz |32 kHz|15.7 kHz|7.8 kHz |3.9 kHz|1.9 kHz|976 Hz |488 Hz|244 Hz|122 Hz|
|_______|___________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
*/
// ============ Functions for setting up standard PWM signal generation (analogWrite) ============
// These functions do NOT remove one PWM output from 8-bit timesmoat, you can use all 6 PWM pins with the configured frequency! See table.
void PWM_prescaler(byte pin, byte mode);
/* PWM_prescaler(pin, mode) - set the timer prescaler (changes the PWM frequency)
 - Pin: D3, D5, D6, D9, D10, D11
 - Mode: 1-7, see frequency table
*/
void PWM_mode(byte pin, modes mode);
/* PWM_mode(pin, mode) - set the PWM generation mode
 - Pin: D3, D5, D6, D9, D10, D11
 - Mode: 0 - FastPWM, 1 - Phase-correct, see frequency table
*/
void PWM_TMR1_8BIT(); // Set timer 1 (PWM on D9 and D10) to 8 bit mode. See frequency table
void PWM_TMR1_10BIT(); // Set timer 1 (PWM on D9 and D10) to 10 bit mode. See frequency table
/*
 ========== Table #2 of frequencies for standard PWM generation (PWM_prescaler) ==========
 
 Timer 0 works in Fast PWM mode by default
 Timer 1 and 2 work in Phase-correct mode by default
 _________________________________________________________________________________________________
| | Timer0 (pins 5 and 6) 8 bit | Timer 1 (pins 9 and 10) 10 bit | Timer2 (pins 3 and 11) 8 bit|
| | Timer1 (pins 9 and 10) 8 bit| | |
| |________________________________|______________________________|___________________________|
| mode | phase-correct | Fast PWM | phase-correct | Fast PWM | phase-correct | Fast PWM |
|_______|_______________|___________|___________________|___________|_______________|___________|
|1 | 31.4 kHz | 62.5 kHz | 7.8 kHz | 15.6 kHz | 31.4 kHz | 62.5 kHz |
|2 | 4 kHz | 7.8 kHz | 977Hz | 2 kHz | 4 kHz | 8 kHz |
|3 | 490Hz | 976Hz | 122Hz | 244Hz | 980Hz | 2 kHz |
|4 | 122Hz | 244Hz | 30Hz | 61Hz | 490Hz | 980Hz |
|5 | 30Hz | 61Hz | 7.6Hz | 15Hz | 245Hz | 490Hz |
|6 | - | - | - | -| 122Hz | 244Hz |
|7 | - | - | - | - | 30Hz | 60Hz |
|_______|_______________|___________|___________________|___________|_______________|___________|
*/
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include <GyverPWM.h>

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // These functions remove one PWM output from 8-bit timers, leaving us with PWM pins D3, D5, D9 and D10 on the ATmega328

  PWM_16KHZ_D3(30); // PWM 16 kHz on pin D3, padding 30 out of 255
  PWM_20KHZ_D5(50); // PWM 20kHz on pin D5, padding 50 out of 255. Will break millis() and delay()!
  PWM_16KHZ_D9(760); // PWM 16kHz on pin D9, padding 760 out of 1023
  PWM_16KHZ_D10(800); // PWM 16 kHz on pin D10, padding 800 out of 1023
  // pins 9 and 10 operate at the same frequency, it will not work on different ones
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.4
- v1.5 - minor fixes and optimization

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!