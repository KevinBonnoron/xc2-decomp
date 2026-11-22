#include "ml/cache_draw.h"

#include <new>
#include <string.h>

#include "ml/critical_section.h"
#include "ml/win_view.h"
#include "ml/work_cpu.h"
#include "mm_math/mm_cube.h"
#include "mm_math/mm_cylinder.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_sphere.h"
#include "mtl/mem_manager.h"

namespace ml {

CacheDraw::CacheDraw(mtl::ALLOC_HANDLE handle, size_t size)
    : m_ALLOC_HANDLE(handle), m_currentPrio(-1), m_cacheDrawWID(0xffffffff), unknown6054(1.0f), unknown6058(1.0f), m_forceRenderQueue(false), m_suspendSwap(0), unknown6070(true) {
  m_criticalSectionNC = new (handle) CriticalSectionNC();
  m_criticalSectionNC->setCostIgnore(true);
  for (int i = 0; i < 2; i++) {
    unknown08[i].unknown10 = size / 2;
    unknown08[i].unknown00 = static_cast<u8 *>(mtl::MemManager::allocate(handle, size / 2, 0x10, false, "no name", 0));
    unknown08[i].unknown08 = unknown08[i].unknown00;
  }
  clearSystem(true);
  clearSystem(false);
}

void CacheDraw::clearSystem(bool isOdd) {
  if (m_suspendSwap == 0) {
    unknown003 *buf = getBuf(isOdd);
    buf->unknown08 = buf->unknown00;
    buf->unknown3018 = 0;
    for (int i = 0; i < 0x200; i++) {
      // Original bug: every iteration clears the range at the range count, which is 0 here, instead of range i.
      buf->unknown18[buf->unknown3018].unknown08 = nullptr;
      buf->unknown18[buf->unknown3018].unknown00 = nullptr;
      buf->unknown18[buf->unknown3018].unknown10 = -1;
    }
  }
  unknown6054 = 1.0f;
  unknown6058 = 1.0f;
  unknown6070 = true;
}

CacheDraw::~CacheDraw() {
  mtl::MemManager::deallocate(unknown08[0].unknown00, 0, false);
  mtl::MemManager::deallocate(unknown08[1].unknown00, 0, false);
  if (m_criticalSectionNC != nullptr) {
    delete m_criticalSectionNC;
    m_criticalSectionNC = nullptr;
  }
}

void CacheDraw::setSuspendSwap(bool isSuspend) {
  CSNC lock(*m_criticalSectionNC);
  if (isSuspend) {
    if (m_suspendSwap == 0) {
      m_suspendSwap = WorkCpu::getOdd() + 1;
      unknown003 &src = unknown08[WorkCpu::getOdd()];
      unknown003 &dst = unknown08[WorkCpu::getEven()];
      memcpy(dst.unknown00, src.unknown00, src.unknown10);
      dst.unknown08 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown08) - reinterpret_cast<size_t>(src.unknown00)));
      for (u32 i = 0; i < src.unknown3018; i++) {
        dst.unknown18[i].unknown08 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown18[i].unknown08) - reinterpret_cast<size_t>(src.unknown00)));
        dst.unknown18[i].unknown00 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown18[i].unknown00) - reinterpret_cast<size_t>(src.unknown00)));
        dst.unknown18[i].unknown10 = src.unknown18[i].unknown10;
      }
      dst.unknown3018 = src.unknown3018;
    }
  } else if (m_suspendSwap != 0) {
    m_suspendSwap = 0;
    unknown003 *buf = &unknown08[WorkCpu::getEven()];
    buf->unknown08 = buf->unknown00;
    buf->unknown3018 = 0;
    for (int i = 0; i < 0x200; i++) {
      // Original bug: the same range clearing as clearSystem, at the range count instead of range i.
      buf->unknown18[buf->unknown3018].unknown08 = nullptr;
      buf->unknown18[buf->unknown3018].unknown00 = nullptr;
      buf->unknown18[buf->unknown3018].unknown10 = -1;
    }
  }
}

