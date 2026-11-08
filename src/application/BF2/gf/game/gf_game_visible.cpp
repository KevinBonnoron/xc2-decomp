#include "gf/game/gf_game_visible.h"

#include "framework/memory/framework_memory.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {

struct GF_OBJ_HANDLE; // IWYU pragma: keep

void GfGameVisible::build(const GfSetupParam &) {
// __LINE__ must be 40 as in the original file: it is the line argument of operator new.
#line 40
  GfGameVisible *visible = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameVisible();
  if (visible != nullptr) {
    visible->setup();
  }
}

void GfGameVisible::setup() {
  unknown08.setAllocator(fw::FrameworkMemory::getAllocator(5));
  for (u32 i = 0; i < 0x400; i++) {
    unknown20.push(&unknown2030[i]);
  }
}

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
