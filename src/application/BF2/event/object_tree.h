#pragma once
#include "event/object.h"

namespace event {

class ObjectTree : public Object {
public:
  ObjectTree(const char *name);
  virtual ~ObjectTree();
};

static_assert(sizeof(ObjectTree) == 0x68, "");

} // namespace event
