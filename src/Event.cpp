#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Window/Event.hpp>

namespace py = pybind11;

void bind_event(py::module_& m) {

    // Event Class (nests all event types)
    // we will expose is() and getIf() but only after defining each event type
    py::class_<sf::Event> event(m, "Event");

    py::class_<sf::Event::Closed>(event, "Closed");
    py::class_<sf::Event::FocusGained>(event, "FocusGained");
    py::class_<sf::Event::FocusLost>(event, "FocusLost");
    py::class_<sf::Event::JoystickButtonPressed>(event, "JoystickButtonPressed")
        .def_readonly("joystick_id", &sf::Event::JoystickButtonPressed::joystickId)
        .def_readonly("button", &sf::Event::JoystickButtonPressed::button);
    py::class_<sf::Event::JoystickButtonReleased>(event, "JoystickButtonReleased")
        .def_readonly("joystick_id", &sf::Event::JoystickButtonReleased::joystickId)
        .def_readonly("button", &sf::Event::JoystickButtonReleased::button);
    py::class_<sf::Event::JoystickConnected>(event, "JoystickConnected")
        .def_readonly("joystick_id", &sf::Event::JoystickConnected::joystickId);
    py::class_<sf::Event::JoystickDisconnected>(event, "JoystickDisconnected")
        .def_readonly("joystick_id", &sf::Event::JoystickDisconnected::joystickId);
        py::class_<sf::Event::JoystickMoved>(event, "JoystickMoved")
        .def_readonly("joystick_id", &sf::Event::JoystickMoved::joystickId)
        .def_readonly("axis", &sf::Event::JoystickMoved::axis)
        .def_readonly("position", &sf::Event::JoystickMoved::position);
    py::class_<sf::Event::KeyPressed>(event, "KeyPressed")
        .def_readonly("code", &sf::Event::KeyPressed::code)
        .def_readonly("scancode", &sf::Event::KeyPressed::scancode)
        .def_readonly("alt", &sf::Event::KeyPressed::alt)
        .def_readonly("control", &sf::Event::KeyPressed::control)
        .def_readonly("shift", &sf::Event::KeyPressed::shift)
        .def_readonly("system", &sf::Event::KeyPressed::system);
    py::class_<sf::Event::KeyReleased>(event, "KeyReleased")
        .def_readonly("code", &sf::Event::KeyReleased::code)
        .def_readonly("scancode", &sf::Event::KeyReleased::scancode)
        .def_readonly("alt", &sf::Event::KeyReleased::alt)
        .def_readonly("control", &sf::Event::KeyReleased::control)
        .def_readonly("shift", &sf::Event::KeyReleased::shift)
        .def_readonly("system", &sf::Event::KeyReleased::system);
    py::class_<sf::Event::MouseButtonPressed>(event, "MouseButtonPressed")
        .def_readonly("button", &sf::Event::MouseButtonPressed::button)
        .def_readonly("position", &sf::Event::MouseButtonPressed::position);
    py::class_<sf::Event::MouseButtonReleased>(event, "MouseButtonReleased")
        .def_readonly("button", &sf::Event::MouseButtonReleased::button)
        .def_readonly("position", &sf::Event::MouseButtonReleased::position);
    py::class_<sf::Event::MouseEntered>(event, "MouseEntered");
    py::class_<sf::Event::MouseLeft>(event, "MouseLeft");
    py::class_<sf::Event::MouseMoved>(event, "MouseMoved")
        .def_readonly("position", &sf::Event::MouseMoved::position);
    py::class_<sf::Event::MouseMovedRaw>(event, "MouseMovedRaw")
        .def_readonly("delta", &sf::Event::MouseMovedRaw::delta);
    py::class_<sf::Event::MouseWheelScrolled>(event, "MouseWheelScrolled")
        .def_readonly("wheel", &sf::Event::MouseWheelScrolled::wheel)
        .def_readonly("delta", &sf::Event::MouseWheelScrolled::delta)
        .def_readonly("position", &sf::Event::MouseWheelScrolled::position);
    py::class_<sf::Event::Resized>(event, "Resized")
        .def_readonly("size", &sf::Event::Resized::size);
    py::class_<sf::Event::SensorChanged>(event, "SensorChanged")
        .def_readonly("type", &sf::Event::SensorChanged::type)
        .def_readonly("value", &sf::Event::SensorChanged::value);
    py::class_<sf::Event::TextEntered>(event, "TextEntered")
        .def_readonly("unicode", &sf::Event::TextEntered::unicode);
    py::class_<sf::Event::TouchBegan>(event, "TouchBegan")
        .def_readonly("finger", &sf::Event::TouchBegan::finger)
        .def_readonly("position", &sf::Event::TouchBegan::position);
    py::class_<sf::Event::TouchEnded>(event, "TouchEnded")
        .def_readonly("finger", &sf::Event::TouchEnded::finger)
        .def_readonly("position", &sf::Event::TouchEnded::position);
    py::class_<sf::Event::TouchMoved>(event, "TouchMoved")
        .def_readonly("finger", &sf::Event::TouchMoved::finger)
        .def_readonly("position", &sf::Event::TouchMoved::position);

    const py::type
    TClosed = py::type::of<sf::Event::Closed>(),
    TFocusGained = py::type::of<sf::Event::FocusGained>(),
    TFocusLost = py::type::of<sf::Event::FocusLost>(),
    TJoystickButtonPressed = py::type::of<sf::Event::JoystickButtonPressed>(),
    TJoystickButtonReleased = py::type::of<sf::Event::JoystickButtonReleased>(),
    TJoystickConnected = py::type::of<sf::Event::JoystickConnected>(),
    TJoystickDisconnected = py::type::of<sf::Event::JoystickDisconnected>(),
    TJoystickMoved = py::type::of<sf::Event::JoystickMoved>(),
    TKeyPressed = py::type::of<sf::Event::KeyPressed>(),
    TKeyReleased = py::type::of<sf::Event::KeyReleased>(),
    TMouseButtonPressed = py::type::of<sf::Event::MouseButtonPressed>(),
    TMouseButtonReleased = py::type::of<sf::Event::MouseButtonReleased>(),
    TMouseEntered = py::type::of<sf::Event::MouseEntered>(),
    TMouseLeft = py::type::of<sf::Event::MouseLeft>(),
    TMouseMoved = py::type::of<sf::Event::MouseMoved>(),
    TMouseMovedRaw = py::type::of<sf::Event::MouseMovedRaw>(),
    TMouseWheelScrolled = py::type::of<sf::Event::MouseWheelScrolled>(),
    TResized = py::type::of<sf::Event::Resized>(),
    TSensorChanged = py::type::of<sf::Event::SensorChanged>(),
    TTextEntered = py::type::of<sf::Event::TextEntered>(),
    TTouchBegan = py::type::of<sf::Event::TouchBegan>(),
    TTouchEnded = py::type::of<sf::Event::TouchEnded>(),
    TTouchMoved = py::type::of<sf::Event::TouchMoved>();

    // This might be unnecessary since get_if should return a none in the variant if is_type would yield false
    event.def("is_type", [=](const sf::Event& e, const py::type& t) -> bool {
        if (t == TClosed) return e.is<sf::Event::Closed>();
        if (t == TFocusGained) return e.is<sf::Event::FocusGained>();
        if (t == TFocusLost) return e.is<sf::Event::FocusLost>();
        if (t == TJoystickButtonPressed) return e.is<sf::Event::JoystickButtonPressed>();
        if (t == TJoystickButtonReleased) return e.is<sf::Event::JoystickButtonReleased>();
        if (t == TJoystickConnected) return e.is<sf::Event::JoystickConnected>();
        if (t == TJoystickDisconnected) return e.is<sf::Event::JoystickDisconnected>();
        if (t == TJoystickMoved) return e.is<sf::Event::JoystickMoved>();
        if (t == TKeyPressed) return e.is<sf::Event::KeyPressed>();
        if (t == TKeyReleased) return e.is<sf::Event::KeyReleased>();
        if (t == TMouseButtonPressed) return e.is<sf::Event::MouseButtonPressed>();
        if (t == TMouseButtonReleased) return e.is<sf::Event::MouseButtonReleased>();
        if (t == TMouseEntered) return e.is<sf::Event::MouseEntered>();
        if (t == TMouseLeft) return e.is<sf::Event::MouseLeft>();
        if (t == TMouseMoved) return e.is<sf::Event::MouseMoved>();
        if (t == TMouseMovedRaw) return e.is<sf::Event::MouseMovedRaw>();
        if (t == TMouseWheelScrolled) return e.is<sf::Event::MouseWheelScrolled>();
        if (t == TResized) return e.is<sf::Event::Resized>();
        if (t == TSensorChanged) return e.is<sf::Event::SensorChanged>();
        if (t == TTextEntered) return e.is<sf::Event::TextEntered>();
        if (t == TTouchBegan) return e.is<sf::Event::TouchBegan>();
        if (t == TTouchEnded) return e.is<sf::Event::TouchEnded>();
        if (t == TTouchMoved) return e.is<sf::Event::TouchMoved>();
        return false;
    },
    py::return_value_policy::move);

    // I'm not sure whether to be proud or afraid.
    event.def("get_if", [=](const sf::Event& e, const py::type& t)
        -> std::variant<
            const sf::Event::Closed*,
            const sf::Event::FocusGained*,
            const sf::Event::FocusLost*,
            const sf::Event::JoystickButtonPressed*,
            const sf::Event::JoystickButtonReleased*,
            const sf::Event::JoystickConnected*,
            const sf::Event::JoystickDisconnected*,
            const sf::Event::JoystickMoved*,
            const sf::Event::KeyPressed*, 
            const sf::Event::KeyReleased*,
            const sf::Event::MouseButtonPressed*,
            const sf::Event::MouseButtonReleased*,
            const sf::Event::MouseEntered*,
            const sf::Event::MouseLeft*,
            const sf::Event::MouseMoved*,
            const sf::Event::MouseMovedRaw*,
            const sf::Event::MouseWheelScrolled*,
            const sf::Event::Resized*,
            const sf::Event::SensorChanged*,
            const sf::Event::TextEntered*,
            const sf::Event::TouchBegan*,
            const sf::Event::TouchEnded*,
            const sf::Event::TouchMoved*,
        py::none>
    {
        if (t == TClosed) return {e.getIf<sf::Event::Closed>()};
        if (t == TFocusGained) return {e.getIf<sf::Event::FocusGained>()};
        if (t == TFocusLost) return {e.getIf<sf::Event::FocusLost>()};
        if (t == TJoystickButtonPressed) return {e.getIf<sf::Event::JoystickButtonPressed>()};
        if (t == TJoystickButtonReleased) return {e.getIf<sf::Event::JoystickButtonReleased>()};
        if (t == TJoystickConnected) return {e.getIf<sf::Event::JoystickConnected>()};
        if (t == TJoystickDisconnected) return {e.getIf<sf::Event::JoystickDisconnected>()};
        if (t == TJoystickMoved) return {e.getIf<sf::Event::JoystickMoved>()};
        if (t == TKeyPressed) return {e.getIf<sf::Event::KeyPressed>()};
        if (t == TKeyReleased) return {e.getIf<sf::Event::KeyReleased>()};
        if (t == TMouseButtonPressed) return {e.getIf<sf::Event::MouseButtonPressed>()};
        if (t == TMouseButtonReleased) return {e.getIf<sf::Event::MouseButtonReleased>()};
        if (t == TMouseEntered) return {e.getIf<sf::Event::MouseEntered>()};
        if (t == TMouseLeft) return {e.getIf<sf::Event::MouseLeft>()};
        if (t == TMouseMoved) return {e.getIf<sf::Event::MouseMoved>()};
        if (t == TMouseMovedRaw) return {e.getIf<sf::Event::MouseMovedRaw>()};
        if (t == TMouseWheelScrolled) return {e.getIf<sf::Event::MouseWheelScrolled>()};
        if (t == TResized) return {e.getIf<sf::Event::Resized>()};
        if (t == TSensorChanged) return {e.getIf<sf::Event::SensorChanged>()};
        if (t == TTextEntered) return {e.getIf<sf::Event::TextEntered>()};
        if (t == TTouchBegan) return {e.getIf<sf::Event::TouchBegan>()};
        if (t == TTouchEnded) return {e.getIf<sf::Event::TouchEnded>()};
        if (t == TTouchMoved) return {e.getIf<sf::Event::TouchMoved>()};
        return {py::none()};
    },
    py::return_value_policy::move);

    // Somewhat surprisingly, this variant returns the expected subtype but subsequent
    // isinstance(e, type) or 'is' operator checks fail. I'm leaving this in since it
    // *should* be correct but right now it's useless.
    event.def("get_subtype", [=](const sf::Event& e)
        -> std::variant<
            const sf::Event::Closed*,
            const sf::Event::FocusGained*,
            const sf::Event::FocusLost*,
            const sf::Event::JoystickButtonPressed*,
            const sf::Event::JoystickButtonReleased*,
            const sf::Event::JoystickConnected*,
            const sf::Event::JoystickDisconnected*,
            const sf::Event::JoystickMoved*,
            const sf::Event::KeyPressed*, 
            const sf::Event::KeyReleased*,
            const sf::Event::MouseButtonPressed*,
            const sf::Event::MouseButtonReleased*,
            const sf::Event::MouseEntered*,
            const sf::Event::MouseLeft*,
            const sf::Event::MouseMoved*,
            const sf::Event::MouseMovedRaw*,
            const sf::Event::MouseWheelScrolled*,
            const sf::Event::Resized*,
            const sf::Event::SensorChanged*,
            const sf::Event::TextEntered*,
            const sf::Event::TouchBegan*,
            const sf::Event::TouchEnded*,
            const sf::Event::TouchMoved*,
        py::none>
    {
        if (e.is<sf::Event::Closed>()) return {e.getIf<sf::Event::Closed>()};
        if (e.is<sf::Event::FocusGained>()) return {e.getIf<sf::Event::FocusGained>()};
        if (e.is<sf::Event::FocusLost>()) return {e.getIf<sf::Event::FocusLost>()};
        if (e.is<sf::Event::JoystickButtonPressed>()) return {e.getIf<sf::Event::JoystickButtonPressed>()};
        if (e.is<sf::Event::JoystickButtonReleased>()) return {e.getIf<sf::Event::JoystickButtonReleased>()};
        if (e.is<sf::Event::JoystickConnected>()) return {e.getIf<sf::Event::JoystickConnected>()};
        if (e.is<sf::Event::JoystickDisconnected>()) return {e.getIf<sf::Event::JoystickDisconnected>()};
        if (e.is<sf::Event::JoystickMoved>()) return {e.getIf<sf::Event::JoystickMoved>()};
        if (e.is<sf::Event::KeyPressed>()) return {e.getIf<sf::Event::KeyPressed>()};
        if (e.is<sf::Event::KeyReleased>()) return {e.getIf<sf::Event::KeyReleased>()};
        if (e.is<sf::Event::MouseButtonPressed>()) return {e.getIf<sf::Event::MouseButtonPressed>()};
        if (e.is<sf::Event::MouseButtonReleased>()) return {e.getIf<sf::Event::MouseButtonReleased>()};
        if (e.is<sf::Event::MouseEntered>()) return {e.getIf<sf::Event::MouseEntered>()};
        if (e.is<sf::Event::MouseLeft>()) return {e.getIf<sf::Event::MouseLeft>()};
        if (e.is<sf::Event::MouseMoved>()) return {e.getIf<sf::Event::MouseMoved>()};
        if (e.is<sf::Event::MouseMovedRaw>()) return {e.getIf<sf::Event::MouseMovedRaw>()};
        if (e.is<sf::Event::MouseWheelScrolled>()) return {e.getIf<sf::Event::MouseWheelScrolled>()};
        if (e.is<sf::Event::Resized>()) return {e.getIf<sf::Event::Resized>()};
        if (e.is<sf::Event::SensorChanged>()) return {e.getIf<sf::Event::SensorChanged>()};
        if (e.is<sf::Event::TextEntered>()) return {e.getIf<sf::Event::TextEntered>()};
        if (e.is<sf::Event::TouchBegan>()) return {e.getIf<sf::Event::TouchBegan>()};
        if (e.is<sf::Event::TouchEnded>()) return {e.getIf<sf::Event::TouchEnded>()};
        if (e.is<sf::Event::TouchMoved>()) return {e.getIf<sf::Event::TouchMoved>()};
        return {py::none()};
    },
    py::return_value_policy::move);
}
