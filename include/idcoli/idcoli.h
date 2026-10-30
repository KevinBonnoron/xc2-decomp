#pragma once
#include <math.h>
#include <stddef.h>

#include "idcoli/idcoli_grand_mesh.h"
#include "idcoli/idcoli_mem_handle_allocator.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace idcoli {
struct IDCmfPosData;
} // namespace idcoli

namespace ml {
class CriticalSection;
class Scn;
class WinProc;
} // namespace ml

// Inferred role: kind of character collision test; original enumerator names unknown.
enum ColiCheckType {
  ColiCheckType_UNKNOWN_0 = 0,
  ColiCheckType_UNKNOWN_1 = 1,
  ColiCheckType_UNKNOWN_2 = 2,
};

namespace idcoli {

enum ColiState : int;
enum ColiAtrr : int;

// Inferred role: obj type; original type name unknown.
enum unknown098 {
  unknown098_1 = 1, // Inferred role: character; original name unknown.
  unknown098_2 = 2, // Inferred role: phantom; original name unknown.
  unknown098_3 = 3, // Inferred role: grand; original name unknown.
};

enum ShapeType : unsigned int {
  SHAPE_TYPE_SPHERE = 0,
  SHAPE_TYPE_BOX = 1,
  SHAPE_TYPE_CAPSULE = 2,
  SHAPE_TYPE_CHARACTER = 3,
  SHAPE_TYPE_BOX_ROTATE = 6,
  SHAPE_TYPE_CAPSULE_ROTATE = 7,
};

template <typename T> struct ColiLinkList {
  ColiLinkList() : m_head(nullptr), m_tail(nullptr) {}

  // Inferred helper: appends an object to the list; original name unknown.
  void unknown001(T *object) {
    if (m_tail == nullptr) {
      m_head = object;
      m_tail = object;
      object->unknown08 = nullptr;
    } else {
      m_tail->unknown10 = object;
      object->unknown08 = m_tail;
      m_tail = object;
    }
    object->unknown10 = nullptr;
  }

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

  IDColiTreeTop();
  ~IDColiTreeTop();
  void begin();
  void end();
  void updateTree();
  int setupTreeList(IDColiTreeObj *node, const mm::Vec3 &max, const mm::Vec3 &min);
  void initCehckTree(int index, int level, int x, int z);
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

  static const f32 OBJ_CALC_RADIUS;

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
  unknown098 unknown24; // Inferred role: type; original member name unknown.
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

enum IdSweepAxisType : unsigned int {
  IdSweepAxisType_UNKNOWN_0 = 0,
  IdSweepAxisType_UNKNOWN_1 = 1,
};

enum IdVectorAxisType : unsigned int {
  IdVectorAxisType_UNKNOWN_0 = 0,
  IdVectorAxisType_UNKNOWN_1 = 1,
  IdVectorAxisType_UNKNOWN_2 = 2,
};

enum IDColiBaseType : unsigned int {
  IDColiBaseType_UNKNOWN_0 = 0,
  IDColiBaseType_UNKNOWN_1 = 1,
  IDColiBaseType_UNKNOWN_2 = 2,
  IDColiBaseType_UNKNOWN_3 = 3,
  IDColiBaseType_UNKNOWN_4 = 4,
  IDColiBaseType_UNKNOWN_5 = 5,
  IDColiBaseType_UNKNOWN_6 = 6,
  IDColiBaseType_UNKNOWN_7 = 7,
};

class IDColiPrimitive {
public:
  static void createSphere(CLSphereWork &sphere, const IDColiInput &input);
  static void createSphere(CLSphereWork &sphere, const mm::Vec3 &center, f32 radius);
  static void createAaBbBox(mm::Vec3 &max, mm::Vec3 &min, const void *data);
  static void createAaBbPoli(mm::Vec3 &max, mm::Vec3 &min, const void *data);
  static void createBaPosSphere(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data);
  static void createBaPosBox(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data);
  static void createAaBbCapsule(mm::Vec3 &max, mm::Vec3 &min, const void *data);
  static void createBaPosCapsule(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data);
  static void createBaPosPoli(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data);
  static void createLine(CLLineWork &line, const IDColiInput &input);
  static void createLine(CLLineWork &line, const mm::Vec3 &start, const mm::Vec3 &end);
  static void createRay(CLRayWork &ray, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength);
  static void createCapsule(CLCapsuleWork &capsule, const IDColiInput &input);
  static void createBaseSphere(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void calcBoxAaBb(CLBoxWork *box);
  static void calcCapsuleSetup(CLCapsuleWork *capsule);
  static void calcBaseBoxSetup(CLBoxWork *box, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void calcPosDataSetup(IDCmfPosData *posData, const mm::Mat44 &matrix, const mm::Vec3 &max, const mm::Vec3 &min);
  static void createBaseBox(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void createBaseCapsule(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void createBaseCharacter(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void createBasePoli(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size);
  static void createSubBaseCharacter(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size, bool isSub);
  static void (*const s_CallPrimSet[5])(void *, IDColiBaseType &, const mm::Mat44 &, const mm::Vec3 &);
  static void (*const s_CallAaBb[5])(mm::Vec3 &, mm::Vec3 &, const void *);
  static void (*const s_CallBasePos[5])(mm::Vec3 &, mm::Vec3 &, bool &, f32 &, f32 &, const void *);
};

// Inferred helper: scale of a matrix, length of the sum of its first three rows; original name unknown.
inline f32 unknown123(const mm::Mat44 &matrix) {
  f32 x = matrix.rows[0][0] + matrix.rows[1][0] + matrix.rows[2][0];
  f32 y = matrix.rows[0][1] + matrix.rows[1][1] + matrix.rows[2][1];
  f32 z = matrix.rows[0][2] + matrix.rows[1][2] + matrix.rows[2][2];
  return sqrtf(x * x + y * y + z * z);
}

class IDColiObjBase : public IDColiObj {
public:
  IDColiObjBase(IDColiTreeTop *tree);
  ~IDColiObjBase() override {
    // A body that generates no code still makes the destructor keep its vtable pointer store, which the game's destructors show.
    (void)0;
  }
  void sweepPush(IDColiObjBase *object);
  void sweepPop();
  bool sweepUpdate(IdSweepAxisType sweepAxis, IdVectorAxisType vectorAxis);
  void sweepTreeMax(IdSweepAxisType sweepAxis, IdVectorAxisType vectorAxis);
  void defTreeUpdate();
  void updateBaseTree();

  mm::Vec3 unknown50;  // Inferred role: max; original member name unknown.
  mm::Vec3 unknown60;  // Inferred role: min; original member name unknown.
  mm::Mat44 unknown70; // Inferred role: matrix; original member name unknown.
  mm::Vec3 m_size;
  ShapeType unknownc0;      // Inferred role: shape type; original member name unknown.
  IDColiBaseType unknownc4; // Inferred role: primitive type; original member name unknown.
  u32 unknownc8;            // Inferred role: off material bit; original member name unknown.
  u8 _cc[0xd0 - 0xcc];
  u8 unknownd0[0x180 - 0xd0];   // Inferred role: primitive work; original member name unknown.
  f32 unknown180[2];            // Inferred role: sweep max per axis; original member name unknown.
  IDColiObjBase *unknown188[2]; // Inferred role: sweep prev per axis; original member name unknown.
  IDColiObjBase *unknown198[2]; // Inferred role: sweep next per axis; original member name unknown.
  IDColiTreeTop *unknown1a8;    // Inferred role: tree top; original member name unknown.
  IDColiTreeObj unknown1b0;     // Inferred role: tree list node; original member name unknown.
  IDColiObjBase *unknown1c0;    // Inferred role: owner of the tree node; original member name unknown.
  int unknown1c8;               // Inferred role: tree cell index; original member name unknown.
  int unknown1cc;               // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(IDColiObjBase, unknown50) == 0x50, "");
static_assert(offsetof(IDColiObjBase, unknown70) == 0x70, "");
static_assert(offsetof(IDColiObjBase, unknownc0) == 0xc0, "");
static_assert(offsetof(IDColiObjBase, unknownc4) == 0xc4, "");
static_assert(offsetof(IDColiObjBase, unknownc8) == 0xc8, "");
static_assert(offsetof(IDColiObjBase, unknownd0) == 0xd0, "");
static_assert(offsetof(IDColiObjBase, unknown180) == 0x180, "");
static_assert(offsetof(IDColiObjBase, unknown188) == 0x188, "");
static_assert(offsetof(IDColiObjBase, unknown198) == 0x198, "");
static_assert(offsetof(IDColiObjBase, unknown1a8) == 0x1a8, "");
static_assert(offsetof(IDColiObjBase, unknown1b0) == 0x1b0, "");
static_assert(offsetof(IDColiObjBase, unknown1c0) == 0x1c0, "");
static_assert(offsetof(IDColiObjBase, unknown1c8) == 0x1c8, "");
static_assert(offsetof(IDColiObjBase, unknown1cc) == 0x1cc, "");
static_assert(sizeof(IDColiObjBase) == 0x1d0, "");

struct unknown001 {
  f32 unknown00[4][4]; // Inferred role: bone matrix; original member name unknown.
  u32 unknown40;       // Inferred role: name offset; original member name unknown.
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

// Inferred role: list of primitive indices of a CHCL binary, tested together; original type name unknown.
struct unknown061 {
  u32 unknown00; // Inferred role: index list offset; original member name unknown.
  s32 unknown04; // Inferred role: index count; original member name unknown.
};

static_assert(sizeof(unknown061) == 0x8, "");

// Inferred role: info block of a CHCL binary, at unknown002::unknown0c; original type name unknown.
struct unknown022 {
  u32 unknown00; // Inferred role: primitive data offset; original member name unknown.
  s32 unknown04; // Inferred role: primitive count; original member name unknown.
  u32 unknown08; // Inferred role: bone tbl offset; original member name unknown.
  s32 unknown0c; // Inferred role: bone count; original member name unknown.
  u8 _10[0x18 - 0x10];
  unknown061 unknown18; // Inferred role: check list of the parts tested by ColiCheckType_UNKNOWN_1; original member name unknown.
  unknown061 unknown20; // Inferred role: check list of the parts tested by default; original member name unknown.
  unknown061 unknown28; // Inferred role: check list of the parts tested by ColiCheckType_UNKNOWN_2; original member name unknown.
  u32 unknown30;        // Inferred role: move record tbl offset, followed by the grand records; original member name unknown.
  s32 unknown34;        // Inferred role: grand count; original member name unknown.
};

static_assert(offsetof(unknown022, unknown0c) == 0xc, "");
static_assert(offsetof(unknown022, unknown18) == 0x18, "");
static_assert(offsetof(unknown022, unknown20) == 0x20, "");
static_assert(offsetof(unknown022, unknown28) == 0x28, "");
static_assert(offsetof(unknown022, unknown30) == 0x30, "");
static_assert(offsetof(unknown022, unknown34) == 0x34, "");

struct unknown019;

struct unknown008 {
  unknown019 *unknown00; // Inferred role: ground character collision object, set over the primitive work; original member name unknown.
  u8 _08[0xb0 - 0x08];
  IDColiBaseType unknownb0; // Inferred role: primitive type; original member name unknown.
  u8 _b4[0xc0 - 0xb4];
};

static_assert(offsetof(unknown008, unknownb0) == 0xb0, "");
static_assert(sizeof(unknown008) == 0xc0, "");

struct CHCLBaseData {
  mm::Vec3 unknown00; // Inferred role: size; original member name unknown.
  u8 _10[0x50 - 0x10];
};

static_assert(sizeof(CHCLBaseData) == 0x50, "");

struct CHCLBaseInfo {
  u16 unknown00; // Inferred role: primitive type; original member name unknown.
  u8 _02[0x0c - 0x02];
  u32 unknown0c; // Inferred role: index of the grand record; original member name unknown.
  u8 _10[0x18 - 0x10];
};

static_assert(offsetof(CHCLBaseInfo, unknown0c) == 0xc, "");
static_assert(sizeof(CHCLBaseInfo) == 0x18, "");

struct IDCmfPosData {
  // Inferred helper: translation of the matrix; original name unknown.
  mm::Vec3 unknown081() const { return mm::Vec3(unknown00[0][3], unknown00[1][3], unknown00[2][3]); }

  // Inferred helper: rotates a direction into the local space through the inverse matrix; original name unknown.
  void unknown080(mm::Vec3 &local, const mm::Vec3 &direction) const {
    local.x = direction.x * unknown40[0][0] + direction.y * unknown40[0][1] + direction.z * unknown40[0][2];
    local.y = direction.x * unknown40[1][0] + direction.y * unknown40[1][1] + direction.z * unknown40[1][2];
    local.z = direction.x * unknown40[2][0] + direction.y * unknown40[2][1] + direction.z * unknown40[2][2];
  }

  // Inferred helper: brings a point into the local space through the inverse matrix; original name unknown.
  void unknown011(mm::Vec3 &local, const mm::Vec3 &point) const { unknown080(local, point - unknown081()); }

  // Inferred helper: scale of the inverse matrix; original name unknown.
  f32 unknown012() const {
    f32 x = unknown40[0][0] + unknown40[0][1] + unknown40[0][2];
    f32 y = unknown40[1][0] + unknown40[1][1] + unknown40[1][2];
    f32 z = unknown40[2][0] + unknown40[2][1] + unknown40[2][2];
    return sqrtf(x * x + y * y + z * z);
  }

  f32 unknown00[3][4]; // Inferred role: transposed matrix rows, translation in the fourth column; original member name unknown.
  u8 _30[0x40 - 0x30];
  f32 unknown40[3][4]; // Inferred role: transposed inverse matrix rows; original member name unknown.
  u8 _70[0x80 - 0x70];
  mm::Vec3 unknown80; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: min; original member name unknown.
};

static_assert(offsetof(IDCmfPosData, unknown40) == 0x40, "");
static_assert(offsetof(IDCmfPosData, unknown80) == 0x80, "");
static_assert(offsetof(IDCmfPosData, unknown90) == 0x90, "");
static_assert(sizeof(IDCmfPosData) == 0xa0, "");

class IDColiObjGrand;

// Inferred role: grand record of a ground character binary; original type name unknown.
struct unknown025 {
  u32 unknown00; // Inferred role: unknown; original member name unknown.
  u32 unknown04; // Inferred role: offset of the grand binary; original member name unknown.
  u8 _08[0x14 - 0x08];
};

static_assert(offsetof(unknown025, unknown04) == 0x4, "");
static_assert(sizeof(unknown025) == 0x14, "");

// Inferred role: move record of a ground character binary; original type name unknown.
struct unknown026 {
  u8 _00[0x30 - 0x00];
};

static_assert(sizeof(unknown026) == 0x30, "");

struct unknown019 {
  IDCmfPosData unknown00;      // Inferred role: position data; original member name unknown.
  IDColiObjGrand *unknowna0;   // Inferred role: collision object; original member name unknown.
  const unknown026 *unknowna8; // Inferred role: move record; original member name unknown.
  const unknown025 *unknownb0; // Inferred role: grand record; original member name unknown.
  const u8 *unknownb8;         // Inferred role: grand binary; original member name unknown.
};

static_assert(offsetof(unknown019, unknowna0) == 0xa0, "");
static_assert(offsetof(unknown019, unknowna8) == 0xa8, "");
static_assert(offsetof(unknown019, unknownb0) == 0xb0, "");
static_assert(offsetof(unknown019, unknownb8) == 0xb8, "");
static_assert(sizeof(unknown019) == 0xc0, "");

class IDColiObjGrdChar : public IDColiObj {
public:
  IDColiObjGrdChar();
  ~IDColiObjGrdChar() override;
  void workClear();
  static int getWorkSize(const u8 *binary);
  void createWorkBuffer(const u8 *binary, IDColiObj *owner);
  void update() override;
  bool testLine(IDColiResult &result, const IDColiInput &input);
  bool testRay(IDColiResult &result, const IDColiInput &input);
  bool testSphere(IDColiResult &result, const IDColiInput &input);
  bool testCapsule(IDColiResult &result, const IDColiInput &input);
  bool testWallSphere(IDColiResult &result, const IDColiInput &input);
  bool testWallCapsule(IDColiResult &result, const IDColiInput &input);

  // Inferred helper: whether the test can reach this object (owner state, skipped object, material bits, bounds); original name unknown.
  bool unknown171(const IDColiResult &result, const IDColiInput &input) const {
    if ((unknown78->unknown1c & 0x80) || result.unknown108 == unknown78 || (result.unknowne8 & unknown78->unknown2c)) {
      return false;
    }
    if (unknown50.x < input.unknown10.x || unknown60.x > input.unknown00.x || unknown50.z < input.unknown10.z || unknown60.z > input.unknown00.z || unknown50.y < input.unknown10.y ||
        unknown60.y > input.unknown00.y) {
      return false;
    }
    return true;
  }

  mm::Vec3 unknown50;    // Inferred role: max; original member name unknown.
  mm::Vec3 unknown60;    // Inferred role: min; original member name unknown.
  void *unknown70;       // Inferred role: allocated buffer; original member name unknown.
  IDColiObj *unknown78;  // Inferred role: owner; original member name unknown.
  unknown019 *unknown80; // Inferred role: collision objects; original member name unknown.
  int unknown88;         // Inferred role: collision object count; original member name unknown.
};

static_assert(offsetof(IDColiObjGrdChar, unknown50) == 0x50, "");
static_assert(offsetof(IDColiObjGrdChar, unknown60) == 0x60, "");
static_assert(offsetof(IDColiObjGrdChar, unknown70) == 0x70, "");
static_assert(offsetof(IDColiObjGrdChar, unknown80) == 0x80, "");
static_assert(offsetof(IDColiObjGrdChar, unknown88) == 0x88, "");

class IDColiObjData : public IDColiObjBase {
public:
  IDColiObjData(IDColiTreeTop *tree);
  bool createBinary(const void *binary);
  void workNodeClear();
  const char *getBoneName(int index) const;
  int getBoneIdx(const char *name) const;
  void setBoneMatrix(int index, const mm::Mat44 &matrix);
  mm::Mat44 &getBoneMatrix(int index);
  bool nodeUpdate();
  void primUpdate();
  void calcNodeMatrix(mm::Mat44 &result, const mm::Mat44 &parent, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void calcLinkNodeMatrix(mm::Mat44 &result, const CHCLBaseInfo *info);
  void primset_sphere(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_base(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_subbase(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_capsule(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_bone_capsule(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_box(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);
  void primset_poli(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info);

  static const ShapeType s_TypePrimiteve[7];

  // Inferred helper: releases the ground character object created from the binary; original name unknown.
  void unknown021() {
    if (unknown1c & 0x200) {
      unknown1c &= ~0x200;
      if (unknown200 != nullptr) {
        unknown200->release();
      }
      unknown200 = nullptr;
    }
  }

  const unknown002 *unknown1d0; // Inferred role: binary; original member name unknown.
  const unknown001 *unknown1d8; // Inferred role: bone tbl; original member name unknown.
  void *unknown1e0;             // Inferred role: work buffer; original member name unknown.
  unknown008 *unknown1e8;       // Inferred role: primitive work tbl; original member name unknown.
  mm::Mat44 *unknown1f0;        // Inferred role: bone matrix tbl; original member name unknown.
  int unknown1f8;               // Inferred role: bone max; original member name unknown.
  int unknown1fc;               // Inferred role: primitive max; original member name unknown.
  IDColiObjGrdChar *unknown200; // Inferred role: work node; original member name unknown.
};

static_assert(offsetof(IDColiObjData, unknown1d0) == 0x1d0, "");
static_assert(offsetof(IDColiObjData, unknown1d8) == 0x1d8, "");
static_assert(offsetof(IDColiObjData, unknown1e0) == 0x1e0, "");
static_assert(offsetof(IDColiObjData, unknown1e8) == 0x1e8, "");
static_assert(offsetof(IDColiObjData, unknown1f0) == 0x1f0, "");
static_assert(offsetof(IDColiObjData, unknown1f8) == 0x1f8, "");
static_assert(offsetof(IDColiObjData, unknown1fc) == 0x1fc, "");
static_assert(offsetof(IDColiObjData, unknown200) == 0x200, "");

class IDColiObjChar : public IDColiObjData {
public:
  ~IDColiObjChar() override;
  void release() override;
  void sizeUpdate() override;
  void update() override;
  bool SweepAndPruneUpdate() override;
  void consistentUpdate() override;
  virtual void moveUpdate();

  u8 _208[0x210 - 0x208];
  mm::Vec3 unknown210; // Inferred role: unknown; original member name unknown.
  f32 unknown220;      // Inferred role: adsorption; original member name unknown.
};

static_assert(offsetof(IDColiObjChar, unknown210) == 0x210, "");
static_assert(offsetof(IDColiObjChar, unknown220) == 0x220, "");

class IDColiObjCharCheck : public IDColiObjChar {
public:
  IDColiObjCharCheck(IDColiTreeTop *tree);
  bool testResultLine(IDColiResult &result, const IDColiInput &input);
  bool testResultRay(IDColiResult &result, const IDColiInput &input);
  bool testResultSphere(IDColiResult &result, const IDColiInput &input);
  bool testResultCapsule(IDColiResult &result, const IDColiInput &input);
  bool testCheckLine(IDColiResult &result, const IDColiInput &input);
  bool testCheckRay(IDColiResult &result, const IDColiInput &input);
  bool testCheckSphere(IDColiResult &result, const IDColiInput &input);
  bool testCheckCapsule(IDColiResult &result, const IDColiInput &input);
  bool testCheckBox(IDColiResult &result, const IDColiInput &input);
  bool testTypeLine(IDColiResult &result, const IDColiInput &input, ColiCheckType type);
  bool testTypeSphere(IDColiResult &result, const IDColiInput &input, ColiCheckType type);
  bool testTypeCapsule(IDColiResult &result, const IDColiInput &input, ColiCheckType type);
};

class IDColiObjPhantom : public IDColiObjBase {
public:
  IDColiObjPhantom(IDColiTreeTop *tree);
  ~IDColiObjPhantom() override;
  void sizeUpdate() override;
  void update() override;
  bool SweepAndPruneUpdate() override;
  void consistentUpdate() override;
};

class IDColiObjPhantomCheck : public IDColiObjPhantom {
public:
  IDColiObjPhantomCheck(IDColiTreeTop *tree);
  bool testResultLine(IDColiResult &result, const IDColiInput &input);
  bool testResultRay(IDColiResult &result, const IDColiInput &input);
  bool testResultSphere(IDColiResult &result, const IDColiInput &input);
  bool testResultCapsule(IDColiResult &result, const IDColiInput &input);
  bool testCheckLine(IDColiResult &result, const IDColiInput &input);
  bool testCheckRay(IDColiResult &result, const IDColiInput &input);
  bool testCheckSphere(IDColiResult &result, const IDColiInput &input);
  bool testCheckCapsule(IDColiResult &result, const IDColiInput &input);
};

struct IDCmfMovePosData {
  mm::Mat44 unknown00; // Inferred role: initial matrix; original member name unknown.
  u8 _40[0x50 - 0x40];
  mm::Vec3 unknown50; // Inferred role: bounds corner; original member name unknown.
  mm::Vec3 unknown60; // Inferred role: bounds corner; original member name unknown.
};

static_assert(offsetof(IDCmfMovePosData, unknown50) == 0x50, "");
static_assert(offsetof(IDCmfMovePosData, unknown60) == 0x60, "");
static_assert(sizeof(IDCmfMovePosData) == 0x70, "");

struct IDCmfMovePosInfo {
  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u16 unknown04; // Inferred role: unknown; original member name unknown.
  u16 unknown06; // Inferred role: id; original member name unknown.
};

static_assert(sizeof(IDCmfMovePosInfo) == 0x8, "");

// Inferred role: position data of a polygon collision followed by its local bounds; original name unknown.
struct unknown085 {
  IDCmfPosData unknown00; // Inferred role: position data; original member name unknown.
  u8 _a0[0xa8 - 0xa0];
  const mm::Vec3 *unknowna8; // Inferred role: local bounds, max then min; original member name unknown.
};

static_assert(offsetof(unknown085, unknowna8) == 0xa8, "");

struct unknown010 {
  unknown085 *unknown00; // Inferred role: position data; original member name unknown.
};

class IDColiGrdMoveObj;

struct unknown006 {
  IDColiTreeObj unknown00;     // Inferred role: tree node; original member name unknown.
  IDColiGrdMoveObj *unknown10; // Inferred role: owner; original member name unknown.
};

static_assert(sizeof(unknown006) == 0x18, "");

struct IDCmfPosInfo {
  u16 unknown00; // Inferred role: index of the parts record; original member name unknown.
  u16 unknown02; // Inferred role: global id; original member name unknown.
};

static_assert(sizeof(IDCmfPosInfo) == 4, "");

class IDColiGrdMoveObj {
public:
  IDColiGrdMoveObj();
  void setMat(const mm::Mat44 &matrix);
  void setMoveData(const u8 *binary, const IDCmfMovePosData *data, const IDCmfMovePosInfo *info);
  void treeUpdate(IDColiTreeTop *tree, int index);
  void update();

  mm::Mat44 unknown00[3];             // Inferred role: matrices (two by stack index, then previous); original member name unknown.
  mm::Mat44 unknownc0;                // Inferred role: inverse matrix work; original member name unknown.
  IDCmfPosData unknown100;            // Inferred role: position data; original member name unknown.
  IDCmfPosInfo unknown1a0;            // Inferred role: parts record index and global id; original member name unknown.
  const IDCmfMovePosData *unknown1a8; // Inferred role: move data; original member name unknown.
  const char *unknown1b0;             // Inferred role: name; original member name unknown.
  void *unknown1b8;                   // Inferred role: user data; original member name unknown.
  u16 unknown1c0;                     // Inferred role: update flags per index; original member name unknown.
  unknown006 unknown1c8[2];           // Inferred role: tree nodes; original member name unknown.
};

static_assert(offsetof(IDColiGrdMoveObj, unknownc0) == 0xc0, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown100) == 0x100, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1a0) == 0x1a0, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1a8) == 0x1a8, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1b0) == 0x1b0, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1b8) == 0x1b8, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1c0) == 0x1c0, "");
static_assert(offsetof(IDColiGrdMoveObj, unknown1c8) == 0x1c8, "");
static_assert(sizeof(IDColiGrdMoveObj) == 0x200, "");

struct unknown014 {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  f32 unknown08; // Inferred role: z; original member name unknown.
};

static_assert(sizeof(unknown014) == 0xc, "");

struct unknown021 {
  u8 _00[0x0c];
  u32 unknown0c; // Inferred role: tree cell object index; original member name unknown.
  u8 _10[0x14 - 0x10];
};

static_assert(sizeof(unknown021) == 0x14, "");

struct IDCmfNormalData;
struct IDCmfPoliData;

struct unknown097 {
  u8 _00[0x28]; // Inferred role: material record of the polygon table; fields not read by the matching code.
};

static_assert(sizeof(unknown097) == 0x28, "");

struct unknown094 {
  u32 unknown00; // Inferred role: global id, 0 when always active; original member name unknown.
  u32 unknown04; // Inferred role: tree cell object index; original member name unknown.
  u16 unknown08; // Inferred role: flags, bit 0 restricts the record to the sub number in the high byte; original member name unknown.
  u8 _0a[0x10 - 0x0a];
};

static_assert(sizeof(unknown094) == 0x10, "");

struct wrkIDCmfWork {
  const u8 *unknown00;               // Inferred role: binary; original member name unknown.
  const unknown021 *unknown08;       // Inferred role: tree cell object table; original member name unknown.
  const IDCmfPoliData *unknown10;    // Inferred role: polygon table; original member name unknown.
  const mm::Vec3 **unknown18;        // Inferred role: vertex tables; original member name unknown.
  const IDCmfNormalData **unknown20; // Inferred role: normal tables; original member name unknown.
  const unknown014 **unknown28;      // Inferred role: vector tables; original member name unknown.
  const IDCmfPosData *unknown30;     // Inferred role: position data table; original member name unknown.
  const IDCmfPosInfo *unknown38;     // Inferred role: position info table; original member name unknown.
  const unknown097 *unknown40;       // Inferred role: material table; original member name unknown.
  u32 *unknown48;                    // Inferred role: first table copied from the binary; original member name unknown.
  u32 *unknown50;                    // Inferred role: second table copied from the binary; original member name unknown.
  u32 *unknown58;                    // Inferred role: third table copied from the binary; original member name unknown.
  const void *unknown60;             // Inferred role: tree bounds table; original member name unknown.
  const void *unknown68;             // Inferred role: tree node table; original member name unknown.
  IDColiGrdMoveObj *unknown70;       // Inferred role: move objs; original member name unknown.
  int unknown78;                     // Inferred role: move max; original member name unknown.
  u8 _7c[0x80 - 0x7c];
  const unknown094 *unknown80; // Inferred role: global id records; original member name unknown.
  int unknown88;               // Inferred role: global id record count; original member name unknown.
  u8 _8c[0x90 - 0x8c];
  IDColiTreeTop *unknown90[2]; // Inferred role: tree tops of the two move object banks; original member name unknown.
  int unknowna0;               // Inferred role: current move object bank; original member name unknown.
  u8 _a4[0xa8 - 0xa4];
  void *unknowna8; // Inferred role: allocated buffer; original member name unknown.
};

static_assert(offsetof(wrkIDCmfWork, unknown08) == 0x8, "");
static_assert(offsetof(wrkIDCmfWork, unknown10) == 0x10, "");
static_assert(offsetof(wrkIDCmfWork, unknown18) == 0x18, "");
static_assert(offsetof(wrkIDCmfWork, unknown40) == 0x40, "");
static_assert(offsetof(wrkIDCmfWork, unknown28) == 0x28, "");
static_assert(offsetof(wrkIDCmfWork, unknown30) == 0x30, "");
static_assert(offsetof(wrkIDCmfWork, unknown38) == 0x38, "");
static_assert(offsetof(wrkIDCmfWork, unknown48) == 0x48, "");
static_assert(offsetof(wrkIDCmfWork, unknown58) == 0x58, "");
static_assert(offsetof(wrkIDCmfWork, unknown60) == 0x60, "");
static_assert(offsetof(wrkIDCmfWork, unknown68) == 0x68, "");
static_assert(offsetof(wrkIDCmfWork, unknown70) == 0x70, "");
static_assert(offsetof(wrkIDCmfWork, unknown80) == 0x80, "");
static_assert(offsetof(wrkIDCmfWork, unknown88) == 0x88, "");
static_assert(offsetof(wrkIDCmfWork, unknown90) == 0x90, "");
static_assert(offsetof(wrkIDCmfWork, unknowna8) == 0xa8, "");
static_assert(sizeof(wrkIDCmfWork) == 0xb0, "");

struct IDColiGrandWork : wrkIDCmfWork {
  IDColiGrandWork();
};

static_assert(sizeof(IDColiGrandWork) == 0xb0, "");

struct unknown017 {
  u8 _00[0x08 - 0x00];
  u32 unknown08; // Inferred role: size; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u32 unknown10; // Inferred role: data offset; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: offset of the first pointer table entries; original member name unknown.
  s32 unknown1c; // Inferred role: move object count; original member name unknown.
  u32 unknown20; // Inferred role: offset of the normal table entries; original member name unknown.
  s32 unknown24; // Inferred role: unknown; original member name unknown.
  u32 unknown28; // Inferred role: offset of the first copied table; original member name unknown.
  s32 unknown2c; // Inferred role: unknown; original member name unknown.
  u32 unknown30; // Inferred role: offset of the second copied table; original member name unknown.
  s32 unknown34; // Inferred role: unknown; original member name unknown.
  u32 unknown38; // Inferred role: offset of the third copied table; original member name unknown.
  s32 unknown3c; // Inferred role: unknown; original member name unknown.
  u32 unknown40; // Inferred role: offset of the data of the first pointer table; original member name unknown.
  u8 _44[0x48 - 0x44];
  u32 unknown48; // Inferred role: offset of the normal data; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  u32 unknown50; // Inferred role: offset of the vector table entries; original member name unknown.
  s32 unknown54; // Inferred role: vector table count; original member name unknown.
  u32 unknown58; // Inferred role: offset of the position data; original member name unknown.
  s32 unknown5c; // Inferred role: position data count; original member name unknown.
  u32 unknown60; // Inferred role: offset of the tree bounds table; original member name unknown.
  u8 _64[0x68 - 0x64];
  u32 unknown68; // Inferred role: offset of the tree node table; original member name unknown.
  u8 _6c[0x74 - 0x6c];
  u32 unknown74; // Inferred role: data offset; original member name unknown.
  u8 _78[0x7c - 0x78];
  u32 unknown7c; // Inferred role: offset of the vector data; original member name unknown.
  u8 _80[0x88 - 0x80];
  u32 unknown88; // Inferred role: flags; original member name unknown.
  u32 unknown8c; // Inferred role: bounds offset; original member name unknown.
  u32 unknown90; // Inferred role: offset of the move position data; original member name unknown.
  s32 unknown94; // Inferred role: tree count; original member name unknown.
  u8 _98[0xa0 - 0x98];
  u32 unknowna0; // Inferred role: offset of the global id records; original member name unknown.
  s32 unknowna4; // Inferred role: global id record count; original member name unknown.
};

static_assert(offsetof(unknown017, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown017, unknown3c) == 0x3c, "");
static_assert(offsetof(unknown017, unknown88) == 0x88, "");
static_assert(offsetof(unknown017, unknown94) == 0x94, "");
static_assert(offsetof(unknown017, unknowna4) == 0xa4, "");

struct unknown018 {
  f32 unknown00[3]; // Inferred role: max; original member name unknown.
  f32 unknown0c[3]; // Inferred role: min; original member name unknown.
};

static_assert(sizeof(unknown018) == 0x18, "");

struct IDCmfNormalData {
  s16 unknown00; // Inferred role: x in 1/16384 units; original member name unknown.
  s16 unknown02; // Inferred role: y in 1/16384 units; original member name unknown.
  s16 unknown04; // Inferred role: z in 1/16384 units; original member name unknown.
};

static_assert(sizeof(IDCmfNormalData) == 6, "");

struct IDCmfPoliData {
  u32 unknown00; // Inferred role: vertex index list offset; original member name unknown.
  u8 unknown04;  // Inferred role: vertex count; original member name unknown.
  u8 unknown05;  // Inferred role: vertex and vector table index; original member name unknown.
  u8 _06[0x0c - 0x06];
};

static_assert(offsetof(IDCmfPoliData, unknown05) == 5, "");
static_assert(sizeof(IDCmfPoliData) == 0xc, "");

class IDColiGrandTree : public IDColiGrandMesh {
public:
  IDColiGrandTree();
  bool isAaBbToAaBb(const float *max, const float *min);
  bool isLineAaBb(const float *max, const float *min);
  bool isRangeAaBb(const mm::Vec3 *max, const mm::Vec3 *min);
  bool treeHitEnd(u32 index);
  bool treeHitDef(u32 index);
  bool instLineHit(u32 index);
  bool instLineHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo);
  bool instRayHit(u32 index);
  bool instRayHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo);
  bool instSphereHit(u32 index);
  bool instSphereHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo);
  bool instCapsuleHit(u32 index);
  bool instCapsuleHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo);
  bool instAaBbHit(u32 index);
  bool instAaBbHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo);

  bool (IDColiGrandTree::*unknown90)(u32);                          // Inferred role: hit test of a tree cell object; original member name unknown.
  bool (IDColiGrandTree::*unknowna0)(u32);                          // Inferred role: hit test of a moved instance; original member name unknown.
  bool (IDColiGrandTree::*unknownb0)(const float *, const float *); // Inferred role: bounds test; original member name unknown.
};

static_assert(offsetof(IDColiGrandTree, unknown90) == 0x90, "");
static_assert(offsetof(IDColiGrandTree, unknowna0) == 0xa0, "");
static_assert(offsetof(IDColiGrandTree, unknownb0) == 0xb0, "");
static_assert(sizeof(IDColiGrandTree) == 0xc0, "");

typedef bool (IDColiGrandTree::*unknown020)(const IDCmfPosData *, const IDCmfPosInfo *); // Inferred role: instance hit test with parts; original name unknown.

class IDColiGrandObj : public IDColiGrandTree {
public:
  IDColiGrandObj(wrkIDCmfWork *work);
  ~IDColiGrandObj();
  bool testLine(IDColiResult &result, const IDColiInput &input);
  bool testLine(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData);
  bool testRay(IDColiResult &result, const IDColiInput &input);
  bool testRay(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData);
  bool testSphere(IDColiResult &result, const IDColiInput &input, bool isWall);
  bool testSphere(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData);
  bool testCapsule(IDColiResult &result, const IDColiInput &input, bool isWall);
  bool testCapsule(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData);
  bool testMoveSphere(IDColiResult &result, const IDColiInput &input, bool isStop);
  bool testMoveCapsule(IDColiResult &result, const IDColiInput &input, bool isStop);
  bool testAaBb(IDColiResult &result, const IDColiInput &input);
  bool getAaBbPoliAaBb(IDColiResult &result, const IDColiInput &input);
  bool coliCallCheck(unknown020 function);
  bool coliCallResl(unknown020 function);
  bool coliMoveCallResl(unknown020 function, bool isStop);
};

static_assert(sizeof(IDColiGrandObj) == 0xc0, "");

class IDColiObjGrand : public IDColiObj {
public:
  IDColiObjGrand();
  ~IDColiObjGrand() override;
  void workClear();
  void update() override;
  void createGrand(mtl::ALLOC_HANDLE handle, const void *binary);
  void createGrandAdder(void *buffer, const void *binary);
  void createMemBinary();
  static int calcGrandBufferSize(const void *binary);
  void getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const;

  // Inferred helper: tests a line against the grand; original name unknown.
  bool unknown051(IDColiResult &result, const IDColiInput &input) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testLine(result, input);
  }

  // Inferred helper: tests a line against the grand placed by the position data; original name unknown.
  bool unknown051(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testLine(result, input, posData);
  }

  // Inferred helper: tests a ray against the grand; original name unknown.
  bool unknown052(IDColiResult &result, const IDColiInput &input) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testRay(result, input);
  }

  // Inferred helper: tests a ray against the grand placed by the position data; original name unknown.
  bool unknown052(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testRay(result, input, posData);
  }

  // Inferred helper: tests a sphere against the grand; original name unknown.
  bool unknown053(IDColiResult &result, const IDColiInput &input, bool isWall) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testSphere(result, input, isWall);
  }

  // Inferred helper: tests a sphere against the grand placed by the position data; original name unknown.
  bool unknown053(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testSphere(result, input, isWall, posData);
  }

  // Inferred helper: tests a capsule against the grand; original name unknown.
  bool unknown054(IDColiResult &result, const IDColiInput &input, bool isWall) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testCapsule(result, input, isWall);
  }

