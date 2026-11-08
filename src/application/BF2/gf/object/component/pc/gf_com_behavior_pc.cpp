#include "gf/object/component/pc/gf_com_behavior_pc.h"

#include <string.h>

#include "framework/memory/allocator.h"
#include "framework/reference_frame.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/pc/gf_pc_agent.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

namespace gf {
class GfComAsm;
struct CallBackCache;

bool isAttenuationPack(const char *name) {
  return strcmp(name, "se_mov_pc_default") == 0 || strcmp(name, "se_fld_move_nopon") == 0 || strcmp(name, "se_fld_move_large") == 0 || strcmp(name, "se_fld_move_hana") == 0 ||
         strcmp(name, "se_fld_move_beast") == 0 || strcmp(name, "se_fld_move_float") == 0 || strcmp(name, "se_fld_allmap") == 0;
}
namespace pc {

AccessPlugin *AccessPlugin::create() {
  // __LINE__ must be 31 as in the original header: it is the line argument of operator new.
#line 31 "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) AccessPlugin();
}

AttachPlugin *AttachPlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) AttachPlugin();
}

ColVelCalculatorPlugin *ColVelCalculatorPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ColVelCalculatorPlugin();
}

DeadColCheckPlugin *DeadColCheckPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) DeadColCheckPlugin();
}

FadePlugin *FadePlugin::create() {
  // __LINE__ must be 34 as in the original header: it is the line argument of operator new.
#line 34 "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FadePlugin();
}

FallDamagePlugin *FallDamagePlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FallDamagePlugin();
}

FallDistanceAchievPlugin *FallDistanceAchievPlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FallDistanceAchievPlugin();
}

FallDistancePlugin *FallDistancePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FallDistancePlugin();
}

FallIntoColiPlugin *FallIntoColiPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FallIntoColiPlugin();
}

LookAxisPlugin *LookAxisPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LookAxisPlugin();
}

LurePlugin *LurePlugin::create() {
  // __LINE__ must be 29 as in the original header: it is the line argument of operator new.
#line 29 "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LurePlugin();
}

LookAtPlugin *LookAtPlugin::create() {
  // __LINE__ must be 39 as in the original header: it is the line argument of operator new.
#line 39 "gf/object/component/pc/plugin/gf_pc_lookat_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LookAtPlugin();
}

SlidePlugin *SlidePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SlidePlugin();
}

TargetIKPlugin *TargetIKPlugin::create() {
  // __LINE__ must be 33 as in the original header: it is the line argument of operator new.
#line 33 "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) TargetIKPlugin();
}

TerrainDamagePlugin *TerrainDamagePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) TerrainDamagePlugin();
}

TimerPlugin *TimerPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) TimerPlugin();
}

WaterInPlugin *WaterInPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) WaterInPlugin();
}

} // namespace pc

void GfComBehaviorPc::Listener::onWkStandbyLogout() { unknown08->unknown130 = nullptr; }

GfComBehaviorPc::GfComBehaviorPc() : unknowna0(fw::Allocator::getProcAllocator()), unknown130(nullptr), unknown138(this) {}

GfComBehaviorPc::~GfComBehaviorPc() {}

void GfComBehaviorPc::callbackBattle(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorPc::callbackField(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorPc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

const mm::mtl::RTTI *GfComBehaviorPc::getRTTI() const { return &m_rtti; }

} // namespace gf

template void mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComBehaviorPc>(const mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)> *,
                                                                                                                         gf::GfComAsm *, const gf::CallBackCache &);