void CacheDraw::swap() {
  if (m_suspendSwap == 0) {
    unknown003 &buf = unknown08[WorkCpu::getOdd()];
    u8 *end = buf.unknown08;
    if (buf.unknown00 < end) {
      buf.unknown3018++;
      buf.unknown18[buf.unknown3018].unknown08 = end;
      buf.unknown18[buf.unknown3018].unknown00 = end;
      buf.unknown18[buf.unknown3018].unknown10 = m_currentPrio;
    }
  }
}

// Written with the odd buffer first: the inlined copies of getBuf then give renderOval (0x7100703018), renderSquare, renderSquareFill, renderGrid and fontScale
// the machine trace whose length lets the AArch64 store-pair suppression pass keep the stp s9, s8 of the two floats (renderOval 0x71007030d4);
// with the even buffer tested first those five functions keep two separate str.
CacheDraw::unknown003 *CacheDraw::getBuf(bool isOdd) {
  if (isOdd || (WorkCpu::getCurrentThreadId() != WorkCpu::getMainThreadId() && m_forceRenderQueue)) {
    return &unknown08[WorkCpu::getOdd()];
  }
  return &unknown08[WorkCpu::getEven()];
}

// Measured at 0x71006fe998 (forms tried that do not match, all 109 or 110 instructions): `position += size` on a u8 pointer and `size + position`
// on a pointer give `add x23, x23, x8`, the game has `add x23, x8, x23` (integer addition, as in setSuspendSwap); `mode == 2 && !isPerspective`,
// nested ifs, a switch and `||` give a branch where the game computes `isPerspective | (mode != 2)` with cset and orr. The game also calls DebDraw::get
// once before the buffer lookup and drops the result (0x71006fe9d4), then calls it again for each range of the priority.
void CacheDraw::flush(int priority, const mm::Mat44 &projection, const mm::Mat44 &view) {
  CSNC lock(*m_criticalSectionNC);
  DebDraw::get(0xffffffff);
  u32 index;
  if (m_suspendSwap == 0) {
    index = WorkCpu::getOdd();
  } else {
    index = m_suspendSwap - 1;
  }
  unknown003 &buf = unknown08[index];
  unknown002 *range = buf.unknown18;
  for (u32 i = 0; i < buf.unknown3018; i++, range++) {
    if (range->unknown10 == priority) {
      DebDraw *draw = DebDraw::get(0xffffffff);
      if (priority == -2) {
        bool isPerspective = false;
        size_t position = reinterpret_cast<size_t>(range->unknown00);
        while (position < reinterpret_cast<size_t>(range->unknown08)) {
          unknown001 *command = reinterpret_cast<unknown001 *>(position);
          if (command->unknown09 == 1) {
            draw->setOrtho();
            isPerspective = false;
          } else if (!(isPerspective | (command->unknown09 != 2))) {
            draw->setPerspective(projection, view);
            isPerspective = true;
          }
          command->flush(draw);
          position = command->unknown0a + position;
        }
      } else {
        size_t position = reinterpret_cast<size_t>(range->unknown00);
        while (position < reinterpret_cast<size_t>(range->unknown08)) {
          unknown001 *command = reinterpret_cast<unknown001 *>(position);
          command->flush(draw);
          position = command->unknown0a + position;
        }
      }
    }
  }
}

void CacheDraw::setForceRenderQueue(bool isForce) {
  m_forceRenderQueue = isForce;
  if (!isForce) {
    swap();
  }
}

void CacheDraw::reset_prim(u32 wid) {
  if (wid != 0xffffffff) {
    m_cacheDrawWID = wid;
  }
  if (m_currentPrio >= 0) {
    unknown003 *buf = getBuf(false);
    if (buf->unknown18[buf->unknown3018].unknown00 != buf->unknown18[buf->unknown3018].unknown08) {
      buf->unknown3018++;
    }
    buf->unknown18[buf->unknown3018].unknown08 = buf->unknown08;
    buf->unknown18[buf->unknown3018].unknown00 = buf->unknown08;
    buf->unknown18[buf->unknown3018].unknown10 = m_currentPrio;
  }
}

