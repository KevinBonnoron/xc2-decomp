#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace fw {

class ResourceObject;
enum eResourceType : int;

class ResourceManager : public ManagerObject, public mm::mtl::PtrSingleton<ResourceManager> {
public:
  static mtl::ALLOC_HANDLE m_hMemoryTemp;

  ~ResourceManager() override;
  void enterFinalizeApplet() override;
  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static void setMemTMP(mtl::ALLOC_HANDLE handle);
  static u32 getHash(const char *name);
  void addResource(ResourceObject *resource);
  void removeResource(ResourceObject *resource);
  ResourceObject *searchResource(u32 type, mtl::ALLOC_HANDLE handle, const char *path);
  ResourceObject *searchResource(u32 type, mm::mtl::IAllocator *allocator, const char *path);
  static bool isDelayReleaseExtention(const char *path);
  void addSafeObject(mm::mtl::ReferenceObject *object, eResourceType type);
  void removeSafeObject(mm::mtl::ReferenceObject *object);

  u8 _18[0x52c - 0x18];
  u32 unknown52c;  // Inferred role: applet state; original member name unknown.
  bool unknown530; // Inferred role: finalize applet; original member name unknown.
};

static_assert(offsetof(ResourceManager, unknown52c) == 0x52c, "");
static_assert(offsetof(ResourceManager, unknown530) == 0x530, "");

} // namespace fw
