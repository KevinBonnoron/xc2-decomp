#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class ScnRenderDrViewCtrl;
} // namespace ml

namespace event {

class OffscrManager : public IManager, public mm::mtl::Singleton<OffscrManager> {
public:
  static constexpr u32 SCREEN_UNKNOWN_4 = 4; // Inferred role: screen count; original name unknown.

  OffscrManager();
  virtual ~OffscrManager() {}
  void clear();
  void createScreen(u32 screenID);
  bool isScreenExist(u32 screenID) const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  ml::ScnRenderDrViewCtrl *unknown10[SCREEN_UNKNOWN_4]; // Inferred role: screens; original member name unknown.
};

static_assert(sizeof(OffscrManager) == 0x30, "");

} // namespace event
