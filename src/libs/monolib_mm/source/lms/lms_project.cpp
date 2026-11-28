#include <stddef.h>

#include "lms/lms_impl.h"
#include "ms/ms_wrapper.h"
#include "types.h"

// Second translation unit of the message library (see lms_impl.h): the project and its accessors. The payload of each
// block is read at byte offsets (decision 38 of docs/decisions.md); the layouts below are what the accessors read.

namespace {

// Inferred role: payload of the colour block ("CLR1"): a count, then one entry of four channels per colour; original
// type name unknown. LMS_GetColor (0x71009851ac) copies the four bytes of an entry one by one.
struct unknown003 {
  s32 unknown00;         // Inferred role: colour count; original member name unknown.
  LMSColor unknown04[1]; // Inferred role: the colours; original member name unknown.
};

// Inferred role: entry of the attribute block ("ATI2"), stride 8; original type name unknown.
struct unknown004 {
  s8 unknown00;  // Inferred role: attribute type, 9 for a list; original member name unknown.
  u8 unknown01;  // Inferred role: padding; original member name unknown.
  u16 unknown02; // Inferred role: for a list, its index in the list block ("ALI2"); original member name unknown.
  s32 unknown04; // Inferred role: offset of the attribute in a message; original member name unknown.
};

// Inferred role: head of the attribute block ("ATI2"): the count, followed by the entries; original type name unknown.
struct unknown005 {
  s32 unknown00; // Inferred role: attribute count; original member name unknown.
};

// Inferred role: table of offsets from its start, of the list block ("ALI2"), of each list in it and of the contents
// block ("CTI1"): a count, then the offsets of the items (strings or lists); original type name unknown.
struct unknown006 {
  s32 unknown00;    // Inferred role: count; original member name unknown.
  u32 unknown04[1]; // Inferred role: offsets of the items from the start of the table; original member name unknown.
};

// Inferred role: entry of the style block ("SYL3"), stride 0x10; original type name unknown.
struct unknown007 {
  u32 unknown00; // Inferred role: region width; original member name unknown.
  u32 unknown04; // Inferred role: line number; original member name unknown.
  s32 unknown08; // Inferred role: font index, -1 when not set; original member name unknown.
  s32 unknown0c; // Inferred role: base colour index, -1 when not set; original member name unknown.
};

// Inferred role: head of the style block ("SYL3"): the count, followed by the entries; original type name unknown.
struct unknown008 {
  u32 unknown00; // Inferred role: style count; original member name unknown.
};

// Inferred role: head of the tag group block ("TGG2"), of the tag block ("TAG2"), of the parameter block ("TGP2") and
// of the list item block ("TGL2"): a count, followed by the u32 offsets of the records from the start of the block;
// original type name unknown. The groups are sorted by their identifier.
struct unknown009 {
  u16 unknown00; // Inferred role: record count; original member name unknown.
  u16 unknown02; // Inferred role: padding; original member name unknown.
};

// Inferred role: record of a tag group: its identifier, the number of its tags and their indexes in the tag block,
// then the NUL terminated name; original type name unknown.
struct unknown00a {
  u16 unknown00;    // Inferred role: group identifier; original member name unknown.
  u16 unknown02;    // Inferred role: tag count; original member name unknown.
  u16 unknown04[1]; // Inferred role: indexes of the tags in the tag block; original member name unknown.
};

// Inferred role: record of a tag: the number of its parameters and their indexes in the parameter block, then the
// NUL terminated name; original type name unknown.
struct unknown00b {
  u16 unknown00;    // Inferred role: parameter count; original member name unknown.
  u16 unknown02[1]; // Inferred role: indexes of the parameters in the parameter block; original member name unknown.
};

// Inferred role: record of a tag parameter: its type, then either the name (types other than 9) or, for a list
// (type 9), the number of items, their indexes in the list item block and the name; original type name unknown.
struct unknown00c {
  u8 unknown00;     // Inferred role: parameter type, 9 for a list; original member name unknown.
  u8 unknown01;     // Inferred role: padding; original member name unknown.
  u16 unknown02;    // Inferred role: for a list, the item count; original member name unknown.
  u16 unknown04[1]; // Inferred role: for a list, the indexes of the items in the list item block; original member name unknown.
};

static_assert(sizeof(unknown004) == 0x08, "stride of LMS_GetAttrType 0x71009853cc");
static_assert(offsetof(unknown004, unknown02) == 0x02, "LMS_GetAttrListItemName 0x7100985584");
static_assert(offsetof(unknown004, unknown04) == 0x04, "LMS_GetAttrOffset 0x7100985434");
static_assert(sizeof(unknown007) == 0x10, "stride of LMS_GetRegionWidth 0x71009860fc");
static_assert(offsetof(unknown007, unknown0c) == 0x0c, "LMS_GetBaseColorIndex 0x71009862f8");
static_assert(offsetof(unknown00c, unknown04) == 0x04, "LMS_GetTagListItemName 0x7100985c74");

// Inferred role: payload of the block with the given index, as the type its accessor reads; original name unknown.
template <typename T> const T *unknown00d(const unknown001 *project, s32 index) { return reinterpret_cast<const T *>(project->unknown18[index].unknown00); }

// Inferred role: word of a block; original name unknown. The label search passes it an unsigned index (0x7100985300:
// `ldr w24, [x8, w9, sxtw #2]`, then `add w9, w9, #1` and `sxtw` again), which only a signed parameter gives.
u32 unknown00e(const unknown002 *block, s32 index) { return reinterpret_cast<const u32 *>(block->unknown00)[index]; }

// Inferred role: length of a label; original name unknown.
int unknown00f(const char *name) {
  int length = 0;
  while (name[length] != 0) {
    length++;
  }
  return length;
}

// Inferred role: search of a label in a label block ("CLB1", "ALB1" or "SLB1"); original name unknown. The block
// holds a u32 bucket count, then the buckets (a count and the offset of the entries), each entry being a length byte,
// the label and a u32 index. Returns the index, or -1.
s32 unknown010(const unknown002 *block, const char *name, int length) {
  u32 index = LMSi_GetHashTableIndexFromLabel(name, unknown00e(block, 0)) << 1 | 1;
  u32 count = unknown00e(block, index);
  if (count == 0) {
    return -1;
  }
  u32 offset = unknown00e(block, index + 1);
  for (u32 i = 0; i < count; i++) {
    u8 size = block->unknown00[offset];
    if (size == length) {
      size_t pos = offset;
      pos++;
      if (LMSi_MemCmp(name, block->unknown00 + pos, length)) {
        pos += size;
        return *reinterpret_cast<const s32 *>(block->unknown00 + pos);
      }
    }
    offset += size + 5;
  }
  return -1;
}

// Inferred role: record of the tag group with the given identifier, or nullptr; original name unknown. The offsets
// are sorted by identifier, which ends the search. The loop shape (offsets read from `table + 1`, a counter from 0)
// is the only one of the forms measured (counters of every width, from 0 or 1, `<` or `<=`, with the bound tested
// before or after the identifier) that gives the game's registers and its pre-increment bound test (0x7100985790).
const unknown00a *unknown011(const unknown001 *project, u16 id) {
  if (project->unknown34 == -1) {
    return nullptr;
  }
  const unknown009 *table = unknown00d<unknown009>(project, project->unknown34);
  const u32 *offsets = reinterpret_cast<const u32 *>(table + 1);
  for (size_t i = 0; i < table->unknown00; i++) {
    const unknown00a *group = reinterpret_cast<const unknown00a *>(reinterpret_cast<const char *>(table) + offsets[i]);
    if (group->unknown00 == id) {
      return group;
    }
    if (group->unknown00 > id) {
      return nullptr;
    }
  }
  return nullptr;
}

// Inferred role: record of a tag of a group, or nullptr; original name unknown.
const unknown00b *unknown012(const unknown001 *project, const unknown00a *group, u16 tag) {
  if (group == nullptr) {
    return nullptr;
  }
  if (project->unknown38 == -1) {
    return nullptr;
  }
  if (group->unknown02 <= tag) {
    return nullptr;
  }
  u16 index = group->unknown04[tag];
  const unknown009 *table = unknown00d<unknown009>(project, project->unknown38);
  return reinterpret_cast<const unknown00b *>(reinterpret_cast<const char *>(table) + reinterpret_cast<const u32 *>(table + 1)[index]);
}

// Inferred role: record of a parameter of a tag, or nullptr; original name unknown. The block index is a s64 local
// that is read before the index of the parameter: the game's `asr` of the second half of the 64-bit load of the
// block indexes (0x7100985abc) comes before the address of the parameter index only with it (every s32 form, in
// every order of the statements, gives the two the other way round in the four users).
const unknown00c *unknown013(const unknown001 *project, const unknown00b *tag, u16 param) {
  if (tag == nullptr) {
    return nullptr;
  }
  if (project->unknown3c == -1) {
    return nullptr;
  }
  if (tag->unknown00 <= param) {
    return nullptr;
  }
  s64 block = project->unknown3c;
  u16 index = tag->unknown02[param];
  const unknown009 *table = reinterpret_cast<const unknown009 *>(project->unknown18[block].unknown00);
  return reinterpret_cast<const unknown00c *>(reinterpret_cast<const char *>(table) + reinterpret_cast<const u32 *>(table + 1)[index]);
}

} // namespace

