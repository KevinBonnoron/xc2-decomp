#pragma once
#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {
class EffectPack;
} // namespace fw

namespace event {

class EffectRes : public IResEvent {
public:
  enum {
    FLAG_LOADING = 1 << 0,
  };

  EffectRes(const char *name);
  virtual ~EffectRes();
  const char *getName() const;
  fw::EffectPack *getResPack() const;
  bool isLoading() const;
  virtual void OnResEvent(const PARAM &param);

private:
  u32 unknown08; // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  fw::EffectPack *m_resPack;
};

static_assert(sizeof(EffectRes) == 0x58, "");

} // namespace event
