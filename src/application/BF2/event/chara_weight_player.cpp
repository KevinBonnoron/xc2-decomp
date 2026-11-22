#include "event/chara_weight_player.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

CharaWeightPlayer::CharaWeightPlayer() : unknown08(gf::unknown020), m_charaObj(nullptr) {}

void CharaWeightPlayer::create(gf::GF_OBJ_HANDLE *handle, CharaObj *chara) {
  this->unknown08 = handle;
  m_charaObj = chara;
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
  unknown08 = gf::unknown020;
  m_charaObj = nullptr;
}

void CharaWeightPlayer::update(f32 delta) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
  if (obj == nullptr) {
    return;
  }
  for (size_t i = 0; i < unknown18.size(); i++) {
    unknown18[i]->update(obj, delta);
  }
  while (unknown18.begin() != unknown18.end()) {
    CharaWeightItem **it = unknown18.begin();
    while ((*it)->isActive()) {
      ++it;
      if (it == unknown18.end()) {
        return;
      }
    }
    CharaWeightItem *item = *it;
    item->destroy(obj);
    delete item;
    unknown18.erase(it);
  }
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
