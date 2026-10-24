#include "scn/scn_obj_acc.h"

#include <string.h>

#include "dr/dr_creator.h"
#include "dr/dr_gpu_check_base.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_ctl_pos.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"
#include "dr/dr_stm_read_obj.h"
#include "grlib/cglib_one_uniform_block.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_obj_model_dr_sys.h"

namespace ml {

ScnObjAccResMdlInfo::ScnObjAccResMdlInfo() : m_drMdl(nullptr) {}

ScnObjAccResMdlInfo::ScnObjAccResMdlInfo(ScnObjModel *model) : m_drMdl(nullptr) { setDrMdl(model); }

void ScnObjAccResMdlInfo::setDrMdl(ScnObjModel *model) { m_drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8; }

int ScnObjAccResMdlInfo::getViewNum() const { return m_drMdl->unknown1a; }

void ScnObjAccResMdlInfo::setChangeViewNum(int viewNum) {
  DrMdlObj *drMdl = m_drMdl;
  if (drMdl->unknown1a != viewNum) {
    drMdl->unknown1d = viewNum;
    drMdl->unknown20 |= 0x80 << DrMan::s_nDblStockIdx;
  }
}

void ScnObjAccResMdlInfo::setFrameSpd(f32 speed) { m_drMdl->unknowndc = speed; }

void ScnObjAccResMdlInfo::setMatrix(const mm::Mat44 &matrix) { m_drMdl->setMatrix(matrix); }

void ScnObjAccResMdlInfo::setGroups(int groups) { m_drMdl->unknown18 = groups; }

int ScnObjAccResMdlInfo::getGroups() const { return m_drMdl->unknown18; }

const mm::Vec3 &ScnObjAccResMdlInfo::getAABBMax() const { return m_drMdl->getAABBMax(); }

const mm::Vec3 &ScnObjAccResMdlInfo::getAABBMin() const { return m_drMdl->getAABBMin(); }

const mm::Vec3 &ScnObjAccResMdlInfo::getCenter() const { return m_drMdl->unknown130; }

f32 ScnObjAccResMdlInfo::getLength() const { return m_drMdl->unknown160; }

void ScnObjAccResMdlInfo::getInitialVertexAABBMax(mm::Vec3 &max, bool isScaled) const { m_drMdl->getInitialVertexAABBMax(max, isScaled); }

void ScnObjAccResMdlInfo::getInitialVertexAABBMin(mm::Vec3 &min, bool isScaled) const { m_drMdl->getInitialVertexAABBMin(min, isScaled); }

int ScnObjAccResMdlInfo::isGpuRender() const { return m_drMdl->isGpuRender(); }

void ScnObjAccResMdlInfo::setAlpha(f32 alpha) { m_drMdl->setAlpha(alpha); }

f32 ScnObjAccResMdlInfo::getAlpha() const { return m_drMdl->getAlpha(); }

void ScnObjAccResMdlInfo::setBloom(f32 bloom) { m_drMdl->unknownd8 = bloom; }

f32 ScnObjAccResMdlInfo::getBloom() const { return m_drMdl->unknownd8; }

void ScnObjAccResMdlInfo::setWriteStencil(bool isEnable) { m_drMdl->setWriteStencil(isEnable); }

void ScnObjAccResMdlInfo::setAlwaysMiddleTexStm(bool isEnable) { m_drMdl->setAlwaysMiddleTexStm(isEnable); }

void ScnObjAccResMdlInfo::setGpuClip(bool isClip) { m_drMdl->setGpuClip(isClip); }

void ScnObjAccResMdlInfo::setSpBlurOff(bool isEnable) { m_drMdl->setSpBlurOff(isEnable); }

void ScnObjAccResMdlInfo::setAlwaysTexStm(bool isEnable) { m_drMdl->setAlwaysTexStm(isEnable); }

void ScnObjAccResMdlInfo::setOcclusionQuery(bool isEnable) { m_drMdl->setOcclusionQuery(isEnable); }

void ScnObjAccResMdlInfo::setDblBuffAlpha(bool isEnable) { m_drMdl->setDblBuffAlpha(isEnable); }

void ScnObjAccResMdlInfo::setSpAlphaMode(bool isEnable) { m_drMdl->setSpAlphaMode(isEnable); }

void ScnObjAccResMdlInfo::setCamCheckMode(bool isEnable) { m_drMdl->setCamCheckMode(isEnable); }

bool ScnObjAccResMdlInfo::isCamCheckResl() const { return m_drMdl->isCamCheckResl(); }

bool ScnObjAccResMdlInfo::isMdlTexStm() const { return m_drMdl->isMdlTexStm(); }

bool ScnObjAccResMdlInfo::isMemTexStm() const { return m_drMdl->isMemTexStm(); }

bool ScnObjAccResMdlInfo::isMemMiddleTexStm() const { return m_drMdl->isMemMiddleTexStm(); }

void ScnObjAccResMdlInfo::setCreateDisplayList() { m_drMdl->setCreateDisplayList(); }

void ScnObjAccResMdlInfo::setExpressDrawMode(bool isEnable) { m_drMdl->setExpressDrawMode(isEnable); }

void ScnObjAccResMdlInfo::setExtraShader(const void *shader) { m_drMdl->setExtraShaderSetup(shader); }

void ScnObjAccResMdlInfo::releaseExtraShader() { m_drMdl->releaseExtraShader(); }

void ScnObjAccResMdlInfo::setSimpleShadow(bool isEnable) { m_drMdl->setSimpleShadow(isEnable); }

void ScnObjAccResMdlInfo::getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle) { DrMdlMan::getTextureStreamInfo(size, count, data, isMiddle); }

