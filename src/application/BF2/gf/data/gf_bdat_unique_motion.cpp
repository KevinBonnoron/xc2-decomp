// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/data/gf_bdat_unique_motion.cpp.
#include "gf/data/gf_bdat_unique_motion.h"

#include "gf/game/gf_game_player_unique_scheduler.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/map.h"        // IWYU pragma: keep
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"     // IWYU pragma: keep

namespace gf {

GfBdatUniqueMotion::Impl::Impl() : unknown00(getAllocator(ALLOCATOR_DEFAULT)), unknown28(getAllocator(ALLOCATOR_DEFAULT)) {}

GfBdatUniqueMotion::Impl::~Impl() {}

#line 180
GfBdatUniqueMotion::GfBdatUniqueMotion() {
  unknown28.reset(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) Impl());
  unknown28->build();
}

#line 190
void GfBdatUniqueMotion::bdatRefresh() {
  unknown28.reset(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) Impl());
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

void GfBdatUniqueMotion::queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key) {
  if (get() != nullptr && get()->unknown28) {
    get()->unknown28->queryPreset(presets, key);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfBdatUniqueMotion>::~PtrSingleton();
template void mm::mtl::UniquePtr<gf::GfBdatUniqueMotion::Impl>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::Vector<gf::GfBdatUniqueMotion::PresetInfo>::expand(size_t, size_t);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>::MapTraits<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, gf::GfBdatUniqueMotion::CharaInfo> &);
template void unknown101::rebalance(unknown101::node *);
