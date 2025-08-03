#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Window.hpp>

namespace py = pybind11;

void bind_mouse(py::module_& m) {

    // Mouse namespace
    auto mouse = m.def_submodule("mouse", "Mouse input handling");
        
    py::native_enum<sf::Mouse::Button>(mouse, "Button", "enum.IntEnum")
        .value("LEFT", sf::Mouse::Button::Left)
        .value("RIGHT", sf::Mouse::Button::Right)
        .value("MIDDLE", sf::Mouse::Button::Middle)
        .value("EXTRA1", sf::Mouse::Button::Extra1)
        .value("EXTRA2", sf::Mouse::Button::Extra2)
        .export_values()
        .finalize();

    py::native_enum<sf::Mouse::Wheel>(mouse, "Wheel", "enum.IntEnum")
        .value("VERTICAL_WHEEL", sf::Mouse::Wheel::Vertical)
        .value("HORIZONTAL_WHEEL", sf::Mouse::Wheel::Horizontal)
        .export_values()
        .finalize();

    mouse.def("is_button_pressed", &sf::Mouse::isButtonPressed, "Check if a mouse button is currently pressed");
    mouse.def("get_position", py::overload_cast<>(&sf::Mouse::getPosition), "Get mouse position relative to desktop");
    mouse.def("get_position", py::overload_cast<const sf::WindowBase&>(&sf::Mouse::getPosition), "Get mouse position relative to window");
    mouse.def("set_position", py::overload_cast<sf::Vector2i>(&sf::Mouse::setPosition), "Set mouse position relative to desktop");
    mouse.def("set_position", py::overload_cast<sf::Vector2i, const sf::WindowBase&>(&sf::Mouse::setPosition), "Set mouse position relative to window");

    mouse.def("button_count", [](){
        return sf::Mouse::ButtonCount;
    }, "The total number of mouse buttons");
}
