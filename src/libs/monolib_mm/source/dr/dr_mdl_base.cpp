#include "dr/dr_mdl_base.h"

namespace ml {

void DrMdlBase::dispOffUpdate() {}

void DrMdlBase::noOffScreenUpdate() {}

void DrMdlBase::shadowRender() {}

bool DrMdlBase::shadowCacheRender(DrPixlShadowCacheObj &cache) { return true; }

void DrMdlBase::shadowCacheAddRender(int index) {}

void DrMdlBase::shadowCacheOnlyRender() {}

void DrMdlBase::shadowPartsRender(int index) {}

void DrMdlBase::callShadowCacheUpdate(u64 flags) {}

void DrMdlBase::occRender() {}

bool DrMdlBase::cloneMdlObj(DrMdlObj *source) { return false; }

void DrMdlBase::setDisp(bool isDisp) { m_updateFlags = !isDisp ? m_updateFlags & ~UPDATE_FLAG_DISP : m_updateFlags | UPDATE_FLAG_DISP; }

void DrMdlBase::setDeleteCall(int deleteCall) { m_updateFlags |= UPDATE_FLAG_DELETE_CALL << deleteCall; }

void DrMdlBase::chageShadowObject(DrMdoSmlShadowMan *shadowMan) {}

} // namespace ml
