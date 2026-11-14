#pragma once
#include <stddef.h>

#include "font/color.h"
#include "types.h"

class FontSys;

namespace ml {
class DebDraw;
} // namespace ml

// Layout evidence: WriteChar::WriteChar 0x710078f330 and the accessors 0x710078f3a8..0x710078fc08.
class WriteChar {
public:
  enum GradationMode {
    GRADATION_MODE_UNKNOWN_0 = 0,
    GRADATION_MODE_UNKNOWN_1 = 1,
    GRADATION_MODE_UNKNOWN_2 = 2,
  };

  WriteChar();
  ~WriteChar();
  void set_font(FontSys *font);
  FontSys *get_font() const;
  float get_origin_width() const;
  float get_origin_height() const;
  float get_origin_size() const;
  void print(u16 code, bool draw, ml::DebDraw *debDraw);
  void set_alpha(u8 alpha);
  u8 get_alpha() const;
  void set_gradation_mode(GradationMode mode);
  GradationMode get_gradation_mode(GradationMode mode) const;
  void set_color(Color color);
  void set_color(Color start, Color end);
  Color get_color() const;
  Color get_gradation_start_color() const;
  Color get_gradation_end_color() const;
  void set_scale(float scale);
  void set_scale(float horizontal, float vertical);
  float get_scale_h() const;
  float get_scale_v() const;
  float get_font_width() const;
  float get_font_height() const;
  void enable_fixed_width(bool enable);
  bool is_fixed_width() const;
  void set_fixed_width(float width);
  float get_fixed_width() const;
  void set_pos(float x, float y);
  void set_pos(float x, float y, float z);
  void set_pos_x(float x);
  void set_pos_y(float y);
  void set_pos_z(float z);
  void set_move(float x, float y);
  void set_move(float x, float y, float z);
  void set_move_x(float x);
  void set_move_y(float y);
  void set_move_z(float z);
  float get_pos_x() const;
  float get_pos_y() const;
  float get_pos_z() const;

private:
  FontSys *m_font;
  Color m_gradation_start_color;
  Color m_gradation_end_color;
  u8 m_alpha;
  GradationMode m_gradation_mode;
  float m_scale_h;
  float m_scale_v;
  bool m_enable_fixed_width;
  float m_fixed_width;
  float m_pos_x;
  float m_pos_y;
  float m_pos_z;

  friend struct WriteCharLayout;
};

struct WriteCharLayout {
  static_assert(offsetof(WriteChar, m_gradation_start_color) == 0x08, "");
  static_assert(offsetof(WriteChar, m_gradation_end_color) == 0x0c, "");
  static_assert(offsetof(WriteChar, m_alpha) == 0x10, "");
  static_assert(offsetof(WriteChar, m_gradation_mode) == 0x14, "");
  static_assert(offsetof(WriteChar, m_scale_h) == 0x18, "");
  static_assert(offsetof(WriteChar, m_scale_v) == 0x1c, "");
  static_assert(offsetof(WriteChar, m_enable_fixed_width) == 0x20, "");
  static_assert(offsetof(WriteChar, m_fixed_width) == 0x24, "");
  static_assert(offsetof(WriteChar, m_pos_x) == 0x28, "");
  static_assert(offsetof(WriteChar, m_pos_z) == 0x30, "");
  static_assert(sizeof(WriteChar) == 0x38, "");
};
