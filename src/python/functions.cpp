#include "../functions.hpp"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace Optima {
namespace Python {

namespace py = pybind11;

void init_functions(py::module &m) {
  m.def("rosen", &TestFunctions::rosen,
        "Multi dimensional version of the rosenbrock function.");
  m.def("parabola", &TestFunctions::parabola, "Multi dimensional parabolic function.");
}
}
}
