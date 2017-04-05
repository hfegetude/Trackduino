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

#include "config.h"
#include "ax25.h"
#include "gps.h"
#include "aprs.h"
#include "sensors_avr.h"
#include "sensors_lib.h"
#include "sensors_pic32.h"
#include <stdio.h>
#include <stdlib.h>
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#  include <WProgram.h>
#endif

// Module functions
float meters_to_feet(float m)
{
  // 10000 ft = 3048 m
  return m / 0.3048;
}

// Exported functions
void aprs_send()
{
  char temp[12];                   // Temperature (int/ext)
  S3DVEC temp_3D;
  TIME_FORMAT current_time = getDateRTC();
  const struct s_address addresses[] = {
    {D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
    {S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign (-11 = balloon, -9 = car)
#ifdef DIGI_PATH1
    {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
#endif
#ifdef DIGI_PATH2
    {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
#endif
  };

  ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));
  ax25_send_byte('/');
  snprintf(temp, 7 ,"%02d%02d%02dz" ,current_time.dayOfMonth, current_time.month, current_time.year );
  ax25_send_byte(temp);              // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
  snprintf(temp, 7 ,"%02d%02d%02dz" ,current_time.hour, current_time.minute, current_time.seconds );
  ax25_send_byte(temp);



  ax25_send_string(gps_aprs_lat);     // Lat: 38deg and 22.20 min (.20 are NOT seconds, but 1/100th of minutes)
  ax25_send_byte('/');                // Symbol table
  ax25_send_string(gps_aprs_lon);     // Lon: 000deg and 25.80 min
  ax25_send_byte('O');                // Symbol: O=balloon, -=QTH
  //snprintf(temp, 4, "%03d", (int)(gps_course + 0.5));
  //ax25_send_string(temp);             // Course (degrees)
  mpuStart();
  temp_3D = getRotation();
  mpuSleep();
  //send rotation
  ax25_send_byte('/RoX=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.x  );
  ax25_send_byte('/RoY=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.y  );
  ax25_send_byte('/RoZ=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.z  );

  mpuStart();
  temp_3D = getAcceleration();
  mpuSleep();
  //send acceleration
  ax25_send_byte('/AcX=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.x  );
  ax25_send_byte('/AcY=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.y  );
  ax25_send_byte('/AcZ=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.z  );

  measureMagnet();
  temp_3D = getMagnet();
  //send acceleration
  ax25_send_byte('/MaX=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.x  );
  ax25_send_byte('/MaY=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.y  );
  ax25_send_byte('/MaZ=');                // and
  snprintf(temp, 4 , "%04x", temp_3D.z  );

  //send pressure
  measurePressure();
  snprintf(temp, 4,"%04x", getPreassure() )
  ax25_send_byte("/Pr=")
  ax25_send_byte(temp)

  ax25_send_string(APRS_COMMENT);     // Comment

  ax25_send_footer();
  ax25_flush_frame();                 // Tell the modem to go
}
