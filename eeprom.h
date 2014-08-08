
#ifndef EEPROM_H
#define EEPROM_H

int eeprom_init();
int eeprom_seek(int pos);
int eeprom_read(char *data, int len);
int eeprom_write(char *data, int len);

#endif /* EEPROM_H */