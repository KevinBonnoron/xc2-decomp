#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace fw {

struct UpdateInfo;
class ResourceObject;
enum eResourceType : int;

class ResourceManager : public ManagerObject, public mm::mtl::PtrSingleton<ResourceManager> {
public:
  static mtl::ALLOC_HANDLE m_hMemoryTemp;

  ResourceManager(mm::mtl::IAllocator *allocator, u32 capacity);
  ~ResourceManager() override;
  void enterFinalizeApplet() override;
  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static void setMemTMP(mtl::ALLOC_HANDLE handle);
  static u32 getHash(const char *name);
  virtual void update(const UpdateInfo &info);
  bool isLoaded();
  void updateSafeReleaseList(bool isForce);
  void addResource(ResourceObject *resource);
  void removeResource(ResourceObject *resource);
  ResourceObject *searchResource(u32 type, mtl::ALLOC_HANDLE handle, const char *path);
  ResourceObject *searchResource(u32 type, mm::mtl::IAllocator *allocator, const char *path);
  static void addDelayReleaseExtention(const char *extension);
  static bool isDelayReleaseExtention(const char *path);
  void addSafeObject(mm::mtl::ReferenceObject *object, eResourceType type);
  void removeSafeObject(mm::mtl::ReferenceObject *object);

  static const u32 TYPE_MAX = 32;
  static const u32 SAFE_OBJECT_MAX = 1024;
  static const u32 DELAY_RELEASE_EXTENSION_MAX = 32;

  // Inferred role: safe object; original type name unknown.
  struct unknown001 {
    mm::mtl::ReferenceObject *unknown00; // Inferred role: object; original member name unknown.
    s16 unknown08;                       // Inferred role: remaining frames; original member name unknown.
    eResourceType unknown0c;             // Inferred role: type; original member name unknown.
  };

  mm::mtl::Vector<ResourceObject *> unknown18[TYPE_MAX];                       // Inferred role: resources per type; original member name unknown.
  mm::mtl::IAllocator *unknown518;                                             // Inferred role: allocator; original member name unknown.
  u32 unknown520;                                                              // Inferred role: unknown; original member name unknown.
  u32 unknown524;                                                              // Role and original member name unknown.
  u32 unknown528;                                                              // Role and original member name unknown.
  u32 unknown52c;                                                              // Inferred role: applet state; original member name unknown.
  bool unknown530;                                                             // Inferred role: finalize applet; original member name unknown.
  mm::mtl::FixedVector<unknown001, SAFE_OBJECT_MAX> unknown538;                // Inferred role: safe objects; original member name unknown.
  mm::mtl::FixedVector<unknown001, SAFE_OBJECT_MAX> unknown4540;               // Inferred role: safe objects to release; original member name unknown.
  mm::mtl::FixedVector<const char *, DELAY_RELEASE_EXTENSION_MAX> unknown8548; // Inferred role: delay release extensions; original member name unknown.
};

static_assert(sizeof(ResourceManager::unknown001) == 0x10, "");
static_assert(offsetof(ResourceManager, unknown18) == 0x18, "");
static_assert(offsetof(ResourceManager, unknown518) == 0x518, "");
static_assert(offsetof(ResourceManager, unknown520) == 0x520, "");
static_assert(offsetof(ResourceManager, unknown528) == 0x528, "");
static_assert(offsetof(ResourceManager, unknown52c) == 0x52c, "");
static_assert(offsetof(ResourceManager, unknown530) == 0x530, "");
static_assert(offsetof(ResourceManager, unknown538) == 0x538, "");
static_assert(offsetof(ResourceManager, unknown4540) == 0x4540, "");
static_assert(offsetof(ResourceManager, unknown8548) == 0x8548, "");

} // namespace fw
