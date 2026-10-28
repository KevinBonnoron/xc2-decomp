#include "gf/object/component/pc/gf_com_behavior_pc.h"

#include "gf/gf_allocator.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

namespace gf {
namespace pc {

AccessPlugin *AccessPlugin::create() {
  // __LINE__ must be 31 as in the original header: it is the line argument of operator new.
#line 31 "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) AccessPlugin();
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

void GfComBehaviorPc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

} // namespace gf
