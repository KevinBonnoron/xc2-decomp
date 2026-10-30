#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

class GfBdatLookAt : public mm::mtl::PtrSingleton<GfBdatLookAt>, public IDataBdat, public fw::MessageObject {
public:
  struct CharactorInfo {
    CharactorInfo() : unknown00(0), unknown02(1) {}

    u16 unknown00; // Inferred role: look type; original member name unknown.
    u16 unknown02; // Inferred role: chara type; original member name unknown.
  };

  // Inferred role: look info; original type name unknown.
  struct unknown001 {
    unknown001() : unknown00(50.0f), unknown04(5.0f), unknown08(5.0f), unknown0c(3.0f), unknown10(5.0f), unknown14(0) {}

    f32 unknown00; // Inferred role: radius; original member name unknown.
    f32 unknown04; // Inferred role: upper height; original member name unknown.
    f32 unknown08; // Inferred role: lower height; original member name unknown.
    f32 unknown0c; // Inferred role: look time; original member name unknown.
    f32 unknown10; // Inferred role: interval; original member name unknown.
    u8 unknown14;  // Inferred role: priority; original member name unknown.
  };

  class Impl;

  GfBdatLookAt();
  void bdatRefresh() override;
  const CharactorInfo &getCharactorInfo(u32 category, u32 refId) const;
  const unknown001 &getLookInfo(u32 category, u32 charaCategory, u32 target, u32 targetRefId) const;
  f32 getMaxRadius();
  f32 getMaxUpper();
  f32 getMaxLower();
  u16 getCharaType(u32 category, u32 refId);

  mm::mtl::UniquePtr<Impl> unknown28; // Inferred role: implementation; original member name unknown.
};

static_assert(offsetof(GfBdatLookAt, unknown28) == 0x28, "");
static_assert(sizeof(GfBdatLookAt) == 0x30, "");

struct CategoryTable {
  CategoryTable() : unknown00(getAllocator(ALLOCATOR_DEFAULT)), unknown28(0), unknown2c(false) {}

  mm::mtl::Vector<GfBdatLookAt::CharactorInfo> unknown00; // Inferred role: characters indexed by ref id; original member name unknown.
  int unknown28;                                          // Inferred role: first ref id; original member name unknown.
  bool unknown2c;                                         // Inferred role: built; original member name unknown.
};

class GfBdatLookAt::Impl {
public:
  Impl();
  ~Impl();
  void build();
  const CharactorInfo *getCharactorInfo(u32 category, u32 refId) const;
  const unknown001 *getLookInfo(u32 category, u32 charaCategory) const;

  mm::mtl::FixedArray<CategoryTable, 16> unknown000; // Inferred role: tables per category; original member name unknown.
  unknown001 unknown300[3][5];                       // Inferred role: look infos; original member name unknown.
  f32 unknown468;                                    // Inferred role: max radius; original member name unknown.
  f32 unknown46c;                                    // Inferred role: max upper height; original member name unknown.
  f32 unknown470;                                    // Inferred role: max lower height; original member name unknown.
};

static_assert(sizeof(CategoryTable) == 0x30, "");
static_assert(sizeof(GfBdatLookAt::CharactorInfo) == 0x4, "");
static_assert(sizeof(GfBdatLookAt::unknown001) == 0x18, "");
static_assert(offsetof(GfBdatLookAt::Impl, unknown300) == 0x300, "");
static_assert(offsetof(GfBdatLookAt::Impl, unknown468) == 0x468, "");
static_assert(offsetof(GfBdatLookAt::Impl, unknown470) == 0x470, "");
static_assert(sizeof(GfBdatLookAt::Impl) == 0x478, "");

} // namespace gf
