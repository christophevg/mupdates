INCLUDE_PATH=../.. -I ../shared
MOOSE_PATH=../../moose

MORE_SRC = ${MOOSE_PATH}/avr.c \
					 ${MOOSE_PATH}/xbee.c \
					 ${MOOSE_PATH}/clock.c

MCU=atmega1284p
F_CPU=8000000

AVRDUDE_PROGRAMMER=jtag2

# external hardware composition ... yummie :-)
MORE_CDEFS=-DSERIAL_ON_USART1

include ${MOOSE_PATH}/Makefile

serial-digitus:
	screen /dev/tty.usbserial-FTSJ84AI 9600

%.bin: %.hex
	@echo "--- creating $@"
	@avr-objcopy -I ihex -O binary $< $@

%.size: %
	@echo "--- sizing $<"
	@wc -c $<

%.diff: ../host/%.bin %.bin
	@echo "--- creating binary diff"
	@bsdiff $^ $@

diff: clean-all main.diff.size

clean-all: clean
	@rm -f *.bin *.diff

.PRECIOUS: main.bin main.diff main.hex ../host/main.bin ../host/main.diff ../host/main.hex ../host/main.elf
	