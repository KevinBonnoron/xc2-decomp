#pragma once

#include "event/attach_actor_base.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace event {

class ModelObj;

class AttachActorMdl : public AttachActorBase {
public:
  AttachActorMdl(const char *name, ModelObj *model);
  virtual ~AttachActorMdl();
  void render();
  virtual void setEffectCaster(bool isSet, u32 effect);
  virtual void setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  virtual bool getMtpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getEfpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getBoneMat(mm::Mat44 &mat, const char *name) const;
  void setTransform(const mm::Mat44 &transform);

private:
  ModelObj *unknowna0; // Inferred role: model object; original member name unknown.
};

static_assert(sizeof(AttachActorMdl) == 0xb0, "");

} // namespace event
