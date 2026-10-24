#pragma once
#include "gf/data/gf_data_map.h"
#include "types.h"

namespace event {

class EnvTransfer {
public:
  EnvTransfer();
  virtual ~EnvTransfer() {}
  void clear();
  void save();
  void load();

protected:
  u32 unknown08;           // Inferred role: hour; original member name unknown.
  u32 unknown0c;           // Inferred role: minute; original member name unknown.
  gf::WEATHERID unknown10; // Inferred role: weather; original member name unknown.
  gf::CLOUD_SEA unknown14; // Inferred role: cloud sea; original member name unknown.
};

static_assert(sizeof(EnvTransfer) == 0x18, "");

} // namespace event
