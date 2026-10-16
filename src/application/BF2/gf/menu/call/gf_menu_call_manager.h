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
    GfMenuCallContext *context;
    u32 handler;
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

  u32 calls[CALL_MAX];
  GfMenuStrLinker strLinker;
  mm::mtl::FixedVector<CallInfo, CONTEXT_MAX> contexts;
};

static_assert(offsetof(GfMenuCallManager, calls) == 0x08, "");
static_assert(offsetof(GfMenuCallManager, strLinker) == 0x228, "");
static_assert(offsetof(GfMenuCallManager, contexts) == 0x1108, "");
static_assert(sizeof(GfMenuCallManager) == 0x2110, "");

} // namespace gf
