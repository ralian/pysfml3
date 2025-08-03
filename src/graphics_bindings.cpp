#include <cstdint>

#include <pybind11/pybind11.h>

#include <pybind11/native_enum.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <SFML/Graphics.hpp>

namespace py = pybind11;

void bind_graphics(py::module_& m) {
    // Color class
    py::class_<sf::Color>(m, "Color")
        .def(py::init<>())
        .def(py::init<std::uint8_t, std::uint8_t, std::uint8_t>())
        .def(py::init<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>())
        .def(py::init<std::uint32_t>())
        .def_readwrite("r", &sf::Color::r)
        .def_readwrite("g", &sf::Color::g)
        .def_readwrite("b", &sf::Color::b)
        .def_readwrite("a", &sf::Color::a)
        .def("to_integer", &sf::Color::toInteger)
        .def(py::self + py::self)
        .def(py::self * py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__repr__", [](const sf::Color& c) {
            return "<Color: (" + std::to_string(c.r) + ", " + std::to_string(c.g) + 
                   ", " + std::to_string(c.b) + ", " + std::to_string(c.a) + ")>";
        })
        .def_readonly_static("BLACK", &sf::Color::Black)
        .def_readonly_static("WHITE", &sf::Color::White)
        .def_readonly_static("RED", &sf::Color::Red)
        .def_readonly_static("GREEN", &sf::Color::Green)
        .def_readonly_static("BLUE", &sf::Color::Blue)
        .def_readonly_static("YELLOW", &sf::Color::Yellow)
        .def_readonly_static("MAGENTA", &sf::Color::Magenta)
        .def_readonly_static("CYAN", &sf::Color::Cyan)
        .def_readonly_static("TRANSPARENT", &sf::Color::Transparent);
    
    // IntRect and FloatRect
    py::class_<sf::Rect<int>>(m, "IntRect")
        .def(py::init<>())
        .def(py::init<sf::Vector2i, sf::Vector2i>())
        .def_readwrite("position", &sf::Rect<int>::position)
        .def_readwrite("size", &sf::Rect<int>::size)
        //TODO
        //.def("contains", py::overload_cast<bool>(&sf::Rect<int>::contains, py::const_))
        //.def("findIntersection", py::overload_cast<const sf::Rect<int>&>(&sf::Rect<int>::findIntersection, py::const_))
        .def(py::self == py::self)
        .def(py::self != py::self);
    
    py::class_<sf::Rect<float>>(m, "FloatRect")
        .def(py::init<>())
        .def(py::init<sf::Vector2f, sf::Vector2f>())
        .def_readwrite("position", &sf::Rect<float>::position)
        .def_readwrite("size", &sf::Rect<float>::size)
        //TODO
        //.def("contains", py::overload_cast<bool>(&sf::Rect<float>::contains, py::const_))
        //.def("findIntersection", py::overload_cast<const sf::Rect<float>&>(&sf::Rect<float>::findIntersection, py::const_))
        .def(py::self == py::self)
        .def(py::self != py::self);

    // Transform class
    py::class_<sf::Transform>(m, "Transform")
        .def(py::init<>())
        .def(py::init<float, float, float, float, float, float, float, float, float>())
        .def("get_matrix", &sf::Transform::getMatrix)
        .def("get_inverse", &sf::Transform::getInverse)
        .def("transform_point", py::overload_cast<sf::Vector2f>(&sf::Transform::transformPoint, py::const_))
        .def("transform_rect", py::overload_cast<const sf::Rect<float>&>(&sf::Transform::transformRect, py::const_))
        .def("combine", &sf::Transform::combine)
        .def("translate", py::overload_cast<sf::Vector2f>(&sf::Transform::translate))
        .def("rotate", py::overload_cast<sf::Angle>(&sf::Transform::rotate))
        .def("rotate", py::overload_cast<sf::Angle, sf::Vector2f>(&sf::Transform::rotate))
        .def("scale", py::overload_cast<sf::Vector2f>(&sf::Transform::scale)) // TODO maybe these should be const in sfml?
        .def("scale", py::overload_cast<sf::Vector2f, sf::Vector2f>(&sf::Transform::scale))
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def_readonly_static("IDENTITY", &sf::Transform::Identity);
    
    // Transformable class
    py::class_<sf::Transformable>(m, "Transformable")
        .def(py::init<>())
        .def("set_position", &sf::Transformable::setPosition)
        .def("set_rotation", &sf::Transformable::setRotation)
        .def("set_scale", &sf::Transformable::setScale)
        .def("set_origin", &sf::Transformable::setOrigin)
        .def("get_position", &sf::Transformable::getPosition)
        .def("get_rotation", &sf::Transformable::getRotation)
        .def("get_scale", &sf::Transformable::getScale)
        .def("get_origin", &sf::Transformable::getOrigin)
        .def("move", &sf::Transformable::move)
        .def("rotate", &sf::Transformable::rotate)
        .def("scale", &sf::Transformable::scale)
        .def("get_transform", py::overload_cast<>(&sf::Transformable::getTransform, py::const_))
        .def("get_inverse_transform", py::overload_cast<>(&sf::Transformable::getInverseTransform, py::const_));
    
    // Image class
    py::class_<sf::Image>(m, "Image")
        .def(py::init<>()) // TODO constructors
        .def("load_from_file", &sf::Image::loadFromFile)
        .def("load_from_memory", [](sf::Image& img, py::buffer b) {
            py::buffer_info info = b.request();
            return img.loadFromMemory(info.ptr, info.size);
        })
        .def("save_to_file", &sf::Image::saveToFile)
        .def("get_size", &sf::Image::getSize)
        .def("create_mask_from_color", &sf::Image::createMaskFromColor)
        .def("copy", py::overload_cast<const sf::Image&, sf::Vector2u, const sf::Rect<int>&, bool>(&sf::Image::copy))
        .def("set_pixel", &sf::Image::setPixel)
        .def("get_pixel", &sf::Image::getPixel) // TODO needs const work here
        .def("get_pixels_ptr", &sf::Image::getPixelsPtr, py::return_value_policy::reference)
        .def("flip_horizontally", &sf::Image::flipHorizontally)
        .def("flip_vertically", &sf::Image::flipVertically);
    
    // Texture class
    py::class_<sf::Texture>(m, "Texture")
        .def(py::init<>()) // TODO constructors
        .def("load_from_file", &sf::Texture::loadFromFile)
        // TODO
        //.def("load_from_memory", [](sf::Texture& tex, py::buffer b, const sf::IntRect& area = sf::IntRect()) {
        //    py::buffer_info info = b.request();
        //    return tex.loadFromMemory(info.ptr, info.size, area);
        //})
        .def("load_from_stream", &sf::Texture::loadFromStream)
        .def("load_from_image", &sf::Texture::loadFromImage)
        .def("get_size", &sf::Texture::getSize)
        .def("copy_to_image", &sf::Texture::copyToImage)
        .def("update", py::overload_cast<const std::uint8_t*>(&sf::Texture::update))
        .def("update", py::overload_cast<const std::uint8_t*, sf::Vector2u, sf::Vector2u>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Texture&>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Texture&, sf::Vector2u>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Image&>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Image&, sf::Vector2u>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Window&>(&sf::Texture::update))
        .def("update", py::overload_cast<const sf::Window&, sf::Vector2u>(&sf::Texture::update))
        .def("set_smooth", &sf::Texture::setSmooth)
        .def("is_smooth", &sf::Texture::isSmooth)
        .def("is_srgb", &sf::Texture::isSrgb)
        .def("set_repeated", &sf::Texture::setRepeated)
        .def("is_repeated", &sf::Texture::isRepeated)
        .def("generate_mipmap", &sf::Texture::generateMipmap)
        .def("swap", &sf::Texture::swap)
        .def("get_native_handle", &sf::Texture::getNativeHandle)
        .def_static("bind", py::overload_cast<const sf::Texture*, sf::CoordinateType>(&sf::Texture::bind))
        .def_static("get_maximum_size", &sf::Texture::getMaximumSize);
    
    // Texture coordinate type enum
    py::native_enum<sf::CoordinateType>(m, "TextureCoordinateType", "enum.IntEnum")
        .value("NORMALIZED", sf::CoordinateType::Normalized)
        .value("PIXELS", sf::CoordinateType::Pixels)
        .export_values()
        .finalize();
    
    // Vertex class
    py::class_<sf::Vertex>(m, "Vertex")
        .def(py::init<>()) // TODO remove? Make defaults for the other?
        .def(py::init<sf::Vector2f, sf::Color, sf::Vector2f>())
        .def_readwrite("position", &sf::Vertex::position)
        .def_readwrite("color", &sf::Vertex::color)
        .def_readwrite("tex_coords", &sf::Vertex::texCoords);
    
    // PrimitiveType enum
    py::native_enum<sf::PrimitiveType>(m, "PrimitiveType", "enum.IntEnum")
        .value("POINTS", sf::PrimitiveType::Points)
        .value("LINES", sf::PrimitiveType::Lines)
        .value("LINE_STRIP", sf::PrimitiveType::LineStrip)
        .value("TRIANGLES", sf::PrimitiveType::Triangles)
        .value("TRIANGLE_STRIP", sf::PrimitiveType::TriangleStrip)
        .value("TRIANGLE_FAN", sf::PrimitiveType::TriangleFan)
        .export_values()
        .finalize();
    
    // Drawable base class
    py::class_<sf::Drawable>(m, "Drawable");
    
    // Sprite class
    py::class_<sf::Sprite, sf::Drawable, sf::Transformable>(m, "Sprite")
        .def(py::init<const sf::Texture&>())
        .def(py::init<const sf::Texture&, const sf::IntRect&>())
        .def("set_texture", py::overload_cast<const sf::Texture&, bool>(&sf::Sprite::setTexture), py::arg("texture"), py::arg("reset_rect") = false)
        .def("set_texture_rect", &sf::Sprite::setTextureRect)
        .def("set_color", &sf::Sprite::setColor)
        .def("get_texture", &sf::Sprite::getTexture, py::return_value_policy::reference_internal)
        .def("get_texture_rect", &sf::Sprite::getTextureRect)
        .def("get_color", &sf::Sprite::getColor)
        .def("get_local_bounds", &sf::Sprite::getLocalBounds)
        .def("get_global_bounds", &sf::Sprite::getGlobalBounds);
    
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
    
    // Text class
    py::class_<sf::Text, sf::Drawable, sf::Transformable>(m, "Text")
        .def(py::init<const sf::Font&, const std::string&, unsigned int>())
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
    py::native_enum<sf::Text::Style>(m, "TextStyle", "enum.IntEnum")
        .value("REGULAR", sf::Text::Regular)
        .value("BOLD", sf::Text::Bold)
        .value("ITALIC", sf::Text::Italic)
        .value("UNDERLINED", sf::Text::Underlined)
        .value("STRIKETHROUGH", sf::Text::StrikeThrough)
        .export_values()
        .finalize();
    
    // RenderStates class
    py::class_<sf::RenderStates>(m, "RenderStates")
        .def(py::init<>())
        .def(py::init<const sf::BlendMode&>())
        .def(py::init<const sf::StencilMode&>())
        .def(py::init<const sf::Transform&>())
        .def(py::init<const sf::Texture*>())
        .def(py::init<const sf::Shader*>())
        .def(py::init<const sf::BlendMode&, const sf::StencilMode&, const sf::Transform&, sf::CoordinateType, const sf::Texture*, const sf::Shader*>())
        .def_readwrite("blend_mode", &sf::RenderStates::blendMode)
        .def_readwrite("stencil_mode", &sf::RenderStates::stencilMode)
        .def_readwrite("transform", &sf::RenderStates::transform)
        .def_readwrite("texture", &sf::RenderStates::texture)
        .def_readwrite("shader", &sf::RenderStates::shader)
        .def_readonly_static("DEFAULT", &sf::RenderStates::Default);
    
    // RenderTarget base class
    py::class_<sf::RenderTarget>(m, "RenderTarget")
        .def("clear", py::overload_cast<sf::Color>(&sf::RenderTarget::clear))
        .def("clear", py::overload_cast<sf::Color, sf::StencilValue>(&sf::RenderTarget::clear))
        .def("set_view", &sf::RenderTarget::setView)
        .def("get_view", &sf::RenderTarget::getView, py::return_value_policy::reference_internal)
        .def("get_default_view", &sf::RenderTarget::getDefaultView, py::return_value_policy::reference_internal)
        .def("get_viewport", &sf::RenderTarget::getViewport)
        .def("map_pixel_to_coords", py::overload_cast<sf::Vector2i>(&sf::RenderTarget::mapPixelToCoords, py::const_))
        .def("map_pixel_to_coords", py::overload_cast<sf::Vector2i, const sf::View&>(&sf::RenderTarget::mapPixelToCoords, py::const_))
        .def("map_coords_to_pixel", py::overload_cast<sf::Vector2f>(&sf::RenderTarget::mapCoordsToPixel, py::const_))
        .def("map_coords_to_pixel", py::overload_cast<sf::Vector2f, const sf::View&>(&sf::RenderTarget::mapCoordsToPixel, py::const_))
        .def("draw", py::overload_cast<const sf::Drawable&, const sf::RenderStates&>(&sf::RenderTarget::draw)) // TODO overloads?
        .def("get_size", &sf::RenderTarget::getSize)
        .def("set_active", &sf::RenderTarget::setActive)
        .def("push_gl_states", &sf::RenderTarget::pushGLStates)
        .def("pop_gl_states", &sf::RenderTarget::popGLStates)
        .def("reset_gl_states", &sf::RenderTarget::resetGLStates);
    
    // RenderWindow class
    py::class_<sf::RenderWindow, sf::RenderTarget, sf::Window>(m, "RenderWindow")
        .def(py::init<>())
        .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State, const sf::ContextSettings&>())
        .def(py::init<sf::VideoMode, const std::string&, sf::State, const sf::ContextSettings&>())
        //.def(py::init<sf::WindowHandle, const sf::ContextSettings&>()) // TODO borken
        .def("get_size", &sf::RenderWindow::getSize);
        // TODO lots missing here
    
    // View class
    py::class_<sf::View>(m, "View")
        .def(py::init<>())
        .def(py::init<const sf::FloatRect&>())
        .def(py::init<const sf::Vector2f&, const sf::Vector2f&>())
        .def("set_center", &sf::View::setCenter)
        .def("set_size", &sf::View::setSize)
        .def("set_rotation", &sf::View::setRotation)
        .def("set_viewport", &sf::View::setViewport)
        .def("get_center", &sf::View::getCenter)
        .def("get_size", &sf::View::getSize)
        .def("get_rotation", &sf::View::getRotation)
        .def("get_viewport", &sf::View::getViewport)
        .def("move", &sf::View::move)
        .def("rotate", &sf::View::rotate)
        .def("zoom", &sf::View::zoom)
        .def("get_transform", &sf::View::getTransform)
        .def("get_inverse_transform", &sf::View::getInverseTransform);
} 