#pragma once
#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class MstxtRes : public IResEvent {
public:
  enum {
    FLAG_LOADING = 1 << 0,
    FLAG_LOADED = 1 << 1,
    FLAG_REGISTERED = 1 << 2,
  };

  MstxtRes(const char *path);
  virtual ~MstxtRes();
  void unregisterBdat();
  void registerBdat();
  unsigned char *getFp();
  int getSeatID(const char *label);
  const char *getText(const char *label);
  int getTop() const;
  int getCount() const;
  virtual void OnResEvent(const PARAM &param);

  bool isLoading() const { return (unknown08 & FLAG_LOADING) != 0; }
  bool isLoaded() const { return (unknown08 & FLAG_LOADED) != 0; }
  const char *getPath() const { return unknown0c.c_str(); }
  const char *getName() const { return unknown30.c_str(); }

private:
  u32 unknown08;                 // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<32> unknown0c; // Inferred role: path; original member name unknown.
  mm::mtl::FixStr<32> unknown30; // Inferred role: name; original member name unknown.
};

static_assert(sizeof(MstxtRes) == 0x58, "");

} // namespace event