extern "C" {

unknown001 *LMS_InitProject(const char *data) {
  unknown001 *project = static_cast<unknown001 *>(LMSi_Malloc(sizeof(unknown001)));
  project->unknown00 = data;
  LMSi_AnalyzeMessageBinary(project, "MsgPrjBn", 4);
  project->unknown24 = LMSi_SearchBlockByName(project, "CLR1");
  project->unknown20 = LMSi_SearchBlockByName(project, "CLB1");
  project->unknown2c = LMSi_SearchBlockByName(project, "ATI2");
  project->unknown28 = LMSi_SearchBlockByName(project, "ALB1");
  project->unknown30 = LMSi_SearchBlockByName(project, "ALI2");
  project->unknown34 = LMSi_SearchBlockByName(project, "TGG2");
  project->unknown38 = LMSi_SearchBlockByName(project, "TAG2");
  project->unknown3c = LMSi_SearchBlockByName(project, "TGP2");
  project->unknown40 = LMSi_SearchBlockByName(project, "TGL2");
  project->unknown44 = LMSi_SearchBlockByName(project, "SYL3");
  project->unknown48 = LMSi_SearchBlockByName(project, "SLB1");
  project->unknown4c = LMSi_SearchBlockByName(project, "CTI1");
  return project;
}

void LMS_CloseProject(unknown001 *project) {
  if (project->unknown18 != nullptr) {
    LMSi_Free(project->unknown18);
  }
  LMSi_Free(project);
}

int LMS_SearchProjectBlockByName(unknown001 *project, const char *name) { return LMSi_SearchBlockByName(project, name); }

s32 LMS_GetContentsNum(const unknown001 *project) {
  if (project->unknown4c == -1) {
    return -1;
  }
  return unknown00d<unknown006>(project, project->unknown4c)->unknown00;
}

const char *LMS_GetContentPath(const unknown001 *project, s32 index) {
  if (project->unknown4c == -1) {
    return nullptr;
  }
  const unknown006 *table = unknown00d<unknown006>(project, project->unknown4c);
  if (table->unknown00 <= index) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(table) + table->unknown04[index];
}

// The three label lookups differ in when the block of the labels is addressed (0x7100985080, 0x71009852c4,
// 0x7100985fcc): the colour and style ones address it before the length of the label, the attribute one after.
s32 LMS_GetColorIndexByName(const unknown001 *project, const char *name) {
  if (project->unknown20 == -1) {
    return -2;
  }
  return unknown010(&project->unknown18[project->unknown20], name, unknown00f(name));
}

s32 LMS_GetColorNum(const unknown001 *project) {
  if (project->unknown24 == -1) {
    return 0;
  }
  return unknown00d<unknown003>(project, project->unknown24)->unknown00;
}

s32 LMS_GetColor(const unknown001 *project, s32 index, LMSColor *color) {
  if (project->unknown24 == -1) {
    return -5;
  }
  const unknown003 *table = unknown00d<unknown003>(project, project->unknown24);
  if (table->unknown00 <= index) {
    return -1;
  }
  color->unknown00 = table->unknown04[index].unknown00;
  color->unknown01 = table->unknown04[index].unknown01;
  color->unknown02 = table->unknown04[index].unknown02;
  color->unknown03 = table->unknown04[index].unknown03;
  return 0;
}

s32 LMS_GetColorByName(const unknown001 *project, const char *name, LMSColor *color) { return LMS_GetColor(project, LMS_GetColorIndexByName(project, name), color); }

s32 LMS_GetAttrInfoIndexByName(const unknown001 *project, const char *name) {
  if (project->unknown28 == -1) {
    return -2;
  }
  int length = unknown00f(name);
  return unknown010(&project->unknown18[project->unknown28], name, length);
}

// The null test of the address of the entry stays in the game (0x71009853d4): the entries are reached through a
// pointer past the head, which clang cannot prove non-null, while an array member of the head loses the test.
// The four attribute accessors repeat this entry lookup (ruling 8 of docs/decisions.md): a helper returning the entry,
// called by each, is measured and does not match, because SimplifyCFG then folds the index test and the null test into
// one `ccmp` (LMS_GetAttrType 19 instructions against the game's 21, LMS_GetAttrOffset 20 against 23,
// LMS_GetAttrListItemName 44 against 47, LMS_GetAttrListItemNum 32 against 39).
s32 LMS_GetAttrType(const unknown001 *project, s32 index) {
  if (project->unknown2c == -1) {
    return 0xff;
  }
  const unknown005 *table = unknown00d<unknown005>(project, project->unknown2c);
  if (table->unknown00 <= index) {
    return 0xff;
  }
  const unknown004 *info = reinterpret_cast<const unknown004 *>(table + 1) + index;
  if (info == nullptr) {
    return 0xff;
  }
  return info->unknown00;
}

s32 LMS_GetAttrOffset(const unknown001 *project, s32 index) {
  if (project->unknown2c == -1) {
    return -1;
  }
  const unknown005 *table = unknown00d<unknown005>(project, project->unknown2c);
  if (table->unknown00 <= index) {
    return -1;
  }
  const unknown004 *info = reinterpret_cast<const unknown004 *>(table + 1) + index;
  if (info == nullptr) {
    return -1;
  }
  return info->unknown04;
}

// The game narrows the index of the attribute to 16 bits before it reads the entry (`and w9, w0, #0xffff`,
// 0x7100985488), and returns the error code of the label lookup for the offset.
s32 LMS_GetAttrTypeByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetAttrInfoIndexByName(project, name);
  if (index < 0) {
    return 0xff;
  }
  return LMS_GetAttrType(project, static_cast<u16>(index));
}

