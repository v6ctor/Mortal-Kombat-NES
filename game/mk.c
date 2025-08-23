#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "neslib.h"
#include <nes.h>
//#link "chr_generic.s"
#include "bcd.h"
//#link "bcd.c"
#include "vrambuf.h"
//#link "vrambuf.c"
#include "assets.h"
//#link "famitone2.s"
//#link "music.s"
//#link "hit-sfx.s"

#define NUM_ACTORS 2

#define DEF_METASPRITE_3x4_FLIP(name, code, pal)\
const unsigned char name[]={\
	  8,-23,(code),pal|OAM_FLIP_H,\
	  0,-23,(code)+1,pal|OAM_FLIP_H,\
	 -8,-23,(code)+2,pal|OAM_FLIP_H,\
	  8,-16,(code)+3,pal|OAM_FLIP_H,\
	  0,-16,(code)+4,pal|OAM_FLIP_H,\
	 -8,-16,(code)+5,pal|OAM_FLIP_H,\
	  8, -8,(code)+6,pal|OAM_FLIP_H,\
	  0, -8,(code)+7,pal|OAM_FLIP_H,\
	 -8, -8,(code)+8,pal|OAM_FLIP_H,\
	  8,  0,(code)+9,pal|OAM_FLIP_H,\
	  0,  0,(code)+10,pal|OAM_FLIP_H,\
	 -8,  0,(code)+11,pal|OAM_FLIP_H,\
	0x80\
};

#define DEF_METASPRITE_3x4(name, code, pal)\
const unsigned char name[]={\
	- 8,-23,(code),pal,\
          0,-23,(code)+1,pal,\
	  8,-23,(code)+2,pal,\
	- 8,-16,(code)+3,pal,\
	  0,-16,(code)+4,pal,\
	  8,-16,(code)+5,pal,\
	- 8,- 8,(code)+6,pal,\
	  0,- 8,(code)+7,pal,\
	  8,- 8,(code)+8,pal,\
	- 8,  0,(code)+9,pal,\
	  0,  0,(code)+10,pal,\
	  8,  0,(code)+11,pal,\
          0x80\
};

#define DEF_METASPRITE_4x4(name, pal)\
const unsigned char name[]={\
	-16,-16,0x0c,pal,\
	- 8,-16,0x0d,pal,\
  	0,-16,0x0e,pal,\
  	8,-16,0x0f,pal,\
	-16,- 8,0x1c,pal,\
	- 8,- 8,0x1d,pal,\
  	0,- 8,0x1e,pal,\
  	8,- 8,0x1f,pal,\
	-16,  0,0x2c,pal,\
	- 8,  0,0x2d,pal,\
  	0,  0,0x2e,pal,\
  	8,  0,0x2f,pal,\
	-16,  8,0x3c,pal,\
	- 8,  8,0x3d,pal,\
  	0,  8,0x3e,pal,\
  	8,  8,0x3f,pal,\
	0x80\
};

#define DEF_METASPRITE_4x4_FLIP(name, pal)\
const unsigned char name[]={\
	16,-16,0x0c,pal|OAM_FLIP_H,\
	8,-16,0x0d,pal|OAM_FLIP_H,\
  	0,-16,0x0e,pal|OAM_FLIP_H,\
  	- 8,-16,0x0f,pal|OAM_FLIP_H,\
	16,- 8,0x1c,pal|OAM_FLIP_H,\
	8,- 8,0x1d,pal|OAM_FLIP_H,\
  	0,- 8,0x1e,pal|OAM_FLIP_H,\
  	-8,- 8,0x1f,pal|OAM_FLIP_H,\
	16,  0,0x2c,pal|OAM_FLIP_H,\
	8,  0,0x2d,pal|OAM_FLIP_H,\
  	0,  0,0x2e,pal|OAM_FLIP_H,\
  	-8,  0,0x2f,pal|OAM_FLIP_H,\
	16,  8,0x3c,pal|OAM_FLIP_H,\
	8,  8,0x3d,pal|OAM_FLIP_H,\
  	0,  8,0x3e,pal|OAM_FLIP_H,\
  	-8,  8,0x3f,pal|OAM_FLIP_H,\
	0x80\
};

#define DEF_METASPRITE_4x2(name, pal)\
const unsigned char name[]={\
	-16,- 8,0x80,pal,\
	- 8,- 8,0x81,pal,\
	  0,- 8,0x82,pal,\
	  8,- 8,0x83,pal,\
	-16,  0,0x90,pal,\
	- 8,  0,0x91,pal,\
	  0,  0,0x92,pal,\
	  8,  0,0x93,pal,\
	0x80\
};

