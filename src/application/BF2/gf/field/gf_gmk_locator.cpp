#include "gf/field/gf_gmk_locator.h"

#include "gmk/gmk_manager.h"

namespace gf {

GfGmkLocator::GfGmkLocator(const CreateInfo *info) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfGmkLocator::create(const CreateInfo &info) {
  m_gmkAcc.dispose();
  m_createInfo.unknown00 = nullptr;
  m_createInfo.unknown08 = false;
  m_createInfo.unknown08 = info.unknown08;
  m_createInfo.unknown00 = info.unknown00;
  gmk::GmkAcc::CreateInfo accInfo;
  accInfo.validate(*info.unknown00);
  m_gmkAcc.create(accInfo);
}

void GfGmkLocator::dispose() {
  m_gmkAcc.dispose();
  m_createInfo.unknown00 = nullptr;
  m_createInfo.unknown08 = false;
}

const gmk::AGmkBase *GfGmkLocator::getBindedGmk() const {
  if (m_createInfo.unknown08) {
    return m_gmkAcc.m_aGmkBase;
  }
  return m_createInfo.unknown00;
}

u32 GfGmkLocator::getFsId() const {
  const gmk::AGmkBase *gmk = getBindedGmk();
  if (gmk != nullptr) {
    return gmk::getBindedFsId(*gmk);
  }
  return 0;
}

} // namespace gf

template void mm::mtl::Vector<gf::GfGmkLocator>::destroy();
template void mm::mtl::Vector<gf::GfGmkLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocator>::push_back(const gf::GfGmkLocator &);
template void mm::mtl::Vector<gf::GfGmkLocator>::assign(const mm::mtl::Vector<gf::GfGmkLocator> &);