void ScnObjAccResMdlInfo::setClone(const ScnObjModel *model) { m_drMdl->cloneMdlObj(static_cast<const ScnObjModelDrSys *>(model)->unknown3d8); }

void ScnObjAccResMdlInfo::createAfterImage(const DrMdlAfterImageParams &params) {
  if (m_drMdl->unknown1c == DR_MDL_TYPE_NORMAL) {
    static_cast<DrMdoCtlNom *>(m_drMdl)->createAfterImage(params.unknown00,
                                                          params.unknown04,
                                                          params.unknown08,
                                                          params.unknown0c,
                                                          params.unknown18,
                                                          params.unknown1c,
                                                          params.unknown20,
                                                          params.unknown24,
                                                          params.unknown30,
                                                          params.unknown34,
                                                          params.unknown38);
  }
}

void ScnObjAccResMdlInfo::releaseAfterImage() {
  if (m_drMdl->unknown1c == DR_MDL_TYPE_NORMAL) {
    static_cast<DrMdoCtlNom *>(m_drMdl)->releaseAfterImage();
  }
}

ScnObjAccResNode::ScnObjAccResNode() : m_drMdl(nullptr) {}

ScnObjAccResNode::ScnObjAccResNode(ScnObjModel *model) : m_drMdl(static_cast<ScnObjModelDrSys *>(model)->unknown3d8) {}

void ScnObjAccResNode::setDrMdl(ScnObjModel *model) { m_drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8; }

void ScnObjAccResNode::setDrMdl(DrMdlObj *drMdl) { m_drMdl = drMdl; }

int ScnObjAccResNode::getBoneMax() const { return m_drMdl->getNodeMax(); }

int ScnObjAccResNode::getBoneIndex(const char *name) const { return m_drMdl->getNodeIdx(name); }

const char *ScnObjAccResNode::getBoneName(int index) const {
  if (index < 0) {
    return nullptr;
  }
  return m_drMdl->getNodeName(index);
}

void ScnObjAccResNode::setBoneMat(int index, const mm::Mat44 &matrix) { m_drMdl->setResBoneMat(index, matrix); }

const mm::Mat44 &ScnObjAccResNode::getBoneMat(int index) const { return m_drMdl->getResBoneMat(index); }

mm::Mat44 *ScnObjAccResNode::getBoneMatPtr(int index) { return m_drMdl->getResBoneMatPtr(index); }

ScnObjAccEtcParams::ScnObjAccEtcParams() : m_etcPamObj(nullptr) {}

ScnObjAccEtcParams::ScnObjAccEtcParams(ScnObjModel *model) { setDrMdl(model); }

void ScnObjAccEtcParams::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c != DR_MDL_TYPE_NORMAL) {
    m_etcPamObj = nullptr;
  } else {
    m_etcPamObj = static_cast<DrMdoCtlNom *>(drMdl)->unknown200;
  }
}

u32 ScnObjAccEtcParams::getMax() const {
  if (m_etcPamObj == nullptr) {
    return 0;
  }
  return m_etcPamObj->unknown18;
}

const char *ScnObjAccEtcParams::getName(u32 index) const {
  if (m_etcPamObj == nullptr) {
    return nullptr;
  }
  if (index >= m_etcPamObj->unknown18) {
    return nullptr;
  }
  return m_etcPamObj->unknown00 + m_etcPamObj->unknown08[index].unknown00;
}

int ScnObjAccEtcParams::getIndex(const char *name) const {
  if (m_etcPamObj != nullptr) {
    for (u64 i = 0; i < m_etcPamObj->unknown18; i++) {
      if (strcmp(name, m_etcPamObj->unknown00 + m_etcPamObj->unknown08[i].unknown00) == 0) {
        return i;
      }
    }
  }
  return -1;
}

