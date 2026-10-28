#include "ptlib/emitter/particle_emitter_manager.h"

#include <math.h>
#include <string.h>

#include "dr/dr_gpu_check_base.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_shader.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "ptlib/emitter/compute/particle_emitter_compute.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_ext.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/emitter/particle_emitter_set_node.h"
#include "ptlib/particle_math.h"
#include "ptlib/particle_system.h"
#include "ptlib/renderer/particle_renderer_eff_state.h"
#include "ptlib/renderer/particle_renderer_manager.h"
#include "ptlib/renderer/particle_renderer_obj.h"
#include "ptlib/renderer/particle_renderer_shader.h"
#include "ptlib/renderer/particle_renderer_stream.h"

namespace ptlib {

namespace emitter {

namespace {
EmitterManager *s_instance;
} // namespace

f32 EmitterObj::getCateSpd() {
  EmitterManager *manager = EmitterManager::getPtr();
  return manager->unknown1700[unknown170];
}

EmitterManager *EmitterManager::get() {
#line 21
  MM_ASSERT(getPtr());
  return getPtr();
}

EmitterManager *&EmitterManager::getPtr() { return s_instance; }

void EmitterManager::moveAfter() {}

void EmitterObj::remove_particle_free_tbl(ParticleObj *particle) {
  unknown40.erase(particle);
  particle->particle_clear_union();
  EmitterManager::get()->addFreeParticleFront(particle);
}

void EmitterObj::releaseParticleAll() {
  IntrusiveList<ParticleObj>::iterator it = unknown40.begin();
  while (it != unknown40.end()) {
    ParticleObj &particle = *it;
    unknown40.erase(it);
    EmitterManager::get()->addFreeParticleFront(&particle);
    it = unknown40.begin();
  }
}

void EmitterObj::emitter_set_param_sub_pos_only2(EmitterParam *param) {
  if (unknown80 == nullptr) {
    unknowne0.unknown30 = mm::Vec3(param->unknown00.unknown30);
  }
  ParticleManager::get()->update_model_spd(this, 1.0f);
}

void EmitterObj::emitter_set_param_sub(EmitterParam *param) {
  u32 type;
  if (unknown80 == nullptr) {
    memcpy(&unknowne0, param, sizeof(unknown001));
    if (unknown98 == nullptr) {
      return;
    }
    type = unknown98->unknown109;
    if (type == 0xff) {
      unknown120 = param->unknown40;
    } else if (type - 1 < 0xe) {
      unknown140 = param->unknown60;
    }
    unknown14c = param->unknown6c;
    unknown130 = param->unknown50;
    unknown150 = param->unknown70;
    f32 radius = param->unknown68;
    if (radius > 0.0f && m_pGpuCheck == nullptr) {
      mm::Vec3NA start = unknown98->unknown14;
      mm::Vec3NA end = unknown98->unknown44;
      f32 dy = start.y - end.y;
      f32 dx = start.x - end.x;
      f32 dz = start.z - end.z;
      unknown31c = sqrtf(dx * dx + dy * dy + dz * dz);
      unknown31c = (unknown31c + (unknown98->unknown9c + unknown98->unknowna0)) * 1.5f;
      const DrDrawWorkInfoEF *info = renderer::RenderManager::get()->getRenderGrObj()->unknown258;
      if (unknown31c < radius) {
        unknown318 = radius;
      } else {
        unknown318 = unknown31c;
      }
      m_pGpuCheck = ml::DrGpuCheckBase::createEffGpuCheckObj(info->unknown560);
    }
  } else {
    type = unknown98->unknown109;
  }
  if (type == 0xff) {
    unknown120 = param->unknown40;
  }
  unknown151 = param->unknown71;
  unknown152 = param->unknown72;
  unknown153 = param->unknown73;
  if (param->unknown78 >= 0.0f) {
    unknown158 = param->unknown78;
  }
  if (param->unknown90 != -1) {
    unknown170 = param->unknown90;
  }
  unknown15c = param->unknown7c;
  unknown154 = param->unknown74;
  unknown156 = param->unknown76;
  unknown157 = param->unknown77;
  unknown160 = param->unknown80;
  unknown164 = param->unknown84;
  unknown168 = param->unknown88;
  unknown16c = param->unknown8c;
  unknown174 = param->unknown94;
}

IntrusiveList<EmitterObj> &EmitterManager::getEmitterActiveList() { return unknown17a8; }

IntrusiveList<EmitterObj>::iterator EmitterManager::getEmitterActiveIt(EmitterObj *emitter) { return unknown17a8.find(emitter); }

EmitterObj *EmitterManager::getEmitterFree() {
  if (unknown17c0.m_size == 0) {
    return nullptr;
  }
  IntrusiveList<EmitterObj>::iterator it = unknown17c0.begin();
  EmitterObj &emitter = *it;
  unknown17c0.erase(it);
  return &emitter;
}

void EmitterManager::addEmitterFree(EmitterObj *emitter) {
  if (emitter->unknown60 != nullptr) {
    emitter->unknown60->release();
  }
  emitter->releaseParticleAll();
  unknown17c0.push_back(emitter);
}

void EmitterManager::removeEmitterActive(EmitterObj *emitter) {
  if (emitter->unknown60 != nullptr) {
    emitter->unknown60->release();
  }
  emitter->releaseParticleAll();
  unknown17a8.erase(getEmitterActiveIt(emitter));
}

void EmitterManager::addEmitterActive(EmitterObj *emitter) { unknown17a8.push_back(emitter); }

void EmitterManager::addEmitterActiveAfterParent(EmitterObj *emitter, EmitterObj *parent) { unknown17a8.push_back(emitter); }

ParticleObj *EmitterManager::particleAlloc(EmitterObj *emitter, bool isFront) {
  ParticleObj *et = getFreeParticle();
  if (et != nullptr) {
    if (isFront) {
      emitter->unknown40.push_front(et);
    } else {
      emitter->unknown40.push_back(et);
    }
    u8 isModel = 1;
    if (emitter->unknown98 == nullptr || emitter->unknown98->unknown00 != 4) {
      isModel = 0;
    }
    et->unknown13e = isModel;
    u8 isLight = 1;
    if (emitter->unknown98 == nullptr || emitter->unknown98->unknown00 != 5) {
      isLight = 0;
    }
    et->unknown144 = isLight;
    et->initUtilObj();
    et->unknown20 = et->unknown10;
    et->getExtParam().m_emParent = emitter;
#line 893
    MM_ASSERT(et->getExtParam().getEmParent());
  }
  return et;
}

ParticleObj *EmitterManager::getFreeParticle() {
  if (unknown17d8.m_size < 1) {
    return nullptr;
  }
  IntrusiveList<ParticleObj>::iterator it = unknown17d8.begin();
  if (it == unknown17d8.end()) {
    return nullptr;
  }
  ParticleObj *particle = it.get();
  unknown17d8.erase(it);
  particle->unknown001();
  return particle;
}

void EmitterManager::addFreeParticleFront(ParticleObj *particle) { unknown17d8.push_front(particle); }

void EmitterManager::addFreeParticleBack(ParticleObj *particle) { unknown17d8.push_back(particle); }

void EmitterManager::emitter_set_param_pos_only(u32 handle, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      if (it->unknown80 == nullptr) {
        memcpy(&it->unknowne0, param, sizeof(unknown001));
      }
      ParticleManager::get()->update_model_spd(it.get(), 1.0f);
    }
  }
}

