#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h" // IWYU pragma: keep
#include "framework/manager_object.h"
#include "framework/pointer_map.h"
#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/list.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace idcoli {
class IDColiManager;
} // namespace idcoli

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class ColiManager : public ManagerObject, public mm::mtl::PtrSingleton<ColiManager> {
public:
  class Impl {
  public:
    static const u32 CONTACT_TABLE_MAX = 512;
    static const u32 CONTACT_LIST_RESERVE = 8;
    static const u32 HANDLE_ID_MAX = 0x7fffffff;
    static const u32 HANDLE_FLAG = 0x80000000;
    static const u32 CONTACT_ATTRIBUTE_MASK = ~(1u << 20);

    static const u32 CONTACT_FLAG_ENTER = 1 << 0;
    static const u32 CONTACT_FLAG_CONTACT = 1 << 1;
    static const u32 CONTACT_FLAG_LEAVE = 1 << 2;
    static const u32 CONTACT_FLAG_CONTACTED = 1 << 3;
    static const u32 CONTACT_FLAG_ENTERED = 1 << 4;

    struct ContactParam {
      ContactParam() : unknown38(0) {}

      mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
      u32 unknown10;      // Inferred role: frame; original member name unknown.
      mm::Vec3 unknown20; // Inferred role: normal; original member name unknown.
      u32 unknown30;      // Inferred role: handle; original member name unknown.
      u32 unknown34;      // Inferred role: other handle; original member name unknown.
      u32 unknown38;      // Inferred role: flags; original member name unknown.
    };

    struct ListParam {
      ListParam(u32 handle, mm::mtl::List<ContactParam> *contacts) : unknown00(handle), unknown08(contacts) {}

      u32 unknown00;                          // Inferred role: handle; original member name unknown.
      mm::mtl::List<ContactParam> *unknown08; // Inferred role: contacts; original member name unknown.
    };

    typedef mm::mtl::FixedList<ListParam, CONTACT_TABLE_MAX> ContactTable;

    Impl(mm::mtl::IAllocator *allocator, u32 capacity);
    ~Impl() { finalize(); }
    void initializeContact();
    bool initialize();
    bool finalize();
    void finalizeContact();
    void updateRelease();
    void update();
    void updateContact();
    void sendContactEvent();
    void postUpdate();
    void tail();
    u32 getFrameCount() const;
    void destroyContactTable();
    mm::mtl::List<ContactParam> *getContactList(u32 handle);
    void makeContactList(ColiObject *object, TColiCheckResult<256> &result, mm::mtl::List<ContactParam> *contacts);
    ColiObject *getObject(u32 handle, bool isCheck) const;
    void addContactList(ColiObject *object, ColiObject *other, const ContactParam &param);
    bool isContactList(mm::mtl::List<ContactParam> &contacts, u32 handle);
    void sendRemoveEvent(u32 handle);
    bool isValidObject(u32 handle);
    void registObject(ColiObject *object);
    void removeObject(ColiObject *object);
    void cleanupObject(ColiObject *object);
    void openDebugWindow();
    bool isGblId(u32 id);
    void setGblId(u32 id, bool isGlobal);
    void *getGblIdTbl();

    mm::mtl::IntrusiveList<ColiObject> unknown00; // Inferred role: objects; original member name unknown.
    ColiObject *unknown18;                        // Inferred role: ground object; original member name unknown.
    idcoli::IDColiManager *unknown20;             // Inferred role: manager; original member name unknown.
    u32 unknown28;                                // Inferred role: frame count; original member name unknown.
    mm::mtl::IAllocator *unknown30;               // Inferred role: allocator; original member name unknown.
    PointerMap unknown38;                         // Inferred role: object map; original member name unknown.
    ContactTable unknown70;                       // Inferred role: contact table; original member name unknown.
  };

  ColiManager(mm::mtl::IAllocator *allocator, u32 capacity);
  ~ColiManager();
  bool initialize() override;
  bool finalize() override;
  void update();
  void postUpdate();
  void tail();
  void registObject(ColiObject *object);
  void removeObject(ColiObject *object);
  void cleanupObject(ColiObject *object);
  const idcoli::IDColiManager *getInterface() const;
  idcoli::IDColiManager *getInterface();
  void openDebugWindow();
  ColiObject *getGroundObject();
  ColiObject *getObject(u32 handle) const;
  bool isGblId(u32 id);
  void setGblId(u32 id, bool isGlobal);
  void *getGblIdTbl();

  mm::mtl::UniquePtr<Impl> unknown18; // Inferred role: impl; original member name unknown.
};

static_assert(offsetof(ColiManager::Impl::ContactParam, unknown10) == 0x10, "");
static_assert(offsetof(ColiManager::Impl::ContactParam, unknown20) == 0x20, "");
static_assert(offsetof(ColiManager::Impl::ContactParam, unknown38) == 0x38, "");
static_assert(sizeof(ColiManager::Impl::ContactParam) == 0x40, "");
static_assert(sizeof(mm::mtl::List<ColiManager::Impl::ContactParam>) == 0x80, "");
static_assert(offsetof(ColiManager::Impl, unknown18) == 0x18, "");
static_assert(offsetof(ColiManager::Impl, unknown20) == 0x20, "");
static_assert(offsetof(ColiManager::Impl, unknown28) == 0x28, "");
static_assert(offsetof(ColiManager::Impl, unknown30) == 0x30, "");
static_assert(offsetof(ColiManager::Impl, unknown38) == 0x38, "");
static_assert(offsetof(ColiManager::Impl, unknown70) == 0x70, "");
static_assert(sizeof(ColiManager::Impl) == 0x3498, "");
static_assert(offsetof(ColiManager, unknown18) == 0x18, "");

} // namespace fw
