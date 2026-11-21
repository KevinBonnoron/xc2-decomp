#include "framework/object/visible_object.h"

#include "dr/dr_gpu_check_base.h"
#include "framework/framework.h"
#include "framework/layer_list.h"
#include "framework/model/model_manager.h"
#include "fw/fw_transform.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_obj_acc.h"

namespace fw {

// Inferred helper: unlinks an object from the list of its layer; original name unknown.
// Evidence: ~VisibleObject (1.0.0: 0x710018ed70) and changeLayer (0x710018eeec) convert the node without the null test that the
// pointer parameter of IntrusiveList::erase gives (select of null before the call of unlinkNode). The destructor written with
// `erase(this)` gives 63 instructions against the game's 61; reached by reference the node needs none.
static void unknown002(VisibleObject &object) { ModelManager::get()->unknown18[object.unknown20].unknown00.erase(&object); }

// Inferred helper: links an object into the list of its layer unless the list holds it already; original name unknown.
// Evidence: VisibleObject::create (0x710018ec10) and changeLayer (0x710018eeec) share the search and the insertion, where neither the
// assert of push_back nor the null test of the node conversion is present. create written with the pointer from `new` gives
// 84 instructions against the game's 75.
static void unknown003(VisibleObject &object) {
  mm::mtl::IntrusiveList<unknown083> &objects = ModelManager::get()->unknown18[object.unknown20].unknown00;
  mm::mtl::IntrusiveList<unknown083>::iterator it = unknown001(objects.begin(), objects.end(), &object);
  if (objects.end() == it) {
    objects.push_back(&object);
  }
}

VisibleObject *VisibleObject::create(const SetupInfo &info, mm::mtl::IAllocator *allocator) {
  VisibleObject *object = new (Framework::getMemHandle()) VisibleObject();
  object->addRef();
  object->unknown30 = ml::ScnObjAccGpuCheck::create(0);
  object->unknown20 = info.unknown00;
  unknown003(*object);
  return object;
}

VisibleObject::VisibleObject() : unknown20(0), unknown30(nullptr), unknown40(0.0f, 0.5f, 0.0f) {}

VisibleObject::~VisibleObject() {
  unknown002(*this);
  mm::mtl::safeRelease(unknown30);
}

void VisibleObject::changeLayer(u32 layer) {
  if (unknown20 != layer) {
    unknown002(*this);
    unknown20 = layer;
    unknown003(*this);
  }
}

void VisibleObject::update() {
  if (unknown30 != nullptr && unknown28.get() != nullptr) {
    mm::Vec3 position = unknown28->unknown40.unknown00;
    position += unknown40;
    ml::ScnObjAccGpuCheck gpuCheck(unknown30);
    gpuCheck.setPos(position, 10.0f);
  }
}

bool VisibleObject::isRender() const {
  if (unknown30 != nullptr) {
    ml::ScnObjAccGpuCheck gpuCheck(unknown30);
    return gpuCheck.isRender();
  }

  return false;
}

} // namespace fw
