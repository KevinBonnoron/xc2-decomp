#include "mm_math/mm_cube.h"

#include "mm_math/mm_line2.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"

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
