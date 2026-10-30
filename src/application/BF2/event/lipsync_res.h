#pragma once
#include "arc/arc_data.h"
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
  void *searchCsv(const char *name, int &size);
  virtual ~LipsyncRes() {}
  const char *getName() const;
  bool isLoading() const;
  virtual void OnResEvent(const PARAM &param);

private:
  u32 unknown08; // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  arc::CArcData unknown50; // Inferred role: lipsync archive; original member name unknown.
  u32 unknown60;           // Inferred role: next file index to search; original member name unknown.
  u8 _64[0x68 - 0x64];
};

static_assert(sizeof(LipsyncRes) == 0x68, "");

} // namespace event
