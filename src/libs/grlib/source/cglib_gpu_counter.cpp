#include "grlib/cglib_gpu_counter.h"

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_buff_occlusion.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

namespace {

// Inferred role: NVN counter types reported by begin and end; original name unknown.
const u32 unknown004[5] = {2, 3, 4, 8, 15};

} // namespace

void CGLibGpuCounter::begin() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibBuffFixAlloc &alloc = context->unknowne38;
  int index = CGLibManager::s_nDblNowIdx;
  if (unknown10[index].unknown00 == nullptr) {
    unknown10[index].unknown08 = alloc.allocID();
    unknown10[index].unknown00 = reinterpret_cast<NVNcounterData *>(alloc.m_buffer + alloc.unknown10 * unknown10[index].unknown08);
    unknown10[index].unknown0c = static_cast<u32>(reinterpret_cast<u64>(unknown10[index].unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
  }
  nvnCommandBufferReportCounter(context->unknown1070.unknown00, NVN_COUNTER_TYPE_TIMESTAMP, nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + unknown10[index].unknown0c);
  for (int i = 0; i < 5; i++) {
    int counterIndex = i * 2 + CGLibManager::s_nDblNowIdx;
    if (unknown50[counterIndex].unknown00 == nullptr) {
      unknown50[counterIndex].unknown08 = alloc.allocID();
      unknown50[counterIndex].unknown00 = reinterpret_cast<unknown003 *>(alloc.m_buffer + alloc.unknown10 * unknown50[counterIndex].unknown08);
      unknown50[counterIndex].unknown0c = static_cast<u32>(reinterpret_cast<u64>(unknown50[counterIndex].unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
    }
    nvnCommandBufferReportCounter(
        context->unknown1070.unknown00, static_cast<NVNcounterType>(unknown004[i]), nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + unknown50[counterIndex].unknown0c);
  }
}

void CGLibGpuCounter::end() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibBuffFixAlloc &alloc = context->unknowne38;
  int index = CGLibManager::s_nDblNowIdx;
  if (unknown30[index].unknown00 == nullptr) {
    unknown30[index].unknown08 = alloc.allocID();
    unknown30[index].unknown00 = reinterpret_cast<NVNcounterData *>(alloc.m_buffer + alloc.unknown10 * unknown30[index].unknown08);
    unknown30[index].unknown0c = static_cast<u32>(reinterpret_cast<u64>(unknown30[index].unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
  }
  nvnCommandBufferReportCounter(context->unknown1070.unknown00, NVN_COUNTER_TYPE_TIMESTAMP, nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + unknown30[index].unknown0c);
  for (int i = 0; i < 5; i++) {
    int counterIndex = i * 2 + CGLibManager::s_nDblNowIdx;
    if (unknownf0[counterIndex].unknown00 == nullptr) {
      unknownf0[counterIndex].unknown08 = alloc.allocID();
      unknownf0[counterIndex].unknown00 = reinterpret_cast<unknown003 *>(alloc.m_buffer + alloc.unknown10 * unknownf0[counterIndex].unknown08);
      unknownf0[counterIndex].unknown0c = static_cast<u32>(reinterpret_cast<u64>(unknownf0[counterIndex].unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
    }
    nvnCommandBufferReportCounter(
        context->unknown1070.unknown00, static_cast<NVNcounterType>(unknown004[i]), nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + unknownf0[counterIndex].unknown0c);
  }
}

int CGLibGpuCounter::getTimeStamp() {
  int index = CGLibManager::s_nDblNowIdx;
  if (unknown10[index].unknown00 == nullptr || unknown30[index].unknown00 == nullptr) {
    return 0;
  }
  int beginTime = nvnDeviceGetTimestampInNanoseconds(&CGLibManager::get()->unknown08, unknown10[index].unknown00);
  int endTime = nvnDeviceGetTimestampInNanoseconds(&CGLibManager::get()->unknown08, unknown30[index].unknown00);
  return endTime - beginTime;
}

int CGLibGpuCounter::getCntNum(u32 index) {
  if (unknown50[index].unknown00 == nullptr) {
    return 0;
  }
  if (unknownf0[index].unknown00 != nullptr) {
    return unknownf0[index].unknown00->unknown00[0] - unknown50[index].unknown00->unknown00[0];
  }
  return 0;
}

int CGLibGpuCounter::getVertexNum() { return getCntNum(CGLibManager::s_nDblNowIdx); }

int CGLibGpuCounter::getPrimitiveNum() { return getCntNum(CGLibManager::s_nDblNowIdx + 2); }

int CGLibGpuCounter::getVsShdNum() { return getCntNum(CGLibManager::s_nDblNowIdx + 4); }

int CGLibGpuCounter::getPsShdNum() { return getCntNum(CGLibManager::s_nDblNowIdx + 6); }

int CGLibGpuCounter::get8x8ZCullNum() { return getCntNum(CGLibManager::s_nDblNowIdx + 8); }

int CGLibGpuCounter::get4x2ZCullNum() {
  u32 index = CGLibManager::s_nDblNowIdx + 8;
  if (unknown50[index].unknown00 == nullptr) {
    return 0;
  }
  if (unknownf0[index].unknown00 != nullptr) {
    return unknownf0[index].unknown00->unknown00[1] - unknown50[index].unknown00->unknown00[1];
  }
  return 0;
}

} // namespace grlib
