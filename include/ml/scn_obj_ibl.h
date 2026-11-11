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
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp; original name unknown.
  };

  ScnObjIBL(Scn *scn);
  ~ScnObjIBL() override;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void setReferencePos(const mm::Vec3 &position) = 0;
  virtual const mm::Vec3 &getReferencePos() const = 0;
  virtual void setFromCaptureTool() = 0;
  virtual void dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}
  virtual void setName(const char *name) = 0;

  u32 unknown14; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(ScnObjIBL, unknown14) == 0x14, "");

} // namespace ml
