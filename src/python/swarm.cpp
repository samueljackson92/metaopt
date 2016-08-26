#include "../Swarm.h"
#include <Eigen/Core>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace MetaOpt
{
namespace Python {

namespace py = pybind11;

void init_swarm(py::module &m) {

  py::class_<Swarm>(m, "Swarm")
      .def(py::init<std::size_t, const Bounds &, const int>())
      .def("optimize", &Swarm::optimize)
      .def("getSolution", &Swarm::getBestSolution);
}
}
}
