#include "event/script_util.h"

namespace event {

OBJTYPE ScriptUtil::getObjType(Object *object) {
  if (object == nullptr) {
    return OBJTYPE_NONE;
  }
  return object->getType();
}

} // namespace event
