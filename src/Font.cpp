#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Graphics/Font.hpp>

namespace py = pybind11;

void bind_font(py::module_& m) {
    // TODO move this...
    py::class_<std::filesystem::path>(m, "Path")
        .def(py::init<std::string>());
    py::implicitly_convertible<std::string, std::filesystem::path>();

    // Font class
    py::class_<sf::Font>(m, "Font")
        .def(py::init<>())
        .def("open_from_file", &sf::Font::openFromFile)
        .def("open_from_memory", [](sf::Font& font, py::buffer b) {
            py::buffer_info info = b.request();
            return font.openFromMemory(info.ptr, info.size);
        })
        .def("get_info", &sf::Font::getInfo)
        .def("get_glyph", &sf::Font::getGlyph)
        // odd - TODO?
        //.def("get_kerning", &sf::Font::getKerning)
        .def("get_line_spacing", &sf::Font::getLineSpacing)
        .def("get_underline_position", &sf::Font::getUnderlinePosition)
        .def("get_underline_thickness", &sf::Font::getUnderlineThickness)
        .def("get_texture", &sf::Font::getTexture, py::return_value_policy::reference_internal);
}
