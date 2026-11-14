#include "ml/win_view_port.h"

#include "ml/dev_graph.h"

namespace ml {

WinViewPort::WinViewPort()
    : unknown00(DevGraph::getRootWidth(), DevGraph::getRootHeight()), m_workSize(DevGraph::getRootWidth(), DevGraph::getRootHeight()), unknown10(0, 0), unknown18(0, 0), unknown20(0, 0) {}

void WinViewPort::addScroll(const mm::Pnt<int> &scroll) {
  mm::Pnt<int> clientSize(unknown00.x - unknown18.x - unknown20.x, unknown00.y - unknown18.y - unknown20.y);
  unknown10.x += scroll.x;
  unknown10.y += scroll.y;
  unknown001(clientSize);
}

void WinViewPort::setSize(const mm::Pnt<int> &size) {
  unknown00 = size;
  unknown001(mm::Pnt<int>(unknown00.x - unknown18.x - unknown20.x, unknown00.y - unknown18.y - unknown20.y));
}

void WinViewPort::setWorkSize(const mm::Pnt<int> &size) { m_workSize = size; }

} // namespace ml
