#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

// Inferred role: dev keyboard key; original type name unknown.
enum unknown032 {
  unknown032_37 = 0x25, // Inferred role: left; original name unknown.
  unknown032_38 = 0x26, // Inferred role: up; original name unknown.
  unknown032_39 = 0x27, // Inferred role: right; original name unknown.
  unknown032_40 = 0x28, // Inferred role: down; original name unknown.
};

// Inferred role: dev keyboard vk; original type name unknown.
enum unknown033 {
  unknown033_1 = 0x1,                // Inferred role: alt; original name unknown.
  unknown033_2 = 0x2,                // Inferred role: ctrl; original name unknown.
  unknown033_4 = 0x4,                // Inferred role: shift; original name unknown.
  unknown033_8 = 0x8,                // Inferred role: delete; original name unknown.
  unknown033_16 = 0x10,              // Inferred role: tab; original name unknown.
  unknown033_32 = 0x20,              // Inferred role: return; original name unknown.
  unknown033_6 = 6,                  // Inferred role: func shift; original name unknown.
  unknown033_524288 = 0x80000,       // Inferred role: page up; original name unknown.
  unknown033_1048576 = 0x100000,     // Inferred role: page down; original name unknown.
  unknown033_2097152 = 0x200000,     // Inferred role: home; original name unknown.
  unknown033_4194304 = 0x400000,     // Inferred role: end; original name unknown.
  unknown033_8388608 = 0x800000,     // Inferred role: up; original name unknown.
  unknown033_16777216 = 0x1000000,   // Inferred role: right; original name unknown.
  unknown033_33554432 = 0x2000000,   // Inferred role: down; original name unknown.
  unknown033_67108864 = 0x4000000,   // Inferred role: left; original name unknown.
  unknown033_134217728 = 0x8000000,  // Inferred role: pause; original name unknown.
  unknown033_268435456 = 0x10000000, // Inferred role: scroll; original name unknown.
};

class IDevInputKeyboard {
public:
  virtual ~IDevInputKeyboard() {}
  virtual void ikReturnDown() = 0;
  virtual void ikReturnUp() = 0;
  virtual void ikTabDown() = 0;
  virtual void ikTabUp() = 0;
  virtual void ikDeleteDown() = 0;
  virtual void ikDeleteUp() = 0;
  virtual void ikShiftDown() = 0;
  virtual void ikShiftUp() = 0;
  virtual void ikCtrlDown() = 0;
  virtual void ikCtrlUp() = 0;
  virtual void ikAltDown() = 0;
  virtual void ikAltUp() = 0;
  virtual void ikHomeDown() = 0;
  virtual void ikHomeUp() = 0;
  virtual void ikEndDown() = 0;
  virtual void ikEndUp() = 0;
  virtual void ikPageUpDown() = 0;
  virtual void ikPageUpUp() = 0;
  virtual void ikPageDownDown() = 0;
  virtual void ikPageDownUp() = 0;
  virtual void ikFuncDown(u8 index) = 0;
  virtual void ikFuncUp(u8 index) = 0;
  virtual void ikCharDown(u8 code) = 0;
  virtual void ikCharUp(u8 code) = 0;
  virtual bool ikIsAltDown() const = 0;
  virtual bool ikIsAltUp() const = 0;
  virtual void ikKeyMsgOn(u32 message) = 0;
  virtual void ikKeyMsgOff(u32 message) = 0;
  virtual void ikPauseDown() = 0;
  virtual void ikPauseUp() = 0;
  virtual void ikScrollDown() = 0;
  virtual void ikScrollUp() = 0;
};

