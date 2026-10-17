#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

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
  VK_PAUSE = 0x8000000,
  VK_SCROLL = 0x10000000,
};

class IDevInputKeyboard {
public:
  virtual ~IDevInputKeyboard();
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
  ~DevKeyboard() override;
  static bool isInitialized();
  static u32 getVkDown();
  static u32 getVkUp();
  static u32 getVkHold();
  static bool isVkDown(u32 key);
  static bool isVkUp(u32 key);
  static int getCharDownNum();
  static u8 getCodeDown(u32 index);
  static int getCharUpNum();
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

  u32 m_downAccum;
  u32 m_upAccum;
  u32 m_hold;
  u32 m_prevHold;
  u32 m_vkDown;
  u32 m_vkUp;
  u8 m_charDownAccum[32];
  u8 m_charUpAccum[32];
  u8 m_charDown[32];
  u8 m_charUp[32];
  int m_charDownNumAccum;
  int m_charUpNumAccum;
  int m_charDownNum;
  int m_charUpNum;
  mm::mtl::FixedVector<u32, 256> m_keyMsgOn;
  mm::mtl::FixedVector<u32, 256> m_keyMsgOff;
};

static_assert(offsetof(DevKeyboard, m_downAccum) == 0x1b8, "");
static_assert(offsetof(DevKeyboard, m_vkDown) == 0x1c8, "");
static_assert(offsetof(DevKeyboard, m_charDownAccum) == 0x1d0, "");
static_assert(offsetof(DevKeyboard, m_charUp) == 0x230, "");
static_assert(offsetof(DevKeyboard, m_charDownNumAccum) == 0x250, "");
static_assert(offsetof(DevKeyboard, m_keyMsgOn) == 0x260, "");
static_assert(offsetof(DevKeyboard, m_keyMsgOff) == 0x668, "");
static_assert(sizeof(DevKeyboard) == 0xa70, "");

} // namespace ml