f32 ScnObjAccEtcParams::getParams(u32 index) const {
  if (m_etcPamObj == nullptr || index >= m_etcPamObj->unknown18) {
    return 0.0f;
  }
  return m_etcPamObj->unknown10[index].getValParams();
}

void ScnObjAccEtcParams::setParams(u32 index, f32 value) {
  if (m_etcPamObj == nullptr || index >= m_etcPamObj->unknown18) {
    return;
  }
  m_etcPamObj->unknown10[index].setParams(value);
}

void ScnObjAccEtcParams::setPreParams(u32 index, f32 value) {
  if (m_etcPamObj == nullptr || index >= m_etcPamObj->unknown18) {
    return;
  }
  m_etcPamObj->unknown10[index].setPreParams(value);
}

void ScnObjAccEtcParams::setInitParams(u32 index, f32 value) {
  if (m_etcPamObj == nullptr || index >= m_etcPamObj->unknown18) {
    return;
  }
  m_etcPamObj->unknown10[index].setInitParams(value);
}

void ScnObjAccEtcParams::setRimBloom(bool isEnable) {
  if (m_etcPamObj != nullptr) {
    m_etcPamObj->unknown1c = !isEnable ? m_etcPamObj->unknown1c & ~1 : m_etcPamObj->unknown1c | 1;
  }
}

ScnObjAccResMaterial::ScnObjAccResMaterial() : m_matCount(0) {}

ScnObjAccResMaterial::ScnObjAccResMaterial(ScnObjModel *model) : m_matCount(0) { setDrMdl(model); }

void ScnObjAccResMaterial::setDrMdl(ScnObjModel *model) {
  MdoWrkMatRes *matRes = static_cast<ScnObjModelDrSys *>(model)->unknown3d8->unknown30;
  if (matRes != nullptr) {
    m_matCount = matRes->unknown30;
    m_matEntries = matRes->unknownc0;
    m_matData = matRes->unknown28;
  }
}

MdoWrkMatEntry *ScnObjAccResMaterial::getMatRes(int index) { return &m_matEntries[index]; }

MdsMatInfoHeader *ScnObjAccResMaterial::getMatData(int index) { return &m_matData[index]; }

ScnObjAccResSubMesh::ScnObjAccResSubMesh() : m_meshObj(nullptr) {}

ScnObjAccResSubMesh::ScnObjAccResSubMesh(ScnObjModel *model) : m_meshObj(nullptr) { setDrMdl(model); }

void ScnObjAccResSubMesh::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c != DR_MDL_TYPE_NORMAL) {
    return;
  }
  MdoWrkMatRes *matRes = drMdl->unknown30;
  if (matRes != nullptr) {
    m_meshObj = static_cast<DrMdoCtlNom *>(drMdl)->unknown1e8;
    const MdsMeshHeader *header = matRes->unknown20;
    m_partsInfos = reinterpret_cast<const MdsMeshPartsInfo *>(reinterpret_cast<const u8 *>(header) + header->unknown64);
  }
}

int ScnObjAccResSubMesh::getExtMax() const {
  if (m_meshObj == nullptr) {
    return 0;
  }
  return m_meshObj->unknown08;
}

int ScnObjAccResSubMesh::getExtIdx(const char *name) const {
  if (m_meshObj == nullptr) {
    return -1;
  }
  return m_meshObj->getIdx(name);
}

const char *ScnObjAccResSubMesh::getExtName(int index) const { return m_meshObj->getParts(index)->m_name; }

const char *ScnObjAccResSubMesh::getExtBoneName(int index) const { return m_meshObj->getParts(index)->m_boneName; }

bool ScnObjAccResSubMesh::isPosRes(int index) const { return (m_partsInfos[index].unknown08 >> 1) & 1; }

mm::Mat44 *ScnObjAccResSubMesh::getExtOfsMat(int index) const { return m_meshObj->getParts(index)->unknown20; }

void ScnObjAccResSubMesh::setExtAlpha(int index, f32 alpha) { m_meshObj->getParts(index)->setDefAlpha(alpha); }

f32 ScnObjAccResSubMesh::getExtAlpha(int index) const { return m_meshObj->getParts(index)->getDefAlpha(); }

void ScnObjAccResSubMesh::setExtRegisterMatrix(int index, bool isRegister) { m_meshObj->getParts(index)->setRegisterMatrix(index, isRegister); }

void ScnObjAccResSubMesh::setExtMatrix(int index, const mm::Mat44 &matrix) {
  DrResMdoMeshParts *parts = m_meshObj->getParts(index);
  if (parts->unknown28 & DrResMdoMeshParts::FLAG_MAT_ADD) {
    parts->setMatrix(matrix);
  }
}

