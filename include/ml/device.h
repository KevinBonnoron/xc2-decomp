#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class LanguageInfo;

class Device : public WorkObj, public mm::mtl::PtrSingleton<Device> {
public:
  struct SCU {
    void (*unknown00)(void *); // Inferred role: update function; original member name unknown.
    void *unknown08;           // Inferred role: update argument; original member name unknown.
  };

  Device(const char *name, WorkObj *parent);
  ~Device() override {}
  bool wkStandbyLogout() override;
  static bool isAllReady();
  static void createPort(const char *name);
  static void removeSubCpuUpdate(void (*update)(void *));
  static void updateSubCpu();
  static u32 jobUpdate(void *argument, void *userData);
  virtual bool createDevice() = 0;
  virtual void createDevicePort(const char *name) = 0;

  s32 unknown1b0; // Inferred role: cpu group handle; original member name unknown.
  u8 _1b4[0x1b8 - 0x1b4];
  mm::mtl::FixedList<SCU, 16> unknown1b8; // Inferred role: sub cpu updates; original member name unknown.
  LanguageInfo *unknown370;               // Inferred role: language info; original member name unknown.
};

static_assert(offsetof(Device, unknown1b0) == 0x1b0, "");
static_assert(offsetof(Device, unknown1b8) == 0x1b8, "");
static_assert(offsetof(Device, unknown370) == 0x370, "");

} // namespace ml
