#pragma once
#include "types.h"

namespace ml {

class ScnObj;
class ScnObjCam;
class WinView;

class ScnPoolObj {
public:
  bool isValidInsert(u16 type) const;
  void insert(ScnObj *obj);
  bool isExistLgtEnv() const;
  void release(ScnObj *obj);
  ScnObjCam *getCam(const WinView *view);
};

} // namespace ml
