#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calbio.h"
#include "env.h"

#define FORCLR (char*)(0xF3E9)
#define BAKCLR (char*)(0xF3EA)
#define BDRCLR (char*)(0xF3EB)
#define CHGCLR (char*)(0x0062)

char back_color_from_env() {
  if (init_env()) {
    env e;
    get_env(&e);
    if (e.humi < 40.0f) { /* dry */
      return 5; /* color 15, 5, 7 */
    }
    if (e.humi > 70.0f) { /* wet */
      return 7; /* color 15, 7, 7 */
    }
  }
  return 4;     /* color 15, 4, 7 */
}

void color_from_env() {
  *FORCLR = 15;
  *BAKCLR = back_color_from_env();
  *BDRCLR =  7;
  regs r;
  calbio(CHGCLR, r);
}

void usage() {
  printf("usage: COLOR 15 4 7\n");
  printf("       COLOR /env\n");
}

int main( int argc, char *argv[]) {
  if (argc == 4) {
    *FORCLR = atoi(argv[1]);
    *BAKCLR = atoi(argv[2]);
    *BDRCLR = atoi(argv[3]);
    regs r;
    calbio(CHGCLR, r);
  } else {
    if ((argc == 2) && (strncmp(argv[1], "/env", 4) == 0)) { // using ENV.III on MSX0
      color_from_env();
    } else {
      usage();
    }
  }
  return 0;
}
