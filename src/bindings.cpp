#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include "EGO_compute.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_core, m)
{
    m.doc() = "deltaEGO C++ VAD vector analysis module with parallel processing";

    //Base Structs (VAD.hpp)
    
    py::class_<VADPoint>(m, "VADPoint")
        .def(py::init<>()) // Allows Python to create this struct
        .def_readwrite("v", &VADPoint::v)
        .def_readwrite("a", &VADPoint::a)
        .def_readwrite("d", &VADPoint::d)
        .def_readwrite("timestamp", &VADPoint::timestamp);

    py::class_<VAD_ave>(m, "VAD_ave")
        .def(py::init<>())
        .def_readwrite("x", &VAD_ave::x)
        .def_readwrite("y", &VAD_ave::y)
        .def_readwrite("z", &VAD_ave::z)
        .def_readwrite("radius", &VAD_ave::radius);

    // Input Helper Structs (with default values)

    py::class_<weight>(m, "weight")
        .def(py::init<>()) // pybind11 will respect the C++ default values
        .def_readwrite("weightA_stress", &weight::weightA_stress)
        .def_readwrite("weightV_stress", &weight::weightV_stress)
        .def_readwrite("weightV_reward", &weight::weightV_reward)
        .def_readwrite("weightA_reward", &weight::weightA_reward)
        .def_readwrite("weight_k", &weight::weight_k);

    py::class_<variable>(m, "variable")
        .def(py::init<>())
        .def_readwrite("theta_0", &variable::theta_0)
        .def_readwrite("dampening_factor", &variable::dampening_factor);

    py::class_<EGO_axis>(m, "EGO_axis")
        .def(py::init<>())
        .def_readwrite("baseline", &EGO_axis::baseline)
        .def_readwrite("stabilityRadius", &EGO_axis::stabilityRadius);

    // Output Helper Structs

    py::class_<InstantMetrics>(m, "InstantMetrics")
        .def(py::init<>())
        .def_readwrite("stress", &InstantMetrics::stress)
        .def_readwrite("reward", &InstantMetrics::reward)
        .def_readwrite("ratio_total", &InstantMetrics::ratio_total)
        .def_readwrite("stress_ratio", &InstantMetrics::stress_ratio)
        .def_readwrite("reward_ratio", &InstantMetrics::reward_ratio)
        .def_readwrite("deviation", &InstantMetrics::deviation);

    py::class_<DynamicMetrics>(m, "DynamicMetrics")
        .def(py::init<>())
        .def_readwrite("delta", &DynamicMetrics::delta)
        .def_readwrite("affective_lability", &DynamicMetrics::affective_lability);

    py::class_<CumulativeMetrics>(m, "CumulativeMetrics")
        .def(py::init<>())
        .def_readwrite("average_area", &CumulativeMetrics::average_area)
        .def_readwrite("stress", &CumulativeMetrics::stress)
        .def_readwrite("reward", &CumulativeMetrics::reward)
        .def_readwrite("total", &CumulativeMetrics::total)
        .def_readwrite("stress_ratio", &CumulativeMetrics::stress_ratio)
        .def_readwrite("reward_ratio", &CumulativeMetrics::reward_ratio);

    // Main Input Struct    
    py::class_<compute_in>(m, "compute_in")
        .def(py::init<>())
        .def_readwrite("current", &compute_in::current)
        .def_readwrite("history", &compute_in::history) // std::vector <-> list
        .def_readwrite("prev", &compute_in::prev)       // std::optional <-> None
        .def_readwrite("emotion_base", &compute_in::emotion_base)
        .def_readwrite("variables", &compute_in::variables)
        .def_readwrite("weights", &compute_in::weights);

    // Main Output Struct
    
    py::class_<AnalysisResult>(m, "AnalysisResult")
        .def(py::init<>())
        .def_readwrite("instant", &AnalysisResult::instant)
        .def_readwrite("dynamics", &AnalysisResult::dynamics)
        .def_readwrite("cumulative", &AnalysisResult::cumulative);

    // Main Function
    
    m.def("compute", &EGO_compute, 
          "Run the full deltaEGO analysis from an input bundle",
          py::arg("user_in"));
}