u8 ScnObjAccResSubMesh::getExtVolumeFadeEffect(int index) const { return m_meshObj->getParts(index)->unknown3a; }

ScnObjAccResDecShader::ScnObjAccResDecShader() : m_shdObj(nullptr) {}

ScnObjAccResDecShader::ScnObjAccResDecShader(ScnObjModel *model) : m_shdObj(nullptr) { setDrMdl(model); }

void ScnObjAccResDecShader::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c == DR_MDL_TYPE_NORMAL) {
    m_shdObj = static_cast<DrMdoCtlNom *>(drMdl)->unknown1d0;
  }
}

u32 ScnObjAccResDecShader::getMax() const {
  if (m_shdObj == nullptr) {
    return 0;
  }
  return m_shdObj->unknown10;
}

const char *ScnObjAccResDecShader::getDecName(u32 index) const {
  if (m_shdObj == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(m_shdObj->unknown00) + m_shdObj->unknown08[index].unknown00->unknown00;
}

u32 ScnObjAccResDecShader::getID(u32 index) const {
  if (m_shdObj == nullptr) {
    return 0;
  }
  return m_shdObj->getDecShdID(index);
}

int ScnObjAccResDecShader::getIdx(const char *name) const {
  if (m_shdObj == nullptr) {
    return -1;
  }
  return m_shdObj->getDecShdIdx(name);
}

int ScnObjAccResDecShader::getIdx(u32 id) const {
  if (m_shdObj == nullptr) {
    return -1;
  }
  return m_shdObj->getDecShdIdx(id);
}

void ScnObjAccResDecShader::setParm(u32 index, u32 parm) {
  if (m_shdObj != nullptr) {
    m_shdObj->setDecShdParm(index, parm);
  }
}

u32 ScnObjAccResDecShader::getParm(u32 index) const {
  if (m_shdObj == nullptr) {
    return 0;
  }
  return m_shdObj->getDecShdParm(index);
}

u32 ScnObjAccResDecShader::getParmMax(u32 index) const {
  if (m_shdObj == nullptr) {
    return 0;
  }
  return m_shdObj->getDecShdParmMax(index);
}

ScnObjAccResAvatar::ScnObjAccResAvatar() : m_avatar(nullptr) {}

ScnObjAccResAvatar::ScnObjAccResAvatar(ScnObjModel *model) : m_avatar(nullptr) { setDrMdl(model); }

void ScnObjAccResAvatar::setDrMdl(ScnObjModel *model) {
  m_drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (m_drMdl->unknown30 != nullptr) {
    m_avatar = m_drMdl->unknown30->unknown110;
  }
}

bool ScnObjAccResAvatar::isAvatarChar() const {
  if (m_avatar != nullptr && m_avatar->unknown40 != nullptr) {
    return true;
  }
  return false;
}

bool ScnObjAccResAvatar::isAvatarDoll() const {
  if (m_avatar != nullptr && m_avatar->unknown48 != nullptr) {
    return true;
  }
  return false;
}

bool ScnObjAccResAvatar::isAvatarEyeTex() const {
  if (m_avatar != nullptr && (m_avatar->unknown00 & 8)) {
    return true;
  }
  return false;
}

bool ScnObjAccResAvatar::isAvatarMapMode() const { return m_drMdl->unknown40 != nullptr; }

void ScnObjAccResAvatar::setAvatarCharColor(int index, const mm::Col4 &color) { *reinterpret_cast<mm::Col4 *>(static_cast<f32 *>(m_avatar->unknown40->m_mapping) + index * 4) = color; }

void ScnObjAccResAvatar::setAvatarDollColor(int index, const mm::Col4 &color) { *reinterpret_cast<mm::Col4 *>(static_cast<f32 *>(m_avatar->unknown48->m_mapping) + index * 4) = color; }

void ScnObjAccResAvatar::setAvatarDollMat(bool isEnable) { m_avatar->unknown38 = isEnable; }

void ScnObjAccResAvatar::setAvatarMapColor(int index, const mm::Col3 &color) {
  mm::Col3 *colors = m_drMdl->unknown40;
  if (colors != nullptr) {
    colors[index] = color;
  }
}

f32 *ScnObjAccResAvatar::getAvatarCharColor(int index) { return static_cast<f32 *>(m_avatar->unknown40->m_mapping) + index * 4; }

f32 *ScnObjAccResAvatar::getAvatarDollColor(int index) { return static_cast<f32 *>(m_avatar->unknown48->m_mapping) + index * 4; }

mm::Col3 *ScnObjAccResAvatar::getAvatarMapColor(int index) const { return &m_drMdl->unknown40[index]; }

void ScnObjAccResAvatar::setAvatarTexture(ScnObjModelDrTexutre *texture, u32 index) {
  MdoWrkAvatar *avatar = m_avatar;
  avatar->unknown18[index] = texture->texture;
  avatar->unknown00 |= 0x10000 << index;
}

void ScnObjAccResAvatar::resetAvatarTexture(u32 index) {
  MdoWrkAvatar *avatar = m_avatar;
  avatar->unknown08[index] = DrMan::getIns()->unknown78->getDammyTexObj();
  avatar->unknown00 &= ~(0x10000 << index);
  avatar->unknown18[index] = nullptr;
  m_drMdl->setCreateDisplayList();
}

void ScnObjAccResAvatar::setAvatarEyeTexture(ScnObjModelDrTexutre *texture) {
  MdoWrkAvatar *avatar = m_avatar;
  avatar->unknown30 = texture->texture;
  avatar->unknown00 |= 0x40000;
}

void ScnObjAccResAvatar::resetAvatarEyeTexture() {
  MdoWrkAvatar *avatar = m_avatar;
  avatar->unknown28 = DrMan::getIns()->unknown78->getDammyTexObj();
  avatar->unknown00 &= ~0x40000;
  avatar->unknown30 = nullptr;
  m_drMdl->setCreateDisplayList();
}

void ScnObjAccResAvatar::resetAvatarTexture() {
  MdoWrkAvatar *avatar = m_avatar;
  for (u32 i = 0; i < 2; i++) {
    avatar->unknown00 &= ~(0x10000 << i);
    avatar->unknown08[i] = DrMan::getIns()->unknown78->getDammyTexObj();
    avatar->unknown18[i] = nullptr;
  }
  avatar->unknown28 = DrMan::getIns()->unknown78->getDammyTexObj();
  avatar->unknown00 &= ~0x40000;
  avatar->unknown30 = nullptr;
  m_drMdl->setCreateDisplayList();
}

static const mm::Col3 s_defaultShaderColor(0.5f, 0.5f, 0.5f);

ScnObjAccResShaderParm::ScnObjAccResShaderParm() : m_shaderParm(nullptr) {}

ScnObjAccResShaderParm::ScnObjAccResShaderParm(ScnObjModel *model) : m_shaderParm(nullptr) { setDrMdl(model); }

void ScnObjAccResShaderParm::setDrMdl(ScnObjModel *model) {
  MdoWrkMatRes *matRes = static_cast<ScnObjModelDrSys *>(model)->unknown3d8->unknown30;
  if (matRes != nullptr) {
    m_shaderParm = matRes->unknown118;
  }
}

void ScnObjAccResShaderParm::setColor(int index, const mm::Col3 &color) {
  if (m_shaderParm != nullptr) {
    m_shaderParm->unknown00[index] = color;
  }
}

void ScnObjAccResShaderParm::setVal(int index, f32 value) {
  if (m_shaderParm != nullptr) {
    m_shaderParm->unknown30[index] = value;
  }
}

const mm::Col3 *ScnObjAccResShaderParm::getColor(int index) const {
  if (m_shaderParm == nullptr) {
    return &s_defaultShaderColor;
  }
  return &m_shaderParm->unknown00[index];
}

f32 ScnObjAccResShaderParm::getVal(int index) const {
  if (m_shaderParm == nullptr) {
    return 1.0f;
  }
  return m_shaderParm->unknown30[index];
}

ScnObjAccVolumeFade::ScnObjAccVolumeFade() : m_drMdl(nullptr) {}

ScnObjAccVolumeFade::ScnObjAccVolumeFade(ScnObjModel *model) : m_drMdl(static_cast<ScnObjModelDrSys *>(model)->unknown3d8) {}

void ScnObjAccVolumeFade::setDrMdl(ScnObjModel *model) { m_drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8; }

ScnObjAccVolumeFade::~ScnObjAccVolumeFade() {}

u32 ScnObjAccVolumeFade::getMax() const {
  if (m_drMdl == nullptr) {
    return 0;
  }
  return m_drMdl->getVanishEffectMax();
}

void ScnObjAccVolumeFade::setRatio(f32 ratio, int index) {
  if (m_drMdl == nullptr) {
    return;
  }
  if (index >= 0) {
    MdoWrkVanishEffect *effect = m_drMdl->getVanishEffectWrk(index, DrMan::s_nDblIdx);
    if (effect != nullptr) {
      effect->unknowna4 = ratio;
      effect->unknownd4 |= 0x100;
    }
  } else {
    for (u32 i = 0; i < m_drMdl->getVanishEffectMax(); i++) {
      MdoWrkVanishEffect *effect = m_drMdl->getVanishEffectWrk(i, DrMan::s_nDblIdx);
      effect->unknowna4 = ratio;
      effect->unknownd4 |= 0x100;
    }
  }
}

ScnObjAccRimBloom::ScnObjAccRimBloom() : m_drMdl(nullptr) {}

ScnObjAccRimBloom::ScnObjAccRimBloom(ScnObjModel *model) : m_drMdl(static_cast<ScnObjModelDrSys *>(model)->unknown3d8) {}

void ScnObjAccRimBloom::setDrMdl(ScnObjModel *model) { m_drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8; }

ScnObjAccRimBloom::~ScnObjAccRimBloom() {}

bool ScnObjAccRimBloom::isExist() const {
  if (m_drMdl == nullptr) {
    return false;
  }
  return m_drMdl->getRimBloomWrk(2) != nullptr;
}

void ScnObjAccRimBloom::setRimColor(const mm::Col3 &color) {
  if (m_drMdl == nullptr) {
    return;
  }
  MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
  if (rimBloom != nullptr) {
    rimBloom->unknown00 = color;
    rimBloom->unknown1c |= 1;
  }
}

const mm::Col3 &ScnObjAccRimBloom::getRimColor() const {
  const mm::Col3 *color = &mm::Col3::black;
  if (m_drMdl != nullptr) {
    MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(2);
    if (rimBloom != nullptr) {
      color = &rimBloom->unknown00;
    }
  }
  return *color;
}

void ScnObjAccRimBloom::setRimEmissive(f32 emissive) {
  if (m_drMdl == nullptr) {
    return;
  }
  MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
  if (rimBloom != nullptr) {
    rimBloom->unknown14 = emissive;
    rimBloom->unknown1c |= 8;
  }
}

f32 ScnObjAccRimBloom::getRimEmissive() const {
  if (m_drMdl != nullptr) {
    MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(2);
    if (rimBloom != nullptr) {
      return rimBloom->unknown14;
    }
  }
  return 0.0f;
}

void ScnObjAccRimBloom::setRimPower(f32 power) {
  if (m_drMdl == nullptr) {
    return;
  }
  MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
  if (rimBloom != nullptr) {
    rimBloom->unknown0c = power;
    rimBloom->unknown1c |= 2;
  }
}

f32 ScnObjAccRimBloom::getRimPower() const {
  if (m_drMdl != nullptr) {
    MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(2);
    if (rimBloom != nullptr) {
      return rimBloom->unknown0c;
    }
  }
  return 0.0f;
}

void ScnObjAccRimBloom::setBlackRatio(f32 ratio) {
  if (m_drMdl == nullptr) {
    return;
  }
  MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
  if (rimBloom != nullptr) {
    rimBloom->unknown10 = ratio;
    rimBloom->unknown1c |= 4;
  }
}

f32 ScnObjAccRimBloom::getBlackRatio() const {
  if (m_drMdl != nullptr) {
    MdoWrkRimBloom *rimBloom = m_drMdl->getRimBloomWrk(2);
    if (rimBloom != nullptr) {
      return rimBloom->unknown10;
    }
  }
  return 0.0f;
}

ScnObjAccMdlParticle::ScnObjAccMdlParticle() : m_vtxMeshObj(nullptr) {}

ScnObjAccMdlParticle::ScnObjAccMdlParticle(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c != DR_MDL_TYPE_NORMAL) {
    m_vtxMeshObj = nullptr;
  } else {
    m_vtxMeshObj = static_cast<DrMdoCtlNom *>(drMdl)->unknown1d8;
  }
}

