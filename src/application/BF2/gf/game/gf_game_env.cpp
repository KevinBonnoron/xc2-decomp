#include "gf/game/gf_game_env.h"

#include "framework/framework.h"
#include "fw/fw_update_info.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_obj.h"

namespace gf {
struct GF_LP_HANDLE;

static void applyLayerPause(u32 layer, bool isPause) {
  if (fw::Framework::isLayerPause(layer) != isPause) {
    fw::Framework::setLayerPause(layer, isPause);
    GfObjLayerSpeed::reqApplyModelLayerSpeed(layer, isPause ? 0.0f : 1.0f);
    GfEvent::callLayerPause(layer, isPause);
  }
}

GfLayerPause::GfLayerPause(const GfSetupParam &param)
    : section4PauseBits(0), section1PauseBits(0), section7PauseBits(0), section10PauseBits(0), section0PauseBits(0),
      section4Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)), section0Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)),
      section1Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)), section7Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)),
      section10Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)) {
  initialize(param);
}

void GfLayerPause::initialize(const GfSetupParam &) { initialized = true; }

GfLayerPause::~GfLayerPause() {}

void GfLayerPause::build(const GfSetupParam &param) {
  // __LINE__ must be 108 as in the original file: its value changes the instruction order.
#line 108
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfLayerPause(param);
}

void GfLayerPause::destroy() {
  GfLayerPause *layerPause = get();
  layerPause->finalize();
  delete layerPause;
}

void GfLayerPause::finalize() { initialized = false; }

bool GfLayerPause::isInitialized() { return get() != nullptr && get()->initialized; }

void GfLayerPause::update(const fw::UpdateInfo &) {}

void GfLayerPause::gevPause(u32 resumeBits, u32 pauseBits) {
  GfLayerPause *layerPause = get();
  if ((resumeBits & PAUSE_BIT_SYSTEM) != 0) {
    destroyLayerPause(layerPause->section4Handle);
    destroyLayerPause(layerPause->section0Handle);
    destroyLayerPause(layerPause->section1Handle);
    destroyLayerPause(layerPause->section7Handle);
  } else if ((pauseBits & PAUSE_BIT_SYSTEM) != 0) {
    layerPause->section4Handle = setLayerPause(4);
    layerPause->section0Handle = setLayerPause(0);
    layerPause->section1Handle = setLayerPause(1);
    layerPause->section7Handle = setLayerPause(7);
  }
  if ((resumeBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    destroyLayerPause(layerPause->section10Handle);
  } else if ((pauseBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    layerPause->section10Handle = setLayerPause(10);
  }
}

void GfLayerPause::destroyLayerPause(GF_LP_HANDLE *&handle) {
  if (handle == reinterpret_cast<GF_LP_HANDLE *>(-1)) {
    return;
  }
  u32 value = reinterpret_cast<u64>(handle);
  u32 index = value >> 8;
  u32 layer = value & 0xff;
  u32 *pauseBits = get()->getPauseBits(layer);
  *pauseBits &= ~(1 << index);
  if (*pauseBits == 0) {
    applyLayerPause(layer, false);
    if (layer != 0) {
      applyLayerPause(layer + 1, false);
      applyLayerPause(layer + 2, false);
    }
  }
  handle = reinterpret_cast<GF_LP_HANDLE *>(-1);
}

GF_LP_HANDLE *GfLayerPause::setLayerPause(u32 layer) {
  u32 *pauseBits = get()->getPauseBits(layer);
  u32 index;
  u32 bit = 1;
  for (index = 0; index < 32; index++) {
    if ((*pauseBits & bit) == 0) {
      break;
    }
    bit <<= 1;
  }
  if (index >= 32) {
    return reinterpret_cast<GF_LP_HANDLE *>(-1);
  }
  *pauseBits |= bit;
  if (layer != 0) {
    applyLayerPause(layer + 1, true);
    applyLayerPause(layer + 2, true);
  }
  applyLayerPause(layer, true);
  return reinterpret_cast<GF_LP_HANDLE *>(static_cast<u64>(layer | index << 8));
}

void GfLayerPause::destroyLayerPause() {
  GfLayerPause *layerPause = get();
  destroyLayerPause(layerPause->section4Handle);
  destroyLayerPause(layerPause->section0Handle);
  destroyLayerPause(layerPause->section1Handle);
  destroyLayerPause(layerPause->section7Handle);
  destroyLayerPause(layerPause->section10Handle);
}

bool GfLayerPause::isLayerPause(u32 layer) { return fw::Framework::isLayerPause(layer); }

constexpr f32 MIN_LAYER_SPEED = 1e-06f;

GfGameSpeed::GfGameSpeed(const GfSetupParam &param) : intervalSpeed(1.0f), intervalTime(0.0f) { initialize(param); }

void GfGameSpeed::initialize(const GfSetupParam &) { initialized = true; }

GfGameSpeed::~GfGameSpeed() {}

void GfGameSpeed::build(const GfSetupParam &param) {
  // __LINE__ must be 347 as in the original file: its value changes the instruction order.
#line 347
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameSpeed(param);
  setGlobalSpeed(param.globalSpeed);
}

void GfGameSpeed::setGlobalSpeed(f32 speed) { get()->setSpeed(GF_SPEED_GLOBAL, speed); }

void GfGameSpeed::destroy() {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->finalize();
  delete gameSpeed;
}

void GfGameSpeed::finalize() { initialized = false; }

bool GfGameSpeed::isInitialized() { return get() != nullptr && get()->initialized; }

void GfGameSpeed::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->updateFrameSpeed(info);
  }
}

