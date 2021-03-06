#include <avr/io.h>
#include <util/delay.h>

#include "moose.h"
#include "light_sensor_config.h"
#include "xbee_send_to_coordinator.h"

#include <string.h>

void xbee_send_string(const char* str) {
  xbee_send_bytes((uint8_t*)str, strlen(str));
}

// global light reading information
union {
  uint16_t reading;
  uint8_t  bytes[2];
} light;

// a prototype for handlers
typedef void (*handler_t)(void);

// an implementation of the handler, reporting it
void report(void) {
  xbee_send_bytes(light.bytes, 2);
}

void alert(void) {
  if(light.reading > 700) {
    xbee_send_string("alert, light above 700");
  }
}

// a datastructure holding handlers
handler_t handlers[] = { &report, &alert, NULL };

int main(void) {
  avr_init();
  avr_adc_init();

  xbee_init();
  xbee_wait_for_association();

  avr_clear_bit(LIGHT_SENSOR_PORT, LIGHT_SENSOR_PIN);

  while(TRUE) {
    light.reading = avr_adc_read(LIGHT_SENSOR_PIN);
    int i = 0;
    while(handlers[i]) { handlers[i++](); }
    _delay_ms(60000L);
  }

  return(0);
}
