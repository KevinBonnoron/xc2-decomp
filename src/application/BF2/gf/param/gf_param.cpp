#include "gf/param/gf_param.h"

#include "arc/arc_data.h"
#include "framework/pad/pad_res_event.h"
#include "framework/pad/pad_res_event_manager.h"
#include "framework/param/param_builder.h"
#include "framework/reflection.h"
#include "framework/resource/common_resource.h"
#include "fw/fw_param_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_static_res.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h"
#include "types.h"

namespace gf {

namespace {

// Inferred role: pad event file of /param/pad.pdp and its source path, per pad resource index; original name unknown.
struct unknown001 {
  const char *unknown00; // Inferred role: file name in the archive; original member name unknown.
  const char *unknown08; // Inferred role: source path; original member name unknown.
};

// Inferred role: pad resources bound by bindPadResources; original name unknown.
const unknown001 unknown002[] = {
    {"field.pad", "T:/BF2/param/pad/data/field.pdml"},
    {"battle.pad", "T:/BF2/param/pad/data/battle.pdml"},
    {"camera.pad", "T:/BF2/param/pad/data/camera.pdml"},
    {"target.pad", "T:/BF2/param/pad/data/target.pdml"},
    {"system.pad", "T:/BF2/param/pad/data/system.pdml"},
};

} // namespace

void bindPadResources() {
  fw::PadResEventManager *manager = fw::PadResEventManager::get();
  if (manager != nullptr) {
    manager->setup(5, getAllocator(ALLOCATOR_UNKNOWN_0));
    fw::CommonResource *resource = GfStaticRes::search("/param/pad.pdp");
    if (resource != nullptr) {
      arc::CArcData archive(resource->getAssetData());
      for (u32 index = 0; index < 5; index++) {
        fw::PadResEventManager::setResource(index, fw::PadEventImporter::create(archive.getFileAdr(unknown002[index].unknown00), unknown002[index].unknown08));
      }
    }
  }
}

void unbindPadResource() {
  fw::PadResEventManager *manager = fw::PadResEventManager::get();
  if (manager != nullptr) {
    for (u32 index = 0; index < 5; index++) {
      fw::PadResEventManager::setResource(index, nullptr);
    }
    manager->cleanup();
  }
}

void destroyGfParameter() {
  for (u32 index = 0; index < 25; index++) {
    fw::ParamBuilder::destroy(index);
  }
}

} // namespace gf

namespace fw {

void ParamManager::addReflectionFileName(Reflection &reflection, const char *name) {
  RefInfo info;
  info.unknown00 = &reflection;
  info.unknown08 = name;
  unknown808.insert(mm::mtl::MapPair<Reflection *, RefInfo>(&reflection, info));
}

} // namespace fw

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<const fw::Reflection *, fw::ParamManager::RefInfo>::MapTraits<const fw::Reflection *, fw::ParamManager::RefInfo>> unknown101;

// Instantiated here: the game emits them after gf::destroyGFReflections, which erases the reflection file names (1.0.0: 0x71005b921c, 0x71005b9450).
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