bool CacheDraw::calcCurrentBuf(size_t size) {
  unknown003 *buf = getBuf(false);
  u8 *start = buf->unknown18[buf->unknown3018].unknown00;
  u8 *end = buf->unknown08;
  if (start == nullptr) {
    buf->unknown18[buf->unknown3018].unknown00 = end;
    buf->unknown18[buf->unknown3018].unknown10 = m_currentPrio;
  }
  buf->unknown08 = end + size;
  buf->unknown18[buf->unknown3018].unknown08 = buf->unknown08;
  return true;
}

bool CacheDraw::clear() {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DCLEAR();
    return calcCurrentBuf(sizeof(DCLEAR));
  }
  return false;
}

bool CacheDraw::setMatrix(const mm::Mat44 &matrix) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DMAT(matrix);
    return calcCurrentBuf(sizeof(DMAT));
  }
  return false;
}

bool CacheDraw::setPers(const mm::Mat44 &view, f32 fovy, f32 nearClip, f32 farClip, const mm::Vec3 *position) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DPERS(view, fovy, nearClip, farClip, position == nullptr ? mm::Vec3::zero : *position);
    return calcCurrentBuf(sizeof(DPERS));
  }
  return false;
}

bool CacheDraw::setOrtho() {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DORTHO();
    return calcCurrentBuf(sizeof(DORTHO));
  }
  return false;
}

bool CacheDraw::setCol(const mm::Col4 &color) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DCOL(color);
    return calcCurrentBuf(sizeof(DCOL));
  }
  return false;
}

bool CacheDraw::setTex(grlib::CGLibTextureBuffer *texture) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DTEX(texture);
    return calcCurrentBuf(sizeof(DTEX));
  }
  return false;
}

bool CacheDraw::setDoubleSide(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DDOUBLESIDE(isEnable);
    return calcCurrentBuf(sizeof(DDOUBLESIDE));
  }
  return false;
}

bool CacheDraw::setZComp(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DZCOMP(isEnable);
    return calcCurrentBuf(sizeof(DZCOMP));
  }
  return false;
}

bool CacheDraw::setZWrite(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    unknown6070 = isEnable;
    new (getBuf(false)->unknown08) DZWRITE(isEnable);
    return calcCurrentBuf(sizeof(DZWRITE));
  }
  return false;
}

bool CacheDraw::setAlpha(f32 alpha) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DALPHA(alpha);
    return calcCurrentBuf(sizeof(DALPHA));
  }
  return false;
}

bool CacheDraw::renderRect(const mm::Rect<int> &rect) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRRECT(rect);
    return calcCurrentBuf(sizeof(DRRECT));
  }
  return false;
}

bool CacheDraw::renderRectFill(const mm::Rect<int> &rect) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRRECT_FILL(rect);
    return calcCurrentBuf(sizeof(DRRECT_FILL));
  }
  return false;
}

bool CacheDraw::renderTriangle(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRTRI(first, second, third);
    return calcCurrentBuf(sizeof(DRTRI));
  }
  return false;
}

bool CacheDraw::renderTriangleFill(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRTRI_FILL(first, second, third);
    return calcCurrentBuf(sizeof(DRTRI_FILL));
  }
  return false;
}

bool CacheDraw::renderTriangle2DFill(const mm::Pnt<int> &first, const mm::Pnt<int> &second, const mm::Pnt<int> &third) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRTRI2D_FILL(first, second, third);
    return calcCurrentBuf(sizeof(DRTRI2D_FILL));
  }
  return false;
}

bool CacheDraw::renderCube(const mm::Vec3 &min, const mm::Vec3 &max) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCUBE(min, max);
    return calcCurrentBuf(sizeof(DRCUBE));
  }
  return false;
}

bool CacheDraw::renderCubeFill(const mm::Vec3 &min, const mm::Vec3 &max) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCUBE_FILL(min, max);
    return calcCurrentBuf(sizeof(DRCUBE_FILL));
  }
  return false;
}

bool CacheDraw::renderCircle(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE(center, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE));
  }
  return false;
}

bool CacheDraw::renderCircle2D(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE2D(center, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE2D));
  }
  return false;
}

bool CacheDraw::renderCircleFill(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE_FILL(center, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE_FILL));
  }
  return false;
}

