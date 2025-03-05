#ifndef ALLEGROPP_COLOR
#define ALLEGROPP_COLOR

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
#include <allegro5/allegro_color.h>
#include <memory>
#include <string>
#include <tuple>

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Allegro color class
//! \author Eduardo Aguiar
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class color
{
public:
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Datatypes
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  using component_type = unsigned char;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Constructors
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  color ();
  color (component_type, component_type, component_type);
  color (component_type, component_type, component_type, component_type);
  color (color&&) noexcept = default;
  color (const color&) noexcept = default;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Operators
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  color& operator= (const color&) noexcept = default;
  color& operator= (color&&) noexcept = default;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Function prototypes
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  std::tuple <component_type, component_type, component_type> get_rgb () const;
  std::tuple <component_type, component_type, component_type, component_type> get_rgba () const;
  std::string get_name () const;
  std::string get_html () const;
  ALLEGRO_COLOR get_implementation () const;

private:
  //! \brief Implementation class forward declaration
  class impl;

  //! \brief Implementation pointer
  std::shared_ptr <impl> impl_;
};

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Functions
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
color new_color_by_name (const std::string&);
color new_color_by_html (const std::string&);
color new_color_by_cmyk (float, float, float, float);
color new_color_by_hsl (float, float, float);
color new_color_by_hsv (float, float, float);
color new_color_by_yuv (float, float, float);
color new_color_by_rgb (float, float, float);
color new_color_by_rgba (float, float, float, float);

} // namespace allegropp

#endif