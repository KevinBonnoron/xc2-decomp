#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class DrResMdoSeamParmRead;
class DrResMdoVertex;

// Inferred role: list node of the seam work objects (next and previous object of the pool lists); original type name unknown.
template <typename T> class unknown133 {
public:
  unknown133() : unknown08(nullptr), unknown10(nullptr) {}
  virtual ~unknown133() {}

  T *unknown08; // Inferred role: next object; original member name unknown.
  T *unknown10; // Inferred role: previous object; original member name unknown.
};

class DrResMdoSeamMemObj {
public:
  virtual ~DrResMdoSeamMemObj() {}

  DrResMdoSeamMemObj *unknown08; // Inferred role: prev; original member name unknown.
  DrResMdoSeamMemObj *unknown10; // Inferred role: next; original member name unknown.
  u8 *m_buffer;
  u32 m_size;
  u32 unknown24; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamMemObj, m_buffer) == 0x18, "");
static_assert(offsetof(DrResMdoSeamMemObj, unknown24) == 0x24, "");
static_assert(sizeof(DrResMdoSeamMemObj) == 0x28, "");

// Inferred type: texture entry of the seam texture list data; the original type name is unknown.
struct unknown134 {
  u32 unknown00; // Inferred role: unknown; original member name unknown.
  u32 unknown04; // Inferred role: texture size; original member name unknown.
  u32 unknown08; // Inferred role: texture offset in the data; original member name unknown.
  u32 unknown0c; // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(unknown134, unknown04) == 0x04, "");
static_assert(offsetof(unknown134, unknown08) == 0x08, "");
static_assert(sizeof(unknown134) == 0x10, "");

// Inferred type: header of the seam texture list data; the original type name is unknown.
struct unknown135 {
  u32 unknown00; // Inferred role: texture number; original member name unknown.
  u32 unknown04; // Inferred role: offset of the texture entries; original member name unknown.
};

static_assert(offsetof(unknown135, unknown04) == 0x04, "");

class DrResMdoSeamTexList {
public:
  static int SEAMRES_TEXLIST_CNTMAX;

  DrResMdoSeamTexList(int index);
  virtual ~DrResMdoSeamTexList();
  void release();
  bool update(DrResMdoSeamParmRead *parmRead);
  void changeMemTextureList();
  static void setListCnt(int count);
  void createTextureList(mtl::ALLOC_HANDLE handle);
  bool isTextureErrChk(const u16 *errors);

  DrResMdoSeamTexList *unknown08;       // Inferred role: next; original member name unknown.
  DrResMdoSeamTexList *unknown10;       // Inferred role: prev; original member name unknown.
  DrResMdoSeamMemObj *unknown18;        // Inferred role: mem object; original member name unknown.
  grlib::CGLibTextureBuffer *unknown20; // Inferred role: textures; original member name unknown.
  const u8 *unknown28;                  // Inferred role: header; original member name unknown.
  void *m_buffer;
  u16 unknown38;  // Inferred role: index; original member name unknown.
  u8 unknown3a;   // Inferred role: cnt; original member name unknown.
  bool unknown3b; // Inferred role: is change mem; original member name unknown.
  u16 unknown3c;  // Inferred role: err idx; original member name unknown.
  u16 unknown3e;  // Inferred role: tex num; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamTexList, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamTexList, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamTexList, unknown3e) == 0x3e, "");
static_assert(sizeof(DrResMdoSeamTexList) == 0x40, "");

class DrResMdoSeamTexture {
public:
  static int SEAMRES_NOM_CNTMAX;
  static int SEAMRES_HEIGHT_CNTMAX;

  DrResMdoSeamTexture(int index);
  virtual ~DrResMdoSeamTexture();
  void release();
  bool update();
  bool updateHeight();
  void createTexture(int size);
  void createHeightMoveTexture(int offset, u32 size);
  void createHeightTexture(int size, int heightSize);
  void resetTexture(int size);
  void changeMemTexture(int size);
  void changeMemTexture(int size, int heightSize);

  DrResMdoSeamTexture *unknown08;      // Inferred role: next; original member name unknown.
  DrResMdoSeamTexture *unknown10;      // Inferred role: prev; original member name unknown.
  grlib::CGLibTextureBuffer unknown18; // Inferred role: texture; original member name unknown.
  DrResMdoSeamMemObj *unknown88;       // Inferred role: mem object; original member name unknown.
  DrResMdoSeamMemObj *unknown90;       // Inferred role: height mem object; original member name unknown.
  int unknown98;                       // Inferred role: height offset; original member name unknown.
  u16 unknown9c;                       // Inferred role: index; original member name unknown.
  u16 unknown9e;                       // Inferred role: seam idx; original member name unknown.
  u8 unknowna0;                        // Inferred role: nom cnt; original member name unknown.
  bool unknowna1;                      // Inferred role: is change mem; original member name unknown.
  u8 unknowna2;                        // Inferred role: height cnt; original member name unknown.
  u8 unknowna3;                        // Inferred role: height state; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamTexture, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamTexture, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamTexture, unknown9c) == 0x9c, "");
static_assert(offsetof(DrResMdoSeamTexture, unknowna3) == 0xa3, "");
static_assert(sizeof(DrResMdoSeamTexture) == 0xa8, "");

class DrResMdoSeamVertex {
public:
  static int SEAMRES_CNTMAX;

  DrResMdoSeamVertex(int index);
  virtual ~DrResMdoSeamVertex();
  void release();
  bool update();
  void createVertex();
  void changeMemVertex();

  DrResMdoSeamVertex *unknown08; // Inferred role: next; original member name unknown.
  DrResMdoSeamVertex *unknown10; // Inferred role: prev; original member name unknown.
  DrResMdoSeamMemObj *unknown18; // Inferred role: mem object; original member name unknown.
  DrResMdoVertex *unknown20;     // Inferred role: vertex; original member name unknown.
  u16 unknown28;                 // Inferred role: index; original member name unknown.
  s16 unknown2a;                 // Inferred role: cnt; original member name unknown.
  u16 unknown2c;                 // Inferred role: seam idx; original member name unknown.
  u16 unknown2e;                 // Inferred role: is change mem; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamVertex, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamVertex, unknown2e) == 0x2e, "");
static_assert(sizeof(DrResMdoSeamVertex) == 0x30, "");

} // namespace ml
