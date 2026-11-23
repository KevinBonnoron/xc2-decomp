#include "mm_math/mm_cube.h"

#include "mm_math/mm_line2.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace mm {

f32 Cube::m_fHalfLength = 0.5f;

// Inferred role: vertices of the unit cube; original name unknown.
static const Vec3 unknown006[8] = {
    Vec3(0.5f, 0.5f, 0.5f),
    Vec3(-0.5f, 0.5f, 0.5f),
    Vec3(-0.5f, 0.5f, -0.5f),
    Vec3(0.5f, 0.5f, -0.5f),
    Vec3(0.5f, -0.5f, 0.5f),
    Vec3(-0.5f, -0.5f, 0.5f),
    Vec3(-0.5f, -0.5f, -0.5f),
    Vec3(0.5f, -0.5f, -0.5f),
};

// Inferred role: planes of the unit cube; original name unknown.
static const Plane unknown007[6] = {
    Plane(Vec3(0.0f, 1.0f, 0.0f), 0.5f),
    Plane(Vec3(0.0f, -1.0f, 0.0f), 0.5f),
    Plane(Vec3(1.0f, 0.0f, 0.0f), 0.5f),
    Plane(Vec3(-1.0f, 0.0f, 0.0f), 0.5f),
    Plane(Vec3(0.0f, 0.0f, -1.0f), 0.5f),
    Plane(Vec3(0.0f, 0.0f, 1.0f), 0.5f),
};

// Inferred role: edges of the unit cube; original name unknown.
static const Line2 unknown008[12] = {
    {Vec3(1.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f), Vec3(-0.5f, 0.5f, 0.5f)},
    {Vec3(0.0f, 0.0f, 1.0f), Vec3(-0.5f, 0.5f, 0.5f), Vec3(-0.5f, 0.5f, -0.5f)},
    {Vec3(-1.0f, 0.0f, 0.0f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(0.5f, 0.5f, -0.5f)},
    {Vec3(0.0f, 0.0f, -1.0f), Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, 0.5f, 0.5f)},
    {Vec3(1.0f, 0.0f, 0.0f), Vec3(0.5f, -0.5f, 0.5f), Vec3(-0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 0.0f, 1.0f), Vec3(-0.5f, -0.5f, 0.5f), Vec3(-0.5f, -0.5f, -0.5f)},
    {Vec3(-1.0f, 0.0f, 0.0f), Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f)},
    {Vec3(0.0f, 0.0f, -1.0f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f), Vec3(0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(-0.5f, 0.5f, 0.5f), Vec3(-0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(-0.5f, -0.5f, -0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f)},
};

f32 Cube::getHalfLength() { return m_fHalfLength; }

const Vec3 *Cube::getBaseVertices() { return unknown006; }

const Plane *Cube::getBasePlanes() { return unknown007; }

const Line2 *Cube::getBaseLines() { return unknown008; }

void Cube::getOBB(Obb &obb) const {
  Mat44 matrix;
  unknown001(matrix);
  f32 halfLength = m_fHalfLength;
  Vec3 size;
  size.x = halfLength * scale.x;
  size.y = halfLength * scale.y;
  size.z = halfLength * scale.z;
  obb.setMat(matrix, size);
}

void Cube::getVertices(mtl::FixedArray<Vec3, 8> &vertices) const {
  Mat44 matrix;
  getMat(matrix);
  for (u32 i = 0; i < 8; i++) {
    const Vec3 &base = unknown006[i];
    // The three sums are computed in the order x, y, z (0x71009adbc4..0x71009adc18) and stored as z, y, x (stp y, z at 0x71009adc1c, then x at 0x71009adc20): the first store, z, puts the
    // induction pointer on the z element (add x9, x19, #8 at 0x71009adba8); stored in the order x, y, z (or built as a Vec3) it sits on x or y and the pair is x, y.
    f32 x = base.x * matrix.rows[0][0] + base.y * matrix.rows[1][0] + base.z * matrix.rows[2][0] + matrix.rows[3][0];
    f32 y = base.x * matrix.rows[0][1] + base.y * matrix.rows[1][1] + base.z * matrix.rows[2][1] + matrix.rows[3][1];
    f32 z = base.x * matrix.rows[0][2] + base.y * matrix.rows[1][2] + base.z * matrix.rows[2][2] + matrix.rows[3][2];
    vertices[i].z = z;
    vertices[i].y = y;
    vertices[i].x = x;
  }
}

bool Cube::isCollide(const PrimBase &prim) const {
  switch (prim.type) {
  case PRIM_CUBE:
    return isCollideCube(prim);
  case PRIM_SPHERE:
    return isCollideSphere(prim);
  case PRIM_CYLINDER:
    return prim.isCollide(*this);
  }
  return false;
}

} // namespace mm
