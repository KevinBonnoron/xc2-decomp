#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
class GfMenuAdapterManager : public mm::mtl::PtrSingleton<GfMenuAdapterManager> {
public:
  // Inferred role: adapters of one category; original type name unknown.
  struct unknown001 {
    mm::mtl::IntrusiveList<GfMenuAdapter> unknown00; // Inferred role: adapters; original member name unknown.
  };

  GfMenuAdapterManager(const GfSetupParam &param);
  virtual ~GfMenuAdapterManager();
  static bool isAdapterFull();
  static bool isInitialized();
  static void destroy();
  static void beginCategory(u32 category);
  static void endCategory();
  static void beginAddAfter();
  static void endAddAfter();
  static void addActiveCategory(u32 category);
  static void delActiveCategory(u32 category);
  void addAdapter(GfMenuAdapter *adapter, bool isUpdateAfter);
  void setAfterUpdate(GfMenuAdapter *adapter);
  static void postUpdate(const fw::UpdateInfo &info);
  static void postUpdateAfter(const fw::UpdateInfo &info);

  unknown001 unknown08[4];                                   // Inferred role: adapters of each category; original member name unknown.
  mm::mtl::IntrusiveList<GfMenuAdapter> unknown68;           // Inferred role: adapters without category; original member name unknown.
  mm::mtl::IntrusiveList<GfMenuAdapter> unknown80;           // Inferred role: adapters updated after; original member name unknown.
  u32 unknown98;                                             // Inferred role: mask of active categories; original member name unknown.
  u32 unknown9c;                                             // Inferred role: current category; original member name unknown.
  bool unknowna0;                                            // Inferred role: adding after update; original member name unknown.
  mm::mtl::IntrusiveList<GfMenuAdapter>::iterator unknowna8; // Inferred role: next adapter to update; original member name unknown.
};

static_assert(offsetof(GfMenuAdapterManager, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuAdapterManager, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuAdapterManager, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuAdapterManager, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuAdapterManager, unknown9c) == 0x9c, "");
static_assert(offsetof(GfMenuAdapterManager, unknowna0) == 0xa0, "");
static_assert(offsetof(GfMenuAdapterManager, unknowna8) == 0xa8, "");
static_assert(sizeof(GfMenuAdapterManager) == 0xb0, "");

} // namespace gf
