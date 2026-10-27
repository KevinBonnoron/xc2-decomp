#include "gf/asset/gf_asset_log.h"

#include "fw/fw_debug.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/hash.h"

namespace gf {

GfAssetLog::GfAssetLog() {}

GfAssetLog::~GfAssetLog() {}

u32 GfAssetLog::getHash(const char *name) const { return mm::mtl::hashStrCrc(name); }

GfAssetLog::AssetInfo *GfAssetLog::getAssetInfo(u32 hash) {
  for (mm::mtl::FixedQueue<AssetInfo, 32>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if ((*it).unknown28 == hash) {
      return &*it;
    }
  }
  return nullptr;
}

void GfAssetLog::createAssetPack(const GfAssetPack *pack) {
  u32 hash = getHash(pack->getAssetName());
  if (getAssetInfo(hash) != nullptr) {
    return;
  }
  if (unknown08.size() == 32) {
    unknown08.pop_front();
  }
  AssetInfo info;
  info.unknown28 = hash;
  info.unknown00 = pack->getAssetName();
  unknown08.push(info);
}

void GfAssetLog::setAssetPackForLoaded(const GfAssetPack *pack) {
  AssetInfo *info = getAssetInfo(getHash(pack->getAssetName()));
  if (info != nullptr && !(info->unknown24 > 0.0f)) {
    info->unknown24 = info->unknown30.getSecLap();
  }
}

void GfAssetLog::create(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfAssetLog(); }

void GfAssetLog::initialize(const GfSetupParam &param) {}

void GfAssetLog::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfAssetLog::finalize() {}

void GfAssetLog::renderInfo() {
  int y = GfInfo::m_nScreenH - unknown08.size() * 18;
  fw::debug::drawFontColor(mm::Col4::green);
  mm::mtl::FixedQueue<AssetInfo, 32>::iterator last = unknown08.end();
  for (mm::mtl::FixedQueue<AssetInfo, 32>::iterator it = unknown08.begin(); it != last; ++it) {
    mm::mtl::FixStr<128> text;
    text.format("%5.2f:%s", (*it).unknown24, (*it).unknown00.c_str());
    fw::debug::drawFont(80, y, text.c_str());
    y += 18;
  }
}

void GfAssetLog::update() {}

} // namespace gf