bool CacheDraw::renderCircle2DFill(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE2D_FILL(center, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE2D_FILL));
  }
  return false;
}

bool CacheDraw::renderCircle(const mm::Mat44 &matrix, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE_MAT(matrix, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE_MAT));
  }
  return false;
}

bool CacheDraw::renderFan(const mm::Vec3 &center, f32 radius, f32 direction, f32 angle) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRFAN(center, radius, direction, angle);
    return calcCurrentBuf(sizeof(DRFAN));
  }
  return false;
}

bool CacheDraw::renderFanFill(const mm::Vec3 &center, f32 radius, f32 direction, f32 angle) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRFAN_FILL(center, radius, direction, angle);
    return calcCurrentBuf(sizeof(DRFAN_FILL));
  }
  return false;
}

bool CacheDraw::renderAxis(f32 length) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRAXIS(length);
    return calcCurrentBuf(sizeof(DRAXIS));
  }
  return false;
}

bool CacheDraw::renderArrow(const mm::Vec3 &start, const mm::Vec3 &end) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRARROW(start, end);
    return calcCurrentBuf(sizeof(DRARROW));
  }
  return false;
}

bool CacheDraw::renderCubeArrow(const mm::Vec3 &start, const mm::Vec3 &end) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRARROW_CUBE(start, end);
    return calcCurrentBuf(sizeof(DRARROW_CUBE));
  }
  return false;
}

bool CacheDraw::renderSphereFill(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE_FILL(center, radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE_FILL));
  }
  return false;
}

bool CacheDraw::renderSphere(const mm::Vec3 &center, f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE(center, radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE));
  }
  return false;
}

bool CacheDraw::renderRealSphereFill(f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE_REAL_FILL(radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE_REAL_FILL));
  }
  return false;
}

bool CacheDraw::renderRealSphere(f32 radius, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE_REAL(radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE_REAL));
  }
  return false;
}

bool CacheDraw::renderConeFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCONE_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCONE_FILL));
  }
  return false;
}

bool CacheDraw::renderCone(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCONE(radius, height, division);
    return calcCurrentBuf(sizeof(DRCONE));
  }
  return false;
}

bool CacheDraw::renderCylinderFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCYLINDER_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCYLINDER_FILL));
  }
  return false;
}

bool CacheDraw::renderCylinder(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCYLINDER(radius, height, division);
    return calcCurrentBuf(sizeof(DRCYLINDER));
  }
  return false;
}

bool CacheDraw::renderCapsuleFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAPSULE_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCAPSULE_FILL));
  }
  return false;
}

bool CacheDraw::renderCapsule(f32 radius, f32 height, u32 division) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAPSULE(radius, height, division);
    return calcCurrentBuf(sizeof(DRCAPSULE));
  }
  return false;
}

bool CacheDraw::renderOval(f32 width, f32 height) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DROVAL(width, height);
    return calcCurrentBuf(sizeof(DROVAL));
  }
  return false;
}

bool CacheDraw::renderSquareFill(f32 width, f32 height) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSQUARE_FILL(width, height);
    return calcCurrentBuf(sizeof(DRSQUARE_FILL));
  }
  return false;
}

bool CacheDraw::renderSquare(f32 width, f32 height) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSQUARE(width, height);
    return calcCurrentBuf(sizeof(DRSQUARE));
  }
  return false;
}

bool CacheDraw::renderPrim(const mm::Mat44 &matrix, u32 type) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRPRIM(matrix, type);
    return calcCurrentBuf(sizeof(DRPRIM));
  }
  return false;
}

bool CacheDraw::renderOBB(const mm::Obb &obb) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DROBB(obb);
    return calcCurrentBuf(sizeof(DROBB));
  }
  return false;
}

bool CacheDraw::renderGrid(f32 size, f32 step) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRGRID(size, step);
    return calcCurrentBuf(sizeof(DRGRID));
  }
  return false;
}

bool CacheDraw::renderCamera() {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAMERA();
    return calcCurrentBuf(sizeof(DRCAMERA));
  }
  return false;
}

