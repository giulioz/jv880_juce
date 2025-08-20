#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <array>
#include <string>

struct RomInfo {
  size_t length;
  std::string filename;
  std::string checksum;
  bool needsUnscramble;
  std::string checksumUnscrambled;
  bool loaded;
};

constexpr size_t romCount = 27;
constexpr size_t romCountRequired = 5;
constexpr size_t romCountChk = 26;
extern RomInfo romInfos[romCount];

int getRomIndex(std::string filename);
bool loadRom(int romI, uint8_t *dst, std::array<uint8_t *, romCount> &cache);
bool preloadAll(std::array<uint8_t *, romCount> &cache);

void unscrambleRom(const uint8_t *src, uint8_t *dst, int len);