  // Inferred helper: tests a capsule against the grand placed by the position data; original name unknown.
  bool unknown054(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testCapsule(result, input, isWall, posData);
  }

  // Inferred helper: tests an AABB against the grand; original name unknown.
  bool unknown034(IDColiResult &result, const IDColiInput &input) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.testAaBb(result, input);
  }

  // Inferred helper: gathers the AABB of the grand polygons in an AABB; original name unknown.
  bool unknown035(IDColiResult &result, const IDColiInput &input) {
    if (unknown1c & 0x80) {
      return false;
    }
    IDColiGrandObj object(&unknown50);
    return object.getAaBbPoliAaBb(result, input);
  }

  IDColiGrandWork unknown50; // Inferred role: work; original member name unknown.
};

static_assert(offsetof(IDColiObjGrand, unknown50) == 0x50, "");
static_assert(sizeof(IDColiObjGrand) == 0x100, "");

class IDColiManager : public mm::mtl::PtrSingleton<IDColiManager> {
public:
  static int s_nDebIdx;
  static int s_nStkIdx;

  static ml::CriticalSection &getCriticalSection();

  IDColiManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, u32 size);
  ~IDColiManager() override;
  void update();
  void objUpdate();
  void addList(ColiLinkList<IDColiObj> &list, ColiLinkList<IDColiObj> &source, bool isSweep);
  void release();
  void addDelUpdate();
  void consistentUpdate();
  void updateConsistentList(ColiLinkList<IDColiObj> &list);
  void tail();
  IDColiObj *createColiGrand(const void *binary);
  IDColiObj *createColiCharacter();
  IDColiObj *createColiPhantom();
  IDColiObj *createColiGrdChar();
  bool getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const;
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

  ColiLinkList<IDColiObj> unknown08[4];    // Inferred role: object lists; original member name unknown.
  ColiLinkList<IDColiObj> unknown48[4][2]; // Inferred role: object lists waiting to be added or removed; original member name unknown.
  u8 _c8[0xd8 - 0xc8];
  IDColiTreeTop *unknownd8[2]; // Inferred role: tree tops; original member name unknown.
  u32 *m_gblIdTbl;
  u32 unknownf0;               // Inferred role: sub num; original member name unknown.
  mtl::ALLOC_HANDLE unknownf4; // Inferred role: memory handle; original member name unknown.
  IDColiMemHandleAllocator m_allocator;
};

