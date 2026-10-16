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

  OBJTYPE getType() const { return mType; }
  const char *getName() const { return mName.c_str(); }
  Object *getChild() const { return mChild; }
  Object *getNext() const { return mNext; }
  void setChild(Object *child) { mChild = child; }

  void addChild(Object *child) {
    if (mChild == nullptr) {
      mChild = child;
    } else {
      Object *last = mChild;
      while (last->mNext != nullptr) {
        last = last->mNext;
      }
      last->mNext = child;
    }
  }

protected:
  OBJTYPE mType;
  mm::mtl::FixStr<64> mName;
  Object *mChild;
  Object *mNext;
};

static_assert(sizeof(Object) == 0x68, "");

} // namespace event
