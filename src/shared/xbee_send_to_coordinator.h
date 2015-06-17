#define DESTINATION XBEE_COORDINATOR

void xbee_send_bytes(uint8_t *bytes, uint8_t size) {
  xbee_tx_t frame;

  frame.size        = size;
  frame.id          = XB_TX_NO_RESPONSE;
  frame.address     = XB_COORDINATOR;
  frame.nw_address  = XB_NW_ADDR_UNKNOWN;
  frame.radius      = XB_MAX_RADIUS;
  frame.options     = XB_OPT_NONE;
  frame.data        = bytes;

  xbee_send(&frame);
}