static_assert(offsetof(IDColiManager, unknown08) == 0x8, "");
static_assert(offsetof(IDColiManager, unknownf4) == 0xf4, "");
static_assert(offsetof(IDColiManager, m_allocator) == 0xf8, "");
static_assert(sizeof(IDColiManager) == 0x108, "");
static_assert(offsetof(IDColiManager, unknown48) == 0x48, "");
static_assert(offsetof(IDColiManager, unknownd8) == 0xd8, "");
static_assert(offsetof(IDColiManager, m_gblIdTbl) == 0xe8, "");

// Inferred role: tree list node of an IDColiObjBase followed by its owner (IDColiObjBase::unknown1b0 and unknown1c0); original type name unknown.
struct unknown031 {
  IDColiTreeObj unknown00;  // Inferred role: tree list node; original member name unknown.
  IDColiObjBase *unknown10; // Inferred role: owner; original member name unknown.
};

static_assert(offsetof(unknown031, unknown10) == 0x10, "");
static_assert(sizeof(unknown031) == 0x18, "");

// Inferred role: cell range of one tree level; original type name unknown.
struct unknown032 {
  int unknown00; // Inferred role: current x; original member name unknown.
  int unknown04; // Inferred role: current z; original member name unknown.
  int unknown08; // Inferred role: start x; original member name unknown.
  int unknown0c; // Inferred role: start z; original member name unknown.
  int unknown10; // Inferred role: end x; original member name unknown.
  int unknown14; // Inferred role: end z; original member name unknown.
};

