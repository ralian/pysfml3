#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

#include <SFML/System.hpp>

namespace py = pybind11;

void bind_system(py::module_& m) {
    // Time class
    py::class_<sf::Time>(m, "Time")
        .def(py::init<>())
        .def("as_seconds", &sf::Time::asSeconds)
        .def("as_milliseconds", &sf::Time::asMilliseconds)
        .def("as_microseconds", &sf::Time::asMicroseconds)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * float())
        .def(py::self / float())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= float())
        .def(py::self /= float())
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self) */
        .def("__repr__", [](const sf::Time& t) {
            return "<Time: " + std::to_string(t.asSeconds()) + "s>";
        });
    
    // Time utility functions
    m.def("seconds", &sf::seconds, "Create a time value from seconds");
    m.def("milliseconds", &sf::milliseconds, "Create a time value from milliseconds");
    m.def("microseconds", &sf::microseconds, "Create a time value from microseconds");
    
    // Clock class
    py::class_<sf::Clock>(m, "Clock")
        .def(py::init<>())
        .def("get_elapsed_time", &sf::Clock::getElapsedTime)
        .def("restart", &sf::Clock::restart);

    // Angle class
    py::class_<sf::Angle>(m, "Angle") 
        .def(py::init<>())
        .def("as_degrees", &sf::Angle::asDegrees)
        .def("as_radians", &sf::Angle::asRadians)
        .def("wrap_signed", &sf::Angle::wrapSigned)
        .def("wrap_unsigned", &sf::Angle::wrapUnsigned)
        .def("__repr__", [](const sf::Angle& a) {
            return "<Angle: " + std::to_string(a.asDegrees()) + " deg>";
        });
    
    // Vector2 template for different types
    py::class_<sf::Vector2i>(m, "Vector2i")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def_readwrite("x", &sf::Vector2i::x)
        .def_readwrite("y", &sf::Vector2i::y)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * int())
        .def(py::self / int())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= int())
        .def(py::self /= int())
        .def(py::self == py::self)
        .def(py::self != py::self) */
        .def("__repr__", [](const sf::Vector2i& v) {
            return "<Vector2i: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")>";
        });
    
    py::class_<sf::Vector2u>(m, "Vector2u")
        .def(py::init<>())
        .def(py::init<unsigned int, unsigned int>())
        .def_readwrite("x", &sf::Vector2u::x)
        .def_readwrite("y", &sf::Vector2u::y)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self /= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self) */
        .def("__repr__", [](const sf::Vector2u& v) {
            return "<Vector2u: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")>";
        });
    
    py::class_<sf::Vector2f>(m, "Vector2f")
        .def(py::init<>())
        .def(py::init<float, float>())
        .def_readwrite("x", &sf::Vector2f::x)
        .def_readwrite("y", &sf::Vector2f::y)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * float())
        .def(py::self / float())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= float())
        .def(py::self /= float())
        .def(py::self == py::self)
        .def(py::self != py::self) */
        .def("__repr__", [](const sf::Vector2f& v) {
            return "<Vector2f: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")>";
        });
    
    // Vector3 template for different types
    py::class_<sf::Vector3i>(m, "Vector3i")
        .def(py::init<>())
        .def(py::init<int, int, int>())
        .def_readwrite("x", &sf::Vector3i::x)
        .def_readwrite("y", &sf::Vector3i::y)
        .def_readwrite("z", &sf::Vector3i::z)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * int())
        .def(py::self / int())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= int())
        .def(py::self /= int())
        .def(py::self == py::self)
        .def(py::self != py::self) */
        .def("__repr__", [](const sf::Vector3i& v) {
            return "<Vector3i: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")>";
        });
    
    py::class_<sf::Vector3f>(m, "Vector3f")
        .def(py::init<>())
        .def(py::init<float, float, float>())
        .def_readwrite("x", &sf::Vector3f::x)
        .def_readwrite("y", &sf::Vector3f::y)
        .def_readwrite("z", &sf::Vector3f::z)
/*         .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * float())
        .def(py::self / float())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= float())
        .def(py::self /= float())
        .def(py::self == py::self)
        .def(py::self != py::self) */
        .def("__repr__", [](const sf::Vector3f& v) {
            return "<Vector3f: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")>";
        });
} 