s32 LMS_GetAttrOffsetByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetAttrInfoIndexByName(project, name);
  if (index < 0) {
    return index;
  }
  return LMS_GetAttrOffset(project, static_cast<u16>(index));
}

const char *LMS_GetAttrListItemName(const unknown001 *project, s32 index, s32 item) {
  if (project->unknown2c == -1) {
    return nullptr;
  }
  const unknown005 *table = unknown00d<unknown005>(project, project->unknown2c);
  if (table->unknown00 <= index) {
    return nullptr;
  }
  const unknown004 *info = reinterpret_cast<const unknown004 *>(table + 1) + index;
  if (info == nullptr) {
    return nullptr;
  }
  if (info->unknown00 != 9) {
    return nullptr;
  }
  if (project->unknown30 == -1) {
    return nullptr;
  }
  const unknown006 *lists = unknown00d<unknown006>(project, project->unknown30);
  const unknown006 *list = reinterpret_cast<const unknown006 *>(reinterpret_cast<const char *>(lists) + lists->unknown04[info->unknown02]);
  if (list->unknown00 <= item) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(list) + list->unknown04[item];
}

const char *LMS_GetAttrListItemNameByName(const unknown001 *project, const char *name, s32 item) {
  s32 index = LMS_GetAttrInfoIndexByName(project, name);
  if (index < 0) {
    return nullptr;
  }
  return LMS_GetAttrListItemName(project, index, item);
}