static_assert(sizeof(unknown032) == 0x18, "");

class IDColiUtilTreeAcc {
public:
  IDColiUtilTreeAcc(IDColiTreeTop *tree) : unknown00(tree), unknown30(0) {}
  void startTreeAaBbMode(const mm::Vec3 &max, const mm::Vec3 &min);

  // Inferred helper: returns the object list of the next cell in range, or nullptr at the end; original name unknown.
  ColiLinkList<IDColiTreeObj> *unknown033() {
    for (; unknown30 < 5; unknown30++) {
      unknown032 &cell = unknown34[unknown30];
      for (; cell.unknown04 <= cell.unknown14; cell.unknown04++) {
        if (cell.unknown00 <= cell.unknown10) {
          int x = cell.unknown00++;
          return unknown00->getObjList(x, cell.unknown04, unknown30);
        }
        cell.unknown00 = cell.unknown08;
      }
      cell.unknown04 = cell.unknown0c;
    }
    return nullptr;
  }

  IDColiTreeTop *unknown00; // Inferred role: tree top; original member name unknown.
  u8 _08[0x30 - 0x08];
  int unknown30;           // Inferred role: current level; original member name unknown.
  unknown032 unknown34[5]; // Inferred role: cell range per level; original member name unknown.
};

static_assert(offsetof(IDColiUtilTreeAcc, unknown30) == 0x30, "");
static_assert(offsetof(IDColiUtilTreeAcc, unknown34) == 0x34, "");
static_assert(sizeof(IDColiUtilTreeAcc) == 0xb0, "");

