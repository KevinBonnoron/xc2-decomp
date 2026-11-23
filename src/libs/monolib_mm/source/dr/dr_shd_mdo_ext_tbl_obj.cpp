#include "dr/dr_shd_mdo_ext_tbl_obj.h"

#include <new>

#include "dr/dr_mdo_mat.h"
#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "dr/dr_shd_mdo_dec_res.h"
#include "dr/dr_shd_mdo_dec_shd_obj.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_shd_list.h"

namespace ml {

DrShdMdoExtTblObj::DrShdMdoExtTblObj() : m_drShdMdoDecShdObj(nullptr), m_drShdMdoDecExtTbl(nullptr) {}

int DrShdMdoExtTblObj::getDecWorkSize(int declarationNum, const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  const unknown002 *entry = reinterpret_cast<const unknown002 *>(data + header->unknown08);
  int count = header->unknown0c;
  int tblSize = count * 0x38;
  int declSize = declarationNum * 4;
  const u8 *tables = data + header->unknown18;
  u32 size = 0;
  for (int i = 0; i < header->unknown0c; i++) {
    size += grlib::CGLibDecShader::calcTblSize(tables + entry[i].unknown00);
  }
  int padding = 0;
  if ((size & 3) != 0) {
    padding = 4 - (size & 3);
  }
  return tblSize + declSize + size + padding;
}

int DrShdMdoExtTblObj::setDecObj(DrShdMdoDecShdObj *obj, u8 *work, const u8 *data, int declarationNum, const MdsMatTechnique *technique, const u8 *extData) {
  m_drShdMdoDecShdObj = obj;
  m_drShdMdoDecExtTbl = static_cast<DrShdMdoDecExtTbl *>(static_cast<void *>(work));
  s32 count = obj->unknown28.unknown50;
  size_t tableSize = count * sizeof(DrShdMdoDecExtTbl);
  // The game keeps the end of the extension tables in x21 (0x71008a1198), apart from the declaration table pointer, which it forms from the same size (x8) plus declarationNum * 4 (0x71008a119c).
  u8 *params = work + tableSize;
  u8 *declarations = work + (tableSize + declarationNum * sizeof(u32));
  for (s32 i = 0; i < count; i++) {
    new (&m_drShdMdoDecExtTbl[i]) DrShdMdoDecExtTbl();
    DrShdMdoDecRes *shader = unknown102(obj->unknown28, i);
    m_drShdMdoDecExtTbl[i].setTbl(declarations);
    m_drShdMdoDecExtTbl[i].setObj(shader);
    int declarationMax = shader->getDeclarationMax();
    m_drShdMdoDecExtTbl[i].setShaderParamAdd(static_cast<u32 *>(static_cast<void *>(params + technique[i].unknown2c * 4)),
                                             static_cast<u32 *>(static_cast<void *>(params + technique[i].unknown2e * 4)));
    m_drShdMdoDecExtTbl[i].setupShderInfo(shader, &technique[i], data);
    declarations += declarationMax;
  }
  return getDecWorkSize(declarationNum, extData);
}

} // namespace ml
