#include <avr/io.h>
#include <util/delay.h>

#include "moose.h"
#include "light_sensor_config.h"
#include "xbee_send_to_coordinator.h"

#include <string.h>

void xbee_send_string(const char* str) {
  xbee_send_bytes((uint8_t*)str, strlen(str));
}

void alert(uint16_t light_reading) {
  if(light_reading > 700) {
    xbee_send_string("alert, light above 700");
  }
}

int main(void) {
  avr_init();
  avr_adc_init();

  xbee_init();
  xbee_wait_for_association();

  avr_clear_bit(LIGHT_SENSOR_PORT, LIGHT_SENSOR_PIN);

  union {
    uint16_t reading;
    uint8_t  bytes[2];
  } light;

  while(TRUE) {
    light.reading = avr_adc_read(LIGHT_SENSOR_PIN);
    xbee_send_bytes(light.bytes, 2);
    alert(light.reading);
    _delay_ms(60000L);
  }

  return(0);
}
