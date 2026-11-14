#include "event/object_party_list.h"

#include "gf/game/event/gf_game_event.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, ObjectPartyList::MEMBER_UNKNOWN_3> ObjectPartyList::s_drlist;
mm::mtl::FixedVector<gf::GF_OBJ_HANDLE *, ObjectPartyList::MEMBER_UNKNOWN_3> ObjectPartyList::s_bllist;

bool ObjectPartyList::isInvalidChara(gf::GF_OBJ_HANDLE *handle) { return handle == gf::unknown020; }

bool ObjectPartyList::isTemporaryChara(gf::GF_OBJ_HANDLE *handle) {
  if (handle != gf::unknown020) {
    u32 id = gf::GfObjAcc(handle).getBdatId();
    if (gf::GfGameEvent::isLeaderCharaNG(id)) {
      return true;
    }
  }
  return false;
}

gf::GF_OBJ_HANDLE *ObjectPartyList::getDriver(u32 index) { return unknown001(s_drlist, index); }

gf::GF_OBJ_HANDLE *ObjectPartyList::getBlade(u32 index) { return unknown001(s_bllist, index); }

u32 ObjectPartyList::getLeaderDriverId() const {
  if (s_drlist.empty()) {
    return 1;
  }
  gf::GF_OBJ_HANDLE *handle = s_drlist.front();
  if (handle == gf::unknown020) {
    return 1;
  }
  return gf::GfObjAcc(handle).getBdatId();
}

} // namespace event
