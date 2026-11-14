#include "font/write_char.h"

#include "font/font_sys.h"
#include "types.h"

WriteChar::WriteChar() : m_font(nullptr) {
  m_alpha = 255;
  m_gradation_mode = GRADATION_MODE_UNKNOWN_0;
  m_scale_h = 1.0f;
  m_scale_v = 1.0f;
  m_enable_fixed_width = false;
  m_fixed_width = 0.0f;
  m_pos_x = 0.0f;
  m_pos_y = 0.0f;
  m_pos_z = 0.0f;
}

WriteChar::~WriteChar() {}

void WriteChar::set_font(FontSys *font) {
  m_font = font;
  if (font != nullptr) {
    m_fixed_width = font->get_origin_width();
  }
}

FontSys *WriteChar::get_font() const { return m_font; }

float WriteChar::get_origin_width() const { return m_font->get_origin_width(); }

float WriteChar::get_origin_height() const { return m_font->get_origin_height(); }

float WriteChar::get_origin_size() const { return m_font->get_font_size(); }

void WriteChar::set_alpha(u8 alpha) { m_alpha = alpha; }

u8 WriteChar::get_alpha() const { return m_alpha; }

void WriteChar::set_gradation_mode(GradationMode mode) { m_gradation_mode = mode; }

WriteChar::GradationMode WriteChar::get_gradation_mode(GradationMode mode) const { return m_gradation_mode; }

void WriteChar::set_color(Color color) { m_gradation_start_color = m_gradation_end_color = color; }

void WriteChar::set_color(Color start, Color end) {
  m_gradation_start_color = start;
  m_gradation_end_color = end;
}

Color WriteChar::get_color() const { return m_gradation_start_color; }

Color WriteChar::get_gradation_start_color() const { return m_gradation_start_color; }

Color WriteChar::get_gradation_end_color() const { return m_gradation_end_color; }

void WriteChar::set_scale(float scale) { m_scale_h = m_scale_v = scale; }

void WriteChar::set_scale(float horizontal, float vertical) {
  m_scale_h = horizontal;
  m_scale_v = vertical;
}

float WriteChar::get_scale_h() const { return m_scale_h; }

float WriteChar::get_scale_v() const { return m_scale_v; }

float WriteChar::get_font_width() const { return m_font->get_origin_width() * m_scale_h; }

float WriteChar::get_font_height() const { return m_font->get_origin_height() * m_scale_v; }

void WriteChar::enable_fixed_width(bool enable) { m_enable_fixed_width = enable; }

bool WriteChar::is_fixed_width() const { return m_enable_fixed_width; }

void WriteChar::set_fixed_width(float width) { m_fixed_width = width; }

float WriteChar::get_fixed_width() const { return m_fixed_width; }

void WriteChar::set_pos(float x, float y) {
  m_pos_x = x;
  m_pos_y = y;
  m_pos_z = 0.0f;
}

void WriteChar::set_pos(float x, float y, float z) {
  m_pos_x = x;
  m_pos_y = y;
  m_pos_z = z;
}

void WriteChar::set_pos_x(float x) { m_pos_x = x; }

void WriteChar::set_pos_y(float y) { m_pos_y = y; }

void WriteChar::set_pos_z(float z) { m_pos_z = z; }

void WriteChar::set_move(float x, float y) {
  m_pos_x += x;
  m_pos_y += y;
}

void WriteChar::set_move(float x, float y, float z) {
  m_pos_x += x;
  m_pos_y += y;
  m_pos_z += z;
}

void WriteChar::set_move_x(float x) { m_pos_x += x; }

void WriteChar::set_move_y(float y) { m_pos_y += y; }

void WriteChar::set_move_z(float z) { m_pos_z += z; }

float WriteChar::get_pos_x() const { return m_pos_x; }

float WriteChar::get_pos_y() const { return m_pos_y; }

float WriteChar::get_pos_z() const { return m_pos_z; }
