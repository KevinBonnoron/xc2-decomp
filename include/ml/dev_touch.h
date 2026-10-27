#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

namespace dev_touch_detail {

extern mm::Vec2 s_initPos;

} // namespace dev_touch_detail

struct DevTouchInfo {
  DevTouchInfo();
  void initialize();

  u64 unknown00; // Inferred role: contact data; original member name unknown.
  s32 unknown08; // Inferred role: state; original member name unknown.
  s32 unknown0c; // Inferred role: contact id; original member name unknown.
  u16 unknown10; // Inferred role: flags; original member name unknown.
  u8 _12[0x20 - 0x12];
  mm::Vec2 unknown20; // Inferred role: initial position; original member name unknown.
  u8 _28[0x30 - 0x28];
  mm::Vec2 unknown30; // Inferred role: position; original member name unknown.
  u8 _38[0x40 - 0x38];
  mm::Vec2 unknown40; // Inferred role: previous position; original member name unknown.
  u8 _48[0x50 - 0x48];
  mm::Vec2 unknown50; // Inferred role: move; original member name unknown.
  u8 _58[0x60 - 0x58];
};

static_assert(offsetof(DevTouchInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(DevTouchInfo, unknown10) == 0x10, "");
static_assert(offsetof(DevTouchInfo, unknown20) == 0x20, "");
static_assert(offsetof(DevTouchInfo, unknown50) == 0x50, "");
static_assert(sizeof(DevTouchInfo) == 0x60, "");

class IDevInputTouch {
public:
  virtual ~IDevInputTouch();
  virtual void itDown(u32 index, f32 x, f32 y) = 0;
  virtual void itUp(u32 index, f32 x, f32 y) = 0;
  virtual void itMove(u32 index, f32 x, f32 y) = 0;
};

class DevTouch : public WorkObj, public IDevInputTouch, public mm::mtl::PtrSingleton<DevTouch> {
public:
  ~DevTouch() override;
  static bool isInitialized();
  static int getTouchCount();
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void itDown(u32 index, f32 x, f32 y) override;
  void itUp(u32 index, f32 x, f32 y) override;
  void itMove(u32 index, f32 x, f32 y) override;
  virtual void updateDevice();
  virtual bool createDevice() = 0;
  virtual void releaseDevice() = 0;

  u8 _1b8[0x7c0 - 0x1b8];
  s32 m_touchCount;
};

static_assert(offsetof(DevTouch, m_touchCount) == 0x7c0, "");

} // namespace ml
