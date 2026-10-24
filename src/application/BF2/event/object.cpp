#include "event/object.h"

#include <string.h>

namespace event {

Object::Object(OBJTYPE type, const char *name) : unknown10(type), unknown14(name), unknown58(nullptr), unknown60(nullptr) {}

Object::~Object() {
  Object *child = unknown58;
  while (child != nullptr) {
    Object *next = child->unknown60;
    delete child;
    child = next;
  }
}

Object *Object::searchByPath(const char *path) {
  size_t nameLength = __builtin_strlen(unknown14.c_str());
  if (nameLength <= __builtin_strlen(path) && __builtin_memcmp(path, unknown14.c_str(), nameLength) == 0) {
    if (__builtin_strcmp(path, unknown14.c_str()) == 0) {
      return this;
    }
    char *rest = nullptr;
    char buffer[512];
    __builtin_strcpy(buffer, path);
    strtok_r(buffer, "/", &rest);
    for (Object *child = unknown58; child != nullptr; child = child->unknown60) {
      Object *found = child->searchByPath(rest);
      if (found != nullptr) {
        return found;
      }
    }
  }
  return nullptr;
}

} // namespace event
