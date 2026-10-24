#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"

namespace gf {

enum {
  FLAG16_SCENARIO = 1,
};

enum {
  FLAG_WORD_END = 0xd08,
  FLAG_SHORT_END = 0x1908,
  FLAG_BYTE_END = 0x15908,
  FLAG_BIT_END = 0x25908,
};

GfGameFlag::GfGameFlag(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

void GfGameFlag::initialize(const GfSetupParam &) { mInitialized = true; }

GfGameFlag::~GfGameFlag() {}

void GfGameFlag::build(const GfSetupParam &param) {
  // __LINE__ must be 57 as in the original file: its value changes the instruction order.
#line 57
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameFlag(param);
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
  if (size == 16 && index == FLAG16_SCENARIO) {
    GfEvent::callChangeScenarioFlag(value, oldValue);
  }
}

void GfGameFlag::getFlagInfo(int flag, u32 &size, u32 &index) {
  u32 globalIndex = flag;
  if (globalIndex < FLAG_WORD_END) {
    size = 32;
    index = flag;
    return;
  }

  if (globalIndex < FLAG_SHORT_END) {
    size = 16;
    index = flag - FLAG_WORD_END;
  } else if (globalIndex < FLAG_BYTE_END) {
    size = 8;
    index = flag - FLAG_SHORT_END;
  } else if (globalIndex < FLAG_BIT_END) {
    size = 1;
    index = flag - FLAG_BYTE_END;
  }
}

void GfGameFlag::setFlag(int flag, u32 value) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_WORD_END) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_SHORT_END) {
    size = 16;
    index = flag - FLAG_WORD_END;
  } else if (globalIndex < FLAG_BYTE_END) {
    size = 8;
    index = flag - FLAG_SHORT_END;
  } else {
    size = 1;
    index = flag - FLAG_BYTE_END;
  }

  setLocal(size, index, value);
}

u32 GfGameFlag::getFlag(int flag) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_WORD_END) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_SHORT_END) {
    size = 16;
    index = flag - FLAG_WORD_END;
  } else if (globalIndex < FLAG_BYTE_END) {
    size = 8;
    index = flag - FLAG_SHORT_END;
  } else {
    size = 1;
    index = flag - FLAG_BYTE_END;
  }

  return getLocal(size, index);
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
