#include "gf/menu/object/gf_menu_obj_idea_gram.h"

#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_IDEA_GRAM = 57;

GfMenuObjIdeaGram::GfMenuObjIdeaGram(u32 handle) : GfMenuObject(handle) {}

GfMenuObjIdeaGram::~GfMenuObjIdeaGram() { ; }

void GfMenuObjIdeaGram::initialize() {
  ui::UIObjectAcc root(handle);
  attachExternalCall(CALL_IDEA_GRAM, ui::UIObjectAcc(handle, "LAY_driver").handle);
  GfMenuObject::initialize();
}

void GfMenuObjIdeaGram::finalize() { GfMenuObject::finalize(); }

void GfMenuObjIdeaGram::update() { GfMenuObject::update(); }

} // namespace gf
