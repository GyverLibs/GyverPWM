#include "GyverPWM.h"

bool isDefault[3] = {true, true, true};		// Массив default - флагов	
bool isMapping[3] = {false, false, false};  // Массив map - флагов

/* Функция быстрой установки состояния пина	*/
void PIN_set(uint8_t pin, uint8_t x) {		
    if (pin < 8) bitWrite(PORTD, pin, x);
    else if (pin < 14) bitWrite(PORTB, (pin - 8), x);
    else if (pin < 20) bitWrite(PORTC, (pin - 14), x);
}

/* Установка параметров таймера по умолчанию */
void PWM_default(uint8_t pin) {	
  PWM_detach(pin);
  PIN_set(pin, LOW);
  switch (pin) {
    case 6: // Timer0 - A
    case 5: // Timer0 - B
      isDefault[0] = true;
      isMapping[0] = false;
      TCCR0A = TCCR0B = 0b11;
      break;

    case 9:  // Timer1 - A
    case 10: // Timer1 - B
      isMapping[1] = false;
      TCCR1A = 0b01;
      TCCR1B = 0b11;
      break;

    case 11: // Timer2 - A
    case 3:  // Timer2 - B
      isDefault[2] = true;
      isMapping[2] = false;
      TCCR2A = TCCR2B = 0b11;
      break;
  }
}

