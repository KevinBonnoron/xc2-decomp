#include "gf/field/gf_fobj_dropitem.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

#include "framework/effect/effect_manager.h"

namespace gf {

bool GfFobjDropitem::isEnableGet() const { return unknown30 > 1; }

void GfFobjDropitem::disposeEffect() {
  if (unknown54 != 0) {
    fw::EffectManager::get()->dead(unknown54);
    unknown54 = 0;
  }
}

} // namespace gf

template mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::erase(mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, float>::MapTraits<unsigned short, float>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, float> &);
template void unknown101::rebalance(unknown101::node *);
