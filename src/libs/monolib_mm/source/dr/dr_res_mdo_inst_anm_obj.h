#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoPos;
struct MdsPosKeepData;

struct MdsInstObjPosData {
  enum Flag {
    FLAG_UNKNOWN_0 = 0x1,   // Inferred role: loop; original name unknown.
    FLAG_UNKNOWN_3 = 0x8,   // Inferred role: node anm; original name unknown.
    FLAG_UNKNOWN_4 = 0x10,  // Inferred role: pos anm; original name unknown.
    FLAG_UNKNOWN_5 = 0x20,  // Inferred role: pos matrix; original name unknown.
    FLAG_UNKNOWN_7 = 0x80,  // Inferred role: switch; original name unknown.
    FLAG_UNKNOWN_9 = 0x200, // Inferred role: disp off; original name unknown.
  };

  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u32 unknown04; // Inferred role: position index; original member name unknown.
  u16 unknown08; // Inferred role: id; original member name unknown.
  union {
    u16 flags;
    struct {
      u8 isLoop : 1;
      u8 isRandomStart : 1;
      u8 : 1;
      u8 isNodeAnm : 1;
      u8 isPosAnm : 1;
      u8 isPosMatrix : 1;
      u8 : 1;
      u8 isSwitch : 1;
    };
  };
  u8 unknown0c; // Inferred role: start rate; original member name unknown.
  u8 unknown0d; // Inferred role: frame scale; original member name unknown.
};

static_assert(offsetof(MdsInstObjPosData, unknown04) == 0x04, "");
static_assert(offsetof(MdsInstObjPosData, unknown08) == 0x08, "");
static_assert(offsetof(MdsInstObjPosData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsInstObjPosData, unknown0d) == 0x0d, "");

struct MdsInstAnmParamInfo {
  u32 unknown00; // Inferred role: key offset; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06; // Inferred role: key count; original member name unknown.
  u16 unknown08; // Inferred role: start frame; original member name unknown.
  u16 unknown0a; // Inferred role: end frame; original member name unknown.
};

static_assert(offsetof(MdsInstAnmParamInfo, unknown06) == 0x06, "");
static_assert(offsetof(MdsInstAnmParamInfo, unknown08) == 0x08, "");
static_assert(offsetof(MdsInstAnmParamInfo, unknown0a) == 0x0a, "");

struct MdsInstAnmInf {
  u32 unknown00; // Inferred role: key offset; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06; // Inferred role: key count; original member name unknown.
  u16 unknown08; // Inferred role: start frame; original member name unknown.
  u16 unknown0a; // Inferred role: end frame; original member name unknown.
};

static_assert(offsetof(MdsInstAnmInf, unknown06) == 0x06, "");
static_assert(offsetof(MdsInstAnmInf, unknown08) == 0x08, "");
static_assert(offsetof(MdsInstAnmInf, unknown0a) == 0x0a, "");

// Inferred role: instance animation hermite key; original type name unknown.
struct unknown095 {
  f32 unknown00; // Inferred role: out slope; original member name unknown.
  f32 unknown04; // Inferred role: in slope; original member name unknown.
  f32 unknown08; // Inferred role: value; original member name unknown.
  u16 unknown0c; // Inferred role: frame; original member name unknown.
  u8 _0e;
  u8 unknown0f; // Inferred role: flags, bit 0 is a step key; original member name unknown.
};

static_assert(offsetof(unknown095, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown095, unknown0f) == 0x0f, "");
static_assert(sizeof(unknown095) == 0x10, "");

struct MdsInstAnmNodeData {
  u8 _00[0x02 - 0x00];
  u16 unknown02; // Inferred role: frame max; original member name unknown.
  u32 unknown04; // Inferred role: coli param offset; original member name unknown.
};

static_assert(offsetof(MdsInstAnmNodeData, unknown02) == 0x02, "");
static_assert(offsetof(MdsInstAnmNodeData, unknown04) == 0x04, "");

// Inferred role: model data inst anm switch; original type name unknown.
struct unknown044 {
  enum Flag {
    FLAG_UNKNOWN_0 = 0x1, // Inferred role: frame; original name unknown.
    FLAG_UNKNOWN_1 = 0x2, // Inferred role: loop; original name unknown.
  };

  u16 unknown00;        // Inferred role: flags; original member name unknown.
  u8 unknown02;         // Inferred role: id; original member name unknown.
  u16 unknown04_0 : 16; // Inferred role: start frame; original member name unknown.
  u16 unknown06_0 : 16; // Inferred role: end frame; original member name unknown.
  u8 _08[0x24 - 0x08];
};

static_assert(offsetof(unknown044, unknown02) == 0x02, "");

static_assert(sizeof(unknown044) == 0x24, "");

// Inferred type: instance animation object header; the original type name is unknown.
struct MdsInstAnmObj {
  u8 _00[0x3e];
  u16 unknown3e;
};

static_assert(offsetof(MdsInstAnmObj, unknown3e) == 0x3e, "");

