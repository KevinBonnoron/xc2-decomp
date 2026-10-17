#pragma once
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace event {

enum ATTACH_TYPE : int;

class IAttachActor {
public:
  virtual ~IAttachActor() {}
  virtual const char *getName() const = 0;
  virtual void setEffectCaster(bool isSet, u32 handle) = 0;
  virtual void setEffectMount(bool isSet, u32 handle, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) = 0;
  virtual void getMat(mm::Mat44 &mat) const = 0;
  virtual void getMtpMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual void getMtpMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasMtp(const char *name) const = 0;
  virtual void getEfpMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual void getEfpMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasEfp(const char *name) const = 0;
  virtual void getBoneMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual void getBoneMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasBone(const char *name) const = 0;
  virtual void getMultipleMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual void getMultipleMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasMultiple(const char *name) const = 0;
};

} // namespace event
