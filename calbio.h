#ifndef __CALBIO_H__
#define __CALBIO_H__

/* From "Introduction to MSX-C" */
/* ISBN: 4-7561-0057-0          */
typedef struct s_regs {
  char     f;
  char     a;
  unsigned bc;
  unsigned de;
  unsigned hl;
} regs;

void calbio(unsigned ad, regs *rg) {
#asm
CALBIO_CALSLT  equ  001ch
CALBIO_EXPTBL  equ  0fcc1h  ;slot address of BIOS ROM
  ld   hl,2
  add  hl,sp
  ld   e,(hl)  ;second param to de
  inc  hl
  ld   d,(hl)
  inc  hl
  ld   c,(hl)  ;first param to hl
  inc  hl
  ld   b,(hl)
  ld   l,c
  ld   h,b
CALBIO01:
  push hl
  pop  ix
  push de
  ex   de,hl
  ld   iy,0
  add  iy,sp
  di
  ld   sp,hl
  pop  af
  pop  bc
  pop  de
  pop  hl
  ei
  ld   sp,iy
  push iy
  ld   iy,(CALBIO_EXPTBL-1)
  call CALBIO_CALSLT
  pop  iy
  exx
  pop  hl
  ld   bc,8
  add  hl,bc
  di
  ld   sp,hl
  exx
  push hl
  push de
  push bc
  push af
  ei
  ld   sp,iy
  pop  af
#endasm
}

#endif