class IDColiDef {
public:
  IDColiDef();
  bool testLine(const mm::Vec3 &start, const mm::Vec3 &end);
  bool testRay(const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength);
  bool testSphere(const mm::Vec3 &center, f32 radius);
  bool testCapsule(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius);
  bool testAaBb(const mm::Vec3 &max, const mm::Vec3 &min);
  bool getAaBbPoliAaBb(mm::Vec3 &max, mm::Vec3 &min, const mm::Vec3 &inputMax, const mm::Vec3 &inputMin);

  bool unknown00;         // Inferred role: test the character objects; original member name unknown.
  bool unknown01;         // Inferred role: test the ground objects; original member name unknown.
  bool unknown02;         // Inferred role: test the ground character objects; original member name unknown.
  f32 unknown04;          // Inferred role: squared range of the inputs; original member name unknown.
  unknown005 *unknown08;  // Inferred role: callback; original member name unknown.
  IDColiResult unknown10; // Inferred role: collision result; original member name unknown.
};

static_assert(offsetof(IDColiDef, unknown04) == 0x4, "");
static_assert(offsetof(IDColiDef, unknown08) == 0x8, "");
static_assert(offsetof(IDColiDef, unknown10) == 0x10, "");
static_assert(sizeof(IDColiDef) == 0x120, "");