class DrResMdoPosInstAnm {
public:
  DrResMdoPosInstAnm(const MdsInstAnmObj *anm, const u8 *data, const MdsPosKeepData *keep);
  void setup(f32 frame);
  void getAnmMatrix(mm::Mat44 *matrix, f32 frame) const;
  f32 getHermiteAttr(const MdsInstAnmInf *inf, f32 frame) const;
  void update();
  void setMatrix(const mm::Mat44 &matrix);
  void getMatrix(mm::Mat44 &matrix) const;
  void setAnmFrame(u16 startFrame, u16 maxFrame);
  static void anmInsPosParm_TranX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_TranY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_TranZ(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotZ(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclZ(mm::Vec3 *transform, f32 value);

  const MdsInstAnmObj *unknown00;  // Inferred role: instance animation; original member name unknown.
  const u8 *unknown08;             // Inferred role: animation data; original member name unknown.
  const MdsPosKeepData *unknown10; // Inferred role: position keep data; original member name unknown.
  u8 _018[0x020 - 0x018];
  mm::Mat44 unknown20; // Inferred role: matrix; original member name unknown.
  u8 _060[0x090 - 0x060];
  mm::Mat44 unknown90[2]; // Inferred role: dbl matrices; original member name unknown.
  mm::Mat44 unknown110;   // Inferred role: animation matrix; original member name unknown.
  u16 unknown150;         // Inferred role: dbl flags; original member name unknown.
  u16 unknown152;         // Inferred role: max frame; original member name unknown.
  u16 unknown154;         // Inferred role: start frame; original member name unknown.
};

static_assert(offsetof(DrResMdoPosInstAnm, unknown00) == 0x00, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown20) == 0x020, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown90) == 0x090, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown152) == 0x152, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown154) == 0x154, "");

class DrResMdoInstPartsObj {
public:
  enum Flag {
    FLAG_UNKNOWN_2 = 0x4, // Inferred role: loop; original name unknown.
  };

  DrResMdoInstPartsObj(const u8 *data, const MdsInstObjPosData *info);
  void setDisp(bool disp);
  bool isDisp() const;
  f32 getSimpleParamAttr(const MdsInstAnmParamInfo *param, f32 frame) const;

  virtual ~DrResMdoInstPartsObj() {}
  virtual void setPosFrame(f32 frame) {}
  virtual f32 getPosFrame() const { return 0.0f; }
  virtual f32 getPosMaxFrame() const { return 0.0f; }
  virtual f32 getPosStartFrame() const { return 0.0f; }
  virtual void setNodeFrame(f32 frame) {}
  virtual f32 getNodeFrame() const { return 0.0f; }
  virtual f32 getCalcNodeFrame() const { return 0.0f; }
  virtual f32 getCalcOldNodeFrame() const { return 0.0f; }
  virtual f32 getNodeMaxFrame() const { return 0.0f; }
  virtual f32 getNodeStartFrame() const { return 0.0f; }
  virtual u32 getSwitchID() const { return 0; }
  virtual void setSwitchID(u8 id) {}
  virtual u32 getSwitchMax() const { return 0; }
  virtual u32 getSwitchIndex(u32 index) const { return 1; }
  virtual void update() {}
  virtual void getMatrix(mm::Mat44 &matrix) const;
  virtual void getAnmMatrix(mm::Mat44 &matrix) const { getMatrix(matrix); }
  virtual void setMatrix(const mm::Mat44 &matrix) {}

  union Flags {
    u32 unknown00; // Inferred role: all; original member name unknown.
    struct {
      u32 : 2;
      bool isLoop : 1;
      bool isColiOff : 1;
      bool isColiSkipData : 1;
      u32 : 27;
    };
  };

  Flags unknown08;                    // Inferred role: flags; original member name unknown.
  const char *unknown10;              // Inferred role: names; original member name unknown.
  const MdsInstObjPosData *unknown18; // Inferred role: info; original member name unknown.
  const mm::Mat44 *unknown20;         // Inferred role: matrix; original member name unknown.
  f32 unknown28;                      // Inferred role: alpha; original member name unknown.
};

static_assert(offsetof(DrResMdoInstPartsObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown28) == 0x28, "");

