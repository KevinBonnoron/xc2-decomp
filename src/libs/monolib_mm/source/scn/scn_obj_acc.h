#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Col4;
struct Mat44;
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
struct unknown059;
struct unknown060;
struct unknown023;
class DrResMdoMat;
struct unknown024;
struct unknown020;
struct MdsMatInfoHeader;

// Layout evidence: ScnObjAccVolumeFade::setParams (0x7107b42cc) copies 0x3c bytes then the members at 0x40, 0x50 and 0x9c to 0xa4;
// gf::GfVolumeFade::copyVolumeFadeParams (0x7104f74a4) fills 0x00..0x3c with five 12 byte colors, 0x40 and 0x50 with the two aligned
// vectors and 0x60..0x9c with three groups of five floats.
struct VolumeFadeParams {
  mm::Col3 unknown00[5]; // Inferred role: colors; original member name unknown.
  mm::Vec3 unknown40;    // Inferred role: position; original member name unknown.
  mm::Vec3 unknown50;    // Inferred role: scale; original member name unknown.
  f32 unknown60[5];      // Inferred role: first group of five floats; original member name unknown.
  f32 unknown74[5];      // Inferred role: second group of five floats; original member name unknown.
  f32 unknown88[5];      // Inferred role: third group of five floats; original member name unknown.
  f32 unknown9c;         // Inferred role: frame; original member name unknown.
  f32 unknowna0;         // Inferred role: rate; original member name unknown.
  f32 unknowna4;         // Role and original member name unknown.
};

static_assert(offsetof(VolumeFadeParams, unknown40) == 0x40, "");
static_assert(offsetof(VolumeFadeParams, unknown50) == 0x50, "");
static_assert(offsetof(VolumeFadeParams, unknown60) == 0x60, "");
static_assert(offsetof(VolumeFadeParams, unknown74) == 0x74, "");
static_assert(offsetof(VolumeFadeParams, unknown88) == 0x88, "");
static_assert(offsetof(VolumeFadeParams, unknown9c) == 0x9c, "");
static_assert(offsetof(VolumeFadeParams, unknowna4) == 0xa4, "");
static_assert(sizeof(VolumeFadeParams) == 0xb0, "");

// Layout evidence: ScnObjAccMdlParticle::setParams (0x7107b48a0) copies 0x34 bytes into DrResMdoVtxMeshObj 0x100..0x134 with the members at 0x24 and 0x28 clamped to 0..1.
struct MdlVtxParticle {
  f32 unknown00;      // Inferred role: life time; original member name unknown.
  f32 unknown04;      // Inferred role: scale divisor; original member name unknown.
  f32 unknown08;      // Inferred role: speed; original member name unknown.
  f32 unknown0c;      // Inferred role: gravity; original member name unknown.
  u32 unknown10;      // Inferred role: particle count limit; original member name unknown.
  mm::Col3 unknown14; // Inferred role: color; original member name unknown.
  f32 unknown20;      // Role and original member name unknown.
  f32 unknown24;      // Inferred role: ratio clamped to 0..1; original member name unknown.
  f32 unknown28;      // Inferred role: ratio clamped to 0..1; original member name unknown.
  f32 unknown2c;      // Role and original member name unknown.
  f32 unknown30;      // Role and original member name unknown.
};

static_assert(offsetof(MdlVtxParticle, unknown10) == 0x10, "");
static_assert(offsetof(MdlVtxParticle, unknown14) == 0x14, "");
static_assert(offsetof(MdlVtxParticle, unknown20) == 0x20, "");
static_assert(offsetof(MdlVtxParticle, unknown30) == 0x30, "");
static_assert(sizeof(MdlVtxParticle) == 0x34, "");

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
  DrResMdoMat *getMatRes(int index);
  const MdsMatInfoHeader *getMatData(int index);

private:
  const MdsMatInfoHeader *m_matData;
  DrResMdoMat *m_matEntries;
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
  const unknown020 *m_partsInfos;
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
  unknown023 *m_avatar;
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
  unknown024 *m_shaderParm;
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
    READ_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
    READ_TYPE_UNKNOWN_1, // Inferred role: load; original name unknown.
    READ_TYPE_UNKNOWN_2, // Inferred role: size; original name unknown.
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
  u32 getID() const;
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
  explicit ScnObjAccPartsEtcPos(unknown059 *etcPos) : m_etcPos(etcPos) {}
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
  unknown059 *m_etcPos;
};

class ScnObjAccSeamEtcPos {
public:
  ScnObjAccSeamEtcPos();
  ScnObjAccSeamEtcPos(ScnObjModel *model);
  void setDrMdl(ScnObjModel *model);
  u32 getObjMax() const;
  ScnObjAccPartsEtcPos getObj(u32 index);

private:
  unknown060 *m_etcPosList;
};

} // namespace ml
