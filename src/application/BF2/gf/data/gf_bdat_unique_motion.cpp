// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/data/gf_bdat_unique_motion.cpp.
#include "gf/data/gf_bdat_unique_motion.h"

#include <algorithm>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/game/gf_game_player_unique_scheduler.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/map.h"        // IWYU pragma: keep
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"     // IWYU pragma: keep

namespace gf {
namespace {

f32 getValF32(u8 *bdat, const char *name, int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(bdat, name, id, 8);
  return value.valueF32;
}

} // namespace

GfBdatUniqueMotion::Impl::Impl() : unknown00(getAllocator(ALLOCATOR_UNKNOWN_0)), unknown28(getAllocator(ALLOCATOR_UNKNOWN_0)) {}

GfBdatUniqueMotion::Impl::~Impl() {}

void GfBdatUniqueMotion::Impl::build() {
  // The Chara0..5, Motion0..5 and Delay0..5 groups are written out: the game's string pool holds Chara0, Motion0, Delay0, Chara1, ... in code order (no name table), so it has six separate blocks.
  u8 *presetBdat = GfDataBdat::getFP(BDAT_FLD_UNIQUE_PRESET);
  u32 presetTop = Bdat::getIdTop(presetBdat);
  u32 presetCount = Bdat::getIdCount(presetBdat);
  u32 presetEnd = presetTop + presetCount;
  unknown00.reserve(presetCount);
  for (u32 id = presetTop; id < presetEnd; id++) {
    PresetInfo info;
    info.unknown00 = Bdat::getValCheck(presetBdat, "Frequency", id, 2);
    info.unknown04[0].unknown00 = Bdat::getValCheck(presetBdat, "Chara0", id, 2);
    info.unknown04[0].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion0", id, 1));
    info.unknown04[0].unknown04 = getValF32(presetBdat, "Delay0", id);
    info.unknown04[1].unknown00 = Bdat::getValCheck(presetBdat, "Chara1", id, 2);
    info.unknown04[1].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion1", id, 1));
    info.unknown04[1].unknown04 = getValF32(presetBdat, "Delay1", id);
    info.unknown04[2].unknown00 = Bdat::getValCheck(presetBdat, "Chara2", id, 2);
    info.unknown04[2].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion2", id, 1));
    info.unknown04[2].unknown04 = getValF32(presetBdat, "Delay2", id);
    info.unknown04[3].unknown00 = Bdat::getValCheck(presetBdat, "Chara3", id, 2);
    info.unknown04[3].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion3", id, 1));
    info.unknown04[3].unknown04 = getValF32(presetBdat, "Delay3", id);
    info.unknown04[4].unknown00 = Bdat::getValCheck(presetBdat, "Chara4", id, 2);
    info.unknown04[4].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion4", id, 1));
    info.unknown04[4].unknown04 = getValF32(presetBdat, "Delay4", id);
    info.unknown04[5].unknown00 = Bdat::getValCheck(presetBdat, "Chara5", id, 2);
    info.unknown04[5].unknown02 = static_cast<u8>(Bdat::getValCheck(presetBdat, "Motion5", id, 1));
    info.unknown04[5].unknown04 = getValF32(presetBdat, "Delay5", id);
    info.unknown34 =
        PresetKey(info.unknown04[0].unknown00, info.unknown04[1].unknown00, info.unknown04[2].unknown00, info.unknown04[3].unknown00, info.unknown04[4].unknown00, info.unknown04[5].unknown00);
    std::sort(info.unknown34.ids, info.unknown34.ids + 6);
    unknown00.push_back(info);
  }
  u8 *tableBdat = GfDataBdat::getFP(BDAT_FLD_UNIQUE_TABLE);
  u32 tableTop = Bdat::getIdTop(tableBdat);
  u32 tableCount = Bdat::getIdCount(tableBdat);
  for (u32 id = tableTop; id < tableTop + tableCount; id++) {
    u16 refId = Bdat::getValCheck(tableBdat, "RefID", id, 2);
    u16 probability = Bdat::getValCheck(tableBdat, "Probability", id, 2);
    f32 delayMin = getValF32(tableBdat, "DelayMin", id);
    f32 delayMax = getValF32(tableBdat, "DelayMax", id);
    u16 frequencyA = Bdat::getValCheck(tableBdat, "FrequencyA", id, 2);
    u16 frequencyB = Bdat::getValCheck(tableBdat, "FrequencyB", id, 2);
    u16 frequencyC = Bdat::getValCheck(tableBdat, "FrequencyC", id, 2);
    mm::mtl::MapPair<u16, CharaInfo> pair;
    pair.first = refId;
    pair.second.unknown00 = refId;
    pair.second.unknown02 = probability;
    pair.second.unknown04 = delayMin;
    pair.second.unknown08 = delayMax;
    pair.second.unknown0c = frequencyA;
    pair.second.unknown0e = frequencyB;
    pair.second.unknown10 = frequencyC;
    unknown28.insert(pair);
  }
}

#line 180
GfBdatUniqueMotion::GfBdatUniqueMotion() {
  unknown28.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) Impl());
  unknown28->build();
}

#line 190
void GfBdatUniqueMotion::bdatRefresh() {
  unknown28.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) Impl());
  unknown28->build();
  GfGamePlayerUniqueScheduler::onReload();
}

void GfBdatUniqueMotion::Impl::queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key) {
  for (u32 i = 0; i < unknown00.size(); i++) {
    if (unknown00[i].unknown34.isContain(key)) {
      presets->push(&unknown00[i]);
    }
  }
}

GfBdatUniqueMotion::CharaInfo *GfBdatUniqueMotion::Impl::getCharaInfo(u16 id) {
  mm::mtl::Map<u16, CharaInfo>::iterator it = unknown28.find(id);
  if (it == unknown28.end()) {
    return nullptr;
  }
  return &it->second;
}

void GfBdatUniqueMotion::queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key) {
  if (get() != nullptr && get()->unknown28) {
    get()->unknown28->queryPreset(presets, key);
  }
}

GfBdatUniqueMotion::CharaInfo *GfBdatUniqueMotion::getCharaInfo(u16 id) {
  if (get() != nullptr && get()->unknown28) {
    return get()->unknown28->getCharaInfo(id);
  }
  return nullptr;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfBdatUniqueMotion>::~PtrSingleton();
template void mm::mtl::UniquePtr<gf::GfBdatUniqueMotion::Impl>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::Vector<gf::GfBdatUniqueMotion::PresetInfo>::expand(size_t, size_t);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>::MapTraits<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, gf::GfBdatUniqueMotion::CharaInfo> &);
template void unknown101::rebalance(unknown101::node *);
