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

class DrResMdoSeamMemObj {
public:
  virtual ~DrResMdoSeamMemObj();

  DrResMdoSeamMemObj *m_prev;
  DrResMdoSeamMemObj *m_next;
  u8 *m_buffer;
  u32 m_size;
  u32 m_flags;
};

static_assert(offsetof(DrResMdoSeamMemObj, m_buffer) == 0x18, "");
static_assert(offsetof(DrResMdoSeamMemObj, m_flags) == 0x24, "");

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

  DrResMdoSeamTexList *m_next;
  u8 _10[0x18 - 0x10];
  DrResMdoSeamMemObj *m_memObj;
  grlib::CGLibTextureBuffer *m_textures;
  const u8 *m_header;
  void *m_buffer;
  u16 m_index;
  u8 m_cnt;
  bool m_isChangeMem;
  u16 m_errIdx;
  u16 m_texNum;
};

static_assert(offsetof(DrResMdoSeamTexList, m_memObj) == 0x18, "");
static_assert(offsetof(DrResMdoSeamTexList, m_index) == 0x38, "");
static_assert(offsetof(DrResMdoSeamTexList, m_texNum) == 0x3e, "");
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

  DrResMdoSeamTexture *m_next;
  u8 _10[0x18 - 0x10];
  grlib::CGLibTextureBuffer m_texture;
  DrResMdoSeamMemObj *m_memObj;
  DrResMdoSeamMemObj *m_heightMemObj;
  int m_heightOffset;
  u16 m_index;
  u16 m_seamIdx;
  u8 m_nomCnt;
  bool m_isChangeMem;
  u8 m_heightCnt;
  u8 m_heightState;
};

static_assert(offsetof(DrResMdoSeamTexture, m_texture) == 0x18, "");
static_assert(offsetof(DrResMdoSeamTexture, m_memObj) == 0x88, "");
static_assert(offsetof(DrResMdoSeamTexture, m_index) == 0x9c, "");
static_assert(offsetof(DrResMdoSeamTexture, m_heightState) == 0xa3, "");
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

  DrResMdoSeamVertex *m_next;
  u8 _10[0x18 - 0x10];
  DrResMdoSeamMemObj *m_memObj;
  DrResMdoVertex *m_vertex;
  u16 m_index;
  s16 m_cnt;
  u8 _2c[0x2e - 0x2c];
  u16 m_isChangeMem;
};

static_assert(offsetof(DrResMdoSeamVertex, m_memObj) == 0x18, "");
static_assert(offsetof(DrResMdoSeamVertex, m_isChangeMem) == 0x2e, "");
static_assert(sizeof(DrResMdoSeamVertex) == 0x30, "");

} // namespace ml
