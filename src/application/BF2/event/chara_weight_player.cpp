#include "event/chara_weight_player.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

CharaWeightPlayer::CharaWeightPlayer() : handle(gf::INVALID_HANDLE), mChara(nullptr) {}

void CharaWeightPlayer::create(gf::GF_OBJ_HANDLE *handle, CharaObj *chara) {
  this->handle = handle;
  mChara = chara;
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

CharaWeightItem *CharaWeightPlayer::searchItem(const char *stat) {
  for (CharaWeightItem **it = mItems.begin(); it != mItems.end(); ++it) {
    if (__builtin_strcmp((*it)->getStat(), stat) == 0) {
      return *it;
    }
  }
  return nullptr;
}

} // namespace event
