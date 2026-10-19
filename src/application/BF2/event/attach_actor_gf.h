#pragma once

#include "event/attach_actor_base.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class AttachActorGf : public AttachActorBase {
public:
  AttachActorGf(const char *name, gf::GF_OBJ_HANDLE *handle);
  virtual ~AttachActorGf();
  void render();
  virtual void setEffectCaster(bool isSet, u32 effect);
  virtual void setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  virtual bool getMtpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getEfpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getBoneMat(mm::Mat44 &mat, const char *name) const;
  void setTransform(const mm::Mat44 &transform);

private:
  gf::GF_OBJ_HANDLE *unknowna0; // Inferred role: game object handle; original member name unknown.
};

static_assert(sizeof(AttachActorGf) == 0xb0, "");

} // namespace event
