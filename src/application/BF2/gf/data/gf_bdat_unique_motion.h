#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

class GfBdatUniqueMotion : public mm::mtl::PtrSingleton<GfBdatUniqueMotion>, public IDataBdat, public fw::MessageObject {
public:
  class Impl;

  // Layout evidence: Impl::build (0x71002862c4) fills it from the bdat columns before
  // Map<u16, CharaInfo>::insert (0x71002874a4), whose node copies the 0x18-byte MapPair (key at 0x00, value at 0x04).
  struct CharaInfo {
    u16 unknown00; // Inferred role: reference id ("RefID"); original member name unknown.
    u16 unknown02; // Inferred role: probability ("Probability"); original member name unknown.
    f32 unknown04; // Inferred role: minimum delay ("DelayMin"); original member name unknown.
    f32 unknown08; // Inferred role: maximum delay ("DelayMax"); original member name unknown.
    u16 unknown0c; // Inferred role: first frequency ("FrequencyA"); original member name unknown.
    u16 unknown0e; // Inferred role: second frequency ("FrequencyB"); original member name unknown.
    u16 unknown10; // Inferred role: third frequency ("FrequencyC"); original member name unknown.
  };

  struct PresetKey {
    PresetKey() {}

    // Inferred: GfGamePlayerUniqueScheduler::rebuildPreset loads the six characters before it stores any of them, as a constructor call does;
    // the constructor is always inlined and the original parameter names are unknown.
    PresetKey(u16 id0, u16 id1, u16 id2, u16 id3, u16 id4, u16 id5) : ids{id0, id1, id2, id3, id4, id5} {}

    bool isContain(const PresetKey &key) const;

    u16 ids[6];
  };

  // Inferred role: motion of one character of a preset; original type name unknown.
  struct unknown001 {
    unknown001() : unknown00(0), unknown02(0), unknown04(0.0f) {}

    u16 unknown00; // Inferred role: character ("Chara0" to "Chara5"); original member name unknown.
    u16 unknown02; // Inferred role: motion ("Motion0" to "Motion5"); original member name unknown.
    f32 unknown04; // Inferred role: delay ("Delay0" to "Delay5"); original member name unknown.
  };

  // Layout evidence: Impl::build (0x71002862c4) fills it from the bdat columns, sorts a copy of the characters into the
  // key at 0x34 and copies the 0x40 bytes into Vector<PresetInfo>, whose expand (0x7100287390) moves them with memcpy.
  struct PresetInfo {
    u16 unknown00;           // Inferred role: frequency ("Frequency"); original member name unknown.
    unknown001 unknown04[6]; // Inferred role: character motions; original member name unknown.
    PresetKey unknown34;     // Inferred role: sorted characters; original member name unknown.
  };

  GfBdatUniqueMotion();
  void bdatRefresh() override;
  static void queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key);
  static CharaInfo *getCharaInfo(u16 id);

  mm::mtl::UniquePtr<Impl> unknown28; // Inferred role: implementation; original member name unknown.
};

class GfBdatUniqueMotion::Impl {
public:
  Impl();
  ~Impl();
  void build();
  CharaInfo *getCharaInfo(u16 id);
  void queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key);

  mm::mtl::Vector<PresetInfo> unknown00;  // Inferred role: presets; original member name unknown.
  mm::mtl::Map<u16, CharaInfo> unknown28; // Inferred role: characters by reference id; original member name unknown.
};

static_assert(offsetof(GfBdatUniqueMotion::CharaInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfBdatUniqueMotion::CharaInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(GfBdatUniqueMotion::CharaInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfBdatUniqueMotion::CharaInfo) == 0x14, "");
static_assert(offsetof(GfBdatUniqueMotion::PresetInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfBdatUniqueMotion::PresetInfo, unknown34) == 0x34, "");
static_assert(sizeof(GfBdatUniqueMotion::PresetInfo) == 0x40, "");
static_assert(offsetof(GfBdatUniqueMotion, unknown28) == 0x28, "");
static_assert(sizeof(GfBdatUniqueMotion) == 0x30, "");
static_assert(offsetof(GfBdatUniqueMotion::Impl, unknown28) == 0x28, "");
static_assert(sizeof(GfBdatUniqueMotion::Impl) == 0x40, "");

} // namespace gf
