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
#include "dr/dr_res_mdo_sampler.h"
#include "dr/dr_res_mpf_sampler.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_list.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/cglib_vtx_stm_out.h"

namespace ml {

void DrMdoShdSet::setupMofFetchShader(const MdsMatInfoHeader *header) {
  if (header->unknown04 & MdsMatInfoHeader::unknown015_15) {
    if (m_drMdoSetup->unknown179 != 1) {
      m_drMdoSetup->unknown179 = 1;
      m_drMdoSetup->unknown17c = -1;
    }
  } else {
    if (m_drMdoSetup->unknown179 != 0) {
      m_drMdoSetup->unknown179 = 0;
      m_drMdoSetup->unknown17c = -1;
    }
  }
}

void DrMdoShdSet::setOneTexShaderSet(int index, u32 location) {
  DrAPCache *cache = DrMan::get()->m_drAPCache;
  const u8 *data = m_drMdoSetup->unknown30->unknown10;
  const MdsMatTextureInfo *infos = reinterpret_cast<const MdsMatTextureInfo *>(data + reinterpret_cast<const MdsMatTopHeader *>(data)->unknown3c);
  grlib::CGLibTextureBuffer *texture = m_drMdoSetup->unknown30->unknowne8[infos[index].unknown00];
  u16 mipmap = texture->getMipmap();
  const grlib::CGLibSampler *samplers = m_drMdoSetup->unknown30->m_drResMdoSampler->unknown30;
  if (mipmap == 0) {
    cache->setTexture(*texture, samplers[infos[index].unknown04], location);
  } else {
    cache->setTexture(*texture, samplers[infos[index].unknown02], location);
  }
}

void DrMdoShdSet::setDitherTexShaderSet(u32 location, int index) {
  DrAPCache *cache = DrMan::get()->m_drAPCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(DrMan::get()->m_drIniSys->unknown98[index], location);
}

void DrMdoShdSet::setDitherShaderSet(u32 location, u32 binding, int index) {
  DrAPCache *cache = DrMan::get()->m_drAPCache;
  cache->beginTexSampling(2, 0);
  cache->setTexture(DrMan::get()->m_drIniSys->unknown98[index], location);
  DrCalcViewWork *viewWork = DrMan::get()->m_drCalcMan->m_drCalcViewWork;
  grlib::CGLibDblUniformBlock *uniform = &viewWork->unknown938;
  if (index != 1) {
    uniform = &viewWork->unknown970;
  }
  uniform->setUniformBlock(binding);
}

void DrMdoShdSet::setFlagWaveTexSet(u32 location, int index) {
  DrAPCache *cache = DrMan::get()->m_drAPCache;
  cache->beginTexSampling(0, 1);
  if (index == 0) {
    cache->setTexture(DrMan::get()->m_drIniSys->unknown98[16], location);
  } else {
    cache->setTexture(DrMan::get()->m_drIniSys->unknown98[17], location);
  }
}

void DrMdoShdSet::setFlagWaveUniform(int index, u32 binding) {
  unknown009 *uniforms = m_drMdoSetup->unknown30->unknown140;
  if (uniforms != nullptr) {
    u16 waveIndex = uniforms->unknown00[index];
    (*uniforms->unknown18)[waveIndex].setUniformBlock(binding);
  }
}

void DrMdoShdSetPrePass::preshd_Obj(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
  } else {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetPrePass::preshd_ObjT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
  } else {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Obj_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  } else {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetPrePass::preshd_ObjT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    m_drMdoSetup->unknown17a = uniformIndex;
    setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
    return;
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  if (m_drMdoSetup->unknown17a != uniformIndex) {
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
  }
  bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
  if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
    if (!isCurrent) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    }
  } else {
    if (isCurrent) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Mot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    return;
  }
  m_drMdoSetup->unknown17c = index;
  prePass->setupShader(m_drMdoSetup->unknown179, type);
  DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  list->unknown958.setStorageBuffer(0);
}

void DrMdoShdSetPrePass::preshd_MotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    list->unknown958.setStorageBuffer(0);
  }
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Mot_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    list->unknown958.setStorageBuffer(0);
  } else {
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetPrePass::preshd_MotT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    list->unknown958.setStorageBuffer(0);
    m_drMdoSetup->unknown17a = uniformIndex;
    setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
    return;
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  if (m_drMdoSetup->unknown17a != uniformIndex) {
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
  }
  bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
  if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
    if (!isCurrent) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    }
  } else {
    if (isCurrent) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (m_drMdoSetup->unknown17c == index) {
    return;
  }
  m_drMdoSetup->unknown17c = index;
  prePass->setupShader(0, type);
  DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
}