s32 LMS_GetAttrNum(const unknown001 *project) {
  if (project->unknown2c == -1) {
    return 0;
  }
  return unknown00d<unknown005>(project, project->unknown2c)->unknown00;
}

s32 LMS_GetAttrListItemNum(const unknown001 *project, s32 index) {
  if (project->unknown2c == -1) {
    return 0;
  }
  const unknown005 *table = unknown00d<unknown005>(project, project->unknown2c);
  if (table->unknown00 <= index) {
    return 0;
  }
  const unknown004 *info = reinterpret_cast<const unknown004 *>(table + 1) + index;
  if (info == nullptr) {
    return 0;
  }
  if (info->unknown00 != 9) {
    return 0;
  }
  if (project->unknown30 == -1) {
    return 0;
  }
  const unknown006 *lists = unknown00d<unknown006>(project, project->unknown30);
  const unknown006 *list = reinterpret_cast<const unknown006 *>(reinterpret_cast<const char *>(lists) + lists->unknown04[info->unknown02]);
  return list->unknown00;
}

const char *LMS_GetTagGroupName(const unknown001 *project, u16 group) {
  const unknown00a *info = unknown011(project, group);
  if (info == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(&info->unknown04[info->unknown02]);
}

const char *LMS_GetTagName(const unknown001 *project, u16 group, u16 tag) {
  const unknown00b *info = unknown012(project, unknown011(project, group), tag);
  if (info == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<const char *>(&info->unknown02[info->unknown00]);
}

const char *LMS_GetTagParamName(const unknown001 *project, u16 group, u16 tag, u16 param) {
  const unknown00c *info = unknown013(project, unknown012(project, unknown011(project, group), tag), param);
  if (info == nullptr) {
    return nullptr;
  }
  if (info->unknown00 == 9) {
    return reinterpret_cast<const char *>(&info->unknown04[info->unknown02]);
  }
  return reinterpret_cast<const char *>(info) + 1;
}

s32 LMS_GetTagParamType(const unknown001 *project, u16 group, u16 tag, u16 param) {
  const unknown00c *info = unknown013(project, unknown012(project, unknown011(project, group), tag), param);
  if (info == nullptr) {
    return 0xff;
  }
  if (info->unknown00 > 9) {
    return 0xff;
  }
  return info->unknown00;
}

const char *LMS_GetTagListItemName(const unknown001 *project, u16 group, u16 tag, u16 param, u16 item) {
  const unknown00c *info = unknown013(project, unknown012(project, unknown011(project, group), tag), param);
  if (info == nullptr) {
    return nullptr;
  }
  if (project->unknown40 == -1) {
    return nullptr;
  }
  if (info->unknown00 != 9) {
    return nullptr;
  }
  if (info->unknown02 <= item) {
    return nullptr;
  }
  u16 index = info->unknown04[item];
  const unknown009 *table = unknown00d<unknown009>(project, project->unknown40);
  return reinterpret_cast<const char *>(table) + reinterpret_cast<const u32 *>(table + 1)[index];
}

s32 LMS_GetTagGroupNum(const unknown001 *project) {
  if (project->unknown34 == -1) {
    return 0;
  }
  return unknown00d<unknown009>(project, project->unknown34)->unknown00;
}

u16 LMS_GetTagNum(const unknown001 *project, u16 group) {
  const unknown00a *info = unknown011(project, group);
  if (info == nullptr) {
    return 0;
  }
  return info->unknown02;
}

u16 LMS_GetTagParamNum(const unknown001 *project, u16 group, u16 tag) {
  const unknown00b *info = unknown012(project, unknown011(project, group), tag);
  if (info == nullptr) {
    return 0;
  }
  return info->unknown00;
}

s32 LMS_GetTagListItemNum(const unknown001 *project, u16 group, u16 tag, u16 param) {
  const unknown00c *info = unknown013(project, unknown012(project, unknown011(project, group), tag), param);
  if (info == nullptr) {
    return 0;
  }
  if (info->unknown00 != 9) {
    return 0;
  }
  return info->unknown02;
}

s32 LMS_GetStyleIndexByName(const unknown001 *project, const char *name) {
  if (project->unknown48 == -1) {
    return -9;
  }
  return unknown010(&project->unknown18[project->unknown48], name, unknown00f(name));
}

s32 LMS_GetStyleNum(const unknown001 *project) {
  if (project->unknown44 == -1) {
    return 0;
  }
  return unknown00d<unknown008>(project, project->unknown44)->unknown00;
}

// The style accessors compare the index with the count unsigned (0x71009860f0) and return -1 for an index out of
// range; the ...ByName ones return the error code of the label lookup when it is negative.
u32 LMS_GetRegionWidth(const unknown001 *project, s32 index) {
  if (project->unknown44 == -1) {
    return -1;
  }
  const unknown008 *table = unknown00d<unknown008>(project, project->unknown44);
  if (index >= table->unknown00) {
    return -1;
  }
  return reinterpret_cast<const unknown007 *>(table + 1)[index].unknown00;
}

u32 LMS_GetRegionWidthByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetStyleIndexByName(project, name);
  if (index < 0) {
    return index;
  }
  return LMS_GetRegionWidth(project, index);
}

u32 LMS_GetLineNum(const unknown001 *project, s32 index) {
  if (project->unknown44 == -1) {
    return -1;
  }
  const unknown008 *table = unknown00d<unknown008>(project, project->unknown44);
  if (index >= table->unknown00) {
    return -1;
  }
  return reinterpret_cast<const unknown007 *>(table + 1)[index].unknown04;
}

u32 LMS_GetLineNumByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetStyleIndexByName(project, name);
  if (index < 0) {
    return index;
  }
  return LMS_GetLineNum(project, index);
}