#define DEF_METASPRITE_4x2_FLIP(name, pal)\
const unsigned char name[]={\
	16,- 8,0x80,pal|OAM_FLIP_H,\
	8,- 8,0x81,pal|OAM_FLIP_H,\
	  0,- 8,0x82,pal|OAM_FLIP_H,\
	  -8,- 8,0x83,pal|OAM_FLIP_H,\
	16,  0,0x90,pal|OAM_FLIP_H,\
	8,  0,0x91,pal|OAM_FLIP_H,\
	  0,  0,0x92,pal|OAM_FLIP_H,\
	  -8,  0,0x93,pal|OAM_FLIP_H,\
	0x80\
};

#define DEF_METASPRITE_8x4(name, pal)\
const unsigned char name[]={\
	-32,-16,0xc0,pal,\
	-24,-16,0xc1,pal,\
	-16,-16,0xc2,pal,\
	- 8,-16,0xc3,pal,\
	  0,-16,0xc4,pal,\
	  8,-16,0xc5,pal,\
	 16,-16,0xc6,pal,\
	 24,-16,0xc7,pal,\
	-32,- 8,0xd0,pal,\
	-24,- 8,0xd1,pal,\
	-16,- 8,0xd2,pal,\
	- 8,- 8,0xd3,pal,\
	  0,- 8,0xd4,pal,\
	  8,- 8,0xd5,pal,\
	 16,- 8,0xd6,pal,\
	 24,- 8,0xd7,pal,\
	-32,  0,0xe0,pal,\
	-24,  0,0xe1,pal,\
	-16,  0,0xe2,pal,\
	- 8,  0,0xe3,pal,\
	  0,  0,0xe4,pal,\
	  8,  0,0xe5,pal,\
	 16,  0,0xe6,pal,\
	 24,  0,0xe7,pal,\
	-32,  8,0xf0,pal,\
	-24,  8,0xf1,pal,\
	-16,  8,0xf2,pal,\
	- 8,  8,0xf3,pal,\
	  0,  8,0xf4,pal,\
	  8,  8,0xf5,pal,\
	 16,  8,0xf6,pal,\
	 24,  8,0xf7,pal,\
	0x80\
};

#define DEF_METASPRITE_8x4_FLIP(name, pal)\
const unsigned char name[]={\
	32,-16,0xc0,pal|OAM_FLIP_H,\
	24,-16,0xc1,pal|OAM_FLIP_H,\
	16,-16,0xc2,pal|OAM_FLIP_H,\
	8,-16,0xc3,pal|OAM_FLIP_H,\
	  0,-16,0xc4,pal|OAM_FLIP_H,\
	  -8,-16,0xc5,pal|OAM_FLIP_H,\
	 -16,-16,0xc6,pal|OAM_FLIP_H,\
	 -24,-16,0xc7,pal|OAM_FLIP_H,\
	32,- 8,0xd0,pal|OAM_FLIP_H,\
	24,- 8,0xd1,pal|OAM_FLIP_H,\
	16,- 8,0xd2,pal|OAM_FLIP_H,\
	8,- 8,0xd3,pal|OAM_FLIP_H,\
	  0,- 8,0xd4,pal|OAM_FLIP_H,\
	  -8,- 8,0xd5,pal|OAM_FLIP_H,\
	 -16,- 8,0xd6,pal|OAM_FLIP_H,\
	 -24,- 8,0xd7,pal|OAM_FLIP_H,\
	32,  0,0xe0,pal|OAM_FLIP_H,\
	24,  0,0xe1,pal|OAM_FLIP_H,\
	16,  0,0xe2,pal|OAM_FLIP_H,\
	8,  0,0xe3,pal|OAM_FLIP_H,\
	  0,  0,0xe4,pal|OAM_FLIP_H,\
	  -8,  0,0xe5,pal|OAM_FLIP_H,\
	 -16,  0,0xe6,pal|OAM_FLIP_H,\
	 -24,  0,0xe7,pal|OAM_FLIP_H,\
	32,  8,0xf0,pal|OAM_FLIP_H,\
	24,  8,0xf1,pal|OAM_FLIP_H,\
	16,  8,0xf2,pal|OAM_FLIP_H,\
	8,  8,0xf3,pal|OAM_FLIP_H,\
	  0,  8,0xf4,pal|OAM_FLIP_H,\
	  -8,  8,0xf5,pal|OAM_FLIP_H,\
	 -16,  8,0xf6,pal|OAM_FLIP_H,\
	 -24,  8,0xf7,pal|OAM_FLIP_H,\
	0x80\
};


