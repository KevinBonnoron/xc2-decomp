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

// Ruling 8 (P4): the game (0x71005b97a4, 756 instructions) holds one straight-line block per archive and one create call per file, each with its own immediate index and string pair, so the blocks
// are written out. A loop over a table of file name, index and path does not unroll (403 instructions, frame 176 against the game's 240), and a file-local helper taking the archive, the name,
// the index and the path inlines but shares one stack slot for the returned parameter list (756 instructions, frame 48 against 240).
void createGfParameter() {
  fw::CommonResource *resource = GfStaticRes::search("/param/common.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("common_target.param"), 0, "T:/BF2/param/param/common/common_target.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_look_at_ik.param"), 1, "T:/BF2/param/param/common/common_look_at_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_spine_ik.param"), 2, "T:/BF2/param/param/common/common_spine_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_spc_ik.param"), 3, "T:/BF2/param/param/common/common_spc_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_foot_ik.param"), 4, "T:/BF2/param/param/common/common_foot_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_access.param"), 5, "T:/BF2/param/param/common/common_access.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_battle.param"), 10, "T:/BF2/param/param/common/common_battle.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_formation.param"), 6, "T:/BF2/param/param/common/common_formation.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_lure.param"), 7, "T:/BF2/param/param/common/common_lure.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_env_sensor.param"), 8, "T:/BF2/param/param/common/common_env_sensor.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_spine_rotate_ik.param"), 9, "T:/BF2/param/param/common/common_spine_rotate_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_eye.param"), 11, "T:/BF2/param/param/common/common_eye.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_unique_motion.param"), 12, "T:/BF2/param/param/common/common_unique_motion.xml");
    fw::ParamBuilder::create(archive.getFileAdr("common_enemy.param"), 21, "T:/BF2/param/param/common/common_enemy.xml");
  }

  resource = GfStaticRes::search("/param/pc.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("pc_common.param"), 13, "T:/BF2/param/param/pc/pc_common.xml");
    fw::ParamBuilder::create(archive.getFileAdr("pc_act_field.param"), 14, "T:/BF2/param/param/pc/pc_act_field.xml");
    fw::ParamBuilder::create(archive.getFileAdr("pc_act_ai_field.param"), 15, "T:/BF2/param/param/pc/pc_act_ai_field.xml");
    fw::ParamBuilder::create(archive.getFileAdr("pc_ai_field.param"), 16, "T:/BF2/param/param/pc/pc_ai_field.xml");
    fw::ParamBuilder::create(archive.getFileAdr("pc_coli.param"), 17, "T:/BF2/param/param/pc/pc_coli.xml");
    fw::ParamBuilder::create(archive.getFileAdr("pc_sound.param"), 18, "T:/BF2/param/param/pc/pc_sound.xml");
  }

  resource = GfStaticRes::search("/param/camera.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("camera.param"), 19, "T:/BF2/param/param/camera/camera.xml");
  }

  resource = GfStaticRes::search("/param/menu.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("menu.param"), 20, "T:/BF2/param/param/menu/menu.xml");
  }

  resource = GfStaticRes::search("/param/event.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("ev_look_at_ik.param"), 22, "T:/BF2/param/param/event/ev_look_at_ik.xml");
    fw::ParamBuilder::create(archive.getFileAdr("ev_spine_ik.param"), 23, "T:/BF2/param/param/event/ev_spine_ik.xml");
  }

  resource = GfStaticRes::search("/param/effect.prm");
  if (resource != nullptr) {
    arc::CArcData archive(resource->getAssetData());
    fw::ParamBuilder::create(archive.getFileAdr("eff_footstep.param"), 24, "T:/BF2/param/param/effect/eff_footstep.xml");
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
