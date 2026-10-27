#include "ml/win_view_port.h"

#include "ml/dev_graph.h"

namespace ml {

WinViewPort::WinViewPort()
    : unknown00(DevGraph::getRootWidth(), DevGraph::getRootHeight()), unknown08(DevGraph::getRootWidth(), DevGraph::getRootHeight()), unknown10(0, 0), unknown18(0, 0), unknown20(0, 0) {}

void WinViewPort::setWorkSize(const mm::Pnt<int> &size) { unknown08 = size; }

} // namespace ml
