#pragma once
#include <stddef.h>

#include "ml/scn_obj.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class Scn;
class WinProc;

class ScnObjIBL : public ScnObj {
public:
  enum Flag {
    FLAG_DISP = 1 << 0,
  };

  ScnObjIBL(Scn *scn);
  ~ScnObjIBL() override;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void setReferencePos(const mm::Vec3 &position) = 0;
  virtual const mm::Vec3 &getReferencePos() const = 0;
  virtual void setFromCaptureTool() = 0;
  virtual void dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}

  u32 m_flags;
};

static_assert(offsetof(ScnObjIBL, m_flags) == 0x14, "");

} // namespace ml
