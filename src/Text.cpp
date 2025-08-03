#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace py = pybind11;

void bind_text(py::module_& m) {

    // Text class
    py::class_<sf::Text, sf::Drawable, sf::Transformable> text(m, "Text");
    
    text.def(py::init<const sf::Font&, const std::string&, unsigned int>())
        .def("set_string", &sf::Text::setString)
        .def("set_font", py::overload_cast<const sf::Font&>(&sf::Text::setFont))
        .def("set_character_size", &sf::Text::setCharacterSize)
        .def("set_line_spacing", &sf::Text::setLineSpacing)
        .def("set_letter_spacing", &sf::Text::setLetterSpacing)
        .def("set_style", &sf::Text::setStyle)
        .def("set_fill_color", &sf::Text::setFillColor)
        .def("set_outline_color", &sf::Text::setOutlineColor)
        .def("set_outline_thickness", &sf::Text::setOutlineThickness)
        .def("get_string", &sf::Text::getString)
        .def("get_font", &sf::Text::getFont, py::return_value_policy::reference_internal)
        .def("get_character_size", &sf::Text::getCharacterSize)
        .def("get_line_spacing", &sf::Text::getLineSpacing)
        .def("get_letter_spacing", &sf::Text::getLetterSpacing)
        .def("get_style", &sf::Text::getStyle)
        .def("get_fill_color", &sf::Text::getFillColor)
        .def("get_outline_color", &sf::Text::getOutlineColor)
        .def("get_outline_thickness", &sf::Text::getOutlineThickness)
        .def("find_character_pos", &sf::Text::findCharacterPos)
        .def("get_local_bounds", &sf::Text::getLocalBounds)
        .def("get_global_bounds", &sf::Text::getGlobalBounds);
    
    // Text style enum
    py::native_enum<sf::Text::Style>(text, "Style", "enum.IntEnum")
        .value("REGULAR", sf::Text::Regular)
        .value("BOLD", sf::Text::Bold)
        .value("ITALIC", sf::Text::Italic)
        .value("UNDERLINED", sf::Text::Underlined)
        .value("STRIKETHROUGH", sf::Text::StrikeThrough)
        .export_values()
        .finalize();
}