void EmitterManager::emitter_set_param_pos_only2(u32 handle, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->emitter_set_param_sub_pos_only2(param);
    }
  }
}

void EmitterManager::emitter_set_param(u32 handle, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->emitter_set_param_sub(param);
    }
  }
  f32 skip = param->unknown7c;
  if (skip >= 1.0f) {
    int count = static_cast<int>(skip * 0.5f);
    if (count < 1) {
      count = 1;
    } else {
      skip = 2.0f;
    }
    for (int i = 0; i < count; i++) {
      emitter_update(handle, skip, false);
    }
  }
}

void EmitterManager::emitter_set_param(FxHeader *header, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown58 == header) {
      it->emitter_set_param_sub(param);
    }
  }
}

void EmitterManager::emitter_set_disp(u32 handle, int isDisp) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown151 = isDisp;
    }
  }
}

void EmitterManager::emitter_set_alpha(u32 handle, f32 alpha) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown120.a = alpha;
    }
  }
}

void EmitterManager::emitter_set_category(u32 handle, u32 category) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown170 = category;
    }
  }
}

void EmitterManager::emitter_set_nowait(u32 handle, int isNoWait) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown152 = isNoWait;
    }
  }
}

void EmitterManager::emitter_set_viewnum(u32 handle, int viewnum) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown274 = viewnum;
      it->unknown90 = ParticleManager::getGrp(viewnum & 0xff);
    }
  }
}

void EmitterManager::emitter_set_link(FxHeader *header) {
  if (unknown1808.m_size < 1) {
#line 908
    MM_ASSERT(0);
    return;
  }
  IntrusiveList<EmitterSetNode>::iterator it = unknown1808.begin();
  EmitterSetNode &node = *it;
  unknown1808.erase(it);
  node.unknown18 = header;
  unknown17f0.push_back(&node);
}

