#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class Scn;
class WinProc;
} // namespace ml

namespace idcoli {

enum ColiState : int;
enum ColiAtrr : int;

enum ObjType {
  OBJ_TYPE_CHARACTER = 1,
  OBJ_TYPE_PHANTOM = 2,
  OBJ_TYPE_GRAND = 3,
};

enum ShapeType {
  SHAPE_TYPE_SPHERE = 0,
  SHAPE_TYPE_BOX = 1,
  SHAPE_TYPE_CAPSULE = 2,
  SHAPE_TYPE_CHARACTER = 3,
  SHAPE_TYPE_BOX_ROTATE = 6,
  SHAPE_TYPE_CAPSULE_ROTATE = 7,
};

template <typename T> struct ColiLinkList {
  T *m_head;
  T *m_tail;
};

class IDColiTreeTop {
public:
  void begin();
  void end();
};

class IDColiObj {
public:
  static const u32 FLAG_LANDING = 1 << 0;
  static const u32 FLAG_OUT_RANGE = 1 << 1;
  static const u32 FLAG_CONTACT_WALL = 1 << 2;

  static const u32 UPDATE_MATRIX = 1 << 3;
  static const u32 UPDATE_SIZE = 1 << 5;
  static const u32 UPDATE_ROTATE = 1 << 10;

  bool isDeleteCall() const;
  IDColiObj();
  virtual ~IDColiObj() {}
  virtual void release();
  void setDeleteCall();
  bool isDeleteAll() const;
  virtual void sizeUpdate() {}
  virtual void update() {}
  virtual bool SweepAndPruneUpdate() { return false; }
  virtual void consistentUpdate() {}

  IDColiObj *m_prev;
  IDColiObj *m_next;
  u32 m_state;
  u32 m_updateFlags;
  u32 m_attr;
  ObjType m_type;
  u32 m_materialData;
  u32 m_materialBit;
  u64 _30;
  u64 _38;
  u32 _40;
  void *m_userData;
};

static_assert(offsetof(IDColiObj, m_state) == 0x18, "");
static_assert(offsetof(IDColiObj, m_materialBit) == 0x2c, "");
static_assert(offsetof(IDColiObj, m_userData) == 0x48, "");
static_assert(sizeof(IDColiObj) == 0x50, "");

class IDColiObjBase : public IDColiObj {
public:
  mm::Vec3 m_max;
  mm::Vec3 m_min;
  mm::Mat44 m_matrix;
  mm::Vec3 m_size;
  ShapeType m_shapeType;
  u32 _c4;
  u32 m_offMaterialBit;
  u8 _cc[0x1cc - 0xcc];
  int m_priority;
};

static_assert(offsetof(IDColiObjBase, m_max) == 0x50, "");
static_assert(offsetof(IDColiObjBase, m_matrix) == 0x70, "");
static_assert(offsetof(IDColiObjBase, m_shapeType) == 0xc0, "");
static_assert(offsetof(IDColiObjBase, m_offMaterialBit) == 0xc8, "");
static_assert(sizeof(IDColiObjBase) == 0x1d0, "");

class IDColiObjData : public IDColiObjBase {
public:
  void createBinary(const void *binary);
  const char *getBoneName(int index) const;
  int getBoneIdx(const char *name) const;
  void setBoneMatrix(int index, const mm::Mat44 &matrix);
  mm::Mat44 &getBoneMatrix(int index);

  u8 _1d0[0x1f0 - 0x1d0];
  mm::Mat44 *m_boneMatrixTbl;
  int m_boneMax;
  u8 _1fc[0x208 - 0x1fc];
};

static_assert(offsetof(IDColiObjData, m_boneMatrixTbl) == 0x1f0, "");
static_assert(offsetof(IDColiObjData, m_boneMax) == 0x1f8, "");

class IDColiObjChar : public IDColiObjData {
public:
  u8 _208[0x220 - 0x208];
  f32 m_adsorption;
};

static_assert(offsetof(IDColiObjChar, m_adsorption) == 0x220, "");

class IDColiObjPhantom : public IDColiObjBase {};

class IDColiGrdMoveObj {
public:
  void setMat(const mm::Mat44 &matrix);

  u8 _000[0x1a2 - 0x000];
  u16 m_id;
  u8 _1a4[0x1b0 - 0x1a4];
  const char *m_name;
  void *m_userData;
  u8 _1c0[0x200 - 0x1c0];
};

static_assert(offsetof(IDColiGrdMoveObj, m_id) == 0x1a2, "");
static_assert(offsetof(IDColiGrdMoveObj, m_name) == 0x1b0, "");
static_assert(sizeof(IDColiGrdMoveObj) == 0x200, "");

struct IDColiGrandWork {
  u8 _00[0x70 - 0x00];
  IDColiGrdMoveObj *m_moveObjs;
  int m_moveMax;
};

static_assert(offsetof(IDColiGrandWork, m_moveObjs) == 0x70, "");

class IDColiObjGrand : public IDColiObj {
public:
  bool getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const;

