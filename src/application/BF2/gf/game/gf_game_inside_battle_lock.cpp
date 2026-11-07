#include "gf/game/gf_game_inside_battle_lock.h"

#include "fw/fw_transform.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {
struct GF_OBJ_HANDLE;

void GfGameInsideBattleLock::destroy() { delete get(); }

bool GfGameInsideBattleLock::isInsideBattleLock(GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj == nullptr || obj->unknown28 != OBJECT_TYPE_ENEMY) {
    return false;
  }

  mm::Vec3 position;
  if (acc.isValidTransform()) {
    position = acc.getWorldTransform().unknown00;
  } else {
    position = GfObjUtil::getObjSetup(handle)->unknown20;
  }
  return isInside(position);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameInsideBattleLock>::~PtrSingleton();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_OBJ_HANDLE *, bool>::MapTraits<gf::GF_OBJ_HANDLE *, bool>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, bool> &);
template void unknown101::rebalance(unknown101::node *);
