#ifndef L2_2WCACHE_H
#define L2_2WCACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Cache.h"

#define SET_SIZE 2
#define L1_LINES (L1_SIZE / BLOCK_SIZE)
#define L2_LINES (L2_SIZE / BLOCK_SIZE)
#define L2_SETS (L2_LINES / SET_SIZE)

void resetTime();

uint32_t getTime();

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t, uint8_t *, uint32_t);

/*********************** Cache *************************/

void initCache();
void initCache1();
void initCache2();

void accessL1(uint32_t, uint8_t *, uint32_t);
void accessL2(uint32_t, uint8_t *, uint32_t);

typedef struct CacheLine {
  uint8_t Valid;
  uint8_t Dirty;
  uint32_t Tag;
  uint8_t words[BLOCK_SIZE];
} CacheLine;


typedef struct CacheSet{
  uint32_t init;
  CacheLine lines[SET_SIZE];
  uint8_t lru;
} CacheSet;

typedef struct Cache1 {
  uint32_t init;
  CacheLine line[L1_LINES];
} Cache1;

typedef struct Cache2 {
  uint32_t init;
  CacheSet sets[L2_SETS];
} Cache2;

/*********************** Interfaces *************************/

void read(uint32_t, uint8_t *);

void write(uint32_t, uint8_t *);

#endif
