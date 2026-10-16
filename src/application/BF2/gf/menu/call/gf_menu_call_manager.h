#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuCallManager : public mm::mtl::PtrSingleton<GfMenuCallManager> {
public:
  bool canCall(u32 call) const;
  void attachCall(u32 call, u32 object);
  void detachCall(u32 call);
  u32 getAttachedObject(u32 call);
  u16 registString(const ui::UIStr &string);
  void releaseString(u16 id);
  const ui::UIStr &getString(u16 id);
  void startCallContext(GfMenuCallContext *context, u32 call, u32 menu);
  void nextCallContext(GfMenuCallContext *context, u32 menu);
  void setCallContextEventHandler(GfMenuCallContext *context, u32 handler);
};

} // namespace gf
