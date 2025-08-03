#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Window.hpp>

namespace py = pybind11;

void bind_window(py::module_& m) {
    // VideoMode class
    py::class_<sf::VideoMode>(m, "VideoMode")
        .def(py::init<>())
        .def(py::init<sf::Vector2u, unsigned int>())
        .def_readwrite("size", &sf::VideoMode::size)
        .def_readwrite("bits_per_pixel", &sf::VideoMode::bitsPerPixel)
        .def("is_valid", &sf::VideoMode::isValid)
        .def_static("get_desktop_mode", &sf::VideoMode::getDesktopMode)
        .def_static("get_fullscreen_modes", &sf::VideoMode::getFullscreenModes)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)
        .def("__repr__", [](const sf::VideoMode& vm) {
            return "<VideoMode: " + std::to_string(vm.size.x) + "x" + 
                   std::to_string(vm.size.y) + "x" + std::to_string(vm.bitsPerPixel) + ">";
        });
    
    // ContextSettings class
    py::class_<sf::ContextSettings>(m, "ContextSettings")
        .def(py::init<>())
        .def(py::init<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool>())
        .def_readwrite("depth_bits", &sf::ContextSettings::depthBits)
        .def_readwrite("stencil_bits", &sf::ContextSettings::stencilBits)
        .def_readwrite("antialiasing_level", &sf::ContextSettings::antiAliasingLevel)
        .def_readwrite("major_version", &sf::ContextSettings::majorVersion)
        .def_readwrite("minor_version", &sf::ContextSettings::minorVersion)
        .def_readwrite("attribute_flags", &sf::ContextSettings::attributeFlags)
        .def_readwrite("srgb_capable", &sf::ContextSettings::sRgbCapable);
    
    // Window styles enum
    // TODO
    /*py::enum_<sf::Style>(m, "Style")
        .value("NONE", sf::Style::None)
        .value("TITLEBAR", sf::Style::Titlebar)
        .value("RESIZE", sf::Style::Resize)
        .value("CLOSE", sf::Style::Close)
        .value("DEFAULT", sf::Style::Default)
        .export_values();*/

    // Window state enum
    py::native_enum<sf::State>(m, "State", "enum.IntEnum")
        .value("NONE", sf::State::Windowed)
        .value("TITLEBAR", sf::State::Fullscreen)
        .export_values()
        .finalize();
    
    // WindowBase class
    py::class_<sf::WindowBase>(m, "WindowBase")
        .def(py::init<>())
        //.def(py::init<sf::WindowHandle>()) // TODO borken
        .def(py::init<sf::VideoMode, const std::string&, sf::State>())
        .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State>())
        // TODO create needed?
        .def("close", &sf::WindowBase::close)
        .def("is_open", &sf::WindowBase::isOpen)
        .def("poll_event", &sf::WindowBase::pollEvent, py::return_value_policy::move)
        .def("wait_event", &sf::WindowBase::waitEvent, py::return_value_policy::move)
        .def("get_position", &sf::WindowBase::getPosition)
        .def("set_position", &sf::WindowBase::setPosition)
        .def("get_size", &sf::WindowBase::getSize)
        .def("set_size", &sf::WindowBase::setSize)
        .def("set_title", &sf::WindowBase::setTitle)
        .def("set_icon", &sf::WindowBase::setIcon)
        .def("set_visible", &sf::WindowBase::setVisible)
        .def("set_mouse_cursor_visible", &sf::WindowBase::setMouseCursorVisible)
        .def("set_mouse_cursor_grabbed", &sf::WindowBase::setMouseCursorGrabbed)
        .def("set_key_repeat_enabled", &sf::WindowBase::setKeyRepeatEnabled)
        .def("set_joystick_threshold", &sf::WindowBase::setJoystickThreshold)
        .def("request_focus", &sf::WindowBase::requestFocus)
        .def("has_focus", &sf::WindowBase::hasFocus);
    
    // Window class (extends WindowBase)
    py::class_<sf::Window, sf::WindowBase>(m, "Window")
        .def(py::init<>())
        //.def(py::init<sf::WindowHandle, const sf::ContextSettings&>()) // TODO borken
        .def(py::init<sf::VideoMode, const std::string&, sf::State, const sf::ContextSettings&>())
        .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State, const sf::ContextSettings&>())
        // TODO create needed?
        .def("set_active", &sf::Window::setActive)
        .def("display", &sf::Window::display)
        .def("set_framerate_limit", &sf::Window::setFramerateLimit)
        .def("set_vertical_sync_enabled", &sf::Window::setVerticalSyncEnabled)
        .def("get_settings", &sf::Window::getSettings);
} 