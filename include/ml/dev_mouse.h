#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class IDevInputMouse {
public:
  virtual ~IDevInputMouse() {}
  virtual void imPos(int x, int y) = 0;
  virtual void imMove(int x, int y) = 0;
  virtual void imWheel(int wheel) = 0;
  virtual void imLButtonUp() = 0;
  virtual void imMButtonUp() = 0;
  virtual void imRButtonUp() = 0;
  virtual void imLButtonDown() = 0;
  virtual void imMButtonDown() = 0;
  virtual void imRButtonDown() = 0;
  virtual void imLButtonDbl() = 0;
  virtual void imMButtonDbl() = 0;
  virtual void imRButtonDbl() = 0;
};

class DevMouse : public WorkObj, public IDevInputMouse, public mm::mtl::PtrSingleton<DevMouse> {
public:
  ~DevMouse() override {}
  static bool isInitialized();
  static void setClipMove(int x, int y);
  static void getClipMove(mm::Pnt<int> &move);
  static const mm::Pnt<int> &getPos();
  static const mm::Pnt<int> &getMove();
  static int getWheel();
  static u32 buttonOn();
  static u32 buttonOff();
  static u32 button();
  static u32 buttonDbl();
  void imPos(int x, int y) override;
  void imMove(int x, int y) override;
  void imWheel(int wheel) override;
  void imLButtonUp() override;
  void imMButtonUp() override;
  void imRButtonUp() override;
  void imLButtonDown() override;
  void imMButtonDown() override;
  void imRButtonDown() override;
  void imLButtonDbl() override;
  void imMButtonDbl() override;
  void imRButtonDbl() override;
  virtual void updateDevice();
  virtual bool createDevice() = 0;
  virtual void releaseDevice() = 0;
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static void setPadMouse(bool isPadMouse);
  static bool isPadMouse();
  static void resetMouse();

  mm::Pnt<int> unknown1b8; // Inferred role: pos; original member name unknown.
  mm::Pnt<int> unknown1c0; // Inferred role: move accum; original member name unknown.
  mm::Pnt<int> unknown1c8; // Inferred role: move; original member name unknown.
  int unknown1d0;          // Inferred role: wheel accum; original member name unknown.
  int unknown1d4;          // Inferred role: wheel; original member name unknown.
  u32 unknown1d8;          // Inferred role: button on accum; original member name unknown.
  u32 unknown1dc;          // Inferred role: button off accum; original member name unknown.
  u32 unknown1e0;          // Inferred role: button on; original member name unknown.
  u32 unknown1e4;          // Inferred role: button off; original member name unknown.
  u32 unknown1e8;          // Inferred role: button; original member name unknown.
  u32 unknown1ec;          // Inferred role: button dbl; original member name unknown.
  u32 unknown1f0;          // Inferred role: button dbl accum; original member name unknown.
  bool unknown1f4;         // Inferred role: pad mouse; original member name unknown.
  f32 unknown1f8;          // Inferred role: pad mouse speed; original member name unknown.
  bool unknown1fc;         // Inferred role: mouse input; original member name unknown.
  u8 _1fd[0x200 - 0x1fd];
};

static_assert(offsetof(DevMouse, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DevMouse, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DevMouse, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DevMouse, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DevMouse, unknown1f4) == 0x1f4, "");
static_assert(offsetof(DevMouse, unknown1f8) == 0x1f8, "");

} // namespace ml
