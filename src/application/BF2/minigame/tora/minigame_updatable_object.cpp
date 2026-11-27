// The game compiles MinigameUpdatableObject, factory::create and the minigame constructor inlined in myinit in a unit of their own, between framework and minigame_tora.cpp (0x71006a0524 to
// 0x71006a0fb8): the functions of minigame_tora.cpp (getResult, update, initialize, finalize) are called here, not inlined (getResult would be: cost 145 against the threshold 275 when it is defined
// in the same unit). The vtable of minigame and the destructors of minigame and PtrSingleton<minigame> are emitted at the end of this unit, with the constructor used by myinit.
#include <string.h>

#include <new>

#include "framework/memory/framework_memory.h"
#include "framework/object/updatable_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/object/updatable_object_factory.h"
#include "framework/pointer_map.h"
#include "framework/resource/common_resource.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_item_util.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_mem_obj.h"
#include "layer/layer_base.h"
#include "layer/layer_obj_manager.h"
#include "minigame/tora/minigame_tora.h"
#include "ml/scn.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "types.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"

namespace fw {
enum LOAD_PRIO : int;
enum SoundCategory : int;
} // namespace fw

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace minigame {
namespace tora {

MinigameUpdatableObject::MinigameUpdatableObject(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer)
    : fw::UpdatableObject(type, handle, layer), m_uIObjectAcc(nullptr), m_layerBase(nullptr), m_commonResource(nullptr), m_soundResource(nullptr), m_minigame(nullptr), m_menuCallContext(nullptr),
      unknown110(nullptr) {}

MinigameUpdatableObject::~MinigameUpdatableObject() {
  if (m_uIObjectAcc != nullptr) {
    delete m_uIObjectAcc;
    m_uIObjectAcc = nullptr;
  }
  if (m_layerBase != nullptr) {
    ml::ScnRenderDrSysParmAcc parmAcc(ml::Scn::get()->unknown38, 0);
    parmAcc.resetModelTexture(0);
    parmAcc.resetModelTexture(1);
    if (m_layerBase != nullptr) {
      m_layerBase->release();
    }
    m_layerBase = nullptr;
  }
  mm::mtl::safeRelease(m_soundResource);
  mm::mtl::safeRelease(m_commonResource);
  m_minigame->finalize();
  if (m_minigame != nullptr) {
    delete m_minigame;
    m_minigame = nullptr;
  }
  gf::GfFieldBgm::get()->stopBgmForDebug(false);
}

void MinigameUpdatableObject::res_load() {
  m_commonResource = fw::CommonResource::request(gf::getAllocator(static_cast<gf::ALLOCATOR>(10)), "minigame/tora.bin", 10, false);
  fw::SoundResource::SetupInfo info;
  info.unknown00 = static_cast<fw::SoundCategory>(5);
  m_soundResource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), "sound/se/minigame.xsp", info, static_cast<fw::LOAD_PRIO>(10));
}

void MinigameUpdatableObject::myinit(ui::UIObjectAcc *parent) {
  gf::GfFieldBgm::get()->stopBgmForDebug(true);
  fw::SoundManager::get()->stopBgmAll();
  m_minigame = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->getMemHandle(), nullptr, 0, 4, false) minigame;
  m_minigame->initialize();
  res_load();
  m_uIObjectAcc = parent;
  if (parent != nullptr && parent->isValid()) {
    parent->setDisp(true);
    m_uIObjectAcc->setTexFilterNearest();
  }
  layer::LayerAccManager manager;
  m_layerBase = manager.createMemObj(0x140, 0xf0, layer::LAYER_MEM_TYPE_UNKNOWN_1);
  layer::LayerAccMemObj memAcc(m_layerBase);
  memAcc.setRender(false);
  grlib::CGLibTextureBuffer *buffer = memAcc.getTexture();
  ml::ScnRenderDrSysParmAcc parmAcc(ml::Scn::get()->unknown38, 0);
  ml::ScnRenderDrMdlTexture texture;
  texture.unknown00 = buffer;
  texture.unknown08 = 0;
  texture.unknown0c = true;
  parmAcc.setModelTexture(texture);
  texture.unknown00 = buffer;
  texture.unknown08 = 1;
  texture.unknown0c = false;
  parmAcc.setModelTexture(texture);
  memset(memAcc.getMemBufer(), 0, memAcc.getMemWidth() * memAcc.getMemHeight() * 3);
  memAcc.updateMemBufer();
}

bool MinigameUpdatableObject::disp_result() {
  if (m_menuCallContext == nullptr || unknown110 == nullptr || unknown110->unknown00 >= unknown110->unknown02) {
    return false;
  }
  gf::GfMenuItemList list;
  // The SetupParam shares its stack slot (0x71006a09f0 to 0x71006a09fc, sp+0) with the MenuItemInfo of the loop: its lifetime ends with this block (ruling 3).
  {
    ui::UIListInfoBase::SetupParam param;
    list.setup(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), param);
  }
  u16 index = unknown110->unknown00;
  if (index < unknown110->unknown02) {
    // pos walks the items and count the window of five: the game compares (count + 1) > 4 as a 32-bit value next to the 64-bit counter (0x71006a0a7c, cmp w9, #4). With a single counter
    // (about 200 spellings of its type and of the loop measured) the compare is widened to 64 bits (cmp x9) and the sum is hoisted out of the loop.
    int count = 0;
    int pos = index;
    do {
      gf::MenuItemInfo info;
      info.unknown04 = unknown110[pos].unknown00;
      info.unknown00 = gf::GfItemUtil::getType(info.unknown04);
      info.unknown08 = unknown110[pos].unknown02;
      list.addContents(info);
      pos++;
      count++;
    } while (pos < unknown110->unknown02 && count < 5);
    index += count;
  }
  unknown110->unknown00 = index;
  gf::GfMenuObjCommonText::openGetItem(m_menuCallContext, &list);
  return true;
}