void DrMdoShdSetPrePass::preshd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(0, type);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Inst_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(0, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    return;
  }
  f32 alphaRef;
  if (header->unknown1c == 0.0f) {
    alphaRef = 0.5f;
  } else {
    alphaRef = header->unknown1c;
  }
  list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
  bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
  if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
    if (isCurrent) {
      return;
    }
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
    m_drMdoSetup->unknownf8 |= 0x40000000;
  } else {
    if (!isCurrent) {
      return;
    }
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
    m_drMdoSetup->unknownf8 &= ~0x40000000;
  }
}

void DrMdoShdSetPrePass::preshd_InstT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(0, type);
    f32 alphaRef;
    if (header->unknown1c == 0.0f) {
      alphaRef = 0.5f;
    } else {
      alphaRef = header->unknown1c;
    }
    list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  } else {
    f32 alphaRef;
    if (header->unknown1c == 0.0f) {
      alphaRef = 0.5f;
    } else {
      alphaRef = header->unknown1c;
    }
    list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_Inst_Bill_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(0, type);
    f32 alphaRef;
    if (header->unknown1c == 0.0f) {
      alphaRef = 0.5f;
    } else {
      alphaRef = header->unknown1c;
    }
    list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
  } else {
    f32 alphaRef;
    if (header->unknown1c == 0.0f) {
      alphaRef = 0.5f;
    } else {
      alphaRef = header->unknown1c;
    }
    list->getAlphaTestUniform(alphaRef)->setUniformBlock(prePass->unknown08[8]);
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  (*m_mdoWrkMatRes->unknown120_1->unknown08)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
}

void DrMdoShdSetPrePass::preshd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
  } else {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    setFlagWaveTexSet(prePass->unknown08[3], 0);
    setFlagWaveTexSet(prePass->unknown08[4], 1);
  }
  setFlagWaveUniform(flagWaveIndex, prePass->unknown08[10]);
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetPrePass::preshd_FwT(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
  } else {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    setFlagWaveTexSet(prePass->unknown08[3], 0);
    setFlagWaveTexSet(prePass->unknown08[4], 1);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
  setFlagWaveUniform(flagWaveIndex, prePass->unknown08[10]);
}

void DrMdoShdSetPrePass::preshd_FwT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    setFlagWaveTexSet(prePass->unknown08[3], 0);
    setFlagWaveTexSet(prePass->unknown08[4], 1);
  } else {
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
  setFlagWaveUniform(flagWaveIndex, prePass->unknown08[10]);
}

void DrMdoShdSetPrePass::preshd_Fw_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    setFlagWaveTexSet(prePass->unknown08[3], 0);
    setFlagWaveTexSet(prePass->unknown08[4], 1);
  } else {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  setFlagWaveUniform(flagWaveIndex, prePass->unknown08[10]);
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetPrePass::preshd_ObjT_Al_FS(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    m_drMdoSetup->unknown17a = uniformIndex;
    setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
    return;
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  if (m_drMdoSetup->unknown17a != uniformIndex) {
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
  }
  bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
  if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
    if (!isCurrent) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    }
  } else {
    if (isCurrent) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_MotT_Al_FS(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    list->unknown958.setStorageBuffer(0);
    m_drMdoSetup->unknown17a = uniformIndex;
    setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
    return;
  }
  list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
  if (m_drMdoSetup->unknown17a != uniformIndex) {
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
  }
  bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
  if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
    if (!isCurrent) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    }
  } else {
    if (isCurrent) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
}

