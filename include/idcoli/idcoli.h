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
  ColiLinkList() : m_head(nullptr), m_tail(nullptr) {}

  T *m_head;
  T *m_tail;
};

struct IDColiTreeObj {
  IDColiTreeObj *unknown00; // Inferred role: prev; original member name unknown.
  IDColiTreeObj *unknown08; // Inferred role: next; original member name unknown.
};

static_assert(offsetof(IDColiTreeObj, unknown08) == 0x8, "");
static_assert(sizeof(IDColiTreeObj) == 0x10, "");

struct unknown003 {
  f32 unknown00; // Inferred role: max x; original member name unknown.
  f32 unknown04; // Inferred role: max z; original member name unknown.
  f32 unknown08; // Inferred role: min x; original member name unknown.
  f32 unknown0c; // Inferred role: min z; original member name unknown.
};

static_assert(sizeof(unknown003) == 0x10, "");

class IDColiTreeTop {
public:
  static const u8 COLI_TBL_GRID[5];
  static const u8 COLI_TBL_INDEX[5];

  ~IDColiTreeTop();
  void begin();
  void end();
  void updateTree();
  ColiLinkList<IDColiTreeObj> *getObjList(int x, int z, int level);
  static u32 getMorton2(u32 x, u32 y);
  static u32 getPart1By1(u32 value);

  mm::Vec3 unknown00;                          // Inferred role: max of the registered objects; original member name unknown.
  mm::Vec3 unknown10;                          // Inferred role: min of the registered objects; original member name unknown.
  mm::Vec3 unknown20;                          // Inferred role: max of the tree; original member name unknown.
  mm::Vec3 unknown30;                          // Inferred role: min of the tree; original member name unknown.
  mm::Vec3 unknown40[5];                       // Inferred role: cell size per level; original member name unknown.
  mm::Vec3 unknown90[5];                       // Inferred role: inverse cell size per level; original member name unknown.
  mm::Vec3 unknowne0[5];                       // Inferred role: cell margin per level; original member name unknown.
  u64 unknown130[6];                           // Inferred role: initialized cell bits; original member name unknown.
  u32 unknown160;                              // Inferred role: flags; original member name unknown.
  u32 unknown164;                              // Inferred role: usable level bits; original member name unknown.
  ColiLinkList<IDColiTreeObj> unknown168[341]; // Inferred role: object lists per cell; original member name unknown.
  unknown003 unknown16b8[341];                 // Inferred role: cell bounds; original member name unknown.
};

static_assert(offsetof(IDColiTreeTop, unknown40) == 0x40, "");
static_assert(offsetof(IDColiTreeTop, unknown90) == 0x90, "");
static_assert(offsetof(IDColiTreeTop, unknowne0) == 0xe0, "");
static_assert(offsetof(IDColiTreeTop, unknown130) == 0x130, "");
static_assert(offsetof(IDColiTreeTop, unknown168) == 0x168, "");
static_assert(offsetof(IDColiTreeTop, unknown16b8) == 0x16b8, "");
static_assert(sizeof(IDColiTreeTop) == 0x2c10, "");

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

  IDColiObj *unknown08; // Inferred role: prev; original member name unknown.
  IDColiObj *unknown10; // Inferred role: next; original member name unknown.
  u32 unknown18;        // Inferred role: state; original member name unknown.
  u32 unknown1c;        // Inferred role: update flags; original member name unknown.
  u32 unknown20;        // Inferred role: attr; original member name unknown.
  ObjType unknown24;    // Inferred role: type; original member name unknown.
  u32 unknown28;        // Inferred role: material data; original member name unknown.
  u32 unknown2c;        // Inferred role: material bit; original member name unknown.
  u64 _30;
  u64 _38;
  u32 _40;
  void *unknown48; // Inferred role: user data; original member name unknown.
};

static_assert(offsetof(IDColiObj, unknown18) == 0x18, "");
static_assert(offsetof(IDColiObj, unknown2c) == 0x2c, "");
static_assert(offsetof(IDColiObj, unknown48) == 0x48, "");
static_assert(sizeof(IDColiObj) == 0x50, "");

class IDColiObjBase : public IDColiObj {
public:
  mm::Vec3 unknown50;  // Inferred role: max; original member name unknown.
  mm::Vec3 unknown60;  // Inferred role: min; original member name unknown.
  mm::Mat44 unknown70; // Inferred role: matrix; original member name unknown.
  mm::Vec3 m_size;
  ShapeType unknownc0; // Inferred role: shape type; original member name unknown.
  u32 _c4;
  u32 unknownc8; // Inferred role: off material bit; original member name unknown.
  u8 _cc[0x1cc - 0xcc];
  int unknown1cc; // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(IDColiObjBase, unknown50) == 0x50, "");
static_assert(offsetof(IDColiObjBase, unknown70) == 0x70, "");
static_assert(offsetof(IDColiObjBase, unknownc0) == 0xc0, "");
static_assert(offsetof(IDColiObjBase, unknownc8) == 0xc8, "");
static_assert(sizeof(IDColiObjBase) == 0x1d0, "");

struct unknown001 {
  u8 _00[0x40 - 0x00];
  u32 unknown40; // Inferred role: name offset; original member name unknown.
};

static_assert(offsetof(unknown001, unknown40) == 0x40, "");
static_assert(sizeof(unknown001) == 0x44, "");

struct unknown002 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: version; original member name unknown.
  u32 unknown08; // Inferred role: flags; original member name unknown.
  u32 unknown0c; // Inferred role: info offset; original member name unknown.
};

