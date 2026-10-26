#pragma once
#include "types.h"

namespace mm {
struct Vec3;
}

namespace btl {

class ActionCommand {
public:
  enum COMMAND_TYPE {
    COMMAND_TYPE_NONE,
    COMMAND_TYPE_MOVE_DIR_RATE,
    COMMAND_TYPE_MOVE_LOCK,
    COMMAND_TYPE_SUFFER_DAMAGE,
    COMMAND_TYPE_ATTACK_REPELLED,
    COMMAND_TYPE_BLADE_GUARD,
  };

  enum {
    MOVE_LOCK_FIELD_RUN = 0x1,
    MOVE_LOCK_TURN_TARGET = 0x2,
    MOVE_LOCK_SATELLITE = 0x4,
  };

  ActionCommand();
  void Reset();
  void SetActionID(int action);
  bool IsProcAction(int action) const;

  union {
    struct {
      f32 unknown00; // Inferred role: direction X; original member name unknown.
      f32 unknown04; // Inferred role: direction Z; original member name unknown.
      f32 unknown08; // Inferred role: rate; original member name unknown.
      u32 unknown0c; // Inferred role: field run flag; original member name unknown.
    } unknown00_0;   // Inferred role: move direction rate data; original member name unknown.
    struct {
      f32 unknown00;      // Inferred role: input X; original member name unknown.
      f32 unknown04;      // Inferred role: input Y; original member name unknown.
      u32 unknown08;      // Inferred role: move lock flags; original member name unknown.
    } unknown00_1;        // Inferred role: move lock data; original member name unknown.
    u8 unknown00_2[0x10]; // Inferred role: raw command data; original member name unknown.
  };
  union {
    u32 unknown10;
    struct {
      u32 unknown10_0 : 6;  // Inferred role: command type; original member name unknown.
      u32 unknown10_6 : 25; // Inferred role: action flags; original member name unknown.
    };
  };
};

static_assert(sizeof(ActionCommand) == 0x14, "");

namespace act_cmd {

class MOVE_DIR_RATE : public ActionCommand {
public:
  void Initialize(mm::Vec3 &direction, f32 rate, bool isFieldRun);
  void GetMoveData(mm::Vec3 &move) const;
  void GetDirection(mm::Vec3 &direction) const;
  f32 GetRate() const;
  bool IsFieldRun() const;
};

class MOVE_LOCK : public ActionCommand {
public:
  void Initialize(f32 inputX, f32 inputY, bool isFieldRun, bool isTurnTarget, bool isSatellite);
  void GetInput(f32 &inputX, f32 &inputY) const;
  bool IsFieldRun() const;
  bool IsTurnTarget() const;
  bool IsSatellite() const;
};

class SUFFER_DAMAGE : public ActionCommand {
public:
  void Initialize();
};

class ATTACK_REPELLED : public ActionCommand {
public:
  void Initialize();
};

class BLADE_GUARD : public ActionCommand {
public:
  void Initialize();
};

} // namespace act_cmd

} // namespace btl
