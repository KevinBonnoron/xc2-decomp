#include "gf/game/gf_game_inside_battle_lock.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {
struct GF_OBJ_HANDLE;

void GfGameInsideBattleLock::destroy() { delete get(); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameInsideBattleLock>::~PtrSingleton();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_OBJ_HANDLE *, bool>::MapTraits<gf::GF_OBJ_HANDLE *, bool>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, bool> &);
template void unknown101::rebalance(unknown101::node *);
