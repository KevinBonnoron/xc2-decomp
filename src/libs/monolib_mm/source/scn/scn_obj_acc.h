#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Col4;
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {
class DrGpuCheckBase;
class DrMdlObj;
class DrMdoCtlSeamAll;
class DrMdoMat;
class DrResEtcPamObj;
class DrResMdoInstAnmObj;
class DrResMdoInstPartsObj;
class DrResMdoMeshObj;
class DrResMdoShdObj;
class DrResMdoVtxMeshObj;
class DrStmReadObj;
class ScnObjModel;
struct DrSeamEtcPos;
struct DrSeamEtcPosList;
struct MdlVtxParticle;
struct MdoWrkAvatar;
struct MdoWrkMatEntry;
struct MdoWrkShaderParm;
struct MdsMeshPartsInfo;
struct MdsMatInfoHeader;
struct VolumeFadeParams;

struct DrMdlAfterImageParams {
  f32 unknown00;      // Inferred role: count; original member name unknown.
  f32 unknown04;      // Inferred role: span; original member name unknown.
  f32 unknown08;      // Inferred role: fade; original member name unknown.
  mm::Col3 unknown0c; // Inferred role: head color; original member name unknown.
  f32 unknown18;      // Inferred role: head alpha; original member name unknown.
  f32 unknown1c;      // Inferred role: head emissive; original member name unknown.
  f32 unknown20;      // Inferred role: head scale; original member name unknown.
  mm::Col3 unknown24; // Inferred role: tail color; original member name unknown.
  f32 unknown30;      // Inferred role: tail alpha; original member name unknown.
  f32 unknown34;      // Inferred role: tail emissive; original member name unknown.
  f32 unknown38;      // Inferred role: tail scale; original member name unknown.
};

static_assert(offsetof(DrMdlAfterImageParams, unknown0c) == 0x0c, "");
static_assert(offsetof(DrMdlAfterImageParams, unknown18) == 0x18, "");
static_assert(offsetof(DrMdlAfterImageParams, unknown24) == 0x24, "");
static_assert(offsetof(DrMdlAfterImageParams, unknown38) == 0x38, "");

struct ScnObjModelDrTexutre {
  grlib::CGLibTextureBuffer *texture;
};

class ScnObjAccResMdlInfo {
public:
  ScnObjAccResMdlInfo();
  ScnObjAccResMdlInfo(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  int getViewNum() const;
  void setChangeViewNum(int viewNum);
  void setFrameSpd(f32 speed);
  void setMatrix(const mm::Mat44 &matrix);
  void setGroups(int groups);
  int getGroups() const;
  const mm::Vec3 &getAABBMax() const;
  const mm::Vec3 &getAABBMin() const;
  const mm::Vec3 &getCenter() const;
  f32 getLength() const;
  void getInitialVertexAABBMax(mm::Vec3 &max, bool isScaled) const;
  void getInitialVertexAABBMin(mm::Vec3 &min, bool isScaled) const;
  int isGpuRender() const;
  void getCamPosToNewPosScale(mm::Vec3 &position, f32 &scale, const mm::Vec3 &cameraPosition, const mm::Vec3 &targetPosition, f32 fovy);
  void setAlpha(f32 alpha);
  f32 getAlpha() const;
  void setBloom(f32 bloom);
  f32 getBloom() const;
  void setWriteStencil(bool isEnable);
  void setAlwaysMiddleTexStm(bool isEnable);
  void setGpuClip(bool isClip);
  void setSpBlurOff(bool isEnable);
  void setAlwaysTexStm(bool isEnable);
  void setOcclusionQuery(bool isEnable);
  void setDblBuffAlpha(bool isEnable);
  void setSpAlphaMode(bool isEnable);
  void setCamCheckMode(bool isEnable);
  bool isCamCheckResl() const;
  bool isMdlTexStm() const;
  bool isMemTexStm() const;
  bool isMemMiddleTexStm() const;
  void setCreateDisplayList();
  void setExpressDrawMode(bool isEnable);
  void setExtraShader(const void *shader);
  void releaseExtraShader();
  void setSimpleShadow(bool isEnable);
  static void getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);
  void setClone(const ScnObjModel *model);
  void createAfterImage(const DrMdlAfterImageParams &params);
  void releaseAfterImage();

private:
  DrMdlObj *m_drMdl;
};

class ScnObjAccResNode {
public:
  ScnObjAccResNode();
  ScnObjAccResNode(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  void setDrMdl(DrMdlObj *drMdl);
  int getBoneMax() const;
  int getBoneIndex(const char *name) const;
  const char *getBoneName(int index) const;
  void setBoneMat(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getBoneMat(int index) const;
  mm::Mat44 *getBoneMatPtr(int index);

private:
  DrMdlObj *m_drMdl;
};

class ScnObjAccEtcParams {
public:
  ScnObjAccEtcParams();
  ScnObjAccEtcParams(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  u32 getMax() const;
  const char *getName(u32 index) const;
  int getIndex(const char *name) const;
  f32 getParams(u32 index) const;
  void setParams(u32 index, f32 value);
  void setPreParams(u32 index, f32 value);
  void setInitParams(u32 index, f32 value);
  void setRimBloom(bool isEnable);

private:
  DrResEtcPamObj *m_etcPamObj;
};

class ScnObjAccResMaterial {
public:
  ScnObjAccResMaterial();
  ScnObjAccResMaterial(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  MdoWrkMatEntry *getMatRes(int index);
  MdsMatInfoHeader *getMatData(int index);

private:
  MdsMatInfoHeader *m_matData;
  MdoWrkMatEntry *m_matEntries;
  u32 m_matCount;
};

class ScnObjAccResSubMesh {
public:
  ScnObjAccResSubMesh();
  ScnObjAccResSubMesh(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  int getExtMax() const;
  int getExtIdx(const char *name) const;
  const char *getExtName(int index) const;
  const char *getExtBoneName(int index) const;
  bool isPosRes(int index) const;
  mm::Mat44 *getExtOfsMat(int index) const;
  void setExtAlpha(int index, f32 alpha);
  f32 getExtAlpha(int index) const;
  void setExtRegisterMatrix(int index, bool isRegister);
  void setExtMatrix(int index, const mm::Mat44 &matrix);
  u8 getExtVolumeFadeEffect(int index) const;

private:
  const MdsMeshPartsInfo *m_partsInfos;
  DrResMdoMeshObj *m_meshObj;
};

class ScnObjAccResDecShader {
public:
  ScnObjAccResDecShader();
  ScnObjAccResDecShader(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  u32 getMax() const;
  const char *getDecName(u32 index) const;
  u32 getID(u32 index) const;
  int getIdx(const char *name) const;
  int getIdx(u32 id) const;
  void setParm(u32 index, u32 parm);
  u32 getParm(u32 index) const;
  u32 getParmMax(u32 index) const;

private:
  DrResMdoShdObj *m_shdObj;
};

class ScnObjAccResAvatar {
public:
  ScnObjAccResAvatar();
  ScnObjAccResAvatar(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  bool isAvatarChar() const;
  bool isAvatarDoll() const;
  bool isAvatarEyeTex() const;
  bool isAvatarMapMode() const;
  void setAvatarCharColor(int index, const mm::Col4 &color);
  void setAvatarDollColor(int index, const mm::Col4 &color);
  void setAvatarDollMat(bool isEnable);
  void setAvatarMapColor(int index, const mm::Col3 &color);
  f32 *getAvatarCharColor(int index);
  f32 *getAvatarDollColor(int index);
  mm::Col3 *getAvatarMapColor(int index) const;
  void setAvatarTexture(ScnObjModelDrTexutre *texture, u32 index);
  void resetAvatarTexture(u32 index);
  void setAvatarEyeTexture(ScnObjModelDrTexutre *texture);
  void resetAvatarEyeTexture();
  void resetAvatarTexture();

private:
  MdoWrkAvatar *m_avatar;
  DrMdlObj *m_drMdl;
};

class ScnObjAccResShaderParm {
public:
  ScnObjAccResShaderParm();
  ScnObjAccResShaderParm(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  void setColor(int index, const mm::Col3 &color);
  void setVal(int index, f32 value);
  const mm::Col3 *getColor(int index) const;
  f32 getVal(int index) const;

private:
  MdoWrkShaderParm *m_shaderParm;
};

class ScnObjAccVolumeFade {
public:
  ScnObjAccVolumeFade();
  ScnObjAccVolumeFade(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  ~ScnObjAccVolumeFade();
  u32 getMax() const;
  void setParams(const VolumeFadeParams &params, int index);
  void setRatio(f32 ratio, int index);
  f32 getRatio(u32 index) const;

private:
  DrMdoMat *m_drMdl;
};

class ScnObjAccRimBloom {
public:
  ScnObjAccRimBloom();
  ScnObjAccRimBloom(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  ~ScnObjAccRimBloom();
  bool isExist() const;
  void setRimColor(const mm::Col3 &color);
  const mm::Col3 &getRimColor() const;
  void setRimEmissive(f32 emissive);
  f32 getRimEmissive() const;
  void setRimPower(f32 power);
  f32 getRimPower() const;
  void setBlackRatio(f32 ratio);
  f32 getBlackRatio() const;

private:
  DrMdlObj *m_drMdl;
};

class ScnObjAccMdlParticle {
public:
  ScnObjAccMdlParticle();
  ScnObjAccMdlParticle(ScnObjModel *model);
  void setActive(bool isActive, u32 index);
  void setParams(const MdlVtxParticle &params);
  void setInitVector(const mm::Vec3 &vector);
  void setAddVector(const mm::Vec3 &vector);

private:
  DrResMdoVtxMeshObj *m_vtxMeshObj;
};

class ScnObjAccGpuCheck {
public:
  ScnObjAccGpuCheck(DrGpuCheckBase *gpuCheck);
  void setPos(const mm::Vec3 &position, f32 radius);
  bool isRender() const;
  static DrGpuCheckBase *create(u32 type);

private:
  DrGpuCheckBase *m_gpuCheck;
};

class ScnObjAccStmReadObj {
public:
  enum ReadType {
    READ_TYPE_NONE,
    READ_TYPE_LOAD,
    READ_TYPE_SIZE,
  };

  ScnObjAccStmReadObj(DrStmReadObj *readObj);
  void readType(ReadType type);
  u64 getAdder();
  static DrStmReadObj *create(const char *path);
  static DrStmReadObj *createSizeObj(u32 size);

private:
  DrStmReadObj *m_readObj;
};

class ScnObjAccSeamResMdlInfo {
public:
  ScnObjAccSeamResMdlInfo();
  ScnObjAccSeamResMdlInfo(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  bool isReadSafe() const;

private:
  DrMdoCtlSeamAll *m_seam;
};

class ScnObjAccPartsPos {
public:
  ScnObjAccPartsPos(DrResMdoInstPartsObj *partsObj);
  ~ScnObjAccPartsPos() {}
  void setMatrix(const mm::Mat44 &matrix);
  void getMatrix(mm::Mat44 &matrix);
  const char *getName() const;
  u16 getID() const;
  bool isPosAnm() const;
  bool isNodeAnm() const;
  bool isPosMatrix() const;
  bool isRandomStart() const;
  u32 isSwitch() const;
  bool isColiOff() const;
  bool isColiSkipData() const;
  f32 getAlpha() const;
  void setAlpha(f32 alpha);
  bool isLoop() const;
  void setPosFrame(f32 frame);
  f32 getPosFrame() const;
  f32 getPosMaxFrame() const;
  f32 getPosStartFrame() const;
  void setNodeFrame(f32 frame);
  f32 getNodeFrame() const;
  f32 getNodeMaxFrame() const;
  f32 getNodeStartFrame() const;
  void getAnmMatrix(mm::Mat44 *matrix) const;
  u32 getSwitchMax() const;
  u32 getSwitchIndex(u32 index) const;
  u32 getSwitchID() const;
  void setSwitchID(u32 id);

private:
  DrResMdoInstPartsObj *m_partsObj;
};

class ScnObjAccSeamPos {
public:
  ScnObjAccSeamPos();
  ScnObjAccSeamPos(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  u32 getMax() const;
  u32 getAnmMax() const;
  ScnObjAccPartsPos getObj(u32 index);
  int getObjIdx(const char *name);

private:
  DrResMdoInstAnmObj *m_instAnmObj;
};

class ScnObjAccPartsEtcPos {
public:
  explicit ScnObjAccPartsEtcPos(DrSeamEtcPos *etcPos) : m_etcPos(etcPos) {}
  ~ScnObjAccPartsEtcPos() {}
  const char *getObjName() const;
  const char *getEffName() const;
  f32 getRange() const;
  f32 getNearClip(u32 index) const;
  f32 getFarClip(u32 index) const;
  u32 getMatrixMax() const;
  const mm::Mat44 *getMatrix(u32 index) const;
  bool isDisp(u32 index) const;

private:
  DrSeamEtcPos *m_etcPos;
};

class ScnObjAccSeamEtcPos {
public:
  ScnObjAccSeamEtcPos();
  ScnObjAccSeamEtcPos(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  u32 getObjMax() const;
  ScnObjAccPartsEtcPos getObj(u32 index);

private:
  DrSeamEtcPosList *m_etcPosList;
};

} // namespace ml
