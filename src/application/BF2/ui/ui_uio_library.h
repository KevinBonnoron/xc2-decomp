#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
class CommonResource;
struct UpdateInfo;
} // namespace fw

namespace ui {

class UIUioLibrary : public mm::mtl::PtrSingleton<UIUioLibrary> {
public:
  struct UioInfo {
    u32 unknown00; // Inferred role: name hash; original member name unknown.
    u8 _04[0x08 - 0x04];
    fw::CommonResource *unknown08; // Inferred role: resource; original member name unknown.
  };

  UIUioLibrary();
  virtual ~UIUioLibrary();
  void reset();
  bool isLoading() const;
  void update(const fw::UpdateInfo &info);
  bool add(const char *name);

  mm::mtl::Vector<UioInfo> unknown08; // Inferred role: uio resources; original member name unknown.
};

static_assert(sizeof(UIUioLibrary::UioInfo) == 0x10, "");
static_assert(offsetof(UIUioLibrary::UioInfo, unknown08) == 0x08, "");
static_assert(offsetof(UIUioLibrary, unknown08) == 0x08, "");
static_assert(sizeof(UIUioLibrary) == 0x30, "");

} // namespace ui