class DrResMdoInstPartsAnm : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsAnm(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsAnm() override;
  void setPosFrame(f32 frame) override { m_posFrame = frame; }
  f32 getPosFrame() const override { return m_posFrame; }
  f32 getPosMaxFrame() const override {
    if (unknown30 == nullptr) {
      return 0.0f;
    }
    return unknown30->unknown152 * unknown54;
  }
  f32 getPosStartFrame() const override {
    if (unknown30 == nullptr || unknown18->unknown0c == 0) {
      return 0.0f;
    }
    return unknown18->unknown0c * (1.0f / 255.0f) * unknown30->unknown152;
  }
  void setNodeFrame(f32 frame) override;
  f32 getNodeFrame() const override;
  f32 getCalcNodeFrame() const override { return unknown5c + unknown44 * unknown58; }
  f32 getCalcOldNodeFrame() const override { return unknown5c + unknown48 * unknown58; }
  f32 getNodeMaxFrame() const override { return unknown5e * unknown54; }
  f32 getNodeStartFrame() const override {
    if (unknown5e == 0 || unknown18->unknown0c == 0) {
      return 0.0f;
    }
    return unknown18->unknown0c * (1.0f / 255.0f) * unknown5e;
  }
  u32 getSwitchID() const override { return m_switchID; }
  void setSwitchID(u8 id) override;
  void updateSwitch();
  u32 getSwitchMax() const override { return m_switchMax; }
  u32 getSwitchIndex(u32 index) const override;
  void update() override;
  void getMatrix(mm::Mat44 &matrix) const override;
  void getAnmMatrix(mm::Mat44 &matrix) const override;
  void setMatrix(const mm::Mat44 &matrix) override;
  void setNodeAnmData(const MdsInstAnmNodeData *data);
  void setPosAnmData(DrResMdoPosInstAnm *posAnm, DrResMdoPos *pos);

  DrResMdoPosInstAnm *unknown30; // Inferred role: pos anm; original member name unknown.
  DrResMdoPos *unknown38;        // Inferred role: pos; original member name unknown.
  f32 m_posFrame;
  f32 unknown44;                        // Inferred role: node frame; original member name unknown.
  f32 unknown48;                        // Inferred role: old node frame; original member name unknown.
  f32 unknown4c[2];                     // Inferred role: dbl node frames; original member name unknown.
  f32 unknown54;                        // Inferred role: frame scale; original member name unknown.
  f32 unknown58;                        // Inferred role: inv frame scale; original member name unknown.
  u16 unknown5c;                        // Inferred role: node start; original member name unknown.
  u16 unknown5e;                        // Inferred role: node max; original member name unknown.
  const MdsInstAnmParamInfo *unknown60; // Inferred role: coli param; original member name unknown.
  const unknown044 *unknown68;          // Inferred role: switches; original member name unknown.
  u8 m_switchID;
  u8 m_switchMax;
};

static_assert(offsetof(DrResMdoInstPartsAnm, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_posFrame) == 0x40, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown4c) == 0x4c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown54) == 0x54, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown5c) == 0x5c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown60) == 0x60, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchID) == 0x70, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchMax) == 0x71, "");
static_assert(sizeof(DrResMdoInstPartsAnm) == 0x78, "");

class DrResMdoInstPartsGlbID : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsGlbID(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsGlbID() override;
};

// Inferred role: resource mdo inst anm header; original type name unknown.
struct unknown045 {
  u8 _00[0x04 - 0x00];
  u32 unknown04; // Inferred role: object max; original member name unknown.
  s32 unknown08; // Inferred role: anm max; original member name unknown.
  u8 _0c[0x18 - 0x0c];
  s32 unknown18; // Inferred role: pos anm max; original member name unknown.
  s32 unknown1c; // Inferred role: pos anm object count; original member name unknown.
  u8 _20[0x28 - 0x20];
  s32 unknown28; // Inferred role: switch max; original member name unknown.
  u8 _2c[0x34 - 0x2c];
  s32 unknown34; // Inferred role: node anm max; original member name unknown.
};

static_assert(offsetof(unknown045, unknown04) == 0x04, "");
static_assert(offsetof(unknown045, unknown08) == 0x08, "");
static_assert(offsetof(unknown045, unknown18) == 0x18, "");
static_assert(offsetof(unknown045, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown045, unknown28) == 0x28, "");
static_assert(offsetof(unknown045, unknown34) == 0x34, "");

class DrResMdoInstAnmObj {
public:
  DrResMdoInstAnmObj();
  ~DrResMdoInstAnmObj() { release(); }
  static int getWorkSize(const u8 *data);
  void release();
  void update();
  void setupLink(DrResMdoPos *pos) const;
  void setupLink(DrResMdoPos *pos, int posStart, int posCount, int switchStart, int switchCount) const;
  int getObjIdx(const char *name);
  void getUniformOldMat(f32 *work, const DrResMdoPos *pos, const mm::Mat44 &matrix);

  DrResMdoInstPartsObj *getObj(u32 index) const {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    return unknown08[index];
  }

  const unknown045 *unknown00;      // Inferred role: header; original member name unknown.
  DrResMdoInstPartsObj **unknown08; // Inferred role: objs; original member name unknown.
  DrResMdoInstPartsAnm *unknown10;  // Inferred role: anm objs; original member name unknown.
  void *unknown18;                  // Inferred role: data; original member name unknown.
  void *unknown20;                  // Inferred role: data; original member name unknown.
  DrResMdoPosInstAnm *unknown28;    // Inferred role: pos anm objs; original member name unknown.
};

static_assert(offsetof(DrResMdoInstAnmObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstAnmObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstAnmObj, unknown28) == 0x28, "");
static_assert(sizeof(DrResMdoInstAnmObj) == 0x30, "");

} // namespace ml
