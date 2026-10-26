#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "types.h"

namespace ml {

u32 DrMdoCtlSeamAll::getSeamBaseMdlMax() const { return unknown1a8->m_seamBaseMdlMax; }

u32 DrMdoCtlSeamAll::getSeamInstMdlMax() const { return unknown1a8->m_seamInstMdlMax; }

u32 DrMdoCtlSeamAll::getSeamMpfMdlMax() const { return unknown1a8->m_seamMpfMdlMax; }

u32 DrMdoCtlSeamAll::getSeamTextureMax() const { return unknown1a8->m_seamTextureMax; }

u32 DrMdoCtlSeamAll::getSeamVertexMax() const { return unknown1a8->m_seamVertexMax; }

u32 DrMdoCtlSeamAll::getSeamEtcPosDataMax() const { return unknown1a8->m_seamEtcPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamMpfPosDataMax() const { return unknown1a8->m_seamMpfPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamColiMax() const { return unknown1a8->m_seamColiMax; }

u32 DrMdoCtlSeamAll::getSeamShaderMax() const { return unknown1a8->m_seamShaderMax; }

bool DrMdoCtlSeamAll::isReadSafe() const { return (unknownc7c >> 11) & 1; }

bool DrMdoCtlSeamAll::isRenderSafe() const { return (unknownc7c >> 15) & 1; }

void DrMdoCtlSeamAll::setSelectIdDisp(int id, bool isOff) {
  if (isOff) {
    m_drMan->offGblIdx(id);
    return;
  }
  m_drMan->setGblIdx(id);
}

void DrMdoCtlSeamAll::setMdlReadOff(bool isOff) {
  u32 flags = unknownc7c & ~0x200u;
  if (isOff) {
    flags = unknownc7c | 0x200;
  }
  unknownc7c = flags;
}

void DrMdoCtlSeamAll::debugRender() {}

void DrMdoCtlSeamAll::setClearResource(bool isClear) {}

} // namespace ml
