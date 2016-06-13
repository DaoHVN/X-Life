#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#if (EEPROM_CONTROL == ENABLE)

#define EEPROM_SIZE               0x0400
#define EEPROM_START_ADDRESS      0x0000
#define EEPROM_END_ADDRESS        0x03FF

extern void EEPROM_Write_Page(uint16_t address, uint8_t *data, uint16_t len);
extern void EEPROM_Read_Page(uint16_t address, uint8_t *data, uint16_t len);
extern void EEPROM_Read_Init(void);


#endif  /* (EEPROM_CONTROL == ENABLE) */

#endif  /* EEPROM_CONTROL_H */

