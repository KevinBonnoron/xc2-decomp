#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

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
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void itDown(u32 index, f32 x, f32 y) override;
  void itUp(u32 index, f32 x, f32 y) override;
  void itMove(u32 index, f32 x, f32 y) override;
  virtual void updateDevice();
  virtual bool createDevice() = 0;
  virtual void releaseDevice() = 0;
};

} // namespace ml
