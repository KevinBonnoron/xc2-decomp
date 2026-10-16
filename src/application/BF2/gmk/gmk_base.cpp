#include "gmk/gmk_base.h"

namespace gmk {

AGmkBase::AGmkBase() : baseInfo(), _40() {}

void AGmkBase::disposeBase() {
  baseInfo.list = nullptr;
  baseInfo.xform = nullptr;
  baseInfo.gobInfo = nullptr;
}

void AGmkBase::createBase(const CreateBaseInfo &info) { baseInfo = info; }

} // namespace gmk
