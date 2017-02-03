#include "../simulated_annealing.h"
#include <Eigen/Core>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace MetaOpt {
namespace Python {

using namespace Optima;

namespace py = pybind11;

void init_simulated_annealing(py::module &m) {

  auto constructor = py::init<const ParameterSpace &, const SimulatedAnnealingHyperParameters &,
                              size_t>();
  py::class_<SimulatedAnnealing>(m, "SimulatedAnnealing")
      .def(constructor, py::arg("parameter_space"), py::arg("hyper_params"),
           py::arg("num_particles") = 10)
      .def("optimize", &SimulatedAnnealing::optimize)
      .def("getBestParameters", &SimulatedAnnealing::getBestParameters);
}
}
}
