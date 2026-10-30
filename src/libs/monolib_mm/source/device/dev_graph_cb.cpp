#include "ml/dev_graph_cb.h"

#include "ml/dev_graph.h"

namespace ml {

DevGraphCB::DevGraphCB() { DevGraph::entryCb(this); }

void DevGraphCB::viBeginFrame() {}

void DevGraphCB::viBeforeDrawDone() {}

void DevGraphCB::viAfterDrawDone() {}

void DevGraphCB::viAfterSync() {}

void DevGraphCB::viAfterRenderCall() {}

} // namespace ml
