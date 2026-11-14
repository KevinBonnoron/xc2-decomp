#include "gf/menu/adapter/gf_menu_life_adapter.h"

#include "gf/gf_allocator.h"
#include "ml/rand.h"
#include "mm_mtl/rtti.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

// Inferred role: maximum of the random minutes of the effect time; original name unknown.
constexpr int EFF_TIME_UNKNOWN_99 = 99;
// Inferred role: maximum of the random seconds of the effect time; original name unknown.
constexpr int EFF_TIME_UNKNOWN_59 = 59;
// Inferred role: maximum of the bonus number; original name unknown.
constexpr int BONUS_UNKNOWN_99 = 99;

GfMenuLifeAdapter::GfMenuLifeAdapter(ui::UIObjectPlugin *plugin) : GfMenuAdapter(plugin, false, false), unknown30(0), unknown58(true) {}

GfMenuLifeAdapter::~GfMenuLifeAdapter() { ; }

GfMenuLifeAdapter *GfMenuLifeAdapter::create_Time_EffTime(u32 handle, const char *name, u8 index) {
  ui::UIObjectAcc acc(handle, name);
  if (!acc.isValid()) {
    return nullptr;
  }
  return create(ui::UIObjectTimePlugin::create(acc.unknown10, 4), index, &GfMenuLifeAdapter::update_Time_EffTime);
}

GfMenuLifeAdapter *GfMenuLifeAdapter::create(ui::UIObjectPlugin *plugin, u8 index, void (GfMenuLifeAdapter::*update)(u8)) {
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 95 as in the original source: it is the line argument of operator new.
#line 95
  GfMenuLifeAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuLifeAdapter(plugin);
  if (adapter != nullptr) {
    adapter->unknown30 = index;
    adapter->unknown38.bind(adapter, update);
  }
  plugin->release();
  return adapter;
}

void GfMenuLifeAdapter::update_Time_EffTime(u8 index) {
  ui::UIObjectTimePlugin *timePlugin = static_cast<ui::UIObjectTimePlugin *>(unknown18);
  if (timePlugin != nullptr && timePlugin->getRTTI()->isKindOf(&ui::UIObjectTimePlugin::m_rtti)) {
    timePlugin->setMin(ml::mtRand(0, EFF_TIME_UNKNOWN_99));
    timePlugin->setSec(ml::mtRand(0, EFF_TIME_UNKNOWN_59));
  }
}

GfMenuLifeAdapter *GfMenuLifeAdapter::create_Text_BonusName(u32 handle, const char *name, u8 index) {
  ui::UIObjectAcc acc(handle, name);
  if (!acc.isValid()) {
    return nullptr;
  }
  return create(ui::UIObjectTextPlugin::create(acc.unknown10), index, &GfMenuLifeAdapter::update_Text_BonusName);
}

void GfMenuLifeAdapter::update_Text_BonusName(u8 index) {
  ui::UIObjectTextPlugin *textPlugin = static_cast<ui::UIObjectTextPlugin *>(unknown18);
  if (textPlugin != nullptr && textPlugin->getRTTI()->isKindOf(&ui::UIObjectTextPlugin::m_rtti)) {
  }
}

GfMenuLifeAdapter *GfMenuLifeAdapter::create_Number_Bonus(u32 handle, const char *name, u8 index) {
  ui::UIObjectAcc acc(handle, name);
  if (!acc.isValid()) {
    return nullptr;
  }
  ui::UIObjectNumberPlugin *numberPlugin = ui::UIObjectNumberPlugin::create(acc.unknown10);
  numberPlugin->setMin(0);
  numberPlugin->setMax(BONUS_UNKNOWN_99);
  return create(numberPlugin, index, &GfMenuLifeAdapter::update_Number_Bonus);
}

void GfMenuLifeAdapter::update_Number_Bonus(u8 index) {
  ui::UIObjectNumberPlugin *numberPlugin = static_cast<ui::UIObjectNumberPlugin *>(unknown18);
  if (numberPlugin != nullptr && numberPlugin->getRTTI()->isKindOf(&ui::UIObjectNumberPlugin::m_rtti)) {
    numberPlugin->setNumber(ml::mtRand(numberPlugin->unknown80, numberPlugin->unknown84));
  }
}

void GfMenuLifeAdapter::update(const fw::UpdateInfo &info) {
  if (unknown38.isValid() && unknown58) {
    unknown38(unknown30);
    unknown58 = false;
  }
}

} // namespace gf