#define DEF_METASPRITE_8x4x2(name, pal)\
const unsigned char name[]={\
	-28,-16,0x74,pal,\
	-20,-16,0x75,pal,\
	-12,-16,0x76,pal,\
	- 4,-16,0x77,pal,\
	  4,-16,0x78,pal,\
	 12,-16,0x79,pal,\
	 20,-16,0x7a,pal,\
	-28,- 8,0x84,pal,\
	-20,- 8,0x85,pal,\
	-12,- 8,0x86,pal,\
	- 4,- 8,0x87,pal,\
	  4,- 8,0x88,pal,\
	 12,- 8,0x89,pal,\
	 20,- 8,0x8a,pal,\
	-28,  0,0x94,pal,\
	-20,  0,0x95,pal,\
	-12,  0,0x96,pal,\
	- 4,  0,0x97,pal,\
	  4,  0,0x98,pal,\
	 12,  0,0x99,pal,\
	 20,  0,0x9a,pal,\
	-28,  8,0xa4,pal,\
	-20,  8,0xa5,pal,\
	-12,  8,0xa6,pal,\
	- 4,  8,0xa7,pal,\
	  4,  8,0xa8,pal,\
	 12,  8,0xa9,pal,\
	 20,  8,0xaa,pal,\
	0x80\
};

#define DEF_METASPRITE_8x4x2_FLIP(name, pal)\
const unsigned char name[]={\
	28,-16,0x74,pal|OAM_FLIP_H,\
	20,-16,0x75,pal|OAM_FLIP_H,\
	12,-16,0x76,pal|OAM_FLIP_H,\
	4,-16,0x77,pal|OAM_FLIP_H,\
	  -4,-16,0x78,pal|OAM_FLIP_H,\
	 -12,-16,0x79,pal|OAM_FLIP_H,\
	 -20,-16,0x7a,pal|OAM_FLIP_H,\
	28,- 8,0x84,pal|OAM_FLIP_H,\
	20,- 8,0x85,pal|OAM_FLIP_H,\
	12,- 8,0x86,pal|OAM_FLIP_H,\
	4,- 8,0x87,pal|OAM_FLIP_H,\
	  -4,- 8,0x88,pal|OAM_FLIP_H,\
	 -12,- 8,0x89,pal|OAM_FLIP_H,\
	 -20,- 8,0x8a,pal|OAM_FLIP_H,\
	28,  0,0x94,pal|OAM_FLIP_H,\
	20,  0,0x95,pal|OAM_FLIP_H,\
	12,  0,0x96,pal|OAM_FLIP_H,\
	4,  0,0x97,pal|OAM_FLIP_H,\
	  -4,  0,0x98,pal|OAM_FLIP_H,\
	 -12,  0,0x99,pal|OAM_FLIP_H,\
	 -20,  0,0x9a,pal|OAM_FLIP_H,\
	28,  8,0xa4,pal|OAM_FLIP_H,\
	20,  8,0xa5,pal|OAM_FLIP_H,\
	12,  8,0xa6,pal|OAM_FLIP_H,\
	4,  8,0xa7,pal|OAM_FLIP_H,\
	  -4,  8,0xa8,pal|OAM_FLIP_H,\
	 -12,  8,0xa9,pal|OAM_FLIP_H,\
	 -20,  8,0xaa,pal|OAM_FLIP_H,\
	0x80\
};


#define DEF_METASPRITE_4x4x2(name, pal)\
const unsigned char name[]={\
	-16,-12,0x8b,pal,\
	- 8,-12,0x8c,pal,\
	  0,-12,0x8d,pal,\
	  8,-12,0x8e,pal,\
	-16,- 4,0x9b,pal,\
	- 8,- 4,0x9c,pal,\
	  0,- 4,0x9d,pal,\
	  8,- 4,0x9e,pal,\
	-16,  4,0xab,pal,\
	- 8,  4,0xac,pal,\
	  0,  4,0xad,pal,\
	  8,  4,0xae,pal,\
	0x80\
};

#define DEF_METASPRITE_4x4x2_FLIP(name, pal)\
const unsigned char name[]={\
	16,-12,0x8b,pal|OAM_FLIP_H,\
	8,-12,0x8c,pal|OAM_FLIP_H,\
	  0,-12,0x8d,pal|OAM_FLIP_H,\
	  -8,-12,0x8e,pal|OAM_FLIP_H,\
	16,- 4,0x9b,pal|OAM_FLIP_H,\
	8,- 4,0x9c,pal|OAM_FLIP_H,\
	  0,- 4,0x9d,pal|OAM_FLIP_H,\
	  -8,- 4,0x9e,pal|OAM_FLIP_H,\
	16,  4,0xab,pal|OAM_FLIP_H,\
	8,  4,0xac,pal|OAM_FLIP_H,\
	  0,  4,0xad,pal|OAM_FLIP_H,\
	  -8,  4,0xae,pal|OAM_FLIP_H,\
	0x80\
};


