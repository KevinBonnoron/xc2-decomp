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

DrResEtcPamObj::~DrResEtcPamObj() {}

int DrResEtcPamObj::setup(const u8 *data, u8 *work) {
  const unknown002 *header = reinterpret_cast<const unknown002 *>(data + reinterpret_cast<const unknown001 *>(data)->unknown84);
  unknown00 = header;
  unknown08 = reinterpret_cast<const unknown040 *>(reinterpret_cast<const u8 *>(header) + header->unknown00);
  unknown10 = reinterpret_cast<DrResEtcParams *>(work);
  unknown18 = header->unknown04;
  for (u32 i = 0; i < unknown18; i++) {
    new (&unknown10[i]) DrResEtcParams();
  }
  if (unknown00->unknown10 != 0) {
    const f32 *values = reinterpret_cast<const f32 *>(reinterpret_cast<const u8 *>(header) + unknown00->unknown10);
    for (u32 i = 0; i < unknown18; i++) {
      unknown10[i].setInitParams(values[i]);
    }
  }
  return unknown00->unknown04 * sizeof(DrResEtcParams) + sizeof(DrResEtcPamObj);
}

void DrResEtcPamObj::update() {
  for (u32 i = 0; i < unknown18; i++) {
    unknown10[i].update();
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

void DrResEtcPamObj::mdonode_etcpam_etcmesh_disp(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg) {
  f32 value = 1.0f;
  if (param->getParams() <= 0.5f) {
    value = 0.0f;
  }
  DrResMdoMeshParts *parts = arg.unknown00->getParts(callback->unknown04);
  parts->unknown34 = value;
  parts->unknown2c[1] = value;
  parts->unknown2c[0] = value;
  parts->unknown28 &= ~6;
}

void DrResEtcPamObj::mdonode_etcpam_volfadeanm(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg) {
  if ((unknown1c & 1) != 0) {
    f32 value = param->getParams();
    u32 index = arg.unknown00->getParts(callback->unknown04)->unknown3a * 3 + 2;
    if (value <= 0.01f) {
      arg.unknown08[index].unknowna4 = arg.unknown08[index].unknownd0;
    } else if (value > 1.0f) {
      arg.unknown08[index].unknowna4 = arg.unknown08[index].unknownd0 + 1.0f;
    } else {
      arg.unknown08[index].unknowna4 = value + arg.unknown08[index].unknownd0;
    }
    if (arg.unknown08[index].unknowna4 > 1.0f) {
      arg.unknown08[index].unknowna4 = 1.0f;
    } else if (arg.unknown08[index].unknowna4 < 0.0f) {
      arg.unknown08[index].unknowna4 = 0.0f;
    }
  }
}

int DrResEtcPamObj::calcWorkSize(const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  const unknown002 *params = reinterpret_cast<const unknown002 *>(data + header->unknown84);
  return params->unknown04 * sizeof(DrResEtcParams) + 0x20;
}

} // namespace ml