void GfGameSpeed::updateFrameSpeed(const fw::UpdateInfo &info) {
  bool isInterval = false;
  if (intervalTime > 0.0f) {
    intervalTime -= info.deltaTime;
    if (intervalTime <= 0.0f) {
      intervalSpeed = speeds[GF_SPEED_LAYER_4].original;
      intervalTime = 0.0f;
    }
    isInterval = true;
  }
  if (speeds[GF_SPEED_LAYER_1].apply || speeds[GF_SPEED_LAYER_4].apply || speeds[GF_SPEED_PLAY].apply || isInterval) {
    speeds[GF_SPEED_LAYER_1].apply = false;
    speeds[GF_SPEED_LAYER_4].apply = false;
    speeds[GF_SPEED_PLAY].apply = false;
    speeds[GF_SPEED_PLAY].current = speeds[GF_SPEED_PLAY].original;
    const f32 &speed4 = isInterval ? intervalSpeed : speeds[GF_SPEED_LAYER_4].original;
    f32 speed = speed4 * salvageSpeeds[GF_SPEED_LAYER_4].original * speeds[GF_SPEED_PLAY].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    const f32 &speed1 = isInterval ? intervalSpeed : speeds[GF_SPEED_LAYER_1].original;
    f32 speedLayer1 = speed1 * salvageSpeeds[GF_SPEED_LAYER_1].original * salvageSpeeds[GF_SPEED_PLAY].original;
    if (speedLayer1 <= 0.0f) {
      speedLayer1 = MIN_LAYER_SPEED;
    }
    fw::Framework::setLayerUpdateSpeed(0, speed);
    speeds[GF_SPEED_LAYER_0].current = speed;
    fw::Framework::setLayerUpdateSpeed(4, speed);
    speeds[GF_SPEED_LAYER_4].current = speed;
    fw::Framework::setLayerUpdateSpeed(5, speed);
    fw::Framework::setLayerUpdateSpeed(6, speed);
    fw::Framework::setLayerUpdateSpeed(1, speedLayer1);
    speeds[GF_SPEED_LAYER_1].current = speed;
    fw::Framework::setLayerUpdateSpeed(2, speedLayer1);
    fw::Framework::setLayerUpdateSpeed(3, speedLayer1);
  }
  if (speeds[GF_SPEED_LAYER_7].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_7].original * salvageSpeeds[GF_SPEED_LAYER_7].original;
    speeds[GF_SPEED_LAYER_7].apply = false;
    fw::Framework::setLayerUpdateSpeed(7, speed);
    speeds[GF_SPEED_LAYER_7].current = speed;
    fw::Framework::setLayerUpdateSpeed(8, speed);
    fw::Framework::setLayerUpdateSpeed(9, speed);
  }
  if (speeds[GF_SPEED_LAYER_10].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_10].original * salvageSpeeds[GF_SPEED_LAYER_10].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    speeds[GF_SPEED_LAYER_10].apply = false;
    fw::Framework::setLayerUpdateSpeed(10, speed);
    speeds[GF_SPEED_LAYER_10].current = speed;
    fw::Framework::setLayerUpdateSpeed(11, speed);
    fw::Framework::setLayerUpdateSpeed(12, speed);
  }
  if (speeds[GF_SPEED_LAYER_0].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_0].original * salvageSpeeds[GF_SPEED_LAYER_0].original * speeds[GF_SPEED_PLAY].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    speeds[GF_SPEED_LAYER_0].apply = false;
    fw::Framework::setLayerUpdateSpeed(0, speed);
    speeds[GF_SPEED_LAYER_0].current = speed;
  }
  if (speeds[GF_SPEED_GLOBAL].apply) {
    speeds[GF_SPEED_GLOBAL].current = speeds[GF_SPEED_GLOBAL].original;
    speeds[GF_SPEED_GLOBAL].apply = false;
    f32 speed = speeds[GF_SPEED_GLOBAL].current;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    fw::Framework::setUpdateSpeed(speed);
  }
}