void EmitterManager::emitter_create_local_common_life(EmitterObj *emitter, ParticleObj *particle, EmitterArg *arg) {
  u16 base = arg->unknown8e;
  u32 life;
  f32 rate;
  if (base == 0) {
    life = 0x7fff;
    rate = 1.0f;
  } else {
    f32 range = arg->unknown90;
    f32 random = math::unknown001(emitter->unknown268);
    life = static_cast<u32>(range * random) + base;
    f32 total = arg->unknown8c;
    rate = total / static_cast<f32>(life);
  }
  particle->unknownc0 = life;
  particle->unknownbc = rate;
  particle->unknownb8 = 1.0f;
  particle->unknownc3 = 0;
}

void EmitterManager::emitter_set_casparam(u32 handle, const void *model, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle && it->unknown80 == nullptr) {
      it->unknownc0->unknown00 = model;
      it->unknownc0->unknown70[0] = 0;
      it->emitter_set_param_sub(param);
    }
  }
}

void *EmitterManager::createFunc(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param) {
  if (particle->unknownd4_int == 1) {
    return create_local01(emitter, particle, frame, param);
  }
  efAstMsg("0", "create func set error !!!");
  return nullptr;
}

void EmitterManager::emitter_set_casname(u32 handle, const void *model, const char *name, int index, f32 frame, int flags) {
  if (name != nullptr && strlen(name) >= 0x10) {
    efAstMsg("0", "emitter_set_casname:too long name[%s]", name);
  }
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle && it->unknown80 == nullptr) {
      if (model == nullptr) {
        it->unknownc0->unknown00 = nullptr;
        it->unknownc0->unknown70[0] = 0;
      } else {
        it->unknownc0->unknown00 = model;
        it->unknown14c = frame;
        it->unknown153 = flags;
        if (name != nullptr) {
          strcpy(it->unknownc0->unknown70, name);
        }
      }
    }
  }
}

bool EmitterManager::emitter_set_check(FxHeader *header) {
  for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
    if (header != nullptr) {
      return true;
    }
  }
  return false;
}

void EmitterManager::emitter_pack_free(u64 pack) {
  int count = 0;
  for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
    if (it->unknown18->unknown48 == pack) {
      count++;
    }
  }
  if (count > 0) {
    do {
      for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
        if (it->unknown18->unknown48 == pack) {
          emitter_set_free(it->unknown18, 1);
          count--;
          break;
        }
      }
    } while (count > 0);
  }
}

EmitterObj *EmitterManager::emitter_free_core(EmitterObj *emitter) {
  if (emitter->unknown98 == nullptr) {
    efMsg("free type error");
  } else {
    switch (emitter->unknown98->unknown00) {
    case 4:
      for (IntrusiveList<ParticleObj>::iterator it = emitter->unknown40.begin(); it != emitter->unknown40.end(); ++it) {
        (*it).particle_clear_union();
      }
      break;
    case 5:
      for (IntrusiveList<ParticleObj>::iterator it = emitter->unknown40.begin(); it != emitter->unknown40.end(); ++it) {
        *it;
      }
      for (IntrusiveList<ParticleObj>::iterator it = emitter->unknown40.begin(); it != emitter->unknown40.end(); ++it) {
        (*it).particle_clear_union();
      }
      break;
    default:
      for (IntrusiveList<ParticleObj>::iterator it = emitter->unknown40.begin(); it != emitter->unknown40.end(); ++it) {
        (*it).particle_clear_union();
      }
      break;
    }
  }
  if (emitter->unknown90 != nullptr) {
    emitter->unknown90 = nullptr;
  }
  EmitterObj *next = static_cast<EmitterObj *>(emitter->unknown00);
  if (emitter->m_pGpuCheck != nullptr) {
    emitter->m_pGpuCheck->release();
    emitter->m_pGpuCheck = nullptr;
  }
  emitter->unknown98 = nullptr;
  removeEmitterActive(emitter);
  addEmitterFree(emitter);
  return next;
}

