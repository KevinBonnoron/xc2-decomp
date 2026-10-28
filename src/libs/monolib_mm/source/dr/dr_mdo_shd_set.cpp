#include "dr/dr_mdo_shd_set.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mdo_setup.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_etc_uniform_obj.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_list.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"

namespace ml {

void DrMdoShdSet::setDitherTexShaderSet(u32 location, int index) {
  DrAPCache *cache = DrMan::get()->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(DrMan::get()->unknown70->unknown98[index], location);
}

void DrMdoShdSet::setDitherShaderSet(u32 location, u32 binding, int index) {
  DrAPCache *cache = DrMan::get()->unknown5c0;
  cache->beginTexSampling(2, 0);
  cache->setTexture(DrMan::get()->unknown70->unknown98[index], location);
  DrCalcViewWork *viewWork = DrMan::get()->unknown580->unknown10;
  grlib::CGLibDblUniformBlock *uniform = &viewWork->unknown938;
  if (index != 1) {
    uniform = &viewWork->unknown970;
  }
  uniform->setUniformBlock(binding);
}

void DrMdoShdSet::setFlagWaveTexSet(u32 location, int index) {
  DrAPCache *cache = DrMan::get()->unknown5c0;
  cache->beginTexSampling(0, 1);
  if (index == 0) {
    cache->setTexture(DrMan::get()->unknown70->unknown98[16], location);
  } else {
    cache->setTexture(DrMan::get()->unknown70->unknown98[17], location);
  }
}

void DrMdoShdSet::setFlagWaveUniform(int index, u32 binding) {
  unknown009 *uniforms = unknown00->unknown30->unknown140;
  if (uniforms != nullptr) {
    (*uniforms->unknown18)[uniforms->unknown00[index]].setUniformBlock(binding);
  }
}

void DrMdoShdSetPrePass::preshd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (unknown00->unknown17c == index) {
    return;
  }
  unknown00->unknown17c = index;
  prePass->setupShader(0, type);
  DrMan::get()->unknown580->unknown10->unknown7b0.setUniformBlock(prePass->unknown08[6]);
}

void DrMdoShdSetPrePass::preshd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (unknown00->unknown17c != index) {
    unknown00->unknown17c = index;
    prePass->setupShader(0, type);
    DrMan::get()->unknown580->unknown10->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Inst_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (unknown00->unknown17c != index) {
    unknown00->unknown17c = index;
    prePass->setupShader(0, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (!(unknown00->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      unknown00->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      unknown00->unknownf8 &= ~0x40000000;
    }
    DrMan::get()->unknown580->unknown10->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    return;
  }
  f32 alphaRef;
  if (header->unknown1c == 0.0f) {
    alphaRef = 0.5f;
  } else {
    alphaRef = header->unknown1c;
  }
  list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
  bool isCurrent = (unknown00->unknownf8 & 0x40000000) != 0;
  if (!(unknown00->unknownf8 & 0x20000000)) {
    if (isCurrent) {
      return;
    }
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
    unknown00->unknownf8 |= 0x40000000;
  } else {
    if (!isCurrent) {
      return;
    }
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
    unknown00->unknownf8 &= ~0x40000000;
  }
}

// Inferred role: sets the shader, the uniform and the texture of a draw pass; original name unknown.
inline void DrMdoShdSetMpf::unknown001(DrResShdMpf *shd, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler) {
  u32 flags = header->unknown04;
  shd->setupShader((flags >> 8) & 1);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  if (flags & 0x100) {
    (*unknown08->unknown90)[header->unknown12].setUniformBlock(shd->unknown08[5]);
  }
  unknown00->m_drMan->unknown5c0->setTexture(*unknown08->unknowne8[header->unknown14], *sampler->unknown08, shd->unknown08[0]);
}

void DrMdoShdSetMpf::mpfshd_stm_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
}

void DrMdoShdSetMpf::mpfshd_stm_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  grlib::CGLibTriUniformBlock *wind = &unknown00->m_drMan->unknown88->unknown020->unknown18;
  wind->setUniformBlock(shd->unknown08[3]);
  wind->setOldUniformBlock(shd->unknown08[4]);
}

void DrMdoShdSetMpf::mpfshd_stm_bill_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  grlib::CGLibTriUniformBlock *wind = &unknown00->m_drMan->unknown88->unknown020->unknown18;
  wind->setUniformBlock(shd->unknown08[3]);
  wind->setOldUniformBlock(shd->unknown08[4]);
}

void DrMdoShdSetMpf::mpfshd_pre_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 mode = 2;
  if (!isPre) {
    mode = 0;
  }
  shd->setupShader(mode);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  if (isPre) {
    list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
    setDitherTexShaderSet(shd->unknown08[2], 1);
  }
}

void DrMdoShdSetMpf::mpfshd_pre_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 mode = 2;
  if (!isPre) {
    mode = 0;
  }
  shd->setupShader(mode);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  if (isPre) {
    list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
    setDitherTexShaderSet(shd->unknown08[2], 1);
  }
}

void DrMdoShdSetMpf::mpfshd_pre_bill_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 mode = 2;
  if (!isPre) {
    mode = 0;
  }
  shd->setupShader(mode);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  DrAPCache *cache = unknown00->m_drMan->unknown5c0;
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  cache->setTexture(*unknown08->unknowne8[header->unknown18], *sampler->unknown10, shd->unknown08[0]);
  if (isPre) {
    setDitherTexShaderSet(shd->unknown08[2], 1);
  }
}