bool CacheDraw::renderLine(const mm::Vec3 &start, const mm::Vec3 &end) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRLINE(start, end);
    return calcCurrentBuf(sizeof(DRLINE));
  }
  return false;
}

bool CacheDraw::renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRLINE_PNT(start, end);
    return calcCurrentBuf(sizeof(DRLINE_PNT));
  }
  return false;
}

bool CacheDraw::renderPoint(const mm::Vec3 &position) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRPNT(position);
    return calcCurrentBuf(sizeof(DRPNT));
  }
  return false;
}

bool CacheDraw::renderPoint2D(const mm::Vec3 &position, f32 size) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRPNT2D(position, size);
    return calcCurrentBuf(sizeof(DRPNT2D));
  }
  return false;
}

bool CacheDraw::setLineWidth(u32 width) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DLINE_WIDTH(width);
    return calcCurrentBuf(sizeof(DLINE_WIDTH));
  }
  return false;
}

bool CacheDraw::setAlphaBlend(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DALPHA_BLEND(isEnable);
    return calcCurrentBuf(sizeof(DALPHA_BLEND));
  }
  return false;
}

bool CacheDraw::begin(u32 primitive, u32 count) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DBEGIN(primitive, count);
    return calcCurrentBuf(sizeof(DBEGIN));
  }
  return false;
}

bool CacheDraw::end() {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DEND();
    return calcCurrentBuf(sizeof(DEND));
  }
  return false;
}

bool CacheDraw::add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DADDV3_3(first, second, third);
    return calcCurrentBuf(sizeof(DADDV3_3));
  }
  return false;
}

bool CacheDraw::add(const mm::Vec3 &first, const mm::Vec3 &second) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DADDV3_2(first, second);
    return calcCurrentBuf(sizeof(DADDV3_2));
  }
  return false;
}

bool CacheDraw::add(const mm::Vec3 &position) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DADDV3_1(position);
    return calcCurrentBuf(sizeof(DADDV3_1));
  }
  return false;
}

bool CacheDraw::fontColor(const mm::Col4 &color) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_COL(color);
    return calcCurrentBuf(sizeof(DFONT_COL));
  }
  return false;
}

bool CacheDraw::fontBack(const mm::Col4 &color) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_BACKCOL(color);
    return calcCurrentBuf(sizeof(DFONT_BACKCOL));
  }
  return false;
}

bool CacheDraw::fontShadow(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_SHADOW(isEnable);
    return calcCurrentBuf(sizeof(DFONT_SHADOW));
  }
  return false;
}

bool CacheDraw::fontFlush(bool isEnable) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_FLUSH(isEnable);
    return calcCurrentBuf(sizeof(DFONT_FLUSH));
  }
  return false;
}

bool CacheDraw::fontScale(f32 x, f32 y) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_SCALE(x, y);
    unknown6054 = x;
    unknown6058 = y;
    return calcCurrentBuf(sizeof(DFONT_SCALE));
  }
  return false;
}

bool CacheDraw::font(s16 x, s16 y, const char *text) {
  CSNC lock(*m_criticalSectionNC);
  if (DebDraw::isNotRender()) {
    unknown003 *buf = getBuf(false);
    size_t length = strlen(text);
    size_t size;
    if (length < 32) {
      new (buf->unknown08) DFONT32(x, y, text);
      size = sizeof(DFONT32);
    } else if (length < 64) {
      new (buf->unknown08) DFONT64(x, y, text);
      size = sizeof(DFONT64);
    } else if (length < 128) {
      new (buf->unknown08) DFONT128(x, y, text);
      size = sizeof(DFONT128);
    } else {
      new (buf->unknown08) DFONT256(x, y, text);
      size = sizeof(DFONT256);
    }
    return calcCurrentBuf(size);
  }
  return false;
}

void CacheDraw::DMAT::flush(DebDraw *draw) { draw->setMatrix(unknown10); }

void CacheDraw::DCLEAR::flush(DebDraw *draw) { draw->clear(); }

void CacheDraw::DEND::flush(DebDraw *draw) { draw->end(); }

void CacheDraw::DORTHO::flush(DebDraw *draw) { draw->setOrtho(); }