void ScnObjAccMdlParticle::setActive(bool isActive, u32 index) {
  if (m_vtxMeshObj != nullptr) {
    m_vtxMeshObj->setActive(isActive, index);
  }
}

void ScnObjAccMdlParticle::setInitVector(const mm::Vec3 &vector) {
  if (m_vtxMeshObj != nullptr) {
    m_vtxMeshObj->unknowne0 = vector;
  }
}

void ScnObjAccMdlParticle::setAddVector(const mm::Vec3 &vector) {
  if (m_vtxMeshObj != nullptr) {
    m_vtxMeshObj->unknownf0 = vector;
  }
}

ScnObjAccGpuCheck::ScnObjAccGpuCheck(DrGpuCheckBase *gpuCheck) : m_gpuCheck(gpuCheck) {}

void ScnObjAccGpuCheck::setPos(const mm::Vec3 &position, f32 radius) { m_gpuCheck->setPos(position, radius); }

bool ScnObjAccGpuCheck::isRender() const { return m_gpuCheck->isRender(); }

DrGpuCheckBase *ScnObjAccGpuCheck::create(u32 type) {
  DrCreator creator;
  return creator.createGpuCheckObj(type);
}

ScnObjAccStmReadObj::ScnObjAccStmReadObj(DrStmReadObj *readObj) : m_readObj(readObj) {}

