// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @author      Eduardo Aguiar <aguiar@protonmail.ch>
// @copyright   Copyright (c) 2025 Eduardo Aguiar
//
// This file is part of Allegro++.
// 
// Allegro++ is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Allegro++. If not, see <https://www.gnu.org/licenses/>.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "color.hpp"

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief <i>color</i> implementation class
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class color::impl
{
public:
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Constructors and destructor
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  impl () = default;
  impl (component_type, component_type, component_type);
  impl (component_type, component_type, component_type, component_type);
  impl (const impl&) = delete;
  impl (impl&&) = delete;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Operators
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  impl& operator= (const impl&) = delete;
  impl& operator= (impl&&) = delete;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  //! \brief Get implementation pointer
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  ALLEGRO_COLOR
  get_implementation () const
  {
      return obj_;
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Prototypes
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  std::tuple <component_type, component_type, component_type> get_rgb () const;
  std::tuple <component_type, component_type, component_type, component_type> get_rgba () const;
  std::string get_name () const;
  std::string get_html () const;

private:
  //! \brief Allegro color object
  ALLEGRO_COLOR obj_;
};

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param r Red component
//! \param g Green component
//! \param b Blue component
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color::impl::impl (component_type r, component_type g, component_type b)
{
    obj_ = al_map_rgb (r, g, b);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param r Red component
//! \param g Green component
//! \param b Blue component
//! \param a Alpha component
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color::impl::impl (component_type r, component_type g, component_type b, component_type a)
{
    obj_ = al_map_rgba (r, g, b, a);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color RGB components
//! \return RGB components
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::tuple <color::component_type, color::component_type, color::component_type>
color::impl::get_rgb () const
{
    component_type r, g, b;
    al_unmap_rgb (obj_, &r, &g, &b);
    
    return std::make_tuple (r, g, b);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color RGBA components
//! \return RGBA components
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::tuple <color::component_type, color::component_type, color::component_type, color::component_type>
color::impl::get_rgba () const
{
    component_type r, g, b, a;
    al_unmap_rgba (obj_, &r, &g, &b, &a);
    
    return std::make_tuple (r, g, b, a);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color name
//! \return Color name
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::string
color::impl::get_name () const
{
  std::string name;

  component_type r, g, b;
  al_unmap_rgb (obj_, &r, &g, &b);

  const char *s = al_color_rgb_to_name (
    static_cast <float> (r) / 255,
    static_cast <float> (g) / 255,
    static_cast <float> (b) / 255
  );

  if (s)
    name = s;

  return name;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color HTML string
//! \return HTML string
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::string
color::impl::get_html () const
{
  char buffer[16] = {0};

  component_type r, g, b;
  al_unmap_rgb (obj_, &r, &g, &b);

  al_color_rgb_to_html (
    static_cast <float> (r) / 255,
    static_cast <float> (g) / 255,
    static_cast <float> (b) / 255,
    buffer
  );

  return buffer;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color::color ()
  : impl_ (std::make_shared <impl> ())
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param r Red component
//! \param g Green component
//! \param b Blue component
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color::color (component_type r, component_type g, component_type b)
  : impl_ (std::make_shared <impl> (r, g, b))
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param r Red component
//! \param g Green component
//! \param b Blue component
//! \param a Alpha component
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color::color (component_type r, component_type g, component_type b, component_type a)
  : impl_ (std::make_shared <impl> (r, g, b, a))
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color RGB components
//! \return RGB components
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::tuple <color::component_type, color::component_type, color::component_type>
color::get_rgb () const
{
    return impl_->get_rgb ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color RGBA components
//! \return RGBA components
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::tuple <color::component_type, color::component_type, color::component_type, color::component_type>
color::get_rgba () const
{
    return impl_->get_rgba ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color name
//! \return Color name
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::string
color::get_name () const
{
   return impl_->get_name ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get color HTML string
//! \return HTML string
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::string
color::get_html () const
{
   return impl_->get_html ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Get implementation pointer
//! \return Allegro color
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
ALLEGRO_COLOR
color::get_implementation () const
{
   return impl_->get_implementation ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by color name
//! \param name Color name
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_name (const std::string& name)
{
    float r, g, b;
    al_color_name_to_rgb (name.c_str (), &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by HTML string
//! \param html HTML string
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_html (const std::string& html)
{
    float r, g, b;
    al_color_html_to_rgb (html.c_str (), &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by CMYK components
//! \param c C component value
//! \param m M component value
//! \param y Y component value
//! \param k K component value
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_cmyk (float c, float m, float y, float k)
{
    float r, g, b;
    al_color_cmyk_to_rgb (c, m, y, k, &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by HSL components
//! \param h H component value
//! \param s S component value
//! \param l L component value
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_hsl (float h, float s, float l)
{
    float r, g, b;
    al_color_hsl_to_rgb (h, s, l, &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
    
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by HSV components
//! \param h H component value
//! \param s S component value
//! \param v V component value
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_hsv (float h, float s, float v)
{
    float r, g, b;
    al_color_hsv_to_rgb (h, s, v, &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
    
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by YUV components
//! \param y Y component value
//! \param u U component value
//! \param v V component value
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_yuv (float y, float u, float v)
{
    float r, g, b;
    al_color_yuv_to_rgb (y, u, v, &r, &g, &b);
    
    return color (r * 255, g * 255, b * 255);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by RGB components
//! \param r R component value (0..1)
//! \param g G component value (0..1)
//! \param b B component value (0..1)
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_rgb (float r, float g, float b)
{
    return color (r * 255, g * 255, b * 255);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Create color by RGBA components
//! \param r R component value (0..1)
//! \param g G component value (0..1)
//! \param b B component value (0..1)
//! \param a A component value (0..1)
//! \return New color object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color
new_color_by_rgba (float r, float g, float b, float a)
{
    return color (r * 255, g * 255, b * 255, a * 255);
}

} // namespace allegropp
