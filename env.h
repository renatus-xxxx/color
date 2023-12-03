#ifndef __ENV_H__
#define __ENV_H__

#include "libiot.h"

#define SLAVE_ADDR_SHT30   "44"

typedef struct s_env {
  float temp;
  float humi;
} env;

int init_env() {
  int num = iotfindi("device/i2c_a");
  if (num == -1) { return 0; }
  char** str = malloc(sizeof(char*) * num);
  for(int i = 0; i < num; i++) {
    str[i] = malloc(sizeof(char) * 64);
  }
  int cnt = iotfinds("device/i2c_a", str, num);
  int found = 0;
  for(int i = 0; i < num; i++) {
    if (strcmp(str[i], SLAVE_ADDR_SHT30) == 0){
      found = 1;
    }
    free(str[i]);
  }
  free(str);
  return found;
}

void get_env(env* e) { /* https://github.com/m5stack/M5Unit-ENV/blob/master/src/SHT3X.cpp#L10 */
  unsigned char buf[16];
  buf[0] = 0x2C;
  buf[1] = 0x06;
  iotputb("device/i2c_a/" SLAVE_ADDR_SHT30, buf, 2);
  iotgetb("device/i2c_a/" SLAVE_ADDR_SHT30, buf);
  e->temp = ((((buf[0] * 256.0f) + buf[1]) * 175.0f) / 65535.0f) - 45.0f;
  e->humi = ((((buf[3] * 256.0)  + buf[4]) * 100.0f) / 65535.0);
}

#endif