#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaWpnAsm {
public:
  static constexpr size_t QUEUE_COUNT = 8;

  enum MOT {
    MOT_IDLE,
    MOT_NORMAL,
    MOT_BATTLE_START,
    MOT_BATTLE_IDLE,
    MOT_BATTLE_END,
    MOT_BATTLE_MODE_CHANGE,
    MOT_BATTLE_MODE_START,
    MOT_BATTLE_MODE1_START,
    MOT_BATTLE_MODE1,
    MOT_BATTLE_MODE1_END,
    MOT_BATTLE_MODE2_START,
    MOT_BATTLE_MODE2,
    MOT_BATTLE_MODE2_END,
    MOT_BATTLE_MODE3_START,
    MOT_BATTLE_MODE3,
    MOT_BATTLE_MODE3_END,
    MOT_BATTLE_MODE4_START,
    MOT_BATTLE_MODE4,
    MOT_BATTLE_MODE4_END,
    MOT_BATTLE_MODE5_START,
    MOT_BATTLE_MODE5,
    MOT_BATTLE_MODE5_END,
    MOT_SPECIAL,
  };

  enum CMD {
    CMD_NORMAL,
    CMD_BATTLE_START,
    CMD_BATTLE_IDLE,
    CMD_BATTLE_END,
    CMD_BATTLE_MODE1_START,
    CMD_BATTLE_MODE1,
    CMD_BATTLE_MODE1_END,
    CMD_BATTLE_MODE2_START,
    CMD_BATTLE_MODE2,
    CMD_BATTLE_MODE2_END,
    CMD_BATTLE_MODE3_START,
    CMD_BATTLE_MODE3,
    CMD_BATTLE_MODE3_END,
    CMD_BATTLE_MODE4_START,
    CMD_BATTLE_MODE4,
    CMD_BATTLE_MODE4_END,
    CMD_BATTLE_MODE5_START,
    CMD_BATTLE_MODE5,
    CMD_BATTLE_MODE5_END,
    CMD_SPECIAL,
  };

  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_MOUNT = 1 << 1,
    FLAG_LEFT = 1 << 2,
  };

  CharaWpnAsm();
  virtual ~CharaWpnAsm();
  void clear();
  void update(f32 speed);
  static bool isPlayEnd(gf::GfEvtModel *model, bool isLeft);
  static void play(gf::GfEvtModel *model, MOT mot, bool isLeft, void *data);
  static void setSpeed(gf::GfEvtModel *model, f32 speed, bool isLeft);
  void mount(gf::GfEvtModel *model, bool isMount, bool isLeft);
  void execCmd(gf::GfEvtModel *model, CMD cmd, bool isLeft, void *data);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown08 |= flag;
    } else {
      unknown08 &= ~flag;
    }
  }

  u32 unknown08;                                    // Inferred role: flags; original member name unknown.
  gf::GfEvtModel *unknown10;                        // Inferred role: model; original member name unknown.
  void *unknown18;                                  // Inferred role: data; original member name unknown.
  f32 unknown20;                                    // Inferred role: speed; original member name unknown.
  mm::mtl::FixedVector<MOT, QUEUE_COUNT> unknown28; // Inferred role: queue; original member name unknown.
  MOT unknown50;                                    // Inferred role: last mot; original member name unknown.
};

static_assert(sizeof(CharaWpnAsm) == 0x58, "");

} // namespace event
