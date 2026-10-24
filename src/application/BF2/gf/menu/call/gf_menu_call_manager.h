#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_str_linker.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;
struct GfSetupParam;

class GfMenuCallManager : public mm::mtl::PtrSingleton<GfMenuCallManager> {
public:
  static const u32 CALL_MAX = 135;
  static const u32 CONTEXT_MAX = 256;

  struct CallInfo {
    GfMenuCallContext *unknown00; // Inferred role: context; original member name unknown.
    u32 unknown08;                // Inferred role: handler; original member name unknown.
  };

  GfMenuCallManager(const GfSetupParam &param);
  void reset();
  ~GfMenuCallManager() override;
  bool canCall(u32 call) const;
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  void attachCall(u32 call, u32 object);
  void detachCall(u32 call);
  u32 getAttachedObject(u32 call);
  u16 registString(const ui::UIStr &string);
  void releaseString(u16 id);
  const ui::UIStr &getString(u16 id);
  void startCallContext(GfMenuCallContext *context, u32 menu, u32 object);
  void nextCallContext(GfMenuCallContext *context, u32 menu);
  void setCallContextEventHandler(GfMenuCallContext *context, u32 handler);

  u32 unknown08[CALL_MAX];                                 // Inferred role: calls; original member name unknown.
  GfMenuStrLinker unknown228;                              // Inferred role: str linker; original member name unknown.
  mm::mtl::FixedVector<CallInfo, CONTEXT_MAX> unknown1108; // Inferred role: contexts; original member name unknown.
};

static_assert(offsetof(GfMenuCallManager, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuCallManager, unknown228) == 0x228, "");
static_assert(offsetof(GfMenuCallManager, unknown1108) == 0x1108, "");
static_assert(sizeof(GfMenuCallManager) == 0x2110, "");

} // namespace gf