void ScnObjAccStmReadObj::readType(ReadType type) {
  switch (type) {
  case READ_TYPE_NONE:
    m_readObj->unknown18 = 0;
    break;
  case READ_TYPE_LOAD:
    m_readObj->unknown18 = 1;
    break;
  case READ_TYPE_SIZE:
    m_readObj->unknown18 = 2;
    break;
  }
}

u64 ScnObjAccStmReadObj::getAdder() { return m_readObj->getAdder(); }

DrStmReadObj *ScnObjAccStmReadObj::create(const char *path) {
  DrCreator creator;
  return creator.createStmLoadObj(path);
}

DrStmReadObj *ScnObjAccStmReadObj::createSizeObj(u32 size) {
  DrCreator creator;
  return creator.createStmSizeObj(size);
}

ScnObjAccSeamResMdlInfo::ScnObjAccSeamResMdlInfo() {}

ScnObjAccSeamResMdlInfo::ScnObjAccSeamResMdlInfo(ScnObjModel *model) { setDrMdl(model); }

void ScnObjAccSeamResMdlInfo::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c == DR_MDL_TYPE_SEAM) {
    m_seam = static_cast<DrMdoCtlSeamAll *>(drMdl);
  } else {
    m_seam = nullptr;
  }
}

bool ScnObjAccSeamResMdlInfo::isReadSafe() const {
  if (m_seam == nullptr) {
    return false;
  }
  return m_seam->isReadSafe();
}