#define DEF_METASPRITE_3x4x3(name, pal)\
const unsigned char name[]={\
	-16,-12,0x8b,pal,\
	- 8,-12,0x8c,pal,\
  	0,-12,0x8d,pal,\
  	8,-12,0x8e,pal,\
	-16,- 4,0x9b,pal,\
	- 8,- 4,0x9c,pal,\
  	0,- 4,0x9d,pal,\
  	8,- 4,0x9e,pal,\
	-16,  4,0xab,pal,\
	- 8,  4,0xac,pal,\
  	0,  4,0xad,pal,\
  	8,  4,0xae,pal,\
	0x80\
};

#define DEF_METASPRITE_3x4x3_FLIP(name, pal)\
const unsigned char name[]={\
	16,-12,0x8b,pal|OAM_FLIP_H,\
	8,-12,0x8c,pal|OAM_FLIP_H,\
  	0,-12,0x8d,pal|OAM_FLIP_H,\
  	-8,-12,0x8e,pal|OAM_FLIP_H,\
	16,- 4,0x9b,pal|OAM_FLIP_H,\
	8,- 4,0x9c,pal|OAM_FLIP_H,\
  	0,- 4,0x9d,pal|OAM_FLIP_H,\
  	-8,- 4,0x9e,pal|OAM_FLIP_H,\
	16,  4,0xab,pal|OAM_FLIP_H,\
	8,  4,0xac,pal|OAM_FLIP_H,\
  	0,  4,0xad,pal|OAM_FLIP_H,\
  	-8,  4,0xae,pal|OAM_FLIP_H,\
	0x80\
};

#define DEF_METASPRITE_5x2(name, pal)\
const unsigned char name[]={\
	-24,- 8,0xe8,pal,\
	-16,- 8,0xe9,pal,\
	- 8,- 8,0xea,pal,\
	  0,- 8,0xeb,pal,\
	  8,- 8,0xec,pal,\
	 16,- 8,0xed,pal,\
	-24,  0,0xf8,pal,\
	-16,  0,0xf9,pal,\
	- 8,  0,0xfa,pal,\
	  0,  0,0xfb,pal,\
	  8,  0,0xfc,pal,\
	 16,  0,0xfd,pal,\
	0x80\
};

#define DEF_METASPRITE_5x2_FLIP(name, pal)\
const unsigned char name[]={\
	24,- 8,0xe8,pal|OAM_FLIP_H,\
	16,- 8,0xe9,pal|OAM_FLIP_H,\
	8,- 8,0xea,pal|OAM_FLIP_H,\
	  0,- 8,0xeb,pal|OAM_FLIP_H,\
	  -8,- 8,0xec,pal|OAM_FLIP_H,\
	 -16,- 8,0xed,pal|OAM_FLIP_H,\
	24,  0,0xf8,pal|OAM_FLIP_H,\
	16,  0,0xf9,pal|OAM_FLIP_H,\
	8,  0,0xfa,pal|OAM_FLIP_H,\
	  0,  0,0xfb,pal|OAM_FLIP_H,\
	  -8,  0,0xfc,pal|OAM_FLIP_H,\
	 -16,  0,0xfd,pal|OAM_FLIP_H,\
	0x80\
};

#define DEF_METASPRITE_6x2(name, pal)\
const unsigned char name[]={\
	-24,- 8,0xe8,pal,\
	-16,- 8,0xe9,pal,\
	- 8,- 8,0xea,pal,\
	  0,- 8,0xeb,pal,\
	  8,- 8,0xec,pal,\
	 16,- 8,0xed,pal,\
	-24,  0,0xf8,pal,\
	-16,  0,0xf9,pal,\
	- 8,  0,0xfa,pal,\
	  0,  0,0xfb,pal,\
	  8,  0,0xfc,pal,\
	 16,  0,0xfd,pal,\
	0x80\
};

DEF_METASPRITE_3x4(SRStand, 0x00, 0);
DEF_METASPRITE_3x4(SRRun1, 0x40, 0);

DEF_METASPRITE_3x4(SRJump, 0x50, 0);
DEF_METASPRITE_3x4(SRPunch, 0x10, 0);

