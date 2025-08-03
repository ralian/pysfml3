#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/chrono.h>

void bind_system(pybind11::module_& m);
void bind_window(pybind11::module_& m);
void bind_graphics(pybind11::module_& m);
void bind_event(pybind11::module_& m);
void bind_keyboard(pybind11::module_& m);
void bind_mouse(pybind11::module_& m);
void bind_font(pybind11::module_& m);
void bind_text(pybind11::module_& m);

PYBIND11_MODULE(pysfml3, m) {
    m.doc() = "Python bindings for SFML (Simple and Fast Multimedia Library) v3";
    m.attr("__version__") = PYBIND11_STRINGIFY(VERSION_INFO);

    // TODO these need organized better
    bind_system(m);
    bind_window(m);
    bind_graphics(m);

    bind_event(m);
    bind_keyboard(m);
    bind_mouse(m);
    bind_font(m);
    bind_text(m);
}