class IDColiPhantom {
public:
  IDColiPhantom();
  bool testLine(const mm::Vec3 &start, const mm::Vec3 &end);
  bool testRay(const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength);
  bool testSphere(const mm::Vec3 &center, f32 radius);
  bool testCapsule(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius);
  bool testPhantomColiObj(IDColiObj *object, f32 range);

  bool unknown00;         // Inferred role: unknown, initialized like IDColiDef::unknown00; original member name unknown.
  bool unknown01;         // Inferred role: unknown, initialized like IDColiDef::unknown01; original member name unknown.
  bool unknown02;         // Inferred role: unknown, initialized like IDColiDef::unknown02; original member name unknown.
  f32 unknown04;          // Inferred role: squared range of the inputs; original member name unknown.
  unknown005 *unknown08;  // Inferred role: callback; original member name unknown.
  IDColiResult unknown10; // Inferred role: collision result; original member name unknown.
};

static_assert(offsetof(IDColiPhantom, unknown04) == 0x4, "");
static_assert(offsetof(IDColiPhantom, unknown08) == 0x8, "");
static_assert(offsetof(IDColiPhantom, unknown10) == 0x10, "");
static_assert(sizeof(IDColiPhantom) == 0x120, "");

class IDColiCheckObj {
public:
  IDColiCheckObj();
  bool testLine(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end);
  bool testRay(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength);
  bool testSphere(const IDColiObj *object, const mm::Vec3 &center, f32 radius);
  bool testCapsule(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius);

