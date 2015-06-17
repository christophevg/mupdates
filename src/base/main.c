#include <avr/io.h>
#include <util/delay.h>

#include "moose.h"
#include "light_sensor_config.h"
#include "xbee_send_to_coordinator.h"

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
    _delay_ms(60000L);
  }

  return(0);
}