// A font or base colour that the style does not set (-1) gives -12.
s32 LMS_GetFontIndex(const unknown001 *project, s32 index) {
  if (project->unknown44 == -1) {
    return -1;
  }
  const unknown008 *table = unknown00d<unknown008>(project, project->unknown44);
  if (index >= table->unknown00) {
    return -1;
  }
  s32 font = reinterpret_cast<const unknown007 *>(table + 1)[index].unknown08;
  if (font == -1) {
    return -12;
  }
  return font;
}

s32 LMS_GetFontIndexByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetStyleIndexByName(project, name);
  if (index < 0) {
    return index;
  }
  return LMS_GetFontIndex(project, index);
}

s32 LMS_GetBaseColorIndex(const unknown001 *project, s32 index) {
  if (project->unknown44 == -1) {
    return -1;
  }
  const unknown008 *table = unknown00d<unknown008>(project, project->unknown44);
  if (index >= table->unknown00) {
    return -1;
  }
  s32 color = reinterpret_cast<const unknown007 *>(table + 1)[index].unknown0c;
  if (color == -1) {
    return -12;
  }
  return color;
}

s32 LMS_GetBaseColorIndexByName(const unknown001 *project, const char *name) {
  s32 index = LMS_GetStyleIndexByName(project, name);
  if (index < 0) {
    return index;
  }
  return LMS_GetBaseColorIndex(project, index);
}
}
