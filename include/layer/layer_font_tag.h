#pragma once
#include <stddef.h>

#include "layer/layer_tag.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace layer {

class LayerFontIconObj;
class LayerFontResObj;
class LayerFontStyleObj;
struct LyrFontStyleData;

struct LayerTagWork {
  s32 unknown00; // Inferred role: character count; original member name unknown.
  s32 unknown04; // Inferred role: color tag string length; original member name unknown.
  u8 _08[0x0c - 0x08];
  s32 unknown0c; // Inferred role: icon tag count; original member name unknown.
  s32 unknown10; // Inferred role: string length; original member name unknown.
  s32 unknown14; // Inferred role: string byte size; original member name unknown.
};

static_assert(offsetof(LayerTagWork, unknown0c) == 0x0c, "");
static_assert(offsetof(LayerTagWork, unknown14) == 0x14, "");

class LayerFontTag : public LayerTag {
public:
  struct unknown001 {
    f32 unknown00[9]; // Inferred role: font instance; original member name unknown.
  };

  void getWorkSize(LayerTagWork &work, const u8 *string);
  void getWorkSize(LayerTagWork &work, const wchar_t *string);
  void createWork(const u8 *string);
  void createWork(const wchar_t *string);
  void beginParseString() override;
  void parseNotTag(const u8 *string, u32 &index) override;
  void calcTagColorEnd();
  void calcTagWide();

  virtual void createFontCode(u16 code) = 0;
  virtual void createRubyFontCode(u16 code) = 0;
  virtual void createFontIcon(u16 code) = 0;
  virtual void createLineBreak() = 0;

  const LayerFontStyleObj *unknown08; // Inferred role: style object; original member name unknown.
  const LayerFontResObj *unknown10;   // Inferred role: font resource; original member name unknown.
  const LayerFontIconObj *unknown18;  // Inferred role: icon object; original member name unknown.
  const LyrFontStyleData *unknown20;  // Inferred role: style data; original member name unknown.
  bool unknown28;                     // Inferred role: creates the work instead of counting its size; original member name unknown.
  bool unknown29;                     // Inferred role: wide tag; original member name unknown.
  u8 _2a[0x30 - 0x2a];
  LayerTagWork *unknown30; // Inferred role: tag work; original member name unknown.
  s32 unknown38;           // Inferred role: display setting; original member name unknown.
  u32 unknown3c;           // Inferred role: setting is not default; original member name unknown.
  u32 unknown40;           // Inferred role: setting is default; original member name unknown.
  u8 _44[0x48 - 0x44];
  u64 unknown48;         // Inferred role: unknown; original member name unknown.
  unknown001 *unknown50; // Inferred role: font instances; original member name unknown.
  u64 unknown58;         // Inferred role: unknown; original member name unknown.
  u64 unknown60;         // Inferred role: unknown; original member name unknown.
  mm::Col4 unknown68;    // Inferred role: current color; original member name unknown.
  mm::Col4 unknown78;    // Inferred role: saved color; original member name unknown.
  u16 unknown88[0x200];  // Inferred role: ruby character codes; original member name unknown.
  s32 unknown488[2];     // Inferred role: ruby start positions; original member name unknown.
  s32 unknown490;        // Inferred role: ruby character count; original member name unknown.
  s32 unknown494[2];     // Inferred role: ruby end positions; original member name unknown.
  s32 unknown49c;        // Inferred role: line count; original member name unknown.
};

static_assert(offsetof(LayerFontTag, unknown08) == 0x08, "");
static_assert(offsetof(LayerFontTag, unknown10) == 0x10, "");
static_assert(offsetof(LayerFontTag, unknown18) == 0x18, "");
static_assert(offsetof(LayerFontTag, unknown20) == 0x20, "");
static_assert(offsetof(LayerFontTag, unknown28) == 0x28, "");
static_assert(offsetof(LayerFontTag, unknown30) == 0x30, "");
static_assert(offsetof(LayerFontTag, unknown38) == 0x38, "");
static_assert(offsetof(LayerFontTag, unknown48) == 0x48, "");
static_assert(offsetof(LayerFontTag, unknown68) == 0x68, "");
static_assert(offsetof(LayerFontTag, unknown78) == 0x78, "");
static_assert(offsetof(LayerFontTag, unknown88) == 0x88, "");
static_assert(offsetof(LayerFontTag, unknown488) == 0x488, "");
static_assert(offsetof(LayerFontTag, unknown490) == 0x490, "");
static_assert(offsetof(LayerFontTag, unknown494) == 0x494, "");
static_assert(offsetof(LayerFontTag, unknown49c) == 0x49c, "");

} // namespace layer
