#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace event {

class SeqInfo {
public:
  SeqInfo();
  void clear();
  SeqInfo(const char *name);
  void setup(const char *name);
  SeqInfo(int id);
  void setup(int id);
  void setup(const CBdatWrapper &bdat, const char *name, int id);
  bool exist() const;

  bool unknown00;                // Inferred role: exist; original member name unknown.
  mm::mtl::FixStr<64> unknown04; // Inferred role: name; original member name unknown.
  int unknown48;                 // Inferred role: id; original member name unknown.
  u32 unknown4c;                 // Inferred role: chg st id; original member name unknown.
  u32 unknown50;                 // Inferred role: chg ed id; original member name unknown.
  u32 unknown54;                 // Inferred role: category; original member name unknown.
  const char *unknown58;         // Inferred role: mstxt; original member name unknown.
  bool unknown60;                // Inferred role: text; original member name unknown.
  u32 unknown64;                 // Inferred role: weather; original member name unknown.
  const char *unknown68;         // Inferred role: clock; original member name unknown.
  bool unknown70;                // Inferred role: clock stop; original member name unknown.
  u32 unknown74;                 // Inferred role: cloud; original member name unknown.
  bool unknown78;                // Inferred role: op fade out enable; original member name unknown.
  u32 unknown7c;                 // Inferred role: op fade out; original member name unknown.
  u32 unknown80;                 // Inferred role: op fade wait; original member name unknown.
  bool unknown84;                // Inferred role: op fade in enable; original member name unknown.
  u32 unknown88;                 // Inferred role: op fade in; original member name unknown.
  u32 unknown8c;                 // Inferred role: op fade col r; original member name unknown.
  u32 unknown90;                 // Inferred role: op fade col g; original member name unknown.
  u32 unknown94;                 // Inferred role: op fade col b; original member name unknown.
  bool unknown98;                // Inferred role: ed fade out enable; original member name unknown.
  u32 unknown9c;                 // Inferred role: ed fade out; original member name unknown.
  u32 unknowna0;                 // Inferred role: ed fade wait; original member name unknown.
  bool unknowna4;                // Inferred role: ed fade in enable; original member name unknown.
  u32 unknowna8;                 // Inferred role: ed fade in; original member name unknown.
  u32 unknownac;                 // Inferred role: ed fade col r; original member name unknown.
  u32 unknownb0;                 // Inferred role: ed fade col g; original member name unknown.
  u32 unknownb4;                 // Inferred role: ed fade col b; original member name unknown.
  u32 unknownb8;                 // Inferred role: st form id; original member name unknown.
  u32 unknownbc;                 // Inferred role: ed form id; original member name unknown.
  bool unknownc0;                // Inferred role: op bgm; original member name unknown.
  bool unknownc1;                // Inferred role: ed bgm; original member name unknown.
  bool unknownc2;                // Inferred role: hide npc; original member name unknown.
  bool unknownc3;                // Inferred role: hide ene; original member name unknown.
  bool unknownc4;                // Inferred role: hide mob; original member name unknown.
  bool unknownc5;                // Inferred role: hide map; original member name unknown.
  u32 unknownc8;                 // Inferred role: outsider opt; original member name unknown.
  bool unknowncc;                // Inferred role: outsider enable; original member name unknown.
  u32 unknownd0;                 // Inferred role: outsider type; original member name unknown.
  f32 unknownd4;                 // Inferred role: outsider x; original member name unknown.
  f32 unknownd8;                 // Inferred role: outsider y; original member name unknown.
  f32 unknowndc;                 // Inferred role: outsider z; original member name unknown.
  f32 unknowne0;                 // Inferred role: outsider r; original member name unknown.
  u32 unknowne4;                 // Inferred role: next id; original member name unknown.
  int unknowne8;                 // Inferred role: link id; original member name unknown.
  u32 unknownec;                 // Inferred role: next i dtheater; original member name unknown.
  bool unknownf0;                // Inferred role: jiji disp; original member name unknown.
  u32 unknownf4;                 // Inferred role: wpn disp; original member name unknown.
  u32 unknownf8;                 // Inferred role: col filter near; original member name unknown.
  u32 unknownfc;                 // Inferred role: col filter far; original member name unknown.
  u32 unknown100;                // Inferred role: env seam; original member name unknown.
  const char *unknown108;        // Inferred role: evt light; original member name unknown.
  u32 unknown110;                // Inferred role: hood; original member name unknown.
  bool unknown114;               // Inferred role: voice; original member name unknown.
  bool unknown115;               // Inferred role: cssnd; original member name unknown.
  u32 unknown118;                // Inferred role: center id; original member name unknown.
  f32 unknown11c;                // Inferred role: center x; original member name unknown.
  f32 unknown120;                // Inferred role: center y; original member name unknown.
  f32 unknown124;                // Inferred role: center z; original member name unknown.
  f32 unknown128;                // Inferred role: center r; original member name unknown.
  u32 unknown12c;                // Inferred role: center form; original member name unknown.
};

static_assert(sizeof(SeqInfo) == 0x130, "");

} // namespace event
