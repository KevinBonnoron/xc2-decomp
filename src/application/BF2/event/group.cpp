#include "event/group.h"

namespace event {

Group::Group() : mPos(0.0f, 0.0f, 0.0f), mRadius(0.0f), mDir(0.0f) {}

void Group::clear() { mCharas.clear(); }

void Group::push(const CharaObj *chara) { mCharas.push_back(chara); }

void Group::pop(const CharaObj *chara) {
  for (const CharaObj **it = mCharas.begin(); it != mCharas.end(); it++) {
    if (*it == chara) {
      mCharas.erase(it);
      return;
    }
  }
}

} // namespace event
