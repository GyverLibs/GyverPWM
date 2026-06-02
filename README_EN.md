This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverPWM.svg?color=brightgreen)](https://github.com/GyverLibs/GyverPWM/releases/latest/download/GyverPWM.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverPWM.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverPWM)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverPWM?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverPWM
Advanced PWM generation library on ATmega328 (Arduino UNO/Nano/Pro Mini...)
- Hardware generation of PWM of adjustable frequency and bit

### Compatibility
Arduino UNO/Nano/Pro Mini

### Documentation.
There's a library[extended documentation](https://alexgyver.ru/GyverPWM/)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverPWM** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverPWM/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
No.

<a id="usage"></a>
## Use of use
```cpp
// ========= Functions for extended PWM signal generation =================
// These features remove one PWM output from 8-bit timers, leaving us PWM pins D3, D5, D9 and D10 on ATmega328.
void PWM_frequency(byte pin, long freq, modes correct);
/*  PWM_freqency(пин, частота, режим) - запустить ШИМ с выбранной частотой
 - Пины: D3 (таймер 2), D5 (таймер 0 - сломает millis/delay), D9 и D10 (таймер 1)
 - Режим: 0 (FAST_PWM), 1 (CORRECT_PWM)
 - Частота: 250-200'000 Гц для всех таймеров
 - Для изменения заполнения используй PWM_set
  - Разрядность в этом режиме приведена к 8 битам, на деле шаги изменения разные!
*/
void PWM_resolution(byte pin, byte res, modes correct);
/*  PWM_resolution(пин, разрядность, режим) - запустить ШИМ с выбранной разрядностью
 - Пины: D3 (таймер 2), D5 (таймер 0 - сломает millis/delay), D9 и D10 (таймер 1)
 - Режим: 0 (FAST_PWM), 1 (CORRECT_PWM)
 - Разрешение: D3 (4-8 бит), D5 (4-8 бит), D9 и D10 (4-16 бит)
 - Частота в этом режиме выбирается автоматически максимальная согласно возможностям таймера (см. таблицу)
 - Для изменения заполнения используй PWM_set
  - Пределы заполнения для разной разрядности указаны в таблице
*/
void PWM_set(byte pin, unsigned int duty);
/*  PWM_set(пин, заполнение) - изменить заполнение на выбранном пине
 - Пин: D3, D5, D6, D9, D10, D11
 - Заполнение: зависит от разрешения и режима (см. таблицу)
  - При использовании PWM_frequency разрядность составляет 8 бит (0-255)
  - При использовании PWM_resolution макс. значение заполнения равно (2^разрядность - 1), также смотри таблицу
*/
void PWM_detach(byte pin);    // disables PWM on the selected pin (allows you to use digital Read/Write)
void PWM_attach(byte pin);    // PWM connects on the selected pin (with the latest settings)
void PWM_default(byte pin);    // Resetting the settings of the corresponding pin timer to "standard" for Arduino
void PWM_16KHZ_D3(byte duty);
/*   Запуск ШИМ с частотой 16 кГц на пине D3
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 8 битам (заполнение 0-255)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_20KHZ_D3(byte duty);
/*   Запуск ШИМ с частотой 20 кГц на пине D3
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 8 битам (заполнение 0-255)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_16KHZ_D5(byte duty);
/*   Запуск ШИМ с частотой 16 кГц на пине D5
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 8 битам (заполнение 0-255)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_20KHZ_D5(byte duty);
/*   Запуск ШИМ с частотой 20 кГц на пине D5
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 8 битам (заполнение 0-255)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_16KHZ_D9(int duty);
/*   Запуск ШИМ с частотой 16 кГц (15.6 кГц) на пине D9
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность ровно 10 бит (заполнение 0-1023)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_20KHZ_D9(int duty);
/*   Запуск ШИМ с частотой 20 кГц на пине D9
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 10 битам (заполнение 0-1023)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_16KHZ_D10(int duty);
/*   Запуск ШИМ с частотой 16 кГц (15.6 кГц) на пине D10
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность ровно 10 бит (заполнение 0-1023)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
void PWM_20KHZ_D10(int duty);
/*   Запуск ШИМ с частотой 20 кГц на пине D10
 - Отменяет настройки PWM_frequency/PWM_resolution
 - Разрядность приведена к 10 битам (заполнение 0-1023)
 - Заполнение меняет сама (не нужно вызывать PWM_set) */
 
float PWM_square_D9(float frequency);
/*  Генератор меандра (квадратная волна) на пине D9
 Частота от 2 Гц до 8 Мгц, шаг частоты зависит от частоты
 (начиная с 0.01 Гц и заканчивая десятками кГц!!!)
 Отключить можно вызвав PWM_detach(9);
 Для сброса таймера в режим по-умолчанию - PWM_default(9);
 Возвращает установленную частоту в герцах!
 
 Частота    Погрешность
 300 Гц    0.01 Гц
 700 Гц    0.05 Гц
 900 ГЦ    0.1 Гц
 2 кГц    0.5 Гц
 3 кГц    1 Гц
 4 кГц    2 Гц
 9 кГц    10 Гц
 20 кГц    50 Гц
 30 кГц    110 Гц
 63 кГц    500 Гц
 90 кГц    1000 Гц
*/
/*
 ============= Таблица №1 частот для расширенной генерации ШИМ (PWM_resolution) =============
 _________________________________________________________________________________________________________________________
|Разрядность, бит   |4      |5      |6      |7      |8     |9       |10      |11     |12     |13     |14    |15    |16    |
|___________________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
|Макс. значение duty|15     |31     |63     |127    |255   |511     |1023    |2047   |4095   |8191   |16383 |32767 |65535 |
|___________________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
|Fast   | Пины 3, 5 |1 МГц  |516 кГц|254 кГц|126 кГц|63 кГц|-       |-       |-      |-      |-      |-     |-     |-     |
|PWM    | 9, 10     |1 МГц  |516 кГц|254 кГц|126 кГц|63 кГц|31.2 кГц|15.6 кГц|7.8 кГц|3.9 кГц|1.9 кГц|980 Гц|488 Гц|244 Гц|
|_______|___________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
|Correct| Пины 3, 5 |571 кГц|266 кГц|129 кГц|63 кГц |32 кГц|-       |-       |-      |-      |-      |-     |-     |-     |
|PWM    | 9, 10     |571 кГц|266 кГц|129 кГц|63 кГц |32 кГц|15.7 кГц|7.8 кГц |3.9 кГц|1.9 кГц|976 Гц |488 Гц|244 Гц|122 Гц|
|_______|___________|_______|_______|_______|_______|______|________|________|_______|_______|_______|______|______|______|
*/
// ======= Functions for setting the standard PWM signal generation (analogWrite) ===================
// These functions DO NOT remove one PWM output from 8-bit timers, you can use all 6 PWM pins with a configured frequency! See the table.
void PWM_prescaler(byte pin, byte mode);
/*  PWM_prescaler(пин, режим) - установить предделитель таймера (меняет частоту ШИМ)
 - Пин: D3, D5, D6, D9, D10, D11
 - Режим: 1-7, см. таблицу частот
*/
void PWM_mode(byte pin, modes mode);
/*  PWM_mode(пин, режим) - установить режим генерации ШИМ
 - Пин: D3, D5, D6, D9, D10, D11
 - Режим: 0 - FastPWM, 1 - Phase-correct, см. таблицу частот
*/
void PWM_TMR1_8BIT();  // Set the timer 1 (PWM on D9 and D10) in 8 bit mode. See frequency table
void PWM_TMR1_10BIT();  // Set the timer 1 (PWM on D9 and D10) in 10 bit mode. See frequency table
/*
 ========== Таблица №2 частот для стандартной генерации ШИМ (PWM_prescaler) ==========
 
 Timer 0 по умолчанию работает в режиме Fast PWM 
 Timer 1 и 2 по умолчанию работают в режиме Phase-correct
 _______________________________________________________________________________________________
|       | Timer0 (пины 5 и 6) 8 bit | Timer 1 (пины 9 и 10) 10 bit  | Timer2 (пины 3 и 11) 8 bit|
|       | Timer1 (пины 9 и 10) 8 bit|                               |                           |
|       |___________________________|_______________________________|___________________________|
|mode   | Phase-correct | Fast PWM  | Phase-correct     | Fast PWM  | Phase-correct | Fast PWM  |
|_______|_______________|___________|___________________|___________|_______________|___________|
|1      | 31.4 kHz      | 62.5 kHz  | 7.8 kHz           | 15.6 kHz  | 31.4 kHz      | 62.5 kHz  |
|2      | 4 kHz         | 7.8 kHz   | 977 Hz            | 2 kHz     | 4 kHz         | 8 kHz     |
|3      | 490 Hz        | 976 Hz    | 122 Hz            | 244 Hz    | 980 Hz        | 2 kHz     |
|4      | 122 Hz        | 244 Hz    | 30 Hz             | 61 Hz     | 490 Hz        | 980 Hz    |
|5      | 30 Hz         | 61 Hz     | 7.6 Hz            | 15 Hz     | 245 Hz        | 490 Hz    |
|6      | -             | -         | -                 | -         | 122 Hz        | 244 Hz    |
|7      | -             | -         | -                 | -         | 30 Hz         | 60 Hz     |
|_______|_______________|___________|___________________|___________|_______________|___________|
*/
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
#include <GyverPWM.h>

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // These features remove one PWM output from 8-bit timers, leaving us PWM pins D3, D5, D9 and D10 on ATmega328.

  PWM_16KHZ_D3(30);   // PWM 16 kHz on pin D3, filling 30 of 255
  PWM_20KHZ_D5(50);   // PWM 20 kHz on pin D5, filling 50 of 255. Break millis() and delay()!
  PWM_16KHZ_D9(760);  // PWM 16 kHz on D9 pin, filling 760 out of 1023
  PWM_16KHZ_D10(800); // PWM 16 kHz on D10 pin, filling 800 of 1023
  // Pins 9 and 10 operate on the same frequency, you will not be able to run on different
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.4
- v1.5 - Minor corrections and optimization
- v1.6 - Support for ATmega168

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
