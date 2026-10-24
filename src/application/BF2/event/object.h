#pragma once
#include "event/i_bou_callback.h"
#include "event/i_mani_callback.h"
#include "mm_mtl/fixstr.h"

namespace mm {
struct Col4;
}

namespace event {

enum OBJTYPE {
  OBJTYPE_NONE = 0,
  OBJTYPE_TREE = 1,
  OBJTYPE_CHARA = 2,
  OBJTYPE_CAMERA = 3,
  OBJTYPE_EFFECT = 4,
  OBJTYPE_LIGHT = 5,
};

class Object : public IBouCallback, public IManiCallback {
public:
  Object(OBJTYPE type, const char *name);
  virtual ~Object();
  Object *searchByPath(const char *path);
  virtual void clear() {}
  virtual void start() {}
  virtual void end() {}
  virtual void update() {}
  virtual void render(const mm::Col4 &color) {}
  virtual void tail() {}
  virtual bool isLoading() const { return false; }

  OBJTYPE getType() const { return unknown10; }
  const char *getName() const { return unknown14.c_str(); }
  Object *getChild() const { return unknown58; }
  Object *getNext() const { return unknown60; }
  void setChild(Object *child) { unknown58 = child; }

  void addChild(Object *child) {
    if (unknown58 == nullptr) {
      unknown58 = child;
    } else {
      Object *last = unknown58;
      while (last->unknown60 != nullptr) {
        last = last->unknown60;
      }
      last->unknown60 = child;
    }
  }

protected:
  OBJTYPE unknown10;             // Inferred role: type; original member name unknown.
  mm::mtl::FixStr<64> unknown14; // Inferred role: name; original member name unknown.
  Object *unknown58;             // Inferred role: child; original member name unknown.
  Object *unknown60;             // Inferred role: next; original member name unknown.
};

static_assert(sizeof(Object) == 0x68, "");

} // namespace event