void CacheDraw::DBEGIN::flush(DebDraw *draw) { draw->begin(unknown0c, unknown10); }

// Evidence for the casts of the flush functions below (decision 45): the game passes the address of the 12-byte record member to
// functions whose mangled names take const mm::Vec3 & (DRCUBE::flush 0x71007065c0: add x8,x0,#0xc; add x2,x0,#0x18; b DebDraw::renderCube),
// so the original converted a 12-byte field to the 16-byte type's reference.
void CacheDraw::DADDV3_1::flush(DebDraw *draw) { draw->add(reinterpret_cast<const mm::Vec3 &>(unknown0c)); }

void CacheDraw::DADDV3_2::flush(DebDraw *draw) { draw->add(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18)); }

void CacheDraw::DADDV3_3::flush(DebDraw *draw) {
  draw->add(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18), reinterpret_cast<const mm::Vec3 &>(unknown24));
}

void CacheDraw::DPERS::flush(DebDraw *draw) { draw->setPerspective(unknown4c, unknown50, unknown54, unknown0c, &reinterpret_cast<const mm::Vec3 &>(unknown58)); }

void CacheDraw::DRAXIS::flush(DebDraw *draw) { draw->renderAxis(unknown0c); }

void CacheDraw::DRCAMERA::flush(DebDraw *draw) { draw->renderCamera(); }

void CacheDraw::DROBB::flush(DebDraw *draw) { draw->renderOBB(unknown10); }

void CacheDraw::DRRECT::flush(DebDraw *draw) { draw->renderRect(unknown0c); }

void CacheDraw::DRRECT_FILL::flush(DebDraw *draw) { draw->renderRectFill(unknown0c); }

void CacheDraw::DRCUBE::flush(DebDraw *draw) { draw->renderCube(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18)); }

void CacheDraw::DRCUBE_FILL::flush(DebDraw *draw) { draw->renderCubeFill(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18)); }