void DrMdoShdSetMpf::mpfshd_pre_mdl_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 mode = 2;
  if (!isPre) {
    mode = 0;
  }
  shd->setupShader(mode);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  unknown00->m_drMan->unknown5c0->setTexture(*unknown08->unknowne8[header->unknown18], *sampler->unknown10, shd->unknown08[0]);
  if (isPre) {
    setDitherTexShaderSet(shd->unknown08[2], 1);
  }
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  setDitherTexShaderSet(shd->unknown08[2], 1);
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  unknown00->m_drMan->unknown5c0->setTexture(*unknown08->unknowne8[header->unknown18], *sampler->unknown10, shd->unknown08[0]);
  setDitherTexShaderSet(shd->unknown08[2], 1);
}

void DrMdoShdSetMpf::mpfshd_drw_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) { unknown001(shd, header, sampler); }

void DrMdoShdSetMpf::mpfshd_drw_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) { unknown001(shd, header, sampler); }

void DrMdoShdSetMpf::mpfshd_drw_mdl_nonom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) { unknown001(shd, header, sampler); }

void DrMdoShdSetMpf::mpfshd_drw_mdl_def(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) { unknown001(shd, header, sampler); }

void DrMdoShdSetMpf::mpfshd_drw_mdl_defnonom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) { unknown001(shd, header, sampler); }

void DrMdoShdSetMpf::mpfshd_drw_mdl_normalmap(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 flags = header->unknown04;
  shd->setupShader((flags >> 8) & 1);
  unknown00->m_drMan->unknown580->unknown10->unknown900.setUniformBlock(shd->unknown08[6]);
  if (flags & 0x100) {
    (*unknown08->unknown90)[header->unknown12].setUniformBlock(shd->unknown08[5]);
  }
  DrAPCache *cache = unknown00->m_drMan->unknown5c0;
  cache->setTexture(*unknown08->unknowne8[header->unknown14], *sampler->unknown08, shd->unknown08[0]);
  cache->setTexture(*unknown08->unknowne8[header->unknown1c], *sampler->unknown18, shd->unknown08[1]);
}

void DrMdoShdSetMpf::mpfshd_cull_fade_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {}

// Inferred role: selects the shader of the shadow shader object; original name unknown.
inline void DrMdoShdSetShadow::unknown001(int index, DrResShdShw *shw, DrShdDataList *list) {
  unknown00->unknown17c = index;
  u8 type = s_pShwTypeDec[index];
  shw->setDecAType(type >> 4);
  shw->setDecBType(type & 0xf);
  shw->setupShader(list->getFetchShader(s_pShwFethcDef[index]));
}

void DrMdoShdSetShadow::shwShd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  u8 type = s_pShwTypeDec[index];
  u32 decAType = type >> 4;
  u32 decBType = type & 0xf;
  if (unknown00->unknown17c == index) {
    if (unknown00->unknown17a != uniformIndex) {
      (*unknown00->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown00->unknown17c = index;
    shw->setDecAType(decAType);
    shw->setDecBType(decBType);
    shw->setupShader(list->getFetchShader(s_pShwFethcDef[index]));
    if (decAType != 1) {
      list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    }
    unknown00->m_drMan->unknown78->unknown850->setUniformBlock(shw->unknown08[2]);
    (*unknown00->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    setFlagWaveTexSet(shw->unknown08[5], 0);
    setFlagWaveTexSet(shw->unknown08[6], 1);
  }
  if (decAType != 1) {
    setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  }
  unknown009 *flagWaves = unknown00->unknown30->unknown140;
  if (flagWaves != nullptr) {
    u16 waveIndex = flagWaves->unknown00[flagWaveIndex];
    (*flagWaves->unknown18)[waveIndex].setUniformBlock(shw->unknown08[4]);
  }
  unknown00->unknown17a = uniformIndex;
}

void DrMdoShdSetShadow::shwShd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c == index) {
    if (unknown00->unknown178 & 2) {
      unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
  }
  unknown00->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c == index) {
    if (unknown00->unknown178 & 2) {
      unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
  }
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  unknown00->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_Spt_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c == index) {
    if (unknown00->unknown178 & 2) {
      unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    unknown00->m_drMan->unknown78->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  unknown00->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_Spt_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c == index) {
    if (unknown00->unknown178 & 2) {
      unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    unknown00->unknown170->setUniformBlock(shw->unknown08[1]);
    unknown00->m_drMan->unknown78->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  unknown00->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_InstMot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c != index) {
    unknown001(index, shw, list);
    unknown00->m_drMan->unknown78->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  unknown00->m_drMan->unknown88->unknown040->setUniformBlock(unknown00->unknown30->unknown148->unknown20, shw->unknown08[1]);
}

void DrMdoShdSetShadow::shwShd_InstMotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (unknown00->unknown17c != index) {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    unknown00->m_drMan->unknown78->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  unknown00->m_drMan->unknown88->unknown040->setUniformBlock(unknown00->unknown30->unknown148->unknown20, shw->unknown08[1]);
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
}

} // namespace ml
