#include "../Swarm.h"
#include <Eigen/Core>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace MetaOpt {
namespace Python {

namespace py = pybind11;

void init_swarm(py::module &m) {

  auto constructor = py::init<const ParameterSpace &, const Parameters &,
                              std::size_t, const int>();
  py::class_<Swarm>(m, "Swarm")
      .def(constructor, py::arg("parameter_space"), py::arg("hyper_params"),
           py::arg("num_particles") = 10, py::arg("seed") = -1)
      .def("optimize", &Swarm::optimize)
      .def("getBestSolution", &Swarm::getBestSolution)
      .def("getBestParameters", &Swarm::getBestParameters);
}
}
}