void EmitterManager::move() {
  EmitterObj *lastTop = nullptr;
  EmitterObj *lastSecond = nullptr;
  EmitterObj *lastThird = nullptr;
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    EmitterObj *emitter = it.get();
    EmitterArg *arg = emitter->unknown98;
    bool isRender = emitter->isRenderCheck();
    if (arg != nullptr && isRender && ((arg->unknown00 & 0xfe) == 4 || (emitter->unknown151 != 0 && 0.0f < emitter->unknown120.a))) {
      switch (arg->unknown00) {
      case 0:
      case 1:
      case 9:
        if (lastTop == nullptr) {
          unknown1750 = emitter;
        } else {
          lastTop->unknownc8 = emitter;
        }
        lastTop = emitter;
        break;
      case 2:
        if (lastSecond == nullptr) {
          unknown1760 = emitter;
        } else {
          lastSecond->unknownc8 = emitter;
        }
        lastSecond = emitter;
        break;
      case 4:
      case 5:
        if (lastThird == nullptr) {
          unknown1758 = emitter;
        } else {
          lastThird->unknownc8 = emitter;
        }
        lastThird = emitter;
        break;
      case 0xc:
        if (lastTop != nullptr) {
          lastTop->unknownc8 = emitter;
        } else {
          unknown1750 = emitter;
        }
        lastTop = emitter;
        break;
      }
      if (lastTop == nullptr) {
        unknown1750 = nullptr;
      } else {
        lastTop->unknownc8 = nullptr;
      }
      if (lastSecond == nullptr) {
        unknown1760 = nullptr;
      } else {
        lastSecond->unknownc8 = nullptr;
      }
      if (lastThird == nullptr) {
        unknown1758 = nullptr;
      } else {
        lastThird->unknownc8 = nullptr;
      }
      unknown1768 = nullptr;
    }
  }
}

void EmitterManager::emitter_set_speed(u32 handle, f32 speed) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (handle == 0 || it->unknown264 == handle) {
      it->unknown158 = speed;
    }
  }
}

bool EmitterObj::isRenderCheck() const {
  if (m_pGpuCheck == nullptr || m_pGpuCheck->isRender()) {
    return true;
  }
  return unknown18c < 60.0f;
}

// The game executable compiles ComputeManager::calculateParticle in the translation unit of the EmitterManager functions, where EmitterManager::getPtr is inlined.
void ComputeManager::calculateParticle() {
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  grlib::CGLibColorCtl::setColorBufferOn();
  grlib::CGLibDepthCtl::setDepthControl(0, 0, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
  EmitterManager *emitterManager = EmitterManager::getPtr();
  renderer::RenderGrObj *renderGrObj = renderer::RenderManager::get()->getRenderGrObj();
  const DrDrawWorkInfoEF *info = renderGrObj->unknown258;
  grlib::CGLibDecShader *decShader = renderGrObj->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_13);
  grlib::CGLibCtlShader::setShader(*decShader, renderer::EffStateManager::get()->unknown4f0);
  u32 shadowLocation1 = (decShader->unknown38 + decShader->unknown58)->getTextureLocation("shw1");
  u32 shadowLocation2 = (decShader->unknown38 + decShader->unknown58)->getTextureLocation("shw2");
  u32 shadowLocation3 = (decShader->unknown38 + decShader->unknown58)->getTextureLocation("shw3");
  grlib::CGLibCtlTexture::setTexture(*info->unknown090, renderer::EffStateManager::get()->unknown360, shadowLocation1);
  grlib::CGLibCtlTexture::setTexture(*info->unknown098, renderer::EffStateManager::get()->unknown360, shadowLocation2);
  grlib::CGLibCtlTexture::setTexture(*info->unknown0a0, renderer::EffStateManager::get()->unknown360, shadowLocation3);
  u32 commonBuffOffset = (decShader->unknown38 + decShader->unknown58)->getUniformBlockOfs("CommonBuff");
  u32 readBlockOffset = (decShader->unknown38 + decShader->unknown58)->getUniformBlockOfs("ReadBlock");
  unknown108[unknown208].unknown08.setUniformBlock(commonBuffOffset);
  int uniformBlockSize = ComputeUniform::s_nUniformBlockSize[0];
  bool isRasterizerSet = false;
  for (IntrusiveList<EmitterObj>::iterator it = emitterManager->getEmitterActiveList().begin(); it != emitterManager->getEmitterActiveList().end(); ++it) {
    if (it->isRenderCheck() && it->unknown27c != 0) {
      if (!isRasterizerSet) {
        grlib::CGLibPolygon::setRasterizer(true);
      }
      unknown48.unknown08.setUniformBlock(readBlockOffset, it->unknown27e << 9, 0x200);
      grlib::CGLibCtlVertex::setUniformVertex(unknown08.unknown08, uniformBlockSize, it->unknown27a * uniformBlockSize, 0, 0);
      unknown08.unknown08.setStorageBuffer(0);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, it->unknown27c);
      isRasterizerSet = true;
    }
  }
  if (isRasterizerSet) {
    grlib::CGLibPolygon::setRasterizer(false);
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
  }
}

} // namespace emitter
} // namespace ptlib
