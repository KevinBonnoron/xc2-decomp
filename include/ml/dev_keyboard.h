#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

enum DevKeyboardKey {
  KEY_LEFT = 0x25,
  KEY_UP = 0x26,
  KEY_RIGHT = 0x27,
  KEY_DOWN = 0x28,
};

enum DevKeyboardVk {
  VK_ALT = 0x1,
  VK_CTRL = 0x2,
  VK_SHIFT = 0x4,
  VK_DELETE = 0x8,
  VK_TAB = 0x10,
  VK_RETURN = 0x20,
  VK_FUNC_SHIFT = 6,
  VK_PAGE_UP = 0x80000,
  VK_PAGE_DOWN = 0x100000,
  VK_HOME = 0x200000,
  VK_END = 0x400000,
  VK_UP = 0x800000,
  VK_RIGHT = 0x1000000,
  VK_DOWN = 0x2000000,
  VK_LEFT = 0x4000000,
  VK_PAUSE = 0x8000000,
  VK_SCROLL = 0x10000000,
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
