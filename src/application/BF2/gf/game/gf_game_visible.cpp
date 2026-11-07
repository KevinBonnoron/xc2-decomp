#include "gf/game/gf_game_visible.h"

#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {

struct GF_OBJ_HANDLE; // IWYU pragma: keep

void GfGameVisible::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfGameVisible::cleanup() {}

void GfGameVisible::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->updateImpl(info);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVisible>::~PtrSingleton();
template mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *
mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *> &value);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::erase(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *nodePtr);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::free_node(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *target, bool recursive);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::rebalance(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *new_node);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::rebalance_after_erase(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *current);
