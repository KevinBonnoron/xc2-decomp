#pragma once
#include <stddef.h>

#include "layer/layer_acc_font_obj.h"
#include "layer/layer_font_tag.h"
#include "types.h"

namespace layer {

class LayerFontIconObj;
class LayerFontResObj;
class LayerFontStyleObj;
class LayerObjFont;
struct LayerResFontInfo;
struct LyrFontStyleData;

// Evidence: LayerObjFont::setMsg builds one on the stack, calls the constructor and createChar, then reads nothing else.
class LayerFontDrawBuffer : public LayerFontTag {
public:
  LayerFontDrawBuffer(const LayerFontResObj *res, const LayerFontStyleObj *style, const LyrFontStyleData *styleData, const LayerFontIconObj *icon, LayerFontSetting setting, LayerObjFont *font);
  void reset();
  LayerResFontInfo *createChar(const u8 *text);
  void createWorkBuffer(const LayerTagWork &work, const u8 *text);
  void endWorkSetup();
  LayerResFontInfo *createChar(const wchar_t *text);
  void createFontCode(u16 code) override;
  void createRubyFontCode(u16 code) override;
  void createFontIcon(u16 code) override;
  void fontCnt();
  void createLineBreak() override;

  u32 unknown4a0;                       // Inferred role: horizontal, copied by LayerObjFont::setMsg; original member name unknown.
  u32 unknown4a4;                       // Inferred role: vertical, copied by LayerObjFont::setMsg; original member name unknown.
  LayerResFontInfo *m_layerResFontInfo; // Inferred role: created font info, returned by createChar; original member name unknown.
  LayerObjFont *m_layerObjFont;         // Inferred role: font object; original member name unknown.
  u32 unknown4b8;                       // Inferred role: character instance count; original member name unknown.
  u32 unknown4bc;                       // Inferred role: icon instance count; original member name unknown.
  s32 unknown4c0[2];                    // Inferred role: text width and height; original member name unknown.
};

static_assert(offsetof(LayerFontDrawBuffer, unknown4a0) == 0x4a0, "");
static_assert(offsetof(LayerFontDrawBuffer, m_layerObjFont) == 0x4b0, "");
static_assert(offsetof(LayerFontDrawBuffer, unknown4b8) == 0x4b8, "");
static_assert(offsetof(LayerFontDrawBuffer, unknown4c0) == 0x4c0, "");
static_assert(sizeof(LayerFontDrawBuffer) == 0x4c8, "");

} // namespace layer
