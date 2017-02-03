#include <pybind11/pybind11.h>

namespace Optima {
namespace Python {

namespace py = pybind11;

void init_functions(py::module &m);
void init_simulated_annealing(py::module &m);
void init_swarm(py::module &m);

PYBIND11_PLUGIN(pyoptima) {
  py::module m("pyoptima", "Meta heuristic optimization library");
  init_functions(m);
  init_simulated_annealing(m);
  init_swarm(m);
  return m.ptr();
}
}
}
