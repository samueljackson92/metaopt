#include <pybind11/pybind11.h>

namespace MetaOpt {
namespace Python {


namespace py = pybind11;

void init_swarm(py::module &m);
void init_functions(py::module &m);

PYBIND11_PLUGIN(pyoptima) {
  py::module m("pyoptima", "Meta heuristic optimization library");
  init_swarm(m);
  init_functions(m);
  return m.ptr();
}
}
}
