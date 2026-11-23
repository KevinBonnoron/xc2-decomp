#include <new>

#include "dr/dr_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"
#include "dr/dr_res_mdo_inst_mdl_obj.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

DrResMdoInstMdlObj::DrResMdoInstMdlObj() : m_drMdlObj(nullptr), unknown08(0) {}

DrResMdoInstMdlObj::~DrResMdoInstMdlObj() {
  if (m_drMdlObj != nullptr) {
    m_drMdlObj->setDeleteCall(DrMan::s_nDblStockIdx);
    m_drMdlObj = nullptr;
  }
}

void DrResMdoInstMdlObj::releaseWork() {
  if (m_drMdlObj != nullptr) {
    m_drMdlObj->setDeleteCall(DrMan::s_nDblStockIdx);
    m_drMdlObj = nullptr;
  }
}

void DrResMdoInstMdlObj::releaseCall() {
  if (m_drMdlObj != nullptr) {
    m_drMdlObj->setDeleteCall(DrMan::s_nDblStockIdx);
  }
}

DrResMdoInstMdlInfo::DrResMdoInstMdlInfo() : unknown120(0) {
  unknown00 = 0;
  m_drResMdoInstMdlObj = nullptr;
}

DrResMdoInstMdlInfo::~DrResMdoInstMdlInfo() {
  for (int i = 0; i < unknown00; i++) {
    m_drResMdoInstMdlObj[i].releaseWork();
  }
  unknown00 = 0;
}

void DrResMdoInstMdlInfo::releaseWork() {
  for (int i = 0; i < unknown00; i++) {
    m_drResMdoInstMdlObj[i].releaseWork();
  }
  unknown00 = 0;
}

int DrResMdoInstMdlInfo::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  return header->unknown08 * sizeof(DrResMdoInstMdlObj) + sizeof(DrResMdoInstMdlInfo);
}

int DrResMdoInstMdlInfo::setup(u8 *work, const u8 *resource, const char *name) {
  unknown118 = resource;
  unknown00 = reinterpret_cast<const unknown001 *>(resource)->unknown08;
  unknown10 = name;
  int pos = unknown10.unknown004('/');
  // Cuts the name at its last separator, '/' first, then '\\' only when there is no '/' (the game inlines FixStr::unknown004 twice and erase(pos, -1) twice,
  // 0x71008762a0 and 0x71008762e4). Forms tried: one search whose result is erased once (106 instructions against the game's 113), and the '/' branch
  // written first (113 instructions, first difference at 0x71008762c0); the branch of the missing '/' written first gives the game's order.
  if (pos == -1) {
    pos = unknown10.unknown004('\\');
    if (pos != -1) {
      unknown10.erase(pos, -1);
    }
  } else {
    unknown10.erase(pos, -1);
  }
  unknown10 += "/";
  // The multiplication is done before the object array is built (0x7100876354, `lsl w8, w9, #4`), the header size added at the end. The object array is
  // carved out of the same allocation as the header (create), through void * like the DrMdoGrpObj constructor (decision 2026-11-14 #40).
  int size = unknown00 * sizeof(DrResMdoInstMdlObj);
  m_drResMdoInstMdlObj = static_cast<DrResMdoInstMdlObj *>(static_cast<void *>(work));
  for (int i = 0; i < unknown00; i++) {
    new (&m_drResMdoInstMdlObj[i]) DrResMdoInstMdlObj();
  }
  return size + sizeof(DrResMdoInstMdlInfo);
}

// The game (1.0.0: 0x710087645c) stores the work pointer into `info` before the constructor stores and reloads `info` for the setup call;
// `info = new (work) ...` stores it after the constructor and keeps the value in a register (10 against 8 instructions). The cast through void * is
// a single allocation carved into its object, as in the DrMdoGrpObj constructor (decision 2026-11-14 #40).
int DrResMdoInstMdlInfo::create(u8 *work, DrResMdoInstMdlInfo *&info, const u8 *resource, const char *name) {
  info = static_cast<DrResMdoInstMdlInfo *>(static_cast<void *>(work));
  new (info) DrResMdoInstMdlInfo();
  return info->setup(work + sizeof(DrResMdoInstMdlInfo), resource, name);
}

void DrResMdoInstMdlInfo::release(DrResMdoInstMdlInfo *&info) {
  info->releaseWork();
  info = nullptr;
}

void DrResMdoInstMdlInfo::releaseCall() {
  for (int i = 0; i < unknown00; i++) {
    m_drResMdoInstMdlObj[i].releaseCall();
  }
  unknown00 = 0;
  unknown120 |= 2 << DrMan::s_nDblStockIdx;
}

void DrResMdoInstMdlInfo::update(DrResMdlInstMdlArg &arg) {
  if (unknown120 & (2 << DrMan::s_nDblIdx | 1)) {
    unknown120 |= 1;
    return;
  }
  const unknown001 *header = reinterpret_cast<const unknown001 *>(unknown118);
  arg.unknown20 = unknown10.c_str();
  arg.unknown28 = unknown118;
  arg.unknown40 = reinterpret_cast<const unknown761 *>(unknown118 + header->unknown00);
  for (int i = 0; i < header->unknown04; i++) {
    arg.unknown30 = reinterpret_cast<const char *>(unknown118 + arg.unknown40->unknown04);
    arg.unknown38 = unknown118 + arg.unknown40->unknown00;
    arg.unknown48 = reinterpret_cast<const unknown762 *>(unknown118 + header->unknown10) + arg.unknown40->unknown08;
    arg.unknown50 = reinterpret_cast<const mm::Mat44 *>(unknown118 + header->unknown0c) + arg.unknown40->unknown08;
    for (int j = 0; j < arg.unknown40->unknown0c; j++) {
      m_drResMdoInstMdlObj[j + arg.unknown40->unknown08].update(arg);
      arg.unknown50++;
      arg.unknown48++;
    }
    arg.unknown40++;
  }
}

} // namespace ml