ScnObjAccSeamPos::ScnObjAccSeamPos() : m_instAnmObj(nullptr) {}

ScnObjAccSeamPos::ScnObjAccSeamPos(ScnObjModel *model) : m_instAnmObj(nullptr) { setDrMdl(model); }

void ScnObjAccSeamPos::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c == DR_MDL_TYPE_SEAM) {
    m_instAnmObj = &static_cast<DrMdoCtlSeam *>(drMdl)->unknown698;
  } else if (drMdl->unknown1c == DR_MDL_TYPE_POSITION) {
    m_instAnmObj = &static_cast<DrMdoCtlPos *>(drMdl)->unknown1e8;
  } else {
    m_instAnmObj = nullptr;
  }
}

u32 ScnObjAccSeamPos::getMax() const {
  if (m_instAnmObj == nullptr || m_instAnmObj->unknown00 == nullptr) {
    return 0;
  }
  return m_instAnmObj->unknown00->unknown04;
}

u32 ScnObjAccSeamPos::getAnmMax() const {
  if (m_instAnmObj == nullptr || m_instAnmObj->unknown00 == nullptr) {
    return 0;
  }
  return m_instAnmObj->unknown00->unknown08;
}

ScnObjAccPartsPos ScnObjAccSeamPos::getObj(u32 index) {
  if (m_instAnmObj == nullptr) {
    return ScnObjAccPartsPos(nullptr);
  }
  return ScnObjAccPartsPos(m_instAnmObj->getObj(index));
}

int ScnObjAccSeamPos::getObjIdx(const char *name) {
  if (m_instAnmObj == nullptr) {
    return -1;
  }
  return m_instAnmObj->getObjIdx(name);
}

ScnObjAccPartsPos::ScnObjAccPartsPos(DrResMdoInstPartsObj *partsObj) : m_partsObj(partsObj) {}

void ScnObjAccPartsPos::setMatrix(const mm::Mat44 &matrix) { m_partsObj->setMatrix(matrix); }

void ScnObjAccPartsPos::getMatrix(mm::Mat44 &matrix) { m_partsObj->getMatrix(matrix); }

const char *ScnObjAccPartsPos::getName() const { return m_partsObj->unknown10 + m_partsObj->unknown18->unknown00; }

u16 ScnObjAccPartsPos::getID() const { return m_partsObj->unknown18->unknown08; }

bool ScnObjAccPartsPos::isPosAnm() const { return m_partsObj->unknown18->isPosAnm; }

bool ScnObjAccPartsPos::isNodeAnm() const { return m_partsObj->unknown18->isNodeAnm; }

bool ScnObjAccPartsPos::isPosMatrix() const { return m_partsObj->unknown18->isPosAnm || m_partsObj->unknown18->isPosMatrix; }

bool ScnObjAccPartsPos::isRandomStart() const { return m_partsObj->unknown18->isRandomStart; }

u32 ScnObjAccPartsPos::isSwitch() const { return m_partsObj->unknown18->isSwitch; }

bool ScnObjAccPartsPos::isColiOff() const { return m_partsObj->unknown08.isColiOff; }

bool ScnObjAccPartsPos::isColiSkipData() const { return m_partsObj->unknown08.isColiSkipData; }

f32 ScnObjAccPartsPos::getAlpha() const { return m_partsObj->unknown28; }

