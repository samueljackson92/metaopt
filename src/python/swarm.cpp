#include "../swarm.hpp"
#include <Eigen/Core>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace Optima {
namespace Python {

namespace py = pybind11;

void init_swarm(py::module &m) {

  auto constructor = py::init<const ParameterSpace &, const Parameters &,
                              size_t>();
  py::class_<Swarm>(m, "Swarm")
      .def(constructor, py::arg("parameter_space"), py::arg("hyper_params"),
           py::arg("num_particles") = 10)
      .def("optimize", &Swarm::optimize)
      .def("getBestSolution", &Swarm::getBestSolution)
      .def("getBestParameters", &Swarm::getBestParameters)
      .def("getCosts", &Swarm::getCosts);
}
}
}