  bool unknown00;         // Inferred role: unknown, initialized like IDColiDef::unknown00; original member name unknown.
  bool unknown01;         // Inferred role: unknown, initialized like IDColiDef::unknown01; original member name unknown.
  bool unknown02;         // Inferred role: unknown, initialized like IDColiDef::unknown02; original member name unknown.
  f32 unknown04;          // Inferred role: squared range of the inputs; original member name unknown.
  unknown005 *unknown08;  // Inferred role: callback; original member name unknown.
  IDColiResult unknown10; // Inferred role: collision result; original member name unknown.
};

static_assert(offsetof(IDColiCheckObj, unknown04) == 0x4, "");
static_assert(offsetof(IDColiCheckObj, unknown08) == 0x8, "");
static_assert(offsetof(IDColiCheckObj, unknown10) == 0x10, "");
static_assert(sizeof(IDColiCheckObj) == 0x120, "");

class IDColiMove : public IDColiDef {
public:
  // Inferred role: horizontal direction of a wall hit; original member names unknown.
  struct wrlResTempVec {
    f32 unknown00; // Inferred role: x; original member name unknown.
    f32 unknown04; // Inferred role: z; original member name unknown.
  };

  static const f32 s_fBaseWallDot;
  static const f32 s_fLandingAngle;
  static const f32 s_fLandingVecChk;