static_assert(sizeof(unknown002) == 0x10, "");

class IDColiObjData : public IDColiObjBase {
public:
  void createBinary(const void *binary);
  const char *getBoneName(int index) const;
  int getBoneIdx(const char *name) const;
  void setBoneMatrix(int index, const mm::Mat44 &matrix);
  mm::Mat44 &getBoneMatrix(int index);

  const unknown002 *unknown1d0; // Inferred role: binary; original member name unknown.
  const unknown001 *unknown1d8; // Inferred role: bone tbl; original member name unknown.
  u8 _1e0[0x1f0 - 0x1e0];
  mm::Mat44 *unknown1f0; // Inferred role: bone matrix tbl; original member name unknown.
  int unknown1f8;        // Inferred role: bone max; original member name unknown.
  u8 _1fc[0x208 - 0x1fc];
};

static_assert(offsetof(IDColiObjData, unknown1d0) == 0x1d0, "");
static_assert(offsetof(IDColiObjData, unknown1d8) == 0x1d8, "");
static_assert(offsetof(IDColiObjData, unknown1f0) == 0x1f0, "");
static_assert(offsetof(IDColiObjData, unknown1f8) == 0x1f8, "");

class IDColiObjChar : public IDColiObjData {
public:
  u8 _208[0x220 - 0x208];
  f32 unknown220; // Inferred role: adsorption; original member name unknown.
};

static_assert(offsetof(IDColiObjChar, unknown220) == 0x220, "");

class IDColiObjPhantom : public IDColiObjBase {};

class IDColiGrdMoveObj {
public:
  void setMat(const mm::Mat44 &matrix);

  u8 _000[0x1a2 - 0x000];
  u16 unknown1a2; // Inferred role: id; original member name unknown.
  u8 _1a4[0x1b0 - 0x1a4];
  const char *unknown1b0; // Inferred role: name; original member name unknown.
  void *unknown1b8;       // Inferred role: user data; original member name unknown.
  u8 _1c0[0x200 - 0x1c0];
};

static_assert(offsetof(IDColiGrdMoveObj, unknown1a2) == 0x1a2, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1b0) == 0x1b0, "");
static_assert(sizeof(IDColiGrdMoveObj) == 0x200, "");

struct IDColiGrandWork {
  u8 _00[0x70 - 0x00];
  IDColiGrdMoveObj *unknown70; // Inferred role: move objs; original member name unknown.
  int unknown78;               // Inferred role: move max; original member name unknown.
};

static_assert(offsetof(IDColiGrandWork, unknown70) == 0x70, "");

class IDColiObjGrand : public IDColiObj {
public:
  bool getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const;

  IDColiGrandWork unknown50; // Inferred role: work; original member name unknown.
};

static_assert(offsetof(IDColiObjGrand, unknown50) == 0x50, "");

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

  ColiLinkList<IDColiObj> unknown08[4]; // Inferred role: object lists; original member name unknown.
  u8 _48[0xd8 - 0x48];
  IDColiTreeTop *unknownd8[2]; // Inferred role: tree tops; original member name unknown.
  u32 *m_gblIdTbl;
  u32 unknownf0; // Inferred role: sub num; original member name unknown.
  u8 _f4[0x108 - 0xf4];
};

static_assert(offsetof(IDColiManager, unknown08) == 0x8, "");
static_assert(offsetof(IDColiManager, unknownd8) == 0xd8, "");
static_assert(offsetof(IDColiManager, m_gblIdTbl) == 0xe8, "");

class IDColiMove {
public:
  IDColiMove();
  void setShapeParms(f32 radius, f32 height);
  void setAngle(f32 angle);
  void setFloor(f32 floor);
  void setDown(f32 down);
  void setAccuracy(bool accuracy);
  void calcVecDeceleration(f32 &value, mm::Vec3 vector);
  void moveColi(IDColiObj *object, const mm::Vec3 &move);
  bool moveColi(const mm::Vec3 &position, const mm::Vec3 &move);

  u8 _000[0x130];
  mm::Vec3 unknown130; // Inferred role: moved distance; original member name unknown.
  u8 _140[0x1a0 - 0x140];
  mm::Vec3 unknown1a0; // Inferred role: deceleration axis; original member name unknown.
  u8 _1b0[0x1b8 - 0x1b0];
  f32 unknown1b8; // Inferred role: shape parameter; original member name unknown.
  f32 unknown1bc; // Inferred role: shape parameter; original member name unknown.
  f32 m_angle;
  f32 m_floor;
  f32 m_down;
  u8 _1cc[0x1ed - 0x1cc];
  bool m_accuracy;
  u8 _1ee[0x1f3 - 0x1ee];
  bool unknown1f3; // Inferred role: deceleration enabled; original member name unknown.
  u8 _1f4[0x1f8 - 0x1f4];
};

static_assert(offsetof(IDColiMove, unknown130) == 0x130, "");
static_assert(offsetof(IDColiMove, unknown1a0) == 0x1a0, "");
static_assert(offsetof(IDColiMove, unknown1b8) == 0x1b8, "");
static_assert(offsetof(IDColiMove, m_angle) == 0x1c0, "");
static_assert(offsetof(IDColiMove, m_down) == 0x1c8, "");
static_assert(offsetof(IDColiMove, m_accuracy) == 0x1ed, "");
static_assert(offsetof(IDColiMove, unknown1f3) == 0x1f3, "");
static_assert(sizeof(IDColiMove) == 0x200, "");

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
