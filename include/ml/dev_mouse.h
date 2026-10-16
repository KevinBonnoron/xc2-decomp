#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class IDevInputMouse {
public:
  virtual ~IDevInputMouse();
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
  ~DevMouse() override;
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
  static void setPadMouse(bool isPadMouse);
  static bool isPadMouse();
  static void resetMouse();

  mm::Pnt<int> m_pos;
  mm::Pnt<int> m_moveAccum;
  mm::Pnt<int> m_move;
  int m_wheelAccum;
  int m_wheel;
  u32 m_buttonOnAccum;
  u32 m_buttonOffAccum;
  u32 m_buttonOn;
  u32 m_buttonOff;
  u32 m_button;
  u32 m_buttonDbl;
  u32 m_buttonDblAccum;
  bool m_isPadMouse;
  u8 _1f5[0x200 - 0x1f5];
};

static_assert(offsetof(DevMouse, m_pos) == 0x1b8, "");
static_assert(offsetof(DevMouse, m_wheelAccum) == 0x1d0, "");
static_assert(offsetof(DevMouse, m_buttonOnAccum) == 0x1d8, "");
static_assert(offsetof(DevMouse, m_buttonDblAccum) == 0x1f0, "");
static_assert(offsetof(DevMouse, m_isPadMouse) == 0x1f4, "");

} // namespace ml
