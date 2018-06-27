/*
 * MS5637.h
 *
 *  Created on: 26 f�vr. 2017
 *      Author: Vincent
 */

#ifndef LIBRARIES_MS5637_H_
#define LIBRARIES_MS5637_H_


/* 7 bits i2c address of module */
#define MS5637_ADDR                    (0x76)

/* module commands */
#define CMD_RESET                      (0x1E)
#define CMD_PROM_READ(offs)            (0xA0+(offs<<1)) /* Offset 0-7 */
#define CMD_START_D1(oversample_level) (0x40 + 2*(int)oversample_level)
#define CMD_START_D2(oversample_level) (0x50 + 2*(int)oversample_level)
#define CMD_READ_ADC 0x00

#define MS5637_CRC_INDEX 0
#define MS5637_COEFFICIENT_COUNT 7
/* Module supports a range of lower oversampling levels, for faster
   less accurate results.

   Default is maximum accuracy.
 */
enum BaroOversampleLevel {
  OSR_256, OSR_512, OSR_1024, OSR_2048, OSR_4096, OSR_8192 };

typedef enum {
  CELSIUS,
  FAHRENHEIT
} TempUnit;

typedef enum {
  eMS5637MeasCmdTemp,
  eMS5637MeasCmdPress,
} eMS5637MeasType;

typedef struct _ms5637_handle
{
	uint8_t cx_data[MS5637_COEFFICIENT_COUNT*2];
	uint8_t press_adc[3];
	uint8_t temp_adc[3];
	eMS5637MeasType meas_type;
} ms5637_handle_t;

#define BARO_LEVEL    OSR_8192


/*=========================================================================*/
#define MS5637_INIT_REGS \
{                                          \
	CMD_PROM_READ(0),                      \
	CMD_PROM_READ(1),                      \
	CMD_PROM_READ(2),                      \
	CMD_PROM_READ(3),                      \
	CMD_PROM_READ(4),                      \
	CMD_PROM_READ(5),                      \
	CMD_PROM_READ(6)                       \
}

#define MS5637_INIT(r_buffer, p_buffer) \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer  , p_buffer   , 2),  \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+1, p_buffer+2 , 2),  \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+2, p_buffer+4 , 2),  \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+3, p_buffer+6 , 2),  \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+4, p_buffer+8 , 2),  \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+5, p_buffer+10, 2), \
		I2C_READ_REG_REP_START(MS5637_ADDR, r_buffer+6, p_buffer+12, 2)

#define MS5637_CMD_TEMP_REG \
{                                          \
	CMD_START_D2(BARO_LEVEL)               \
}

#define MS5637_CMD_TEMP(p_cmd) \
 		I2C_WRITE   (MS5637_ADDR, p_cmd, 1)

#define MS5637_READ_TEMP_REG \
{                                          \
	CMD_READ_ADC,                          \
	CMD_START_D2(BARO_LEVEL)               \
}

#define MS5637_READ_TEMP(p_buffer, p_cmd) \
		I2C_READ_REG_REP_START(MS5637_ADDR, p_cmd, p_buffer, 3), \
 		I2C_WRITE(MS5637_ADDR, p_cmd+1, 1)

#define MS5637_READ_PRESS_REG \
{                                          \
	CMD_READ_ADC,                          \
	CMD_START_D1(BARO_LEVEL)               \
}

#define MS5637_READ_PRESS(p_buffer, p_cmd) \
		I2C_READ_REG_REP_START(MS5637_ADDR, p_cmd, p_buffer, 3), \
 		I2C_WRITE(MS5637_ADDR, p_cmd+1, 1)

/*=========================================================================*/



class MS5637 {
 public:
  MS5637();
  void init(void);
  bool setCx(ms5637_handle_t *_handle);

  /* Update both temperature and pressure together. This takes less
     time than calling each function separately (as pressure result
     depends on temperature.) Returns true for success, false on an
     error */

  void refresh(ms5637_handle_t *_handle);
  bool computeTempAndPressure(int32_t d1, int32_t d2);

  uint32_t reset();

  inline bool isOK() { return initialised && m_err == 0; }

  float m_temperature, m_pressure;

private:
  bool initialised;
  int8_t m_err;
  uint16_t c1,c2,c3,c4,c5,c6; // Calibration constants used in producing results

  bool crc_check(uint16_t *n_prom, uint8_t crc);
  uint32_t takeReading(uint8_t trigger_cmd, BaroOversampleLevel oversample_level=BARO_LEVEL);

  bool wireWriteByte(uint8_t val);
  int wireReadDataBlock(uint8_t reg, uint8_t *val, unsigned int len);
};


#endif /* LIBRARIES_MS5637_H_ */