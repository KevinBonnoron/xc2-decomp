#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
class CommonResource;
} // namespace fw

namespace ml {
class DrStmReadObj;
} // namespace ml

namespace gf {

class GfAssetResource : public mm::mtl::ReferenceObject {
public:
  // Inferred role: how the resource data is held (0 none, 1 load request, 2 copied, 3 referenced); original enum and enumerator names unknown.
  enum unknown001 {
    unknown001_0 = 0,
    unknown001_1 = 1,
    unknown001_2 = 2,
    unknown001_3 = 3,
  };

  GfAssetResource();
  ~GfAssetResource() override;
  static GfAssetResource *create(const char *assetName, const char *name, mtl::ALLOC_HANDLE handle, int priority);
  static GfAssetResource *create(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, int priority);
  static GfAssetResource *create(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, void *data, u32 size);
  static GfAssetResource *create(const char *assetName, const char *name, void *data, u32 size);
  void setup(const char *assetName, const char *name, mtl::ALLOC_HANDLE handle, int priority);
  void setup(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, int priority);
  void setup(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, void *data, u32 size);
  void setup(const char *assetName, const char *name, void *data, u32 size);
  void destroy();
  void destroyResource();
  void importSample();
  static void checkMemoryForDebug();
  void *getAssetData() const;
  u32 getAssetSize() const;
  const char *getAssetName() const;
  u64 getAssetTimeStamp() const;
  void reloadPre();
  void createStreamObject();
  void destroyStreamObject();
  void setupStreamObject();

private:
  inline void unknown003(); // Inferred role: release loaded data; original name unknown.

public:
  unknown001 unknown0c; // Inferred role: resource kind; original member name unknown.
  int unknown10;        // Inferred role: priority; original member name unknown.
  u8 _14[0x18 - 0x14];
  fw::CommonResource *unknown18;  // Inferred role: requested resource; original member name unknown.
  mm::mtl::IAllocator *unknown20; // Inferred role: allocator; original member name unknown.
  mtl::ALLOC_HANDLE unknown28;    // Inferred role: memory handle; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  void *unknown30;                // Inferred role: data; original member name unknown.
  u32 unknown38;                  // Inferred role: data size; original member name unknown.
  mm::mtl::FixStr<128> unknown3c; // Inferred role: name; original member name unknown.
  const char *unknownc0;          // Inferred role: asset name; original member name unknown.
  ml::DrStmReadObj *unknownc8;    // Inferred role: stream object; original member name unknown.
  u32 unknownd0;                  // Inferred role: first data word; original member name unknown.
  u32 unknownd4;                  // Inferred role: last data word; original member name unknown.
};

static_assert(offsetof(GfAssetResource, unknown0c) == 0x0c, "");
static_assert(offsetof(GfAssetResource, unknown18) == 0x18, "");
static_assert(offsetof(GfAssetResource, unknown28) == 0x28, "");
static_assert(offsetof(GfAssetResource, unknown30) == 0x30, "");
static_assert(offsetof(GfAssetResource, unknown3c) == 0x3c, "");
static_assert(offsetof(GfAssetResource, unknownc0) == 0xc0, "");
static_assert(offsetof(GfAssetResource, unknownc8) == 0xc8, "");
static_assert(offsetof(GfAssetResource, unknownd4) == 0xd4, "");
static_assert(sizeof(GfAssetResource) == 0xd8, "");

} // namespace gf
