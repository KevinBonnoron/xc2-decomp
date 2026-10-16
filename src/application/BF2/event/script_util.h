#pragma once
#include "event/object.h"

namespace event {

class ScriptUtil {
public:
  static OBJTYPE getObjType(Object *object);
};

} // namespace event
