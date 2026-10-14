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
  u32 getShopListShopType(u32 shop) const;
  u32 getShopListTableID(u32 shop) const;
  u32 getShopNormalDefItem(u32 table, u32 index) const;
  u32 getShopNormalAddItem(u32 table, u32 index) const;
  u32 getShopNormalPrivilegeCheck(u32 table, u32 index) const;
  u32 getShopNormalPrivilegeFlag(u32 table) const;
  u32 getShopNormalPrivilegeItem(u32 table) const;
};

} // namespace gf