// The game keeps the compare `phase > 10` un-inverted (cmp w8, #10; b.ls at 0x71006a0b18) and lays the update branch out of line: the condition is the negated `||` chain with the update branch
// written first (the same chain with the clear branch first gives cmp w8, #11; b.lo, and `&& phase <= 10` with the update branch first gives cmp #10; b.hi with the update branch falling through).
void MinigameUpdatableObject::update(const fw::UpdateInfo &info) {
  if (!(m_commonResource == nullptr || !m_commonResource->valid() || m_minigame == nullptr || m_minigame->unknown64c > 10)) {
    if (m_uIObjectAcc != nullptr && m_uIObjectAcc->isValid()) {
      s16 width;
      s16 height;
      m_uIObjectAcc->getSize(false, width, height);
      width *= 3;
      u8 *buffer = static_cast<u8 *>(m_uIObjectAcc->getOnMemoryBuffer());
      m_minigame->update(buffer, width, height, m_commonResource->getAssetData(), m_soundResource);
      m_uIObjectAcc->swapOnMemoryBuffer();
    } else if (m_layerBase != nullptr) {
      layer::LayerAccMemObj memAcc(m_layerBase);
      u8 *buffer = static_cast<u8 *>(memAcc.getMemBufer());
      int width = memAcc.getMemWidth();
      int height = memAcc.getMemHeight();
      m_minigame->update(buffer, width * 3, height, m_commonResource->getAssetData(), m_soundResource);
      memAcc.updateMemBufer();
    }
    if (m_minigame->unknown64c > 10) {
      minigame::_sResult result;
      m_minigame->getResult(&result);
      gf::SCOM_ACHIEV_INC::create(0x44, result.unknown00, 0);
      int itemCount = 0;
      for (int i = 0; result.unknown04[i].unknown02 != 0; i++) {
        if (result.unknown04[i].unknown00 == 0xffff) {
          gf::SCOM_ADD_ETHER::create(result.unknown04[i].unknown02);
        } else {
          itemCount++;
          gf::SCOM_ADD_ITEM::create(result.unknown04[i].unknown00, result.unknown04[i].unknown02);
        }
      }
      if (itemCount > 0) {
        m_menuCallContext = gf::GfMenuCallContext::create();
        unknown110 = static_cast<unknown010 *>(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->allocate((itemCount + 1) * sizeof(unknown010), 0x40));
        unknown110->unknown00 = 1;
        unknown110->unknown02 = itemCount + 1;
        int index = 1;
        for (int i = 0; result.unknown04[i].unknown02 != 0; i++) {
          if (result.unknown04[i].unknown00 != 0xffff) {
            unknown110[index].unknown00 = result.unknown04[i].unknown00;
            unknown110[index].unknown02 = result.unknown04[i].unknown02;
            index++;
          }
        }
        disp_result();
      }
    }
  } else {
    if (m_uIObjectAcc != nullptr && m_uIObjectAcc->isValid()) {
      s16 width;
      s16 height;
      m_uIObjectAcc->getSize(false, width, height);
      memset(m_uIObjectAcc->getOnMemoryBuffer(), 0, width * height * 3);
      m_uIObjectAcc->swapOnMemoryBuffer();
    } else if (m_layerBase != nullptr) {
      layer::LayerAccMemObj memAcc(m_layerBase);
      memset(memAcc.getMemBufer(), 0, memAcc.getMemWidth() * memAcc.getMemHeight() * 3);
      memAcc.updateMemBufer();
    }
    if (m_minigame != nullptr && m_minigame->unknown64c > 10) {
      if (m_menuCallContext == nullptr) {
        gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->deallocate(unknown110);
        unknown110 = nullptr;
        setTerminate();
      } else if (m_menuCallContext->isTerm() && !disp_result()) {
        mm::mtl::safeRelease(m_menuCallContext);
      }
    }
  }
}

namespace factory {

fw::UpdatableObject *create(ui::UIObjectAcc *parent) {
  fw::UpdatableObjectFactory *factory = fw::UpdatableObjectFactory::get();
  void *memory = factory->unknown08->allocate(sizeof(MinigameUpdatableObject), 8);
  fw::HandlePtr<fw::UpdatableObject> handle = factory->m_updatableObjectManager->registPointer(0xf, memory);
  MinigameUpdatableObject *object = new (memory) MinigameUpdatableObject(0xf, handle, 10);
  factory->m_updatableObjectManager->registObject(0xf, object);
  object->initialize();
  if (object != nullptr) {
    object->myinit(parent);
  }
  return object;
}

} // namespace factory

const mm::mtl::RTTI *MinigameUpdatableObject::getRTTI() const { return &m_rtti; }

} // namespace tora
} // namespace minigame
