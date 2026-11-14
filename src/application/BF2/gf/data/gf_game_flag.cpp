#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"

namespace gf {

enum {
  FLAG16_UNKNOWN_1 = 1, // Inferred role: flag16 scenario; original name unknown.
};

enum {
  FLAG_UNKNOWN_3336 = 0xd08,     // Inferred role: flag word end; original name unknown.
  FLAG_UNKNOWN_6408 = 0x1908,    // Inferred role: flag short end; original name unknown.
  FLAG_UNKNOWN_88328 = 0x15908,  // Inferred role: flag byte end; original name unknown.
  FLAG_UNKNOWN_153864 = 0x25908, // Inferred role: flag bit end; original name unknown.
};

GfGameFlag::GfGameFlag(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

void GfGameFlag::initialize(const GfSetupParam &) { mInitialized = true; }

GfGameFlag::~GfGameFlag() {}

void GfGameFlag::build(const GfSetupParam &param) {
  // __LINE__ must be 57 as in the original file: its value changes the instruction order.
#line 57
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameFlag(param);
}

void GfGameFlag::destroy() {
  GfGameFlag *gameFlag = get();
  gameFlag->finalize();
  delete gameFlag;
}

void GfGameFlag::finalize() { mInitialized = false; }

bool GfGameFlag::isInitialized() {
  GfGameFlag *gameFlag = get();
  if (gameFlag == nullptr) {
    return false;
  }

  return gameFlag->mInitialized;
}

void GfGameFlag::sendCallback(u32 size, u32 index, u32 value, u32 oldValue) {
  if (size == 16 && index == FLAG16_UNKNOWN_1) {
    GfEvent::callChangeScenarioFlag(value, oldValue);
  }
}

void GfGameFlag::getFlagInfo(int flag, u32 &size, u32 &index) {
  u32 globalIndex = flag;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
    return;
  }

  if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else if (globalIndex < FLAG_UNKNOWN_153864) {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }
}

void GfGameFlag::setFlag(int flag, u32 value) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }

  setLocal(size, index, value);
}

u32 GfGameFlag::getFlag(int flag) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }

  return getLocal(size, index);
}

void GfGameFlag::setLocal(GameFlag &gameFlag, u32 size, int index, u32 value) {
  switch (size) {
  case 1:
    // The game keeps the index assert of this read (bitflag.h line 119) and reuses its word index and mask for the write.
    gameFlag.unknown00.unknown005(index);
    gameFlag.unknown00.unknown006(index, value != 0);
    break;
  case 2: {
    u32 bit = index * 2;
    u32 word = bit >> 5;
    u32 shift = bit & 31;
    gameFlag.unknown2000[word] &= ~(3 << shift);
    gameFlag.unknown2000[word] |= value << shift;
    break;
  }
  case 4: {
    u32 bit = index * 4;
    u32 word = bit >> 5;
    u32 shift = bit & 31;
    gameFlag.unknown6000[word] &= ~(0xf << shift);
    gameFlag.unknown6000[word] |= value << shift;
    break;
  }
  case 8:
    gameFlag.unknown7000[index] = value;
    break;
  case 16:
    gameFlag.unknown9000[index] = value;
    break;
  case 32:
    gameFlag.unknowna800[index] = value;
    break;
  }
}

u32 GfGameFlag::getMaxFlag(int size) {
  switch (size) {
  case 1:
  case 2:
    return 0x10000;
  case 4:
  case 8:
    return 0x2000;
  case 16:
    return 0xc00;
  case 32:
    return 0xd08;
  default:
    return 0;
  }
}

void GfGameFlag::clear() { __builtin_memset(&GfDataManager::getDataGame()->unknownfbbc4, 0, sizeof(GameFlag)); }

} // namespace gf