void DrMdoShdSetPrePass::preshd_FwT_Al_Fs(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list, PrePassType type) {
  DrResShdPrePass *prePass = list->getPrePassObj(index);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    m_drMdoSetup->unknown17c = index;
    prePass->setupShader(m_drMdoSetup->unknown179, type);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    setDitherShaderSet(prePass->unknown08[1], prePass->unknown08[9], 1);
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
      m_drMdoSetup->unknownf8 |= 0x40000000;
    } else {
      setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
      m_drMdoSetup->unknownf8 &= ~0x40000000;
    }
    (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    DrMan::get()->m_drCalcMan->m_drCalcViewWork->unknown7b0.setUniformBlock(prePass->unknown08[6]);
    setFlagWaveTexSet(prePass->unknown08[3], 0);
    setFlagWaveTexSet(prePass->unknown08[4], 1);
  } else {
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(prePass->unknown08[8]);
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_mdoWrkMatRes->unknowna0)[uniformIndex].setUniformBlock(prePass->unknown08[5]);
    }
    bool isCurrent = (m_drMdoSetup->unknownf8 & 0x40000000) != 0;
    if (!(m_drMdoSetup->unknownf8 & 0x20000000)) {
      if (!isCurrent) {
        setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 1);
        m_drMdoSetup->unknownf8 |= 0x40000000;
      }
    } else {
      if (isCurrent) {
        setDitherShaderSet(prePass->unknown08[2], prePass->unknown08[9], 2);
        m_drMdoSetup->unknownf8 &= ~0x40000000;
      }
    }
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, prePass->unknown08[0]);
  setFlagWaveUniform(flagWaveIndex, prePass->unknown08[10]);
}

// Inferred role: sets the shader, the uniform and the texture of a draw pass; original name unknown.
inline void DrMdoShdSetMpf::unknown001(DrResShdMpf *shd, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler) {
  u32 flags = header->unknown04;
  shd->setupShader((flags >> 8) & 1);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  if (flags & 0x100) {
    (*m_mdoWrkMatRes->unknown90)[header->unknown12].setUniformBlock(shd->unknown08[5]);
  }
  m_drMdoSetup->m_drMan->m_drAPCache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown14], *sampler->unknown08[0], shd->unknown08[0]);
}

void DrMdoShdSetMpf::mpfshd_stm_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
}

void DrMdoShdSetMpf::mpfshd_stm_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  grlib::CGLibTriUniformBlock *wind = &m_drMdoSetup->m_drMan->m_drMdlMan->m_drMdoMpfMan->m_cGLibTriUniformBlock;
  wind->setUniformBlock(shd->unknown08[3]);
  wind->setOldUniformBlock(shd->unknown08[4]);
}

void DrMdoShdSetMpf::mpfshd_stm_bill_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  grlib::CGLibTriUniformBlock *wind = &m_drMdoSetup->m_drMan->m_drMdlMan->m_drMdoMpfMan->m_cGLibTriUniformBlock;
  wind->setUniformBlock(shd->unknown08[3]);
  wind->setOldUniformBlock(shd->unknown08[4]);
}

void DrMdoShdSetMpf::mpfshd_pre_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  u32 mode = 2;
  if (!isPre) {
    mode = 0;
  }
  shd->setupShader(mode);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
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
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
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
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  DrAPCache *cache = m_drMdoSetup->m_drMan->m_drAPCache;
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  cache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown18], *sampler->unknown08[1], shd->unknown08[0]);
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
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  m_drMdoSetup->m_drMan->m_drAPCache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown18], *sampler->unknown08[1], shd->unknown08[0]);
  if (isPre) {
    setDitherTexShaderSet(shd->unknown08[2], 1);
  }
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  setDitherTexShaderSet(shd->unknown08[2], 1);
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {
  shd->setupShader(0);
  list->getAlphaTestUniform(header->unknown08)->setUniformBlock(shd->unknown08[7]);
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  m_drMdoSetup->m_drMan->m_drAPCache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown18], *sampler->unknown08[1], shd->unknown08[0]);
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
  m_drMdoSetup->m_drMan->m_drCalcMan->m_drCalcViewWork->unknown900.setUniformBlock(shd->unknown08[6]);
  if (flags & 0x100) {
    (*m_mdoWrkMatRes->unknown90)[header->unknown12].setUniformBlock(shd->unknown08[5]);
  }
  DrAPCache *cache = m_drMdoSetup->m_drMan->m_drAPCache;
  cache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown14], *sampler->unknown08[0], shd->unknown08[0]);
  cache->setTexture(*m_mdoWrkMatRes->unknowne8[header->unknown1c], *sampler->unknown08[2], shd->unknown08[1]);
}

void DrMdoShdSetMpf::mpfshd_cull_fade_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre) {}

