#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatShop : public mm::mtl::PtrSingleton<GfBdatShop> {
public:
  u32 getMNU_EventTheaterStart() const;
  u32 getMNU_EventTheaterEnd() const;
  u32 getMNU_EventTheaterevent_id(u32 theater) const;
  u32 getMNU_EventTheaterflag_index(u32 theater) const;
  u32 getMNU_EventTheaterblade_id(u32 theater) const;
};

} // namespace gf