void CacheDraw::DRCIRCLE::flush(DebDraw *draw) { draw->renderCircle(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

// The game calls DebDraw::renderCircle for the 2D circle too (0x7100706d58); the 2D mode is the projection stored with the record.
void CacheDraw::DRCIRCLE2D::flush(DebDraw *draw) { draw->renderCircle(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

void CacheDraw::DRCIRCLE_FILL::flush(DebDraw *draw) { draw->renderCircleFill(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

void CacheDraw::DRCIRCLE2D_FILL::flush(DebDraw *draw) { draw->renderCircleFill(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

void CacheDraw::DRFAN::flush(DebDraw *draw) { draw->renderFan(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c, unknown20); }

// The game calls DebDraw::renderFan, not renderFanFill, for the filled fan too (0x71007072e4).
void CacheDraw::DRFAN_FILL::flush(DebDraw *draw) { draw->renderFan(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c, unknown20); }

void CacheDraw::DRARROW::flush(DebDraw *draw) { draw->renderArrow(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18)); }

void CacheDraw::DRARROW_CUBE::flush(DebDraw *draw) { draw->renderCubeArrow(reinterpret_cast<const mm::Vec3 &>(unknown0c), reinterpret_cast<const mm::Vec3 &>(unknown18)); }

void CacheDraw::DRSPHERE_FILL::flush(DebDraw *draw) { draw->renderSphereFill(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

void CacheDraw::DRSPHERE::flush(DebDraw *draw) { draw->renderSphere(reinterpret_cast<const mm::Vec3 &>(unknown0c), unknown18, unknown1c); }

void CacheDraw::DRGRID::flush(DebDraw *draw) { draw->renderGrid(unknown0c, unknown10); }

void CacheDraw::DROVAL::flush(DebDraw *draw) { draw->renderOval(unknown0c, unknown10); }

void CacheDraw::DRSQUARE::flush(DebDraw *draw) { draw->renderSquare(unknown0c, unknown10); }

void CacheDraw::DRSQUARE_FILL::flush(DebDraw *draw) { draw->renderSquareFill(unknown0c, unknown10); }

void CacheDraw::DRPRIM::flush(DebDraw *draw) {
  switch (unknown4c) {
  case mm::PrimBase::PRIM_CUBE: {
    mm::Cube cube(unknown0c);
    draw->renderPrim(&cube);
    break;
  }
  case mm::PrimBase::PRIM_CYLINDER: {
    mm::Cylinder cylinder(unknown0c);
    draw->renderPrim(&cylinder);
    break;
  }
  case mm::PrimBase::PRIM_SPHERE: {
    mm::Sphere sphere(unknown0c);
    draw->renderPrim(&sphere);
    break;
  }
  }
}

void CacheDraw::DRCAPSULE::flush(DebDraw *draw) { draw->renderCapsule(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCAPSULE_FILL::flush(DebDraw *draw) { draw->renderCapsuleFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCONE::flush(DebDraw *draw) { draw->renderCone(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCONE_FILL::flush(DebDraw *draw) { draw->renderConeFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCYLINDER::flush(DebDraw *draw) { draw->renderCylinder(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCYLINDER_FILL::flush(DebDraw *draw) { draw->renderCylinderFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCIRCLE_MAT::flush(DebDraw *draw) { draw->renderCircle(unknown0c, unknown4c, unknown50); }

void CacheDraw::DRSPHERE_REAL::flush(DebDraw *draw) { draw->renderRealSphere(unknown0c, unknown10); }

void CacheDraw::DRSPHERE_REAL_FILL::flush(DebDraw *draw) { draw->renderRealSphereFill(unknown0c, unknown10); }

void CacheDraw::DCOL::flush(DebDraw *draw) { draw->setCol(unknown0c); }

void CacheDraw::DTEX::flush(DebDraw *draw) { draw->setTex(unknown10); }

void CacheDraw::DDOUBLESIDE::flush(DebDraw *draw) { draw->setDoubleSide(unknown0c); }

void CacheDraw::DZCOMP::flush(DebDraw *draw) { draw->setZComp(unknown0c); }

void CacheDraw::DZWRITE::flush(DebDraw *draw) { draw->setZWrite(unknown0c); }

void CacheDraw::DALPHA::flush(DebDraw *draw) { draw->setAlpha(unknown0c); }

void CacheDraw::DLINE_WIDTH::flush(DebDraw *draw) { draw->setLineWidth(unknown0c); }

void CacheDraw::DALPHA_BLEND::flush(DebDraw *draw) { draw->setAlphaBlend(unknown0c); }

void CacheDraw::DRTRI2D_FILL::flush(DebDraw *draw) {
  draw->renderTriangleFill(mm::Vec3(unknown0c.x, unknown0c.y, 0.0f), mm::Vec3(unknown14.x, unknown14.y, 0.0f), mm::Vec3(unknown1c.x, unknown1c.y, 0.0f));
}

void CacheDraw::DRLINE_PNT::flush(DebDraw *draw) { draw->renderLine(unknown0c, unknown14); }

void CacheDraw::DFONT32::flush(DebDraw *draw) { WinView::getView(false)->font(unknown30, unknown32, unknown0c.c_str()); }

void CacheDraw::DFONT64::flush(DebDraw *draw) { WinView::getView(false)->font(unknown50, unknown52, unknown0c.c_str()); }

void CacheDraw::DFONT128::flush(DebDraw *draw) { WinView::getView(false)->font(unknown90, unknown92, unknown0c.c_str()); }

void CacheDraw::DFONT256::flush(DebDraw *draw) { WinView::getView(false)->font(unknown110, unknown112, unknown0c.c_str()); }

void CacheDraw::DFONT_COL::flush(DebDraw *draw) { WinView::getView(false)->fontColor(unknown0c); }

void CacheDraw::DFONT_BACKCOL::flush(DebDraw *draw) { WinView::getView(false)->fontBack(unknown0c); }

void CacheDraw::DFONT_SHADOW::flush(DebDraw *draw) { WinView::getView(false)->fontShadow(unknown0c); }

void CacheDraw::DFONT_FLUSH::flush(DebDraw *draw) { WinView::getView(false)->fontFlush(unknown0c); }

void CacheDraw::DFONT_SCALE::flush(DebDraw *draw) { WinView::getView(false)->fontScale(unknown0c, unknown10); }

} // namespace ml
