// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/camera/plugin/gf_camera_plugin_ship_roll.cpp.
#include "gf/camera/plugin/gf_camera_plugin_ship_roll.h"

#include <math.h>

#include "fw/fw_param_manager.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/game/gf_game_manager.h"
#include "ml/rand.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {

// Inferred role: the plugin pushed on the camera layer; no game symbol, original name unknown.
static mm::mtl::IntrusivePtr<ShipRollPlugin> unknown001;

// Inferred role: ship roll part of the player camera parameters; original type name unknown.
// Layout from ShipRollPlugin::update (1.0.0: 0x71001e5440), which reads the flags at 0x65 and the six values from 0x6c.
struct unknown002 {
  u8 _00[0x65 - 0x00];
  u8 unknown65; // Inferred role: flags, bit 0 selects the sine motion and bit 1 the random amplitude; original member name unknown.
  u8 _66[0x6c - 0x66];
  f32 unknown6c; // Inferred role: smallest roll amplitude in degrees; original member name unknown.
  f32 unknown70; // Inferred role: roll amplitude in degrees; original member name unknown.
  f32 unknown74; // Inferred role: roll speed in degrees; original member name unknown.
  f32 unknown78; // Inferred role: smallest pitch amplitude; original member name unknown.
  f32 unknown7c; // Inferred role: pitch amplitude; original member name unknown.
  f32 unknown80; // Inferred role: pitch speed; original member name unknown.
};

static_assert(offsetof(unknown002, unknown65) == 0x65, "");
static_assert(offsetof(unknown002, unknown6c) == 0x6c, "");
static_assert(offsetof(unknown002, unknown80) == 0x80, "");
static_assert(sizeof(unknown002) == 0x84, "");

ShipRollPlugin::~ShipRollPlugin() {}

void ShipRollPlugin::update(fw::Camera *camera) {
  if (GfGameManager::isPlayerCameraPause() || camera == nullptr) {
    return;
  }

  PlayerCamera *player = mm::mtl::dynamicCast<PlayerCamera>(camera);
  if (player == nullptr) {
    return;
  }

  const unknown002 *param = player->unknownb0.get<unknown002>();
  if ((param->unknown65 & 1) != 0) {
    if (m_rollEnable) {
      unknown28 = param->unknown74 + unknown28;
      if (unknown28 > 360.0f) {
        unknown28 -= 360.0f;
        if ((param->unknown65 & 2) != 0) {
          unknown2c = ml::mtRandf1(param->unknown6c, param->unknown70);
        } else {
          unknown2c = param->unknown70;
        }
      }
      unknown20 = unknown2c * sinf(unknown28 * mm::DEG_TO_RAD) * mm::DEG_TO_RAD;
    } else {
      unknown28 = 0.0f;
      unknown20 = 0.0f;
      unknown2c = param->unknown70;
    }

    if (m_pitchEnable) {
      unknown34 = param->unknown80 + unknown34;
      if (unknown34 > 360.0f) {
        unknown34 -= 360.0f;
        if ((param->unknown65 & 2) != 0) {
          unknown38 = ml::mtRandf1(param->unknown78, param->unknown7c);
        } else {
          unknown38 = param->unknown7c;
        }
      }
      unknown24 = unknown38 * sinf(unknown34 * mm::DEG_TO_RAD);
    } else {
      unknown34 = 0.0f;
      unknown24 = 0.0f;
      unknown38 = param->unknown7c;
    }
  } else {
    unknown28 = 0.0f;
    unknown34 = 0.0f;
    if (m_rollEnable) {
      if (unknown30) {
        unknown20 -= param->unknown74 * mm::DEG_TO_RAD;
        if (unknown20 < -unknown2c * mm::DEG_TO_RAD) {
          unknown30 = false;
          if ((param->unknown65 & 2) != 0) {
            unknown2c = ml::mtRandf1(param->unknown6c, param->unknown70);
          } else {
            unknown2c = param->unknown70;
          }
        }
      } else {
        unknown20 += param->unknown74 * mm::DEG_TO_RAD;
        if (unknown2c * mm::DEG_TO_RAD < unknown20) {
          unknown30 = true;
          if ((param->unknown65 & 2) != 0) {
            unknown2c = ml::mtRandf1(param->unknown6c, param->unknown70);
          } else {
            unknown2c = param->unknown70;
          }
        }
      }
    } else {
      unknown20 = 0.0f;
      unknown2c = param->unknown70;
    }

    if (m_pitchEnable) {
      if (unknown3c) {
        unknown24 -= param->unknown80;
        if (unknown24 < -unknown38) {
          unknown3c = false;
          if ((param->unknown65 & 2) != 0) {
            unknown38 = ml::mtRandf1() * (param->unknown7c - param->unknown78) + param->unknown78;
          } else {
            unknown38 = param->unknown7c;
          }
        }
      } else {
        unknown24 = param->unknown80 + unknown24;
        if (unknown38 < unknown24) {
          unknown3c = true;
          if ((param->unknown65 & 2) != 0) {
            unknown38 = ml::mtRandf1() * (param->unknown7c - param->unknown78) + param->unknown78;
          } else {
            unknown38 = param->unknown7c;
          }
        }
      }
    } else {
      unknown24 = 0.0f;
      unknown38 = param->unknown7c;
    }
  }

  camera->unknown40.y += unknown24;
  camera->unknown50.y += unknown24;
  camera->unknowna4 = unknown20;
  camera->updateViewMatrix();
}

bool ShipRollPlugin::isRollEnable() {
  if (unknown001.get() != nullptr) {
    return unknown001.get()->m_rollEnable;
  }
  return false;
}

bool ShipRollPlugin::isPitchEnable() {
  if (unknown001.get() != nullptr) {
    return unknown001.get()->m_pitchEnable;
  }
  return false;
}

} // namespace gf