class DevKeyboard : public WorkObj, public IDevInputKeyboard, public mm::mtl::PtrSingleton<DevKeyboard> {
public:
  DevKeyboard(const char *name, WorkObj *parent);
  ~DevKeyboard() override {}
  static bool isInitialized();
  static u32 getVkDown();
  static u32 getVkUp();
  static u32 getVkHold();
  static bool isVkDown(u32 key);
  static bool isVkUp(u32 key);
  static int getCharDownNum();
  static u8 getCharDown(u32 index);
  static bool isCharDown(u8 code);
  static u8 getCodeDown(u32 index);
  static int getCharUpNum();
  static u8 getCharUp(u32 index);
  static bool isCharUp(u8 code);
  static u8 getCodeUp(u32 index);
  void ikReturnDown() override;
  void updateKey();
  void ikReturnUp() override;
  void ikTabDown() override;
  void ikTabUp() override;
  void ikDeleteDown() override;
  void ikDeleteUp() override;
  void ikShiftDown() override;
  void ikShiftUp() override;
  void ikCtrlDown() override;
  void ikCtrlUp() override;
  void ikAltDown() override;
  void ikAltUp() override;
  void ikHomeDown() override;
  void ikHomeUp() override;
  void ikEndDown() override;
  void ikEndUp() override;
  void ikPageUpDown() override;
  void ikPageUpUp() override;
  void ikPageDownDown() override;
  void ikPageDownUp() override;
  void ikCharDown(u8 code) override;
  void ikCharUp(u8 code) override;
  void ikFuncDown(u8 index) override;
  void ikFuncUp(u8 index) override;
  void ikPauseDown() override;
  void ikPauseUp() override;
  bool ikIsAltDown() const override;
  bool ikIsAltUp() const override;
  void ikKeyMsgOn(u32 message) override;
  void ikKeyMsgOff(u32 message) override;
  void ikScrollDown() override;
  void ikScrollUp() override;
  bool ikIsHomeDown() const;
  bool ikIsHomeUp() const;
  bool ikIsEndDown() const;
  bool ikIsEndUp() const;
  void wkFrameEnd() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static void clearKey();

  // Inferred role: presses `key` and updates the key states like updateKey(); original name unknown.
  void unknown001(u32 key) {
    u32 up = unknown1bc;
    u32 down = unknown1b8 | key;
    u32 hold = unknown1c0;
    unknown1c4 = hold;
    unknown1c0 = (hold | down) & ~up;
    unknown1c8 = (hold ^ unknown1c0) & down;
    unknown1cc = (hold ^ unknown1c0) & up;
    unknown1b8 = 0;
    unknown1bc = 0;
  }

  u32 unknown1b8;                            // Inferred role: down accum; original member name unknown.
  u32 unknown1bc;                            // Inferred role: up accum; original member name unknown.
  u32 unknown1c0;                            // Inferred role: hold; original member name unknown.
  u32 unknown1c4;                            // Inferred role: prev hold; original member name unknown.
  u32 unknown1c8;                            // Inferred role: vk down; original member name unknown.
  u32 unknown1cc;                            // Inferred role: vk up; original member name unknown.
  u8 unknown1d0[32];                         // Inferred role: char down accum; original member name unknown.
  u8 unknown1f0[32];                         // Inferred role: char up accum; original member name unknown.
  u8 unknown210[32];                         // Inferred role: char down; original member name unknown.
  u8 unknown230[32];                         // Inferred role: char up; original member name unknown.
  int unknown250;                            // Inferred role: char down num accum; original member name unknown.
  int unknown254;                            // Inferred role: char up num accum; original member name unknown.
  int unknown258;                            // Inferred role: char down num; original member name unknown.
  int unknown25c;                            // Inferred role: char up num; original member name unknown.
  mm::mtl::FixedVector<u32, 256> unknown260; // Inferred role: key msg on; original member name unknown.
  mm::mtl::FixedVector<u32, 256> unknown668; // Inferred role: key msg off; original member name unknown.
};

static_assert(offsetof(DevKeyboard, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DevKeyboard, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DevKeyboard, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DevKeyboard, unknown230) == 0x230, "");
static_assert(offsetof(DevKeyboard, unknown250) == 0x250, "");
static_assert(offsetof(DevKeyboard, unknown260) == 0x260, "");
static_assert(offsetof(DevKeyboard, unknown668) == 0x668, "");
static_assert(sizeof(DevKeyboard) == 0xa70, "");

} // namespace ml
