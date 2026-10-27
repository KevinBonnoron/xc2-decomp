#include "gf/game/gf_game_obj.h"

#include "gf/object/gf_obj_util.h"

namespace gf {

bool GfGameObj::isInitialized() {
  GfGameObj *gameObj = get();
  if (gameObj != nullptr) {
    return gameObj->unknown55c70;
  }
  return false;
}

bool GfGameObj::isExistEnemy() { return get()->unknownd868 != 0; }

const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *GfGameObj::getListEnemyBlade() { return &get()->unknownd870; }

bool GfGameObj::isGameObjWaiting(GF_OBJ_HANDLE *handle) { return GfObjUtil::testFlag(handle, OBJ_FLAG_WAIT); }

} // namespace gf
