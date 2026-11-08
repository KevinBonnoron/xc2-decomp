#pragma once
#include <stddef.h>

#include "fw/fw_pad.h"
#include "types.h"

namespace gf {

class CameraPadData : public fw::PadRelay {
public:
  CameraPadData();
  void reset();
  void bind();
  ~CameraPadData();
  void unbind();
  void update();
  void resetAction();
  void zoomCamera();
  void heightCamera();
  void sideLeftCamera();
  void sideRightCamera();
  void sideResetCamera();
  void allResetAction();
  void setARX(f32 value);
  void setARY(f32 value);

  f32 m_ARX;
  f32 m_ARY;
  bool unknown40; // Inferred role: reset; original member name unknown.
  bool unknown41; // Inferred role: all reset; original member name unknown.
  bool unknown42; // Inferred role: zoom; original member name unknown.
  bool unknown43; // Inferred role: height; original member name unknown.
  bool unknown44; // Inferred role: side left; original member name unknown.
  bool unknown45; // Inferred role: side right; original member name unknown.
  bool unknown46; // Inferred role: side reset; original member name unknown.
};

static_assert(offsetof(CameraPadData, m_ARX) == 0x38, "");
static_assert(offsetof(CameraPadData, unknown40) == 0x40, "");
static_assert(offsetof(CameraPadData, unknown46) == 0x46, "");
static_assert(sizeof(CameraPadData) == 0x48, "");

} // namespace gf
