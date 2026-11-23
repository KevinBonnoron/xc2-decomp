#include "gf/gf_static_res.h"

#include "framework/resource/common_resource.h"
#include "framework/resource/resource_manager.h"
#include "gf/gf_manager.h"
#include "gf/sound/gf_sound.h"
#include "ml/ml_mem.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace gf {

mtl::ALLOC_HANDLE GfStaticRes::s_hMem;
mm::mtl::FixedList<GfStaticRes::ResourceInfo, 64> GfStaticRes::s_aResource;

void GfStaticRes::initialize() {
  s_hMem = mtl::MemManager::create(ml::MlMem::getProductMem(), 0x200000, "GfStatic", false);
  loadRequest();
  while (!isLoaFinish()) {
    GfSleep(1);
  }
}

void GfStaticRes::finalize() {
  for (mm::mtl::FixedList<ResourceInfo, 64>::iterator it = s_aResource.begin(); it != s_aResource.end(); ++it) {
    mm::mtl::safeRelease(it->unknown00);
  }
  // The game walks the list a second time without any effect before clear() (1.0.0: 0x71003925a0); the original body is unknown.
  for (mm::mtl::FixedList<ResourceInfo, 64>::iterator it = s_aResource.begin(); it != s_aResource.end(); ++it) {
  }
  s_aResource.clear();
  if (s_hMem.isValid()) {
    mtl::MemManager::erase(s_hMem);
    s_hMem = mtl::ALLOC_HANDLE();
  }
}

void GfStaticRes::loadRequest() {
  loadStaticRes("/param/common.prm");
  loadStaticRes("/param/pc.prm");
  loadStaticRes("/param/camera.prm");
  loadStaticRes("/param/menu.prm");
  loadStaticRes("/param/event.prm");
  loadStaticRes("/param/effect.prm");
  loadStaticRes("/param/pad.pdp");
  loadStaticRes("/camera/params.gca");
  u32 count = getSoundSourceCount();
  for (u32 i = 0; i < count; i++) {
    loadStaticRes(getSoundSourceFileName(i));
  }
}

bool GfStaticRes::isLoaFinish() { return fw::ResourceManager::get()->isLoaded(); }

void GfStaticRes::loadStaticRes(const char *path) {
  fw::CommonResource *resource = fw::CommonResource::request(s_hMem, path, 10, false);
  if (resource != nullptr) {
    ResourceInfo info;
    info.unknown00 = resource;
    info.unknown08 = path;
    s_aResource.push_back(info);
  }
}

fw::CommonResource *GfStaticRes::search(const char *path) { return fw::CommonResource::search(s_hMem, path); }

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// The user, GfStaticRes::reloadRequestForDebug (0x7100392858), keeps the ALLOC_HANDLE temporary of the blockRequest call at sp + 8 and that of the search call at sp.
// Written inline the two slots are swapped (61 instructions, only the sp offsets of the two temporaries differ), because the allocas of an inlined callee land in front of the caller's own.
static fw::CommonResource *requestBlock(const char *path) { return fw::CommonResource::blockRequest(GfStaticRes::s_hMem, path, false); }

void GfStaticRes::reloadRequestForDebug(const char *path) {
  fw::CommonResource *resource = search(path);
  if (resource != nullptr) {
    for (mm::mtl::FixedList<ResourceInfo, 64>::iterator it = s_aResource.begin(); it != s_aResource.end(); ++it) {
      if (it->unknown00 == resource) {
        // The game has no null test before the release (it already knows the node equals the non-null search result), and the node it releases is the one loaded
        // from the list: mm::mtl::safeRelease here makes GVN release the search result instead (62 instructions, a copy of the result in x20), so the release is spelled out.
        it->unknown00->release();
        it->unknown00 = nullptr;
        it->unknown00 = requestBlock(path);
        break;
      }
    }
  }
}

} // namespace gf
