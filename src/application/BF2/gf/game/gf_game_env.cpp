#include "gf/game/gf_game_env.h"

#include "framework/framework.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_speed.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"

namespace gf {

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
