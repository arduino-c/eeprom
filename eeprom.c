

#include <avr/io.h>
#include <avr/interrupt.h>

static void eeprom_wait_while_busy() {
	while(EECR & _BV(EEPE));
}

static unsigned char eeprom_readbyte(int adr) {
	eeprom_wait_while_busy();
	EEAR = adr;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	return EEDR;
}

static void eeprom_writebyte(int adr, unsigned char data) {
	eeprom_wait_while_busy();
	sei();
	EEAR = adr, EEDR = data;
	/* Write logical one to EEMPE */
	EECR |= _BV(EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= _BV(EEPE);
	cli();
}


static int cur;

int eeprom_init() {
}

int eeprom_seek(int pos) {
	cur = pos;
}

int eeprom_read(char *data, int len) {
	int i;
	i = 0;
	while(i < len) {
		data[i++] = eeprom_readbyte(cur++);
	}
}

int eeprom_write(char *data, int len) {
	int i;
	i = 0;
	while(i < len) {
		eeprom_writebyte(cur++, data[i++]);
	}
}