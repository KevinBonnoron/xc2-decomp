#include "gf/camera/gf_camera_pad_data.h"

#include "gf/gf_allocator.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"   // IWYU pragma: keep
#include "mm_mtl/map.h"      // IWYU pragma: keep

namespace gf {

constexpr int TYPE_UNKNOWN_2 = 2; // Inferred role: camera pad type; original name unknown.

CameraPadData::CameraPadData() {
  reset();
  bind();
}

void CameraPadData::reset() {
  m_ARX = 0.0f;
  m_ARY = 0.0f;
  unknown40 = false;
  unknown41 = false;
  unknown42 = false;
  unknown43 = false;
  unknown44 = false;
  unknown45 = false;
  unknown46 = false;
}

void CameraPadData::bind() {
  PadRelay::bind(0, TYPE_UNKNOWN_2, getAllocator(ALLOCATOR_UNKNOWN_0));
  bindAction("reset", this, &CameraPadData::resetAction);
  bindAction("zoom", this, &CameraPadData::zoomCamera);
  bindAction("height", this, &CameraPadData::heightCamera);
  bindAction("side_left", this, &CameraPadData::sideLeftCamera);
  bindAction("side_right", this, &CameraPadData::sideRightCamera);
  bindAction("side_reset", this, &CameraPadData::sideResetCamera);
  bindAction("all_reset", this, &CameraPadData::allResetAction);
  bindAxis("arx", this, &CameraPadData::setARX);
  bindAxis("ary", this, &CameraPadData::setARY);
}

CameraPadData::~CameraPadData() { unbind(); }

void CameraPadData::unbind() { PadRelay::unbind(); }

void CameraPadData::update() {
  reset();
  PadRelay::update();
}

void CameraPadData::resetAction() { unknown40 = true; }

void CameraPadData::zoomCamera() { unknown42 = true; }

void CameraPadData::heightCamera() { unknown43 = true; }

void CameraPadData::sideLeftCamera() { unknown44 = true; }

void CameraPadData::sideRightCamera() { unknown45 = true; }

void CameraPadData::sideResetCamera() { unknown46 = true; }

void CameraPadData::allResetAction() { unknown41 = true; }

void CameraPadData::setARX(f32 value) { m_ARX = value; }

void CameraPadData::setARY(f32 value) { m_ARY = value; }

} // namespace gf

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<mm::mtl::FixStr<32>, mm::mtl::Delegate<void()>>::MapTraits<mm::mtl::FixStr<32>, mm::mtl::Delegate<void()>>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<mm::mtl::FixStr<32>, mm::mtl::Delegate<void()>> &);
template void unknown101::rebalance(unknown101::node *);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<mm::mtl::FixStr<32>, mm::mtl::Delegate<void(float)>>::MapTraits<mm::mtl::FixStr<32>, mm::mtl::Delegate<void(float)>>> unknown102;

template void unknown102::free_node(unknown102::node *, bool);
template unknown102::node *unknown102::insert(const mm::mtl::MapPair<mm::mtl::FixStr<32>, mm::mtl::Delegate<void(float)>> &);
template void unknown102::rebalance(unknown102::node *);
template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::CameraPadData>(const mm::mtl::Delegate<void()> *);
template void mm::mtl::Delegate<void(float)>::memberFuncInvoker<gf::CameraPadData>(const mm::mtl::Delegate<void(float)> *, float);