DEF_METASPRITE_3x4_FLIP(SLStand, 0x00, 0);
DEF_METASPRITE_3x4_FLIP(SLRun1, 0x40, 0);

DEF_METASPRITE_3x4_FLIP(SLJump, 0x50, 0);
DEF_METASPRITE_3x4_FLIP(SLPunch, 0x10, 0);

DEF_METASPRITE_3x4(SRUpperCut, 0x20, 0);
DEF_METASPRITE_3x4_FLIP(SLUpperCut, 0x20, 0);

DEF_METASPRITE_4x4(SRHKick, 0);
DEF_METASPRITE_4x4_FLIP(SLHKick, 0);

DEF_METASPRITE_4x2(SRLKick, 0);
DEF_METASPRITE_4x2_FLIP(SLLKick, 0);

DEF_METASPRITE_8x4(SRFatality, 0);
DEF_METASPRITE_8x4_FLIP(SLFatality, 0);

DEF_METASPRITE_8x4x2(SRFatality_Pull, 0);
DEF_METASPRITE_8x4x2_FLIP(SLFatality_Pull, 0);

DEF_METASPRITE_3x4(ZRStand, 0x00, 1);
DEF_METASPRITE_3x4(ZRRun1, 0x40, 1);

DEF_METASPRITE_3x4(ZRJump, 0x50, 1);
DEF_METASPRITE_3x4(ZRPunch, 0x10, 1);

DEF_METASPRITE_3x4_FLIP(ZLStand, 0x00, 1);
DEF_METASPRITE_3x4_FLIP(ZLRun1, 0x40, 1);

DEF_METASPRITE_3x4_FLIP(ZLJump, 0x50, 1);
DEF_METASPRITE_3x4_FLIP(ZLPunch, 0x10, 1);

DEF_METASPRITE_3x4(ZRUpperCut, 0x20, 1);
DEF_METASPRITE_3x4_FLIP(ZLUpperCut, 0x20, 1);

DEF_METASPRITE_4x4(ZRHKick, 1);
DEF_METASPRITE_4x4_FLIP(ZLHKick, 1);

DEF_METASPRITE_4x2(ZRLKick, 1);
DEF_METASPRITE_4x2_FLIP(ZLLKick, 1);

DEF_METASPRITE_4x4x2(ZRFatality, 1);
DEF_METASPRITE_4x4x2_FLIP(ZLFatality, 1);

DEF_METASPRITE_3x4x3(ZRFatality_Frozen, 1);
DEF_METASPRITE_3x4x3_FLIP(ZLFatality_Frozen, 1);

DEF_METASPRITE_6x2(fight,1);

const unsigned char* const SRunSeq[12] = {
  SLRun1, SLStand, SLRun1,
  SLRun1, SLStand,
  SLRun1,
  SRRun1, SRStand, SRRun1,
  SRRun1, SRStand,
  SRRun1,
};

const unsigned char* const SRRunSeq[3] = {
  SRRun1, SRStand, SRRun1
};

const unsigned char* const SLRunSeq[3] = {
  SLRun1, SLStand, SLRun1
};

const unsigned char* const ZRunSeq[12] = {
  ZLRun1, ZLStand, ZLRun1,
  ZLRun1, ZLStand,
  ZLRun1,
  ZRRun1, ZRStand, ZRRun1,
  ZRRun1, ZRStand,
  ZRRun1,
};

const unsigned char* const ZRRunSeq[3] = {
  ZRRun1, ZRStand, ZRRun1
};

const unsigned char* const ZLRunSeq[3] = {
  ZLRun1, ZLStand, ZLRun1
};

static int gameOver = 0;
static byte time = 0;
static unsigned int t = 0;
static int fight_sign = 0;
static int ice_ballx = 0;
static int ice_bally = 0;
static int ice_balldx = 0;
static int ice_balldy = 0;
static int ice_ballv = 0;

byte actor_x[NUM_ACTORS];	
byte actor_y[NUM_ACTORS];	
sbyte actor_dx[NUM_ACTORS];	
sbyte actor_dy[NUM_ACTORS];
sbyte actor_inair[NUM_ACTORS];	
byte actor_hp[NUM_ACTORS];
byte actor_facingLeft[NUM_ACTORS];
byte actor_punching[NUM_ACTORS];
byte actor_high_kicking[NUM_ACTORS];
byte actor_low_kicking[NUM_ACTORS];
byte actor_uppercut[NUM_ACTORS];
int actor_s_fatality;
int actor_z_fatality;
byte actor_stunned[NUM_ACTORS];
byte actor_combo[NUM_ACTORS];
byte actor_combo_timer[NUM_ACTORS];