  IDColiMove();
  void setShapeParms(f32 radius, f32 height);
  void setAngle(f32 angle);
  void setFloor(f32 floor);
  void setDown(f32 down);
  void setAccuracy(bool accuracy);
  bool moveColi(const mm::Vec3 &position, const mm::Vec3 &move);
  void setupParms(const mm::Vec3 &move);
  void calcCheckParams(const mm::Vec3 &move);
  bool testWallCheck();
  void calcColiBaseParms(wrlResTempVec *wallVec);
  void calcDownVec();
  bool testVecYCheck(const mm::Vec3 &vector);
  void calcColiYVecParms(f32 y);
  bool calcAABBCheck();
  bool moveColi(IDColiObj *object, const mm::Vec3 &move);
  bool moveDataColi();
  bool moveDefColi();
  void setupBaseColiParam();
  void calcColiShapeParms();
  bool calcColiStateParams();
  bool calcWallHitChkVec(const mm::Vec3 &normal, const mm::Vec3 &position, wrlResTempVec *wallVec);
  void calcVecDeceleration(f32 &value, mm::Vec3 vector);
  bool calcColiSubShapeParms();

  int unknown120; // Inferred role: wall direction count; original member name unknown.
  u32 unknown124; // Inferred role: hit count of the vertical test; original member name unknown.
  u8 _128[0x130 - 0x128];
  mm::Vec3 unknown130; // Inferred role: moved distance; original member name unknown.
  mm::Vec3 unknown140; // Inferred role: move vector; original member name unknown.
  mm::Vec3 unknown150; // Inferred role: shape position; original member name unknown.
  mm::Vec3 unknown160; // Inferred role: shape end position; original member name unknown.
  mm::Vec3 unknown170; // Inferred role: base position; original member name unknown.
  mm::Vec3 unknown180; // Inferred role: shape vector; original member name unknown.
  mm::Vec3 unknown190; // Inferred role: step vector; original member name unknown.
  mm::Vec3 unknown1a0; // Inferred role: deceleration axis; original member name unknown.
  f32 unknown1b0;      // Inferred role: half move length; original member name unknown.
  f32 unknown1b4;      // Inferred role: step length; original member name unknown.
  f32 unknown1b8;      // Inferred role: radius; original member name unknown.
  f32 unknown1bc;      // Inferred role: height; original member name unknown.
  f32 m_angle;
  f32 m_floor;
  f32 m_down;
  f32 unknown1cc;            // Inferred role: squared radius; original member name unknown.
  f32 unknown1d0;            // Inferred role: cosine of the landing angle; original member name unknown.
  f32 unknown1d4;            // Inferred role: top height; original member name unknown.
  f32 unknown1d8;            // Inferred role: vertical test length; original member name unknown.
  int unknown1dc;            // Inferred role: step count; original member name unknown.
  IDColiObjChar *unknown1e0; // Inferred role: moved object; original member name unknown.
  bool unknown1e8;           // Inferred role: wall hit; original member name unknown.
  bool unknown1e9;           // Inferred role: unknown flag; original member name unknown.
  bool unknown1ea;           // Inferred role: the shape is a capsule; original member name unknown.
  bool unknown1eb;           // Inferred role: landing; original member name unknown.
  bool unknown1ec;           // Inferred role: ground hit; original member name unknown.
  bool m_accuracy;
  bool unknown1ee; // Inferred role: ceiling hit; original member name unknown.
  bool unknown1ef; // Inferred role: subdivide the next move more; original member name unknown.
  bool unknown1f0; // Inferred role: hit right below; original member name unknown.
  bool unknown1f1; // Inferred role: state test running; original member name unknown.
  bool unknown1f2; // Inferred role: hit on a slope; original member name unknown.
  bool unknown1f3; // Inferred role: deceleration enabled; original member name unknown.
  bool unknown1f4; // Inferred role: stuck in a wall; original member name unknown.
  bool unknown1f5; // Inferred role: moving on the ground; original member name unknown.
};

static_assert(offsetof(IDColiMove, unknown120) == 0x120, "");
static_assert(offsetof(IDColiMove, unknown124) == 0x124, "");
static_assert(offsetof(IDColiMove, unknown130) == 0x130, "");
static_assert(offsetof(IDColiMove, unknown1a0) == 0x1a0, "");
static_assert(offsetof(IDColiMove, unknown1b8) == 0x1b8, "");
static_assert(offsetof(IDColiMove, m_angle) == 0x1c0, "");
static_assert(offsetof(IDColiMove, m_down) == 0x1c8, "");
static_assert(offsetof(IDColiMove, unknown1dc) == 0x1dc, "");
static_assert(offsetof(IDColiMove, unknown1e0) == 0x1e0, "");
static_assert(offsetof(IDColiMove, m_accuracy) == 0x1ed, "");
static_assert(offsetof(IDColiMove, unknown1f3) == 0x1f3, "");
static_assert(offsetof(IDColiMove, unknown1f5) == 0x1f5, "");
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
