/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifdef AVR

#ifndef __AFSK_AVR_H__
#define __AFSK_AVR_H__

#include <stdint.h>
#include <avr/pgmspace.h>
#include "config.h"


#if defined(__AVR_ATmega328P__)
  #define TIFR TIFR2
  #define TOIE TOIE2
  #if AUDIO_PIN == 3
  #  define OCR OCR2B
  #endif
  #if AUDIO_PIN == 11
  #  define OCR OCR2A
  #endif

  #define TOV TOV2
  #define TIMSK TIMSK2
  #define AFSK_ISR ISR(TIMER2_OVF_vect)
  #define DATA_SIZE uint8_t
  #define TCNT TCNT2
#endif

#if defined(__AVR_ATmega2560__)
#ifdef STUPID_IDEA
  #define TIFR TIFR3
  #define TOIE TOIE3
  #define TOV TOV3
  #define OCR OCR3A
  #define TIMSK TIMSK3
  #define AFSK_ISR ISR(TIMER3_OVF_vect)
  #define AFSK_ISR_C ISR(TIMER3_COMPA_vect)
  #define TCNT TCNT3
  #define DATA_SIZE uint16_t

#else
  #define TIFR TIFR3
  #define TOIE TOIE3
  #define TOV TOV3
  #define OCR OCR3A
  #define TIMSK TIMSK3
  #define AFSK_ISR ISR(TIMER3_OVF_vect)
  #define TCNT TCNT3
  #define DATA_SIZE uint8_t

#endif
#endif


// Exported consts
extern const uint32_t MODEM_CLOCK_RATE;
extern const uint8_t REST_DUTY;
extern const uint16_t TABLE_SIZE;
extern const uint32_t PLAYBACK_RATE;

// Exported vars
extern const uint8_t afsk_sine_table[] PROGMEM;

// Inline functions (this saves precious cycles in the ISR)

inline uint8_t afsk_read_sample(int phase)
{

  return pgm_read_byte_near(afsk_sine_table + phase);


}

inline void afsk_output_sample(DATA_SIZE s)
{
  OCR =s;
}

inline void afsk_clear_interrupt_flag()
{
  // atmegas don't need this as opposed to pic32s.
}

#ifdef DEBUG_MODEM
inline uint16_t afsk_timer_counter()
{
  uint16_t t = TCNT2;
  if ((TIFR2 & _BV(TOV2)) && t < 128)
    t += 256;
  return t;
}

inline int afsk_isr_overrun()
{
  return (TIFR2 & _BV(TOV2));
}
#endif


// Exported functions
void afsk_setup();
void afsk_send(const uint8_t *buffer, int len);
void afsk_start();
bool afsk_flush();
void afsk_isr();
void afsk_timer_setup();
void afsk_timer_start();
void afsk_timer_stop();
#ifdef DEBUG_MODEM
void afsk_debug();
#endif

#endif
#endif // AVR