void setup_graphics() {
  oam_clear();
  pal_all(PALETTE);
  vram_adr(NAMETABLE_A + 30*32);
  vram_write(ATTRIBUTE_TABLE, sizeof(ATTRIBUTE_TABLE));
  ppu_on_all(); 
}

void draw_scoreboard(char *id) {
  byte temp = 153 - time;
  *id = oam_spr(8*15, 16, '0'+(temp >> 4), 3, *id);
  *id = oam_spr(8*16, 16, '0'+(temp & 0xf), 3, *id);
  
  temp = 153 - actor_hp[0];
  *id = oam_spr(8*3, 16, '0'+(temp >> 4), 3, *id);
  *id = oam_spr(8*4, 16, '0'+(temp & 0xf), 3, *id);
  
  temp = 153 - actor_hp[1];
  *id = oam_spr(8*27, 16, '0'+(temp >> 4), 3, *id);
  *id = oam_spr(8*28, 16, '0'+(temp & 0xf), 3, *id);
  
   if (actor_combo[0] > 0) {
    *id = oam_spr(actor_x[0], actor_y[0] - 30, '0'+(actor_combo[0] & 0xf), 3, *id);
  }

  if (actor_combo[1] > 0) {
    *id = oam_spr(actor_x[1], actor_y[1] - 30, '0'+(actor_combo[1] & 0xf), 3, *id);
  }
}

void movePlayers(char trigger, char pad) {
  int i;

  for (i=0; i<2; i++) {
	trigger = pad_trigger(i);
    pad = pad_state(i);

    if (pad&PAD_LEFT && actor_x[i]>0 && !actor_inair[i]) {
      
    	actor_dx[i]=-2;
    	actor_facingLeft[i] = 1;
    } else if (pad&PAD_RIGHT && actor_x[i]<240 && !actor_inair[i]) {
      
    	actor_dx[i]=2;
    	actor_facingLeft[i] = 0;
    }
    else if (actor_y[i] > 20*8) actor_dx[i]=0;

    if (trigger&PAD_B && actor_y[i]>20*8) {
    	actor_dy[i] += -10;
    	actor_inair[i] = 1;
    }

    if (actor_dy[i] < 1) actor_dy[i] += 2;

	if (trigger&PAD_A && trigger&PAD_RIGHT && trigger&PAD_UP && !actor_stunned[i]) {
		sfx_play(0, 1);
		actor_high_kicking[i] = 1;
		if (abs(actor_x[i] - actor_x[!i]) < 24) {
        	actor_hp[!i] = bcd_add(actor_hp[!i],7+actor_combo[i]);
			actor_stunned[!i] = 1;

			if (actor_x[i] < actor_x[!i]) {
          		actor_x[!i] += 7;
        	} else {
          		actor_x[!i] -= 7; 
        	}

			if (actor_combo[i] < 5) {
          		actor_combo[i]++;
          		actor_combo_timer[i] = 55;
        	}

        	actor_combo[!i] = 0;
		} else {
			actor_combo[i] = 0;
		}
  	} else if (trigger&PAD_A && pad&PAD_DOWN && !actor_stunned[i]) {
		sfx_play(0, 1);
		actor_low_kicking[i] = 1;
		if (abs(actor_x[i] - actor_x[!i]) < 24) {
        	actor_hp[!i] = bcd_add(actor_hp[!i],7+actor_combo[i]);
			actor_stunned[!i] = 1;

			if (actor_x[i] < actor_x[!i]) {
          		actor_x[!i] += 7;
        	} else {
          		actor_x[!i] -= 7; 
        	}

			if (actor_combo[i] < 5) {
          		actor_combo[i]++;
          		actor_combo_timer[i] = 55;
        	}

        	actor_combo[!i] = 0;
		} else {
			actor_combo[i] = 0;
		}
  	} else if (trigger&PAD_A && pad&PAD_UP && !actor_stunned[i]) {
		sfx_play(0, 1);
		actor_uppercut[i] = 1;
		if (abs(actor_x[i] - actor_x[!i]) < 24) {
        	actor_hp[!i] = bcd_add(actor_hp[!i],4+actor_combo[i]);
                actor_stunned[!i] = 1;
                  
	        actor_y[!i] -= 7;
	        actor_inair[!i] = 1;

			if (actor_combo[i] < 5) {
          		actor_combo[i]++;
          		actor_combo_timer[i] = 55;
        	}

        	actor_combo[!i] = 0;
		} else {
			actor_combo[i] = 0;
		}
  	} else if (trigger&PAD_A && !actor_stunned[i]) {
		sfx_play(0, 1);
    	actor_punching[i] = 1;
    	if (abs(actor_x[i] - actor_x[!i]) < 24) {
    		actor_hp[!i] = bcd_add(actor_hp[!i],3+actor_combo[i]);
			actor_stunned[!i] = 1;
        if (actor_x[i] < actor_x[!i]) {
        	actor_x[!i] += 7;
        } else {
        	actor_x[!i] -= 7; 
        }
        
        if (actor_combo[i] < 5) {
        	actor_combo[i]++;
        	actor_combo_timer[i] = 55;
        }

        actor_combo[!i] = 0;

      	} else {
        	actor_combo[i] = 0;
      	}
    }
    
    if (trigger&PAD_SELECT && !actor_stunned[i] && actor_hp[!i] > 45) {
		sfx_play(0, 1);
		if (!i) {
			actor_s_fatality = 1;
		} else {
                  actor_z_fatality = 1;
                  ice_ballv = 1;
                  ice_ballx = actor_x[i];
                  ice_bally = actor_x[i];
                }

		if (abs(actor_x[i] - actor_x[!i]) < 24) {
        	actor_hp[!i] = 101;
			actor_stunned[!i] = 1;

			if (actor_x[i] < actor_x[!i]) {
          		actor_x[!i] += 7;
        	} else {
          		actor_y[!i] -= 7; 
        	}

			if (actor_combo[i] < 5) {
          		actor_combo[i]++;
          		actor_combo_timer[i] = 55;
        	}

        	actor_combo[!i] = 0;
		} else {
			actor_combo[i] = 0;
		}
        }
  }
}

