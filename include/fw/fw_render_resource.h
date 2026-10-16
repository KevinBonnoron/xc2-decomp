#pragma once
#include "mm_mtl/reference_object.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {

class CommonResource : public mm::mtl::ReferenceObject {
public:
  static CommonResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool);

  virtual void update();
  virtual bool valid() const;
  virtual const char *getAssetName() const;
  void *getAssetData();
  int getAssetSize() const;
};

class RenderResource : public CommonResource {
public:
  static RenderResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority);
};

} // namespace fw
