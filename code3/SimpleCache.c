#include "L2_2WCache.h"

Cache1 L1Cache;
Cache2 L2Cache;
uint8_t DRAM[DRAM_SIZE];
uint32_t time;

/**************** Time Manipulation ***************/
void resetTime() { time = 0; }

uint32_t getTime() { return time; }

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t address, uint8_t *data, uint32_t mode) {

  if (address >= DRAM_SIZE - WORD_SIZE + 1)
    exit(-1);

  if (mode == MODE_READ) {
    memcpy(data, &(DRAM[address]), BLOCK_SIZE);
    time += DRAM_READ_TIME;
  }

  if (mode == MODE_WRITE) {
    memcpy(&(DRAM[address]), data, BLOCK_SIZE);
    time += DRAM_WRITE_TIME;
  }
}

/*********************** L1 cache *************************/

void initCache(){
  initCache1();
  initCache2();
}

void initCache1() {
    for(int i = 0; i < L1_LINES; i++) { 
        L1Cache.line[i].Valid = 0;
        L1Cache.line[i].Tag = 0;
        L1Cache.line[i].Dirty = 0;
    }
    L1Cache.init = 1;
}

void initCache2() {
    for(int i = 0; i < L2_LINES; i++) { 
        L2Cache.line[i].Valid = 0;
        L2Cache.line[i].Tag = 0;
        L2Cache.line[i].Dirty = 0;
    }
    L2Cache.init = 1;
}

void accessL1(uint32_t address, uint8_t *data, uint32_t mode) {

  uint32_t offset, index, tag, MemAddress, word_address;
  uint8_t TempBlock[BLOCK_SIZE];

  uint8_t index_bits = 8, offset_bits = 6, offset_byte_bits = 2;

  /* init cache */
  if (L1Cache.init == 0) {
    initCache1();
  }


  tag = address >> (index_bits + offset_bits); // Why do I do this?
  index = (address >> offset_bits) & ((1 << index_bits) - 1);
  offset = address & ((1 << offset_bits) - 1);
  word_address = offset >> offset_byte_bits;

  CacheLine *Line = &L1Cache.line[index];

  MemAddress = address >> offset_bits;
  MemAddress = MemAddress << offset_bits;

  /* access Cache*/

  if (!Line->Valid || Line->Tag != tag) {         // if block not present - miss
    accessL2(MemAddress, TempBlock, MODE_READ); // get new block from DRAM
   
    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      accessL2(MemAddress, &(L1Cache.line[index].words[0]), MODE_WRITE); // then write back old block
    }

    memcpy(&(L1Cache.line[index].words[0]), TempBlock,
           BLOCK_SIZE); // copy new block to cache line
    Line->Valid = 1;
    Line->Tag = tag;
    Line->Dirty = 0;
  } // if miss, then replaced with the correct block

  if (mode == MODE_READ) {    // read data from cache line
    memcpy(data, &L1Cache.line[index].words[word_address * WORD_SIZE], WORD_SIZE);
    time += L1_READ_TIME;
  }

  if (mode == MODE_WRITE) { // write data from cache line
    memcpy(&L1Cache.line[index].words[word_address * WORD_SIZE], data, WORD_SIZE);
    time += L1_WRITE_TIME;
    Line->Dirty = 1;
  }
}

void accessL2(uint32_t address, uint8_t *data, uint32_t mode) {

  uint32_t index, tag, MemAddress;
  uint8_t TempBlock[BLOCK_SIZE];

  uint8_t index_bits = 9, offset_bits = 6;

  /* init cache */
  if (L2Cache.init == 0) {
    initCache2();
  }


  tag = address >> (index_bits + offset_bits); // Why do I do this?
  index = (address >> offset_bits) & ((1 << index_bits) - 1);

  CacheLine *Line = &L2Cache.line[index];

  MemAddress = address >> offset_bits;
  MemAddress = MemAddress << offset_bits;

  /* access Cache*/

  if (!Line->Valid || Line->Tag != tag) {         // if block not present - miss
    accessDRAM(MemAddress, TempBlock, MODE_READ); // get new block from DRAM
   
    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      accessDRAM(MemAddress, &(L2Cache.line[index].words[0]), MODE_WRITE); // then write back old block
    }

    memcpy(&(L2Cache.line[index].words[0]), TempBlock,
           BLOCK_SIZE); // copy new block to cache line
    Line->Valid = 1;
    Line->Tag = tag;
    Line->Dirty = 0;
  } // if miss, then replaced with the correct block

  if (mode == MODE_READ) {    // read data from cache line
    memcpy(data, &L2Cache.line[index].words[0], BLOCK_SIZE);
    time += L2_READ_TIME;
  }

  if (mode == MODE_WRITE) { // write data from cache line
    memcpy(&L2Cache.line[index].words[0], data, BLOCK_SIZE);
    time += L2_WRITE_TIME;
    Line->Dirty = 1;
  }
}

void read(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_READ);
}

void write(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_WRITE);
}
