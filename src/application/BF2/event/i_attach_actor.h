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
  // Reconstructed vtable: local matrix lookups occupy slots 0x38, 0x50
  // and 0x68. Their callers test bit 0 of w0, establishing bool returns.
  virtual ~IAttachActor() {}
  virtual const char *getName() const = 0;
  virtual void setEffectCaster(bool isSet, u32 effect) = 0;
  virtual void setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) = 0;
  virtual bool getMat(mm::Mat44 &mat) const = 0;
  virtual bool getMtpMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool getMtpMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasMtp(const char *name) const = 0;
  virtual bool getEfpMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool getEfpMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasEfp(const char *name) const = 0;
  virtual bool getBoneMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool getBoneMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasBone(const char *name) const = 0;
  virtual bool getMultipleMatGlobal(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool getMultipleMat(mm::Mat44 &mat, const char *name) const = 0;
  virtual bool hasMultiple(const char *name) const = 0;
};

} // namespace event
