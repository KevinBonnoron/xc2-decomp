#pragma once
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class ObjectPartyList : public mm::mtl::Singleton<ObjectPartyList> {
public:
  static constexpr u32 MEMBER_COUNT = 3;

  virtual ~ObjectPartyList() {}
  void init();
  bool isTemporaryChara(gf::GF_OBJ_HANDLE *handle);
  bool isInvalidChara(gf::GF_OBJ_HANDLE *handle);
  gf::GF_OBJ_HANDLE *getBlade(u32 index);
  u32 getLeaderDriverId() const;

  gf::GF_OBJ_HANDLE *getDriver(u32 index);

private:
  // Original name unknown: returns the 1-based entry of a party list, or
  // INVALID_HANDLE when the index is out of range.
  static gf::GF_OBJ_HANDLE *unknown001(const mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, MEMBER_COUNT> &list, u32 index) {
    if (index == 0 || index > list.size()) {
      return gf::INVALID_HANDLE;
    }
    return list[index - 1];
  }

  static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, MEMBER_COUNT> s_drlist;
  static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, MEMBER_COUNT> s_bllist;
};

static_assert(sizeof(ObjectPartyList) == 0x8, "");

} // namespace event
