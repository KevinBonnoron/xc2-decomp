#pragma once
#include "event/i_attach_actor.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class AttachActorBase : public IAttachActor {
public:
  AttachActorBase(const char *name);
  AttachActorBase(const char *name, gf::GF_OBJ_HANDLE *actor);
  void setActor(gf::GF_OBJ_HANDLE *actor);
  void render();
  virtual const char *getName() const;
  virtual bool getMat(mm::Mat44 &mat) const;
  virtual bool getMtpMatGlobal(mm::Mat44 &mat, const char *name) const;
  virtual bool hasMtp(const char *name) const;
  virtual bool getEfpMatGlobal(mm::Mat44 &mat, const char *name) const;
  virtual bool hasEfp(const char *name) const;
  virtual bool getBoneMatGlobal(mm::Mat44 &mat, const char *name) const;
  virtual bool hasBone(const char *name) const;
  void setTransform(const mm::Mat44 &transform);

  virtual bool getMultipleMatGlobal(mm::Mat44 &mat, const char *name) const {
    if (getMtpMatGlobal(mat, name)) {
      return true;
    }
    if (getEfpMatGlobal(mat, name)) {
      return true;
    }
    return getBoneMatGlobal(mat, name);
  }

  virtual bool getMultipleMat(mm::Mat44 &mat, const char *name) const {
    if (getMtpMat(mat, name)) {
      return true;
    }
    if (getEfpMat(mat, name)) {
      return true;
    }
    return getBoneMat(mat, name);
  }

  virtual bool hasMultiple(const char *name) const {
    if (hasMtp(name)) {
      return true;
    }
    if (hasEfp(name)) {
      return true;
    }
    return hasBone(name);
  }

protected:
  // Inferred roles from access offsets; original member names are unknown.
  mm::mtl::FixStr<64> m_name; // Actor name.
  gf::GF_OBJ_HANDLE *m_actor; // Actor handle.
  mm::Mat44 unknown60;        // Attachment transform.
};

static_assert(sizeof(AttachActorBase) == 0xa0, "");

} // namespace event
