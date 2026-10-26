#include "event/chara_weight_player.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

CharaWeightPlayer::CharaWeightPlayer() : unknown08(gf::INVALID_HANDLE), unknown10(nullptr) {}

void CharaWeightPlayer::create(gf::GF_OBJ_HANDLE *handle, CharaObj *chara) {
  this->unknown08 = handle;
  unknown10 = chara;
}

void CharaWeightPlayer::easeOut(gf::AnimLayer layer, const char *stat, f32 frame, CV_TYPE cv, WeightLayer weightLayer) {
  CharaWeightItem *item = searchItem(stat);
  if (item != nullptr) {
    item->easeOut(frame, cv, weightLayer);
  }
}

void CharaWeightPlayer::setAddWeight(const char *stat, f32 weight, WeightLayer weightLayer) {
  CharaWeightItem *item = searchItem(stat);
  if (item != nullptr) {
    item->setAddWeight(weight, weightLayer);
  }
}

void CharaWeightPlayer::destroy() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
  for (size_t i = 0; i < unknown18.size(); i++) {
    CharaWeightItem *item = unknown18[i];
    if (obj != nullptr) {
      item->destroy(obj);
    }
    delete item;
  }
  unknown18.clear();
  unknown08 = gf::INVALID_HANDLE;
  unknown10 = nullptr;
}

CharaWeightItem *CharaWeightPlayer::searchItem(const char *stat) {
  for (CharaWeightItem **it = unknown18.begin(); it != unknown18.end(); ++it) {
    if (__builtin_strcmp((*it)->getStat(), stat) == 0) {
      return *it;
    }
  }
  return nullptr;
}

} // namespace event