void initGameState() {
  int i;
  for (i=0; i<NUM_ACTORS; i++) {
	actor_x[i] = 20*i*8 + 5*8;
	actor_y[i] = 15*8;
	actor_dx[i] = 0;
	actor_dy[i] = 1;
	actor_inair[i] = 1;
    actor_hp[i] = 0;
    actor_facingLeft[i] = 0;
    actor_punching[i] = 0;
    actor_high_kicking[i] = 0;
    actor_low_kicking[i] = 0;
    actor_uppercut[i] = 0;
    actor_s_fatality = 0;
    actor_z_fatality = 0;
    actor_stunned[i] = 0;
    actor_combo[i] = 0;
  }
  vram_adr(NTADR_A(0,0));
  for (i = 0; i < 32*30; i++) {
    vram_put(nametable[i]);	
  }
}

void renderPlayers(char *oam_id) {
  int i;
  
  if (ice_ballv) {
   ice_ballx += ice_balldx; 
   ice_bally += ice_balldy; 
   *oam_id = oam_spr(ice_ballx, ice_bally, 1, 0x01CE,*oam_id);
    
  }

  for (i=0; i<NUM_ACTORS; i++) {
    int runseq = actor_x[i] % 3;
    
    if (actor_x[i] < actor_x[!i]) {
    	actor_facingLeft[i] = 0;
    } else {
    	actor_facingLeft[i] = 1;
    
    }
    
    if (!i) {
      
      
      if (actor_inair[i]) {
        if (actor_facingLeft[i]) {
      	      *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLJump);
        
        } else {
      	      *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRJump);
        }
        
      } else if (actor_punching[i]) {
      
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLPunch);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRPunch);
        }
      
      } else if (actor_high_kicking[i]) {
    	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLHKick);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRHKick);
        }
        
      } else if (actor_low_kicking[i]) {
    	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLLKick);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRLKick);
        }
        
      } else if (actor_uppercut[i]) {
		if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLUpperCut);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRUpperCut);
        }
        
      } else if (actor_s_fatality) {
		if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLFatality);
            //*oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLFatality_Pull);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRFatality);
            //*oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRFatality_Pull);
        }
    
      } else if (actor_dx[i] == 0) {
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLStand);
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRStand);
        }
      } else {
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SLRunSeq[runseq]);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, SRRunSeq[runseq]);
        }
        
      }
    
      
    } else {
      
      if (actor_inair[i]) {
        if (actor_facingLeft[i]) {
      	      *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLJump);
        
        } else {
      	      *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRJump);
        }
        
      } else if (actor_punching[i]) {
      
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLPunch);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRPunch);
        }
      
      } else if (actor_high_kicking[i]) {
    	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLHKick);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRHKick);
        }
        
      } else if (actor_low_kicking[i]) {
    	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLLKick);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRLKick);
        }
        
      } else if (actor_uppercut[i]) {
	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLUpperCut);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRUpperCut);
        }
        
      } else if (actor_z_fatality) {
	if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLFatality);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRFatality);
        }
    
      } else if (actor_dx[i] == 0) {
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLStand);
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRStand);
        }
        
        
      } else {
        if (actor_facingLeft[i]) {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZLRunSeq[runseq]);
        
        } else {
            *oam_id = oam_meta_spr(actor_x[i], actor_y[i], *oam_id, ZRRunSeq[runseq]);
        }
        
      }
      
    }
    
    actor_x[i] += actor_dx[i];

    if (actor_y[i] > 21*8 && actor_dy[i] > 0) {
      actor_dy[i] = 0;
      actor_inair[i] = 0;
    }
    actor_y[i] += actor_dy[i];
    
    if (t%15==0) {
		actor_punching[i] = 0;
		actor_high_kicking[i] = 0;
		actor_low_kicking[i] = 0;
		actor_uppercut[i] = 0;
	} else if (t % 50 == 0) {
    	actor_s_fatality = 0;
	actor_z_fatality = 0;}
    
  }
}

