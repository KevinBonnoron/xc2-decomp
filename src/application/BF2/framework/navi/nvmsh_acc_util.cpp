#include "navi/nvmsh_acc_util.h"

#include "mm_mtl/singleton.h"

namespace navi {

NvmshAccUtil::NvmshAccUtil() {
  unknown00 = mm::mtl::PtrSingleton<NvmshManager>::get();
  m_avoidAttr = false;
}

void NvmshAccUtil::setAvoidAttr(bool value) { m_avoidAttr = value; }

bool NvmshAccUtil::testNaviColi(mm::Vec3 &position, const mm::Vec3 &target, float radius, float height, int layer) { return testNaviColiRange(position, target, 0.01f, radius, height, layer); }

} // namespace navi
