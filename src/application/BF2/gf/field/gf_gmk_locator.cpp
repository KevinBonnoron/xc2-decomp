#include "gf/field/gf_gmk_locator.h"

#include "gmk/gmk_manager.h"

namespace gf {

GfGmkLocator::GfGmkLocator(const CreateInfo *info) : unknown00(nullptr), unknown08(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfGmkLocator::create(const CreateInfo &info) {
  unknown10.dispose();
  unknown00 = nullptr;
  unknown08 = false;
  unknown08 = info.unknown08;
  unknown00 = info.unknown00;
  gmk::GmkAcc::CreateInfo accInfo;
  accInfo.validate(*info.unknown00);
  unknown10.create(accInfo);
}

void GfGmkLocator::dispose() {
  unknown10.dispose();
  unknown00 = nullptr;
  unknown08 = false;
}

const gmk::AGmkBase *GfGmkLocator::getBindedGmk() const {
  if (unknown08) {
    return unknown10.unknown38;
  }
  return unknown00;
}

u32 GfGmkLocator::getFsId() const {
  const gmk::AGmkBase *gmk = getBindedGmk();
  if (gmk != nullptr) {
    return gmk::getBindedFsId(*gmk);
  }
  return 0;
}

} // namespace gf
