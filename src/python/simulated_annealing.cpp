#include "../simulated_annealing.h"
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace MetaOpt {
namespace Python {

using namespace Optima;

namespace py = pybind11;

auto convert_simulated_annealing_hyperparams(py::dict dict) -> SimulatedAnnealingHyperParameters {
    SimulatedAnnealingHyperParameters hyper_params;
    hyper_params.initialTemp = dict["initial_temp"].cast<double>();
    hyper_params.neighbourFunc = dict["neighbour_func"].cast<std::function<Parameters(const Parameters&)>>();
    hyper_params.temperatureFunc = dict["temperature_func"].cast<std::function<double(double, size_t)>>();
    return hyper_params;
}

void init_simulated_annealing(py::module &m) {

  py::class_<SimulatedAnnealing>(m, "SimulatedAnnealing")
      .def("__init__",
        [](SimulatedAnnealing &instance, Parameters p, py::dict h) {
            auto hyper_params = convert_simulated_annealing_hyperparams(h);
            new (&instance) SimulatedAnnealing(p, hyper_params);
        })
      .def("optimize", &SimulatedAnnealing::optimize)
      .def("get_best_parameters", &SimulatedAnnealing::getBestParameters)
      .def("get_best_solution", &SimulatedAnnealing::getBestSolution);
}
}
}
