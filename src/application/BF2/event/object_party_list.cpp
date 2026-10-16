#include "event/object_party_list.h"

#include "gf/object/gf_obj_acc.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, ObjectPartyList::MEMBER_COUNT> ObjectPartyList::s_drlist;
mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, ObjectPartyList::MEMBER_COUNT> ObjectPartyList::s_bllist;

bool ObjectPartyList::isInvalidChara(gf::GF_OBJ_HANDLE *handle) { return handle == gf::INVALID_HANDLE; }

gf::GF_OBJ_HANDLE *ObjectPartyList::getBlade(u32 index) {
  if (index == 0 || index > s_bllist.size()) {
    return gf::INVALID_HANDLE;
  }
  return s_bllist[index - 1];
}

u32 ObjectPartyList::getLeaderDriverId() const {
  if (s_drlist.empty()) {
    return 1;
  }
  gf::GF_OBJ_HANDLE *handle = s_drlist.front();
  if (handle == gf::INVALID_HANDLE) {
    return 1;
  }
  return gf::GfObjAcc(handle).getBdatId();
}

} // namespace event
