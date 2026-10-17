#include "gf/menu/adapter/gf_menu_field_skill_adapter.h"

#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuFieldSkillAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuFieldSkillAdapter::update_Name, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 9999}},
    {&GfMenuFieldSkillAdapter::update_Lv, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
};

GfMenuFieldSkillAdapter::GfMenuFieldSkillAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr) {}

GfMenuFieldSkillAdapter::~GfMenuFieldSkillAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
  }
}

GfMenuFieldSkillAdapter *GfMenuFieldSkillAdapter::create(u32 handle, u32 type, const MenuFieldSkill &fieldSkill) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 176 as in the original source: it is the line argument of operator new.
#line 176
      GfMenuFieldSkillAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuFieldSkillAdapter(plugin, false);
      adapter->updater.bind(adapter, info.update);
      adapter->fieldSkill = fieldSkill;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuFieldSkillAdapter::update_Name(const MenuFieldSkill &fieldSkill) {
  u8 *bdat;
  u32 textId;
  if (fieldSkill.fieldSkill == 0 || !GfDataFieldSkill::getName(bdat, textId, fieldSkill.fieldSkill)) {
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuFieldSkillAdapter::update_Lv(const MenuFieldSkill &fieldSkill) {
  if (fieldSkill.fieldSkill == 0) {
    return false;
  }
  setNumber(fieldSkill.level);
  return true;
}

GfMenuFieldSkillAdapter *GfMenuFieldSkillAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  MenuFieldSkill fieldSkill;
  converter->getFieldSkill(fieldSkill);
  GfMenuFieldSkillAdapter *adapter = create(handle, type, fieldSkill);
  if (adapter != nullptr) {
    adapter->converter = converter;
  }
  return adapter;
}

GfMenuFieldSkillAdapter *GfMenuFieldSkillAdapter::createFromBlade(u32 handle, u32 type, u32 blade, u32 option) {
  // __LINE__ must be 206 as in the original source: it is the line argument of operator new.
#line 206
  BladeConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeConverter(blade, 0);
  return createFromCoverter(handle, type, converter, false);
}

GfMenuFieldSkillAdapter *GfMenuFieldSkillAdapter::createFromList(u32 handle, u32 type, GfMenuFieldSkillList *list, int listIndex) {
  // __LINE__ must be 214 as in the original source: it is the line argument of operator new.
#line 214
  ListConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListConverter(list, listIndex);
  return createFromCoverter(handle, type, converter, false);
}

GfMenuFieldSkillAdapter *GfMenuFieldSkillAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference) {
  // __LINE__ must be 222 as in the original source: it is the line argument of operator new.
#line 222
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceConverter(reference);
  return createFromCoverter(handle, type, converter, false);
}

void GfMenuFieldSkillAdapter::update(const fw::UpdateInfo &info) {
  if (converter != nullptr) {
    MenuFieldSkill newFieldSkill;
    converter->getFieldSkill(newFieldSkill);
    if (fieldSkill.fieldSkill != newFieldSkill.fieldSkill) {
      fieldSkill.fieldSkill = newFieldSkill.fieldSkill;
      setChange();
    }
    if (fieldSkill.level != newFieldSkill.level) {
      fieldSkill.level = newFieldSkill.level;
      setChange();
    }
  }

  if ((flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0 && updater.isValid()) {
    setDisp(fieldSkill.fieldSkill != 0 && updater(fieldSkill));
    flags &= ~FLAG_CHANGED;
  }
}

void GfMenuFieldSkillAdapter::BladeConverter::getFieldSkill(MenuFieldSkill &fieldSkill) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  if (acc.isValid() && acc.getObjType() == OBJECT_TYPE_BLADE) {
    fieldSkill.fieldSkill = acc.getFieldSkill(slot, false);
    fieldSkill.level = acc.getFieldSkillLevel(slot, false);
  }
}

void GfMenuFieldSkillAdapter::ListConverter::getFieldSkill(MenuFieldSkill &fieldSkill) {
  if (listIndex != -1 && listIndex < static_cast<int>(list->getSize())) {
    MenuFieldSkill &current = list->getContents(list->getPageIndex(listIndex));
    fieldSkill.fieldSkill = current.fieldSkill;
    fieldSkill.level = current.level;
  }
}

void GfMenuFieldSkillAdapter::ReferenceConverter::getFieldSkill(MenuFieldSkill &fieldSkill) {
  if (reference.get() != nullptr) {
    reference->getFs(fieldSkill);
  }
}

} // namespace gf
