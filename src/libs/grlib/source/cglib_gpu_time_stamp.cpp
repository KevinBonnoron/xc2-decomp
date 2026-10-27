#include "grlib/cglib_gpu_time_stamp.h"

#include "grlib/cglib_buff_occlusion.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibGpuTimeStamp::reset() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  for (int i = 1; i < 16; i++) {
    nvnCommandBufferResetCounter(context->unknown1070.unknown00, static_cast<NVNcounterType>(i));
  }
}

void CGLibGpuTimeStamp::begin() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  int index = CGLibManager::s_nDblNowIdx;
  unknown001 &report = unknown08[index];
  if (report.unknown00 == nullptr) {
    report.unknown08 = context->unknowne38.allocID();
    report.unknown00 = reinterpret_cast<NVNcounterData *>(context->unknowne38.m_buffer + context->unknowne38.unknown10 * report.unknown08);
    report.unknown0c = static_cast<u32>(reinterpret_cast<u64>(report.unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
  }
  nvnCommandBufferReportCounter(context->unknown1070.unknown00, NVN_COUNTER_TYPE_TIMESTAMP, nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + report.unknown0c);
}

void CGLibGpuTimeStamp::end() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  int index = CGLibManager::s_nDblNowIdx;
  unknown001 &report = unknown38[index];
  if (report.unknown00 == nullptr) {
    report.unknown08 = context->unknowne38.allocID();
    report.unknown00 = reinterpret_cast<NVNcounterData *>(context->unknowne38.m_buffer + context->unknowne38.unknown10 * report.unknown08);
    report.unknown0c = static_cast<u32>(reinterpret_cast<u64>(report.unknown00)) - static_cast<u32>(reinterpret_cast<u64>(context->unknown2458.unknown18));
  }
  nvnCommandBufferReportCounter(context->unknown1070.unknown00, NVN_COUNTER_TYPE_TIMESTAMP, nvnMemoryPoolGetBufferAddress(context->unknown2458.m_memoryPool) + report.unknown0c);
  if (unknown38[index].unknown10) {
    int nowIndex = CGLibManager::s_nDblNowIdx;
    if (unknown08[nowIndex].unknown00 != nullptr && unknown38[nowIndex].unknown00 != nullptr) {
      s64 beginTime = nvnDeviceGetTimestampInNanoseconds(&CGLibManager::get()->unknown00, unknown08[nowIndex].unknown00);
      s64 endTime = nvnDeviceGetTimestampInNanoseconds(&CGLibManager::get()->unknown00, unknown38[nowIndex].unknown00);
      unknown00 = endTime - beginTime;
    } else {
      unknown00 = 0;
    }
  }
  unknown38[index].unknown10 = true;
}

} // namespace grlib
