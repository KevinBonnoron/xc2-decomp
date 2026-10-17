#pragma once
#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class LipsyncRes : public IResEvent {
public:
  enum {
    FLAG_LOADING = 1 << 0,
    FLAG_LOADED = 1 << 1,
  };

  LipsyncRes(const char *name);
  virtual ~LipsyncRes() {}
  const char *getName() const;
  bool isLoading() const;
  virtual void OnResEvent(const PARAM &param);

private:
  u32 flags;
  mm::mtl::FixStr<64> name;
  u8 _50[0x68 - 0x50];
};

static_assert(sizeof(LipsyncRes) == 0x68, "");

} // namespace event