  IDColiGrandWork m_work;
};

static_assert(offsetof(IDColiObjGrand, m_work) == 0x50, "");

class IDColiManager : public mm::mtl::PtrSingleton<IDColiManager> {
public:
  static int s_nDebIdx;
  static int s_nStkIdx;

  IDColiManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, u32 size);
  ~IDColiManager() override;
  void update();
  void addDelUpdate();
  void consistentUpdate();
  void updateConsistentList(ColiLinkList<IDColiObj> &list);
  void tail();
  IDColiObj *createColiGrand(const void *binary);
  IDColiObj *createColiCharacter();
  IDColiObj *createColiPhantom();
  IDColiObj *getUseObject(ColiLinkList<IDColiObj> &list);
  void updateList(ColiLinkList<IDColiObj> &list);
  static void poolUpdate(void *object);
  int isGblId(u32 id);
  void setGblId(u32 id, bool isClear);
  void *getGblIdTbl();
  void openDebugWindow(ml::WinProc *window);
  void debugDrawCharacter(bool isDraw);
  void debugDrawGrand(bool isDraw);
  void debugDrawPhantom(bool isDraw);

  ColiLinkList<IDColiObj> m_objLists[4];
  u8 _48[0xd8 - 0x48];
  IDColiTreeTop *m_treeTops[2];
  u32 *m_gblIdTbl;
  u32 m_subNum;
  u8 _f4[0x108 - 0xf4];
};

static_assert(offsetof(IDColiManager, m_objLists) == 0x8, "");
static_assert(offsetof(IDColiManager, m_treeTops) == 0xd8, "");
static_assert(offsetof(IDColiManager, m_gblIdTbl) == 0xe8, "");

class IDColiAccMan {
public:
  IDColiAccMan();
  IDColiObj *createColiGrand(const void *binary);
  IDColiObj *createColiCharacter();
  IDColiObj *createColiPhantom();
  bool getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const;
  int isGblId(u32 id);
  void setGblId(u32 id, bool isClear);
  void *getGblIdTbl();
  void setSubNum(u32 num);
  void openDebugWindow(ml::WinProc *window);
  void debugDrawCharacter(bool isDraw);
  void debugDrawGrand(bool isDraw);
  void debugDrawPhantom(bool isDraw);

  u8 _00[0x08 - 0x00];
};

class IDColiPartsMoveGrand {
public:
  IDColiPartsMoveGrand(IDColiGrdMoveObj *moveObj) : m_moveObj(moveObj) {}
  ~IDColiPartsMoveGrand() {}
  const char *getName() const;
  void setMatrix(const mm::Mat44 &matrix);
  void setUserData(void *userData);
  void *getUserData();
  u16 getID() const;

  IDColiGrdMoveObj *m_moveObj;
};

class IDColiParmsGrand {
public:
  IDColiParmsGrand(IDColiObj *object);
  int getMoveMax() const;
  IDColiPartsMoveGrand getMoveObj(u32 index);
  int getMoveObjIdx(const char *name);

  IDColiGrandWork *m_work;
};

class IDColiParmsBase {
public:
  IDColiParmsBase(IDColiObj *object);
  void setPriority(int priority);
  int getPriority() const;
  void setUserData(void *userData);
  void *getUserData();
  bool isAttr(ColiAtrr attribute) const;
  bool isState(ColiState state) const;
  void setState(ColiState state);
  void clearState(ColiState state);
  void setMaterialBit(u32 bit);
  u32 getMaterialBit() const;
  u32 *getMaterialData();
  void setOffMaterialBit(u32 bit);
  u32 getOffMaterialBit() const;
  void setMatrix(const mm::Mat44 &matrix);
  const mm::Mat44 &getMatrix() const;
  const mm::Vec3 &getMax() const;
  const mm::Vec3 &getMin() const;
  void setInstantlyMatrix(const mm::Mat44 &matrix);

  IDColiObjBase *m_object;
};

class IDColiParmsCharacter : public IDColiParmsBase {
public:
  IDColiParmsCharacter(IDColiObj *object);
  void createSphere(f32 radius);
  void createCapsule(f32 radius, f32 height, bool isRotate);
  void createBox(const mm::Vec3 &size, bool isRotate);
  void createCharacter(f32 radius, f32 height);
  void createData(const void *binary);
  void setAdsorption(f32 adsorption);
  f32 getAdsorption() const;

  IDColiObjChar *m_character;
};

class IDColiParmsBone {
public:
  IDColiParmsBone(IDColiObj *object);
  int getBoneMax() const;
  const char *getBoneName(int index) const;
  int getBoneIdx(const char *name);
  void setBoneMatrix(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getBoneMatrix(int index) const;
  mm::Mat44 *getBoneMatrixTbl();

  IDColiObjData *m_data;
};

class IDColiParmsPhantom : public IDColiParmsBase {
public:
  IDColiParmsPhantom(IDColiObj *object);
  void createSphere(f32 radius);
  void createCapsule(f32 radius, f32 height);
  void createBox(const mm::Vec3 &size);
  void createCharacter(f32 radius, f32 height);
  void createData(const void *binary);

  IDColiObjPhantom *m_phantom;
};

} // namespace idcoli
