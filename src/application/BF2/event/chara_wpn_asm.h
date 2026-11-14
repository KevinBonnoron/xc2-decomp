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
  static constexpr size_t QUEUE_UNKNOWN_8 = 8; // Inferred role: queue count; original name unknown.

  enum MOT {
    MOT_UNKNOWN_0,  // Inferred role: idle; original name unknown.
    MOT_UNKNOWN_1,  // Inferred role: normal; original name unknown.
    MOT_UNKNOWN_2,  // Inferred role: battle start; original name unknown.
    MOT_UNKNOWN_3,  // Inferred role: battle idle; original name unknown.
    MOT_UNKNOWN_4,  // Inferred role: battle end; original name unknown.
    MOT_UNKNOWN_5,  // Inferred role: battle mode change; original name unknown.
    MOT_UNKNOWN_6,  // Inferred role: battle mode start; original name unknown.
    MOT_UNKNOWN_7,  // Inferred role: battle mode1 start; original name unknown.
    MOT_UNKNOWN_8,  // Inferred role: battle mode1; original name unknown.
    MOT_UNKNOWN_9,  // Inferred role: battle mode1 end; original name unknown.
    MOT_UNKNOWN_10, // Inferred role: battle mode2 start; original name unknown.
    MOT_UNKNOWN_11, // Inferred role: battle mode2; original name unknown.
    MOT_UNKNOWN_12, // Inferred role: battle mode2 end; original name unknown.
    MOT_UNKNOWN_13, // Inferred role: battle mode3 start; original name unknown.
    MOT_UNKNOWN_14, // Inferred role: battle mode3; original name unknown.
    MOT_UNKNOWN_15, // Inferred role: battle mode3 end; original name unknown.
    MOT_UNKNOWN_16, // Inferred role: battle mode4 start; original name unknown.
    MOT_UNKNOWN_17, // Inferred role: battle mode4; original name unknown.
    MOT_UNKNOWN_18, // Inferred role: battle mode4 end; original name unknown.
    MOT_UNKNOWN_19, // Inferred role: battle mode5 start; original name unknown.
    MOT_UNKNOWN_20, // Inferred role: battle mode5; original name unknown.
    MOT_UNKNOWN_21, // Inferred role: battle mode5 end; original name unknown.
    MOT_UNKNOWN_22, // Inferred role: special; original name unknown.
  };

  enum CMD {
    CMD_UNKNOWN_0,  // Inferred role: normal; original name unknown.
    CMD_UNKNOWN_1,  // Inferred role: battle start; original name unknown.
    CMD_UNKNOWN_2,  // Inferred role: battle idle; original name unknown.
    CMD_UNKNOWN_3,  // Inferred role: battle end; original name unknown.
    CMD_UNKNOWN_4,  // Inferred role: battle mode1 start; original name unknown.
    CMD_UNKNOWN_5,  // Inferred role: battle mode1; original name unknown.
    CMD_UNKNOWN_6,  // Inferred role: battle mode1 end; original name unknown.
    CMD_UNKNOWN_7,  // Inferred role: battle mode2 start; original name unknown.
    CMD_UNKNOWN_8,  // Inferred role: battle mode2; original name unknown.
    CMD_UNKNOWN_9,  // Inferred role: battle mode2 end; original name unknown.
    CMD_UNKNOWN_10, // Inferred role: battle mode3 start; original name unknown.
    CMD_UNKNOWN_11, // Inferred role: battle mode3; original name unknown.
    CMD_UNKNOWN_12, // Inferred role: battle mode3 end; original name unknown.
    CMD_UNKNOWN_13, // Inferred role: battle mode4 start; original name unknown.
    CMD_UNKNOWN_14, // Inferred role: battle mode4; original name unknown.
    CMD_UNKNOWN_15, // Inferred role: battle mode4 end; original name unknown.
    CMD_UNKNOWN_16, // Inferred role: battle mode5 start; original name unknown.
    CMD_UNKNOWN_17, // Inferred role: battle mode5; original name unknown.
    CMD_UNKNOWN_18, // Inferred role: battle mode5 end; original name unknown.
    CMD_UNKNOWN_19, // Inferred role: special; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: mount flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: left flag; original name unknown.
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

  u32 unknown08;                                        // Inferred role: flags; original member name unknown.
  gf::GfEvtModel *unknown10;                            // Inferred role: model; original member name unknown.
  void *unknown18;                                      // Inferred role: data; original member name unknown.
  f32 unknown20;                                        // Inferred role: speed; original member name unknown.
  mm::mtl::FixedVector<MOT, QUEUE_UNKNOWN_8> unknown28; // Inferred role: queue; original member name unknown.
  MOT unknown50;                                        // Inferred role: last mot; original member name unknown.
};

static_assert(sizeof(CharaWpnAsm) == 0x58, "");

} // namespace event
