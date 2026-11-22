#include "dr/dr_res_etc_params.h"

#include <new>

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_mesh_obj.h"

namespace ml {

DrResEtcParams::DrResEtcParams() : unknown00(0), unknown04{0, 0}, unknown0c{0, 0}, m_params(0) {}

f32 DrResEtcParams::getParams() const { return m_params; }

void DrResEtcParams::setParams(f32 value) {
  unknown00 |= 1 << DrMan::s_nDblStockIdx;
  unknown04[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::setPreParams(f32 value) {
  unknown00 |= 4 << DrMan::s_nDblStockIdx;
  unknown0c[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::update() {
  if (unknown00 & (1 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(1 << DrMan::s_nDblMemIdx);
    m_params = unknown04[DrMan::s_nDblMemIdx];
  }
  if (unknown00 & (4 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(4 << DrMan::s_nDblMemIdx);
    m_params = unknown0c[DrMan::s_nDblMemIdx];
  }
}

f32 DrResEtcParams::getValParams() const {
  if (unknown00 & (4 << DrMan::s_nDblStockIdx)) {
    return unknown0c[DrMan::s_nDblStockIdx];
  }
  if (unknown00 & (1 << DrMan::s_nDblStockIdx)) {
    return unknown04[DrMan::s_nDblStockIdx];
  }
  return m_params;
}

// The stores are in the order that matches (decision 2026-11-13, ruling 4): the game stores m_drResEtcParams and unknown00 as two separate 64-bit zeros (0x710086fa70, 0x710086fa74) and
// unknown18/unknown1c as one `stp wzr, w8` (0x710086fa78); in declaration order clang merges m_drResEtcParams, unknown18 and unknown1c into one `stp xzr, x8`.
DrResEtcPamObj::DrResEtcPamObj() {
  m_drResEtcParams = nullptr;
  unknown18 = 0;
  unknown00 = nullptr;
  unknown1c = 1;
}

int DrResEtcPamObj::create(u8 *work, const u8 *data) {
  DrResEtcPamObj *obj = new (work) DrResEtcPamObj();
  return obj->setup(data, work + sizeof(DrResEtcPamObj));
}

DrResEtcPamObj::~DrResEtcPamObj() {}

int DrResEtcPamObj::setup(const u8 *data, u8 *work) {
  const unknown002 *header = reinterpret_cast<const unknown002 *>(data + reinterpret_cast<const unknown001 *>(data)->unknown84);
  unknown00 = header;
  unknown08 = reinterpret_cast<const unknown040 *>(reinterpret_cast<const u8 *>(header) + header->unknown00);
  m_drResEtcParams = reinterpret_cast<DrResEtcParams *>(work);
  unknown18 = header->unknown04;
  for (u32 i = 0; i < unknown18; i++) {
    new (&m_drResEtcParams[i]) DrResEtcParams();
  }
  if (unknown00->unknown10 != 0) {
    const f32 *values = reinterpret_cast<const f32 *>(reinterpret_cast<const u8 *>(header) + unknown00->unknown10);
    for (u32 i = 0; i < unknown18; i++) {
      m_drResEtcParams[i].setInitParams(values[i]);
    }
  }
  return unknown00->unknown04 * sizeof(DrResEtcParams) + sizeof(DrResEtcPamObj);
}

void DrResEtcPamObj::update() {
  for (u32 i = 0; i < unknown18; i++) {
    m_drResEtcParams[i].update();
  }
}

void DrResEtcParams::setInitParams(f32 value) {
  unknown0c[1] = value;
  unknown0c[0] = value;
  unknown04[1] = value;
  unknown04[0] = value;
  m_params = value;
}

void DrResEtcPamObj::release(DrResEtcPamObj *&obj) {
  if (obj != nullptr) {
    obj = nullptr;
  }
}

void (DrResEtcPamObj::*DrResEtcPamObj::s_pMdoNodeEtcParm[2])(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg) = {
    &DrResEtcPamObj::mdonode_etcpam_etcmesh_disp,
    &DrResEtcPamObj::mdonode_etcpam_volfadeanm,
};

// 0x710086fb5c. The entries are indexed (`entries[i]`, with `i` also the index of the param in the first loop): the game keeps a 64 bit counter in both loops (`cmp x21, x8` against the `ldrsw` count,
// 0x710086fbf4 and 0x710086fc60) and loads the two u16 fields of an entry apart (`ldrh` at 0x710086fc1c and 0x710086fc38). A pointer walk (`entry++`, 72 instructions against 73) gives the second loop
// an i32 counter and one `ldr w` split with `ubfx`, and hoists the entries address above the flag test.
void DrResEtcPamObj::callback(DrResMdoMeshObj *meshObj, MdoWrkVanishEffect *vanish) {
  if (unknown00->unknown0c != 0) {
    wrkCallbackArg arg = {meshObj, vanish};
    if ((unknown00->unknown14 & 1) == 0) {
      const MdsEtcParamsCallBack *entries = reinterpret_cast<const MdsEtcParamsCallBack *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown08);
      for (s32 i = 0; i < unknown00->unknown0c; i++) {
        (this->*s_pMdoNodeEtcParm[entries[i].unknown00])(&entries[i], &m_drResEtcParams[i], arg);
      }
    } else {
      const MdsEtcParamsCallBack *entries = reinterpret_cast<const MdsEtcParamsCallBack *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown08);
      for (s32 i = 0; i < unknown00->unknown0c; i++) {
        (this->*s_pMdoNodeEtcParm[entries[i].unknown00])(&entries[i], &m_drResEtcParams[entries[i].unknown02], arg);
      }
    }
  }
}

void DrResEtcPamObj::mdonode_etcpam_etcmesh_disp(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg) {
  f32 value = 1.0f;
  if (param->getParams() <= 0.5f) {
    value = 0.0f;
  }
  DrResMdoMeshParts *parts = arg.m_drResMdoMeshObj->getParts(callback->unknown04);
  parts->unknown34 = value;
  parts->unknown2c[1] = value;
  parts->unknown2c[0] = value;
  parts->unknown28 &= ~6;
}

void DrResEtcPamObj::mdonode_etcpam_volfadeanm(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg) {
  if ((unknown1c & 1) != 0) {
    f32 value = param->getParams();
    u32 index = arg.m_drResMdoMeshObj->getParts(callback->unknown04)->m_extVolumeFadeEffect * 3 + 2;
    if (value <= 0.01f) {
      arg.m_mdoWrkVanishEffect[index].unknowna4 = arg.m_mdoWrkVanishEffect[index].unknownd0;
    } else if (value > 1.0f) {
      arg.m_mdoWrkVanishEffect[index].unknowna4 = arg.m_mdoWrkVanishEffect[index].unknownd0 + 1.0f;
    } else {
      arg.m_mdoWrkVanishEffect[index].unknowna4 = value + arg.m_mdoWrkVanishEffect[index].unknownd0;
    }
    if (arg.m_mdoWrkVanishEffect[index].unknowna4 > 1.0f) {
      arg.m_mdoWrkVanishEffect[index].unknowna4 = 1.0f;
    } else if (arg.m_mdoWrkVanishEffect[index].unknowna4 < 0.0f) {
      arg.m_mdoWrkVanishEffect[index].unknowna4 = 0.0f;
    }
  }
}

int DrResEtcPamObj::calcWorkSize(const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  const unknown002 *params = reinterpret_cast<const unknown002 *>(data + header->unknown84);
  return params->unknown04 * sizeof(DrResEtcParams) + 0x20;
}

} // namespace ml
