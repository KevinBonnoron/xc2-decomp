#pragma once
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace event {

class IManiCallback {
public:
  struct StartParam;

  struct RenderParam {
    mm::Col4 unknown00; // Inferred role: color; original member name unknown.
  };

  struct SetParam {
    u8 _00[0x80 - 0x00];
    mm::Mat44 matrix;
  };

  virtual ~IManiCallback() {}
  virtual bool OnManiStartPos(StartParam &param) { return false; }
  virtual void OnManiSetPos(SetParam &param) {}
  virtual bool OnManiStartRot(StartParam &param) { return false; }
  virtual void OnManiSetRot(SetParam &param) {}
  virtual bool OnManiStartTar(StartParam &param) { return false; }
  virtual void OnManiSetTar(SetParam &param) {}
  virtual void OnManiRender(RenderParam &param) {}
};

} // namespace event
