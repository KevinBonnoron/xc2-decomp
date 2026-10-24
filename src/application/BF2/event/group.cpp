#include "event/group.h"

namespace event {

Group::Group() : unknown410(0.0f, 0.0f, 0.0f), unknown420(0.0f), unknown424(0.0f) {}

void Group::clear() { unknown08.clear(); }

void Group::push(const CharaObj *chara) { unknown08.push_back(chara); }

void Group::pop(const CharaObj *chara) {
  for (const CharaObj **it = unknown08.begin(); it != unknown08.end(); it++) {
    if (*it == chara) {
      unknown08.erase(it);
      return;
    }
  }
}

} // namespace event
