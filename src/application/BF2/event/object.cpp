#include "event/object.h"

#include <string.h>

namespace event {

Object::Object(OBJTYPE type, const char *name) : mType(type), mName(name), mChild(nullptr), mNext(nullptr) {}

Object::~Object() {
  Object *child = mChild;
  while (child != nullptr) {
    Object *next = child->mNext;
    delete child;
    child = next;
  }
}

Object *Object::searchByPath(const char *path) {
  size_t nameLength = __builtin_strlen(mName.c_str());
  if (nameLength <= __builtin_strlen(path) && __builtin_memcmp(path, mName.c_str(), nameLength) == 0) {
    if (__builtin_strcmp(path, mName.c_str()) == 0) {
      return this;
    }
    char *rest = nullptr;
    char buffer[512];
    __builtin_strcpy(buffer, path);
    strtok_r(buffer, "/", &rest);
    for (Object *child = mChild; child != nullptr; child = child->mNext) {
      Object *found = child->searchByPath(rest);
      if (found != nullptr) {
        return found;
      }
    }
  }
  return nullptr;
}

} // namespace event