/* Установка частоты ШИМ сигнала на указанном пине (настраивает таймер) */
void PWM_frequency(uint8_t pin, uint32_t frequency, uint8_t correct) {
  frequency = constrain(frequency, 250, 200000);	// Ограничиваем частоты
  PWM_detach(pin);									// Детачим таймер
  PIN_set(pin, LOW);								// Переводим пин в LOW
	
  switch (pin) {
    case 3: // Timer2 - B
      isDefault[2] = false;															// Ставим флаги
      isMapping[2] = true;
      if (correct) { 			
        TCCR2A = 1 << WGM20;														// Phase correct режим
        if (frequency > MIN_PWMFREQ_CORRECT(1)) {									// Выбираем предделитель
          TCCR2B = (1 << WGM22) | 0b001; OCR2A = (F_CPU / 2UL) / (frequency * 1UL); // Настраиваем делитель + считаем TOP
        } else if (frequency > MIN_PWMFREQ_CORRECT(8)) {
          TCCR2B = (1 << WGM22) | 0b010; OCR2A = (F_CPU / 2UL) / (frequency * 8UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(32)) {
          TCCR2B = (1 << WGM22) | 0b011; OCR2A = (F_CPU / 2UL) / (frequency * 32UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(64)) {
          TCCR2B = (1 << WGM22) | 0b100; OCR2A = (F_CPU / 2UL) / (frequency * 64UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(128)) {
          TCCR2B = (1 << WGM22) | 0b101; OCR2A = (F_CPU / 2UL) / (frequency * 128UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(256)) {
          TCCR2B = (1 << WGM22) | 0b110; OCR2A = (F_CPU / 2UL) / (frequency * 256UL);
        }
      } else {
        TCCR2A = 1 << WGM20 | 1 << WGM21;											// Fast PWM режим
        if (frequency > MIN_PWMFREQ_FAST(1)) {										// Выбираем предделитель
          TCCR2B = (1 << WGM22) | 0b001; OCR2A = (F_CPU / (frequency * 1UL)) - 1;   // Настраиваем делитель + считаем TOP
        } else if (frequency > MIN_PWMFREQ_FAST(8)) {
          TCCR2B = (1 << WGM22) | 0b010; OCR2A = (F_CPU / (frequency * 8UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(32)) {
          TCCR2B = (1 << WGM22) | 0b011; OCR2A = (F_CPU / (frequency * 32UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(64)) {
          TCCR2B = (1 << WGM22) | 0b100; OCR2A = (F_CPU / (frequency * 64UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(128)) {
          TCCR2B = (1 << WGM22) | 0b101; OCR2A = (F_CPU / (frequency * 128UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(256)) {
          TCCR2B = (1 << WGM22) | 0b110; OCR2A = (F_CPU / (frequency * 256UL)) - 1;
        }
      } break;

    case 5: // Timer0 - B
      isDefault[0] = false;
      isMapping[0] = true;
      if (correct) {
        TCCR0A = 1 << WGM00;
        if (frequency > MIN_PWMFREQ_CORRECT(1)) {
          TCCR0B = (1 << WGM02) | 0b001; OCR0A = (F_CPU / 2UL) / (frequency * 1UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(8)) {
          TCCR0B = (1 << WGM02) | 0b010; OCR0A = (F_CPU / 2UL) / (frequency * 8UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(64)) {
          TCCR0B = (1 << WGM02) | 0b011; OCR0A = (F_CPU / 2UL) / (frequency * 64UL);
        } else if (frequency > MIN_PWMFREQ_CORRECT(256)) {
          TCCR0B = (1 << WGM02) | 0b100; OCR0A = (F_CPU / 2UL) / (frequency * 256UL);
        }
      } else {
        TCCR0A = 1 << WGM00 | 1 << WGM01;
        if (frequency > MIN_PWMFREQ_FAST(1)) {
          TCCR0B = (1 << WGM02) | 0b001; OCR0A = (F_CPU / (frequency * 1UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(8)) {
          TCCR0B = (1 << WGM02) | 0b010; OCR0A = (F_CPU / (frequency * 8UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(64)) {
          TCCR0B = (1 << WGM02) | 0b011; OCR0A = (F_CPU / (frequency * 64UL)) - 1;
        } else if (frequency > MIN_PWMFREQ_FAST(256)) {
          TCCR0B = (1 << WGM02) | 0b100; OCR0A = (F_CPU / (frequency * 256UL)) - 1;
        }
      } break;

    case 9:  // Timer1 - A
    case 10: // Timer1 - B
      isMapping[1] = true;
      if (correct) {
        TCCR1A = 1 << WGM11;				// Phase correct режим
        TCCR1B = 1 << WGM13 | 0b001;		// Для таймера 1 делитель всегда 1
        ICR1 = F_CPU / (frequency * 2UL);	// Считаем	
      } else {	
        TCCR1A = 1 << WGM11;				// Fast PWM режим
        TCCR1B = 1 << WGM13 | 1 << WGM12 | 0b001;
        ICR1 = (F_CPU / frequency) - 1;		// Считаем
      } break;
  }
}

/* Установка разрешения ШИМ сигнала на указанном пине (настраивает таймер) */
void PWM_resolution(uint8_t pin, uint8_t resolution, uint8_t correct) {
  PWM_detach(pin);		// Детачим таймер
  PIN_set(pin, LOW);	// Переводим пин в LOW
  
  switch (pin) {
    case 3:  // Timer2 - B
      isDefault[2] = isMapping[2] = false;							// Ставим флаги
      TCCR2A = correct ? (1 << WGM20) : (1 << WGM20 | 1 << WGM21);	// Выбираем Fast PWM или Phase correct
      TCCR2B = 1 << WGM22 | 1 << CS20;						
      OCR2A = (1 << constrain(resolution, 4, 8)) - 1;				// Устанавливаем top с ограничением
      break;

    case 5:  // Timer0 - B
      isDefault[0] = isMapping[0] = false;
      TCCR0A = correct ? (1 << WGM00) : (1 << WGM00 | 1 << WGM01);
      TCCR0B = 1 << WGM02 | 1 << CS00;
      OCR0A = (1 << constrain(resolution, 4, 8)) - 1;
      break;

    case 9:  // Timer1 - A
    case 10: // Timer1 - B
      isMapping[1] = false;
      TCCR1A = 1 << WGM11;
      TCCR1B = (correct ? (1 << WGM13) : (1 << WGM13 | 1 << WGM12)) | 1 << CS10;
      ICR1 = (1 << constrain(resolution, 4, 16)) - 1;
      break;
  }
}

/* Установка заполнения ШИМ сигнала на указанном пине */
void PWM_set(uint8_t pin, uint16_t duty) {
  if (duty < 1) {PWM_detach(pin); return;}	// Если заполнение 0 - детачим пин и в LOW

  switch (pin) {
    case 3: // Timer2 - B
      if (isMapping[2]) duty = constrain(map(duty, 0, 255, 0, OCR2A), 0, OCR2A);	// Масштабируем если нужно
      if (duty == OCR2A){ PWM_detach(pin); PIN_set(pin, HIGH);}						// Если макс. значение - детачим и в HIGH
      else {PWM_attach(pin); OCR2B = duty;}											// Иначе аттачим и выводим заполнение
      break;

    case 5: // Timer0 - B
      if (isMapping[0]) duty = constrain(map(duty, 0, 255, 0, OCR0A), 0, OCR0A);
      if (duty == OCR0A){ PWM_detach(pin); PIN_set(pin, HIGH);}
      else {PWM_attach(pin); OCR0B = duty;}
      break;

    case 6: // Timer0 - A
      if (isDefault[0]) {
        if (duty == 255){ PWM_detach(pin); PIN_set(pin, HIGH);}
        else {PWM_attach(pin); OCR0A = duty;}
      } break;

    case 9: // Timer1 - A
      if (isMapping[1]) duty = constrain(map(duty, 0, 255, 0, ICR1), 0, ICR1);
      if (duty == ICR1){ PWM_detach(pin); PIN_set(pin, HIGH);}
      else {PWM_attach(pin); OCR1A = duty;}
      break;

    case 10: // Timer1 - B
      if (isMapping[1]) duty = constrain(map(duty, 0, 255, 0, ICR1), 0, ICR1);
      if (duty == ICR1){ PWM_detach(pin); PIN_set(pin, HIGH);}
      else {PWM_attach(pin); OCR1B = duty;}
      break;

    case 11: // Timer2 - A
      if (isDefault[2]) {
        if (duty == 255){ PWM_detach(pin); PIN_set(pin, HIGH);}
        else {PWM_attach(pin); OCR2A = duty;}
      } break;
  }
}

/* Отключение пина от таймера */
void PWM_detach(uint8_t pin) {						
  switch (pin) {									// Выбираем пин
    case 3:  bitClear(TCCR2A, COM2B1);  break;		// Сбрасываем нужный бит таймера
    case 5:  bitClear(TCCR0A, COM0B1);  break;
    case 6:  bitClear(TCCR0A, COM0A1);  break;
    case 9:  bitClear(TCCR1A, COM1A1);  break;
    case 10: bitClear(TCCR1A, COM1B1);  break;
    case 11: bitClear(TCCR2A, COM2A1);  break;
  } 
}

/* Подключение пина к таймеру */
void PWM_attach(uint8_t pin) {						
  switch (pin) {									// Выбираем пин
    case 3:  bitSet(TCCR2A, COM2B1);  break;		// Ставим нужный бит таймера
    case 5:  bitSet(TCCR0A, COM0B1);  break;
    case 6:  bitSet(TCCR0A, COM0A1);  break;
    case 9:  bitSet(TCCR1A, COM1A1);  break;
    case 10: bitSet(TCCR1A, COM1B1);  break;
    case 11: bitSet(TCCR2A, COM2A1);  break;
  }
}

/* Установка делителя таймера */
void PWM_prescaler(uint8_t pin, uint8_t prescaler) { //
  switch (pin) {
    case 5:
    case 6:  TCCR0B = TCCR0B & 0xF8 | prescaler; break;
    case 9:
    case 10: TCCR1B = TCCR1B & 0xF8 | prescaler; break;
    case 3:
    case 11: TCCR2B = TCCR2B & 0xF8 | prescaler; break;
  }
}

/* Установка режима таймера */
void PWM_mode(uint8_t pin, uint8_t mode) {
  switch (pin) {
    case 5:
    case 6:   TCCR0A = TCCR0A & 0xFC | (mode ? 0b01 : 0b11);    break;
    case 9 :
    case 10 : TCCR1B = TCCR1B & 0xF7 | (mode ? 0 : 1 << WGM12); break;
    case 3 :
    case 11 : TCCR2A = TCCR2A & 0xFC | (mode ? 0b01 : 0b11);    break;
  }
}

/* Установка режима 8 бит таймеру 1 */
void PWM_TMR1_8BIT() {
    TCCR1A = TCCR1A & 0xE0 | (1 << WGM10);
}

/* Установка режима 10 бит таймеру 1 */
void PWM_TMR1_10BIT() {
    TCCR1A = TCCR1A & 0xE0 | (1 << WGM10 | 1 << WGM11);
}

/* ШИМ 16 кГц "8 Бит" на пине 3 */
void PWM_16KHZ_D3(uint8_t duty) {
  TCCR2A = 1 << COM2B1 | 1 << WGM21 | 1 << WGM20;
  TCCR2B = (1 << WGM22) | 0b010;
  OCR2A = (F_CPU / (16000UL * 8)) - 1;
  if (duty == 0) {
    PWM_detach(3);
    PIN_set(3, LOW);
  } else {
    PWM_attach(3);
    OCR2B = map(duty, 0, 255, 0, OCR2A);
  }
}

/* ШИМ 20 кГц "8 Бит" на пине 3 */
void PWM_20KHZ_D3(uint8_t duty) {
  TCCR2A = 1 << COM2B1 | 1 << WGM21 | 1 << WGM20;
  TCCR2B = (1 << WGM22) | 0b010;
  OCR2A = (F_CPU / (20000UL * 8)) - 1;
  if (duty == 0) {
    PWM_detach(3);
    PIN_set(3, LOW);
  } else {
    PWM_attach(3);
    OCR2B = map(duty, 0, 255, 0, OCR2A);
  }
}

/* ШИМ 16 кГц "8 Бит" на пине 5 */
void PWM_16KHZ_D5(uint8_t duty) {
  TCCR0A = 1 << COM0B1 | 1 << WGM01 | 1 << WGM00;
  TCCR0B = (1 << WGM02) | 0b010;
  OCR0A = (F_CPU / (16000UL * 8)) - 1;
  if (duty == 0) {
    PWM_detach(5);
    PIN_set(5, LOW);
  } else {
    PWM_attach(5);
    OCR0B = map(duty, 0, 255, 0, OCR0A);
  }
}

/* ШИМ 20 кГц "8 Бит" на пине 5 */
void PWM_20KHZ_D5(uint8_t duty) {
  TCCR0A = 1 << COM0B1 | 1 << WGM01 | 1 << WGM00;
  TCCR0B = (1 << WGM02) | 0b010;
  OCR0A = (F_CPU / (20000UL * 8)) - 1;
  if (duty == 0) {
    PWM_detach(5);
    PIN_set(5, LOW);
  } else {
    PWM_attach(5);
    OCR0B = map(duty, 0, 255, 0, OCR0A);
  }
}

/* ШИМ 16 кГц "10 Бит" на пине 9 */
void PWM_16KHZ_D9(uint16_t duty) {
  TCCR1A = 1 << COM1A1 | 1 << WGM11;
  TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b001;
  ICR1 = (F_CPU / 16000UL) - 1;
  OCR1A = map(duty, 0, 1023, 0, ICR1);
}

/* ШИМ 20 кГц "10 Бит" на пине 9 */
void PWM_20KHZ_D9(uint16_t duty) {
  TCCR1A = 1 << COM1A1 | 1 << WGM11;
  TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b001;
  ICR1 = (F_CPU / 20000UL) - 1;
  OCR1A = map(duty, 0, 1023, 0, ICR1);
}

/* ШИМ 16 кГц "10 Бит" на пине 10 */
void PWM_16KHZ_D10(uint16_t duty) {
  TCCR1A = 1 << COM1B1 | 1 << WGM11;
  TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b001;
  ICR1 = (F_CPU / 16000UL) - 1;
  OCR1B = map(duty, 0, 1023, 0, ICR1);
}

/* ШИМ 20 кГц "10 Бит" на пине 10 */
void PWM_20KHZ_D10(uint16_t duty) {
  TCCR1A = 1 << COM1B1 | 1 << WGM11;
  TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b001;
  ICR1 = (F_CPU / 20000UL) - 1;
  OCR1B = map(duty, 0, 1023, 0, ICR1);
}

/* Генерация меандра с указанной частотой на пине 9 */
float PWM_square_D9(float frequency) {
  TCCR1A = 1 << COM1A0;
  TCCR1C = 1 << FOC1A;
  if (frequency < (F_CPU / (65535UL * 16))) {
    TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b011;
    ICR1 = ((float)F_CPU / (frequency * 128UL)) - 1;
    return ((float)F_CPU / ((ICR1 + 1) * 128.0f));
  } else if (frequency < (F_CPU / (65535UL * 2))) {
    TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b010;
    ICR1 = ((float)F_CPU / (frequency * 16UL)) - 1;
    return ((float)F_CPU / ((ICR1 + 1) * 16.0f));
  } else {
    TCCR1B = 1 << WGM12 | 1 << WGM13 | 0b001;
    ICR1 = ((float)F_CPU / (frequency * 2UL)) - 1;
    return ((float)F_CPU / ((ICR1 + 1) * 2.0f));
  }
}
