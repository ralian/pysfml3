#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Window/Joystick.hpp>

namespace py = pybind11;

void bind_joystick(py::module_& m) {

    // Joystick namespace
    auto joystick = m.def_submodule("Joystick", "Joystick input handling");
        
    py::native_enum<sf::Joystick::Axis>(joystick, "Axis", "enum.IntEnum")
        .value("X", sf::Joystick::Axis::X)
        .value("Y", sf::Joystick::Axis::Y)
        .value("Z", sf::Joystick::Axis::Z)
        .value("R", sf::Joystick::Axis::R)
        .value("U", sf::Joystick::Axis::U)
        .value("V", sf::Joystick::Axis::V)
        .value("POV_X", sf::Joystick::Axis::PovX)
        .value("POV_Y", sf::Joystick::Axis::PovY)
        .export_values()
        .finalize();

    // Joystick::Identification struct
    py::class_<sf::Joystick::Identification>(joystick, "Identification", "Structure holding a joystick's identification")
        .def_readonly("name", &sf::Joystick::Identification::name)
        .def_readonly("vendor_id", &sf::Joystick::Identification::vendorId)
        .def_readonly("product_id", &sf::Joystick::Identification::productId);

    // Constants
    joystick.def("count", [](){
        return sf::Joystick::Count;
    }, "Maximum number of supported joysticks");

    joystick.def("button_count", [](){
        return sf::Joystick::ButtonCount;
    }, "Maximum number of supported buttons per joystick");

    joystick.def("axis_count", [](){
        return sf::Joystick::AxisCount;
    }, "Maximum number of supported axes per joystick");

    // Functions
    joystick.def("is_connected", &sf::Joystick::isConnected, 
        "Check if a joystick is connected",
        py::arg("joystick"));

    joystick.def("get_button_count", &sf::Joystick::getButtonCount,
        "Return the number of buttons supported by a joystick",
        py::arg("joystick"));

    joystick.def("has_axis", &sf::Joystick::hasAxis,
        "Check if a joystick supports a given axis",
        py::arg("joystick"), py::arg("axis"));

    joystick.def("is_button_pressed", &sf::Joystick::isButtonPressed,
        "Check if a joystick button is pressed",
        py::arg("joystick"), py::arg("button"));

    joystick.def("get_axis_position", &sf::Joystick::getAxisPosition,
        "Get the current position of a joystick axis",
        py::arg("joystick"), py::arg("axis"));

    joystick.def("get_identification", &sf::Joystick::getIdentification,
        "Get the joystick information",
        py::arg("joystick"));

    joystick.def("update", &sf::Joystick::update,
        "Update the states of all joysticks");
}
