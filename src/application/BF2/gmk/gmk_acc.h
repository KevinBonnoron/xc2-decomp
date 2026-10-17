#pragma once
#include "gmk/gmk_manager.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

class AGmkBase;
class IGmkList;

class GmkAcc : public mm::mtl::IntrusiveListNode<GmkAcc> {
public:
  struct CreateInfo {
    CreateInfo() : gmkSetId(-1), type(GMK_TYPE_NUM), index(0), isUpdateImmediate(true) {}

    bool isValid() const { return gmkSetId > 0 && type != GMK_TYPE_NUM; }
    void validate(const AGmkBase &gmk);

    int gmkSetId;
    GmkType type;
    u32 index;
    bool isUpdateImmediate;
  };

  struct CreateInfoByBdatId {
    CreateInfoByBdatId() : type(GMK_TYPE_NUM), bdatId(-1), isUpdateImmediate(true) {}

    bool isValid() const { return type != GMK_TYPE_NUM && bdatId > 0; }

    GmkType type;
    int bdatId;
    bool isUpdateImmediate;
  };

  GmkAcc();
  explicit GmkAcc(const CreateInfo &info);
  explicit GmkAcc(const CreateInfoByBdatId &info);
  GmkAcc(const GmkAcc &other);
  virtual ~GmkAcc() { dispose(); }

  void create(const CreateInfo &info);
  void create(const CreateInfoByBdatId &info);
  bool isValid() const;
  void dispose();
  void update();

  CreateInfo createInfo;
  CreateInfoByBdatId createInfoByBdatId;
  const AGmkBase *gmk;
};

static_assert(offsetof(GmkAcc, createInfo) == 0x18, "");
static_assert(offsetof(GmkAcc, createInfoByBdatId) == 0x28, "");
static_assert(offsetof(GmkAcc, gmk) == 0x38, "");
static_assert(sizeof(GmkAcc) == 0x40, "");

class GmkAccManager : public mm::mtl::PtrSingleton<GmkAccManager> {
public:
  ~GmkAccManager() override;

  void addGmkAcc(GmkAcc *acc);
  void removeGmkAcc(GmkAcc *acc);
  void update();
  static void invalidateAccs(const IGmkList &list);

  mm::mtl::IntrusiveList<GmkAcc> invalidAccs;
  mm::mtl::IntrusiveList<GmkAcc> validAccs;
};

static_assert(offsetof(GmkAccManager, invalidAccs) == 0x08, "");
static_assert(offsetof(GmkAccManager, validAccs) == 0x20, "");

} // namespace gmk
