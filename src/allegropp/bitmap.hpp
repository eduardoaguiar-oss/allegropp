#ifndef ALLEGROPP_BITMAP
#define ALLEGROPP_BITMAP

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
#include <allegro5/allegro.h>
#include <memory>
#include <string>

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Allegro bitmap class
//! \author Eduardo Aguiar
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class bitmap
{
private:
  //! \brief Implementation class forward declaration
  class impl;

  //! \brief Implementation pointer
  std::shared_ptr <impl> impl_;

public:
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Constructors
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  bitmap ();
  explicit bitmap (const std::string&);
  bitmap (std::size_t, std::size_t);
  bitmap (const std::shared_ptr <impl>&);
  bitmap (bitmap&&) noexcept = default;
  bitmap (const bitmap&) noexcept = default;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Operators
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  bitmap& operator= (const bitmap&) noexcept = default;
  bitmap& operator= (bitmap&&) noexcept = default;
  operator bool() const noexcept;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Function prototypes
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  int get_width () const;
  int get_height () const;
  void draw (int, int, int = 0);
  void draw_scaled (int, int, int, int, int, int, int, int, int = 0);
  bitmap clone () const;
};

} // namespace allegropp

#endif