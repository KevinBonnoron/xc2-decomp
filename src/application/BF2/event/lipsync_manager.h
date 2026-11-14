#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace csvb {
class CCsvbData;
} // namespace csvb

namespace event {

class LipsyncRes;

class LipsyncManager : public IManager, public mm::mtl::Singleton<LipsyncManager> {
public:
  static constexpr u32 RES_UNKNOWN_8 = 8; // Inferred role: res count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: event flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: active flag; original name unknown.
  };

  LipsyncManager();
  virtual ~LipsyncManager() {}
  bool isActive() const;
  f32 getVolume(f32 frame) const;
  void clear();
  void load(const char *name);
  LipsyncRes *searchRes(const char *name);
  bool isLoading() const;
  void setEvent(const char *name);
  bool setTarget(const char *name);
  f32 getFrameMax() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  u32 unknown10;                                               // Inferred role: flags; original member name unknown.
  mm::mtl::FixedVector<LipsyncRes *, RES_UNKNOWN_8> unknown18; // Inferred role: res list; original member name unknown.
  LipsyncRes *unknown60;                                       // Inferred role: current res; original member name unknown.
  mm::mtl::FixStr<128> unknown68;                              // Inferred role: target; original member name unknown.
  csvb::CCsvbData *unknownf0;                                  // Inferred role: csv; original member name unknown.
};

static_assert(sizeof(LipsyncManager) == 0xf8, "");

} // namespace event
