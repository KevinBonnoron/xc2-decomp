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
    CreateInfo() : unknown00(-1), unknown04(GMK_TYPE_NUM), unknown08(0), unknown0c(true) {}

    bool isValid() const { return unknown00 > 0 && unknown04 != GMK_TYPE_NUM; }
    void validate(const AGmkBase &gmk);

    int unknown00;     // Inferred role: gmk set id; original member name unknown.
    GmkType unknown04; // Inferred role: type; original member name unknown.
    u32 unknown08;     // Inferred role: index; original member name unknown.
    bool unknown0c;    // Inferred role: update immediate; original member name unknown.
  };

  struct CreateInfoByBdatId {
    CreateInfoByBdatId() : unknown00(GMK_TYPE_NUM), unknown04(-1), unknown08(true) {}

    bool isValid() const { return unknown00 != GMK_TYPE_NUM && unknown04 > 0; }

    GmkType unknown00; // Inferred role: type; original member name unknown.
    int unknown04;     // Inferred role: bdat id; original member name unknown.
    bool unknown08;    // Inferred role: update immediate; original member name unknown.
  };

  GmkAcc();
  explicit GmkAcc(const CreateInfo &info);
  explicit GmkAcc(const CreateInfoByBdatId &info);
  GmkAcc(const GmkAcc &other);
  // The game's ~GmkAcc calls dispose() without inlining it and was emitted from a gf translation unit (D2 at 0x2da41c).
  // Defining it here would emit it from the gmk unity build, where dispose() is inlined, so it stays declared only.
  virtual ~GmkAcc();

  void create(const CreateInfo &info);
  void create(const CreateInfoByBdatId &info);
  bool isValid() const;
  void dispose();
  void update();

  CreateInfo unknown18;         // Inferred role: create info; original member name unknown.
  CreateInfoByBdatId unknown28; // Inferred role: create info by bdat id; original member name unknown.
  const AGmkBase *unknown38;    // Inferred role: gmk; original member name unknown.
};

static_assert(offsetof(GmkAcc, unknown18) == 0x18, "");
static_assert(offsetof(GmkAcc, unknown28) == 0x28, "");
static_assert(offsetof(GmkAcc, unknown38) == 0x38, "");
static_assert(sizeof(GmkAcc) == 0x40, "");

class GmkAccManager : public mm::mtl::PtrSingleton<GmkAccManager> {
public:
  ~GmkAccManager() override;

  void addGmkAcc(GmkAcc *acc);
  void removeGmkAcc(GmkAcc *acc);
  void update();
  static void invalidateAccs(const IGmkList &list);

  mm::mtl::IntrusiveList<GmkAcc> unknown08; // Inferred role: invalid accs; original member name unknown.
  mm::mtl::IntrusiveList<GmkAcc> unknown20; // Inferred role: valid accs; original member name unknown.
};

static_assert(offsetof(GmkAccManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkAccManager, unknown20) == 0x20, "");

} // namespace gmk