void updateTime() {
  int i;
  if (t >= 55) {
    t = 0;
    if (time < 153) {
      time = bcd_add(time, 1);
    }
    
    for (i = 0; i<2; i++) {
      actor_stunned[i] = 0;
    }
  }
  
  for (i = 0; i < 2; i++) {
    if (actor_combo_timer[i] > 0) {
      actor_combo_timer[i]--;
    }
    if (actor_combo_timer[i] ==0) {
      actor_combo[i] = 0;
    }
  }
}

void checkGameOver() {

  int i;
  
  byte temp1 = 153 - time;
  byte temp2 = 153 - actor_hp[0];
  byte temp3 = 153 - actor_hp[1];
  
  gameOver = temp1 == 0 || temp2 == 0 || temp3 ==0;
  
    
  if (gameOver) {
    oam_clear();
    
    ppu_off();
    

    if (temp2 == temp3) {
      vram_adr(NTADR_A(0,0));
      for (i = 0; i < 32*30; i++) {
        vram_put(tie[i]);	
      }
      pal_all(tie_pal);
      vram_write(AGO, sizeof(ATTRIBUTE_TABLE));

      
    } else if (temp2 > temp3) {
      
      vram_adr(NTADR_A(0,0));
      for (i = 0; i < 32*30; i++) {
        vram_put(p1[i]);	
      }
      pal_all(scorp_pal);
      vram_write(SCORP_ATT_TABLE, sizeof(ATTRIBUTE_TABLE));

    } else {
      vram_adr(NTADR_A(0,0));
      for (i = 0; i < 32*30; i++) {
        vram_put(p2[i]);	
      }
         pal_all(sub_pal);
         vram_write(SUB_ATT_TABLE, sizeof(ATTRIBUTE_TABLE));

    }
    vram_adr(NAMETABLE_A + 30*32);
    ppu_on_all();
    
  }
}

extern const void music_data[];
extern const void hit_sfx[];

void main(void)
{
  char oam_id;
  char pad;
  char trigger;
  int i;
  int started = 0;
  
  famitone_init(&music_data);
  sfx_init(&hit_sfx);

  music_play(0);
  nmi_set_callback(famitone_update);
  
  vram_adr(NTADR_A(0,0));
  for (i = 0; i < 32*30; i++) {
      vram_put(title_screen[i]);	
  }
  oam_clear();
  pal_all(title_pal);
  vram_adr(NAMETABLE_A + 30*32);
  vram_write(ATTRIBUTE_TABLE, sizeof(ATTRIBUTE_TABLE));
  ppu_on_all(); 
  
  while(started == 0) {
    trigger = pad_trigger(0);
    if (trigger&PAD_B) {
    	started = 1;
    }
    ppu_wait_frame();
  }
  ppu_off();
  
  initGameState();
  setup_graphics();
  ppu_on_all();
  
  while (started) {

    t++;
    
    if (!gameOver) {
        oam_id = 0;
      	
        if (t < 30 && !fight_sign) {
          oam_id = oam_meta_spr(16*8, 15*8, oam_id, fight);
          
        } else {
          fight_sign = 1;
        }

        movePlayers(trigger, pad);

        bank_spr(1);
        renderPlayers(&oam_id);

        draw_scoreboard(&oam_id);

        if (oam_id != 0) oam_hide_rest(oam_id);

        ppu_wait_frame();

        updateTime();
        checkGameOver();
    }

  }
  music_stop();
  
}