// Inferred role: selects the shader of the shadow shader object; original name unknown.
inline void DrMdoShdSetShadow::unknown001(int index, DrResShdShw *shw, DrShdDataList *list) {
  m_drMdoSetup->unknown17c = index;
  u8 type = s_pShwTypeDec[index];
  shw->setDecAType(type >> 4);
  shw->setDecBType(type & 0xf);
  shw->setupShader(list->getFetchShader(s_pShwFethcDef[index]));
}

// Inferred role: selects the shader of the shadow shader object with the fetch shader of the seam flag; original name unknown.
inline void DrMdoShdSetShadow::unknown002(int index, DrResShdShw *shw, DrShdDataList *list) {
  m_drMdoSetup->unknown17c = index;
  u8 type = s_pShwTypeDec[index];
  shw->setDecAType(type >> 4);
  shw->setDecBType(type & 0xf);
  shw->setupShader(list->getFetchShader(s_pShwFethcTbl[m_drMdoSetup->unknown179][index]));
}

void DrMdoShdSetShadow::shwShd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int flagWaveIndex, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  u8 type = s_pShwTypeDec[index];
  u32 decAType = type >> 4;
  u32 decBType = type & 0xf;
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    }
  } else {
    m_drMdoSetup->unknown17c = index;
    shw->setDecAType(decAType);
    shw->setDecBType(decBType);
    shw->setupShader(list->getFetchShader(s_pShwFethcDef[index]));
    if (decAType != 1) {
      list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    }
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
    (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    setFlagWaveTexSet(shw->unknown08[5], 0);
    setFlagWaveTexSet(shw->unknown08[6], 1);
  }
  if (decAType != 1) {
    setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  }
  unknown009 *flagWaves = m_drMdoSetup->unknown30->unknown140;
  if (flagWaves != nullptr) {
    u16 waveIndex = flagWaves->unknown00[flagWaveIndex];
    (*flagWaves->unknown18)[waveIndex].setUniformBlock(shw->unknown08[4]);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetShadow::shwShd_Obj(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown002(index, shw, list);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
    (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
}

void DrMdoShdSetShadow::shwShd_ObjT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown17a != uniformIndex) {
      (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown002(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
    (*m_drMdoSetup->unknown30->unknowna0)[uniformIndex].setUniformBlock(shw->unknown08[1]);
  }
  m_drMdoSetup->unknown17a = uniformIndex;
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
}

void DrMdoShdSetShadow::shwShd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown178 & 2) {
      m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
  }
  m_drMdoSetup->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown178 & 2) {
      m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
  }
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  m_drMdoSetup->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_Mot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    unknown002(index, shw, list);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
    list->unknown958.setStorageBuffer(shw->unknown08[1]);
  }
}

void DrMdoShdSetShadow::shwShd_MotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  setupMofFetchShader(header);
  if (m_drMdoSetup->unknown17c != index) {
    unknown002(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
    list->unknown958.setStorageBuffer(shw->unknown08[1]);
  }
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
}

void DrMdoShdSetShadow::shwShd_Spt_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown178 & 2) {
      m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  m_drMdoSetup->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_Spt_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c == index) {
    if (m_drMdoSetup->unknown178 & 2) {
      m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    }
  } else {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    m_drMdoSetup->unknown170->setUniformBlock(shw->unknown08[1]);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
  m_drMdoSetup->unknown178 &= ~2;
}

void DrMdoShdSetShadow::shwShd_InstMot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c != index) {
    unknown001(index, shw, list);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  m_drMdoSetup->m_drMan->m_drMdlMan->m_drResEtcUniformObj->setUniformBlock(m_drMdoSetup->unknown30->unknown148->unknown20, shw->unknown08[1]);
}

void DrMdoShdSetShadow::shwShd_InstMotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list) {
  DrResShdShw *shw = list->getShwObj(s_pShwUseShdader[index]);
  if (m_drMdoSetup->unknown17c != index) {
    unknown001(index, shw, list);
    list->getAlphaTestUniform(header->unknown1c)->setUniformBlock(shw->unknown08[3]);
    m_drMdoSetup->m_drMan->m_drPixlMan->unknown850->setUniformBlock(shw->unknown08[2]);
  }
  m_drMdoSetup->m_drMan->m_drMdlMan->m_drResEtcUniformObj->setUniformBlock(m_drMdoSetup->unknown30->unknown148->unknown20, shw->unknown08[1]);
  setOneTexShaderSet(header->unknown62, shw->unknown08[0]);
}

} // namespace ml