void GfGameSpeed::clear() {
  if (get() != nullptr) {
    get()->intervalSpeed = 1.0f;
    get()->intervalTime = 0.0f;
  }
}

void GfGameSpeed::setIntervalSpeed(f32 speed, f32 time) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->intervalSpeed = speed;
  gameSpeed->intervalTime = time;
}

void GfGameSpeed::setSpeed(GF_SPEED type, f32 speed) {
  f32 value = speed < 0.0f ? 1.0f : speed;
  if (speeds[type].original != value) {
    speeds[type].original = value;
    speeds[type].apply = true;
  }
}

f32 GfGameSpeed::getLayerSpeed(u32 layer) {
  GfGameSpeed *gameSpeed = get();
  switch (layer) {
  case 0:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_0);
  case 1:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_1);
  case 4:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_4);
  case 7:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_7);
  case 10:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_10);
  }
  return 1.0f;
}

f32 GfGameSpeed::getSpeed(GF_SPEED type) { return speeds[type].current; }

f32 GfGameSpeed::getOriginalLayerSpeed(u32 layer) {
  GfGameSpeed *gameSpeed = get();
  switch (layer) {
  case 0:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_0);
  case 1:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_1);
  case 4:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_4);
  case 7:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_7);
  case 10:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_10);
  }
  return 1.0f;
}

f32 GfGameSpeed::getOriginalSpeed(GF_SPEED type) { return speeds[type].original; }

f32 GfGameSpeed::getGlobalSpeed() {
  if (get() != nullptr) {
    return get()->getSpeed(GF_SPEED_GLOBAL);
  }
  return 0.0f;
}

void GfGameSpeed::setPlaySpeed(f32 speed) { get()->setSpeed(GF_SPEED_PLAY, speed); }

f32 GfGameSpeed::getPlaySpeed() {
  if (get() != nullptr) {
    return get()->getSpeed(GF_SPEED_PLAY);
  }
  return 0.0f;
}

bool GfGameSpeed::isApplySpeed(GF_SPEED type) { return speeds[type].apply; }

f32 GfGameSpeed::getSpeedSalvage(GF_SPEED type) { return salvageSpeeds[type].original; }

void GfGameSpeed::setSalvageSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_4].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_4].apply = true;
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_7].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_7].apply = true;
}

void GfGameSpeed::setSalvageCharacterSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_7].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_7].apply = true;
}

} // namespace gf