void ScnObjAccPartsPos::setAlpha(f32 alpha) { m_partsObj->unknown28 = alpha; }

bool ScnObjAccPartsPos::isLoop() const { return m_partsObj->unknown08.isLoop; }

void ScnObjAccPartsPos::setPosFrame(f32 frame) { m_partsObj->setPosFrame(frame); }

f32 ScnObjAccPartsPos::getPosFrame() const { return m_partsObj->getPosFrame(); }

f32 ScnObjAccPartsPos::getPosMaxFrame() const { return m_partsObj->getPosMaxFrame(); }

f32 ScnObjAccPartsPos::getPosStartFrame() const { return m_partsObj->getPosStartFrame(); }

void ScnObjAccPartsPos::setNodeFrame(f32 frame) { m_partsObj->setNodeFrame(frame); }

f32 ScnObjAccPartsPos::getNodeFrame() const { return m_partsObj->getNodeFrame(); }

f32 ScnObjAccPartsPos::getNodeMaxFrame() const { return m_partsObj->getNodeMaxFrame(); }

f32 ScnObjAccPartsPos::getNodeStartFrame() const { return m_partsObj->getNodeStartFrame(); }

void ScnObjAccPartsPos::getAnmMatrix(mm::Mat44 *matrix) const { m_partsObj->getAnmMatrix(*matrix); }

u32 ScnObjAccPartsPos::getSwitchMax() const { return m_partsObj->getSwitchMax(); }

u32 ScnObjAccPartsPos::getSwitchIndex(u32 index) const { return m_partsObj->getSwitchIndex(index); }

u32 ScnObjAccPartsPos::getSwitchID() const { return m_partsObj->getSwitchID(); }

void ScnObjAccPartsPos::setSwitchID(u32 id) { m_partsObj->setSwitchID(id); }

ScnObjAccSeamEtcPos::ScnObjAccSeamEtcPos() : m_etcPosList(nullptr) {}

ScnObjAccSeamEtcPos::ScnObjAccSeamEtcPos(ScnObjModel *model) : m_etcPosList(nullptr) { setDrMdl(model); }

void ScnObjAccSeamEtcPos::setDrMdl(ScnObjModel *model) {
  DrMdlObj *drMdl = static_cast<ScnObjModelDrSys *>(model)->unknown3d8;
  if (drMdl->unknown1c == DR_MDL_TYPE_SEAM) {
    m_etcPosList = &static_cast<DrMdoCtlSeam *>(drMdl)->unknown6c8;
  } else {
    m_etcPosList = nullptr;
  }
}

u32 ScnObjAccSeamEtcPos::getObjMax() const {
  if (m_etcPosList == nullptr) {
    return 0;
  }
  return m_etcPosList->unknown08;
}

ScnObjAccPartsEtcPos ScnObjAccSeamEtcPos::getObj(u32 index) { return ScnObjAccPartsEtcPos(&m_etcPosList->unknown00[index]); }

const char *ScnObjAccPartsEtcPos::getObjName() const {
  const MdsSeamEtcPosData *data = m_etcPos->unknown00;
  return reinterpret_cast<const char *>(data) + data->unknown00;
}

const char *ScnObjAccPartsEtcPos::getEffName() const {
  const MdsSeamEtcPosData *data = m_etcPos->unknown00;
  return reinterpret_cast<const char *>(data) + data->unknown04;
}

f32 ScnObjAccPartsEtcPos::getRange() const { return m_etcPos->unknown00->unknown08; }

f32 ScnObjAccPartsEtcPos::getNearClip(u32 index) const { return m_etcPos->unknown00->unknown14[index]; }

f32 ScnObjAccPartsEtcPos::getFarClip(u32 index) const { return m_etcPos->unknown00->unknown1c[index]; }

u32 ScnObjAccPartsEtcPos::getMatrixMax() const { return m_etcPos->unknown00->unknown0c; }

const mm::Mat44 *ScnObjAccPartsEtcPos::getMatrix(u32 index) const {
  const MdsSeamEtcPosData *data = m_etcPos->unknown00;
  const mm::Mat44 *matrices = reinterpret_cast<const mm::Mat44 *>(reinterpret_cast<const u8 *>(data) + data->unknown10);
  return &matrices[index];
}

bool ScnObjAccPartsEtcPos::isDisp(u32 index) const {
  if (!m_etcPos->unknown08) {
    const MdsSeamEtcPosData *data = m_etcPos->unknown00;
    u16 group = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(data) + data->unknown24)[index];
    if (group != 0 && (DrMan::getIns()->unknown1d20[group >> 5] & (1 << (group & 31)))) {
      return false;
    }
  }
  return true;
}

} // namespace ml
