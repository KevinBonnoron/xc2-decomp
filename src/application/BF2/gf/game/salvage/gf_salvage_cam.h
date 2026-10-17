#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class GfSalvageCam : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  GfSalvageCam(GF_OBJ_HANDLE *target);
  virtual ~GfSalvageCam();
  virtual void onPush();
  virtual void onPop();
  virtual void onActivate();
  virtual void onDeactivate();
  virtual void update(const fw::UpdateInfo &info);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual const char *getName() const;

  GF_OBJ_HANDLE *target;
};

static_assert(offsetof(GfSalvageCam, target) == 0xa8, "");

} // namespace gf
