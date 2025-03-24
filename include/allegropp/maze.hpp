#ifndef ALLEGROPP_MAZE
#define ALLEGROPP_MAZE

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
#include <cstdint>
#include <memory>

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @class Maze
// @author Eduardo Aguiar
// @brief A class to generate and manage a 2D maze with customizable obstacle types.
// @see https://www.astrolog.org/labyrnth/algrithm.htm
//
// This class uses a variant of the Recursive Backtracking algorithm to create
// a perfect maze with wider paths (two-cell steps). It supports different wall
// types and allows querying and modifying the maze grid.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class maze
{
public:
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // @brief Obstacle types for the maze grid (0 = passage, >0 = walls)
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    enum wall_type : std::uint8_t
    {
        PASSAGE = 0,         ///< Open path
        WALL = 1,            ///< Standard wall
        // Add more types as needed (up to 255)
    };

    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Prototypes
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    explicit maze (int width, int height, unsigned int seed = 0);
    wall_type get (int x, int y) const;
    void set (int x, int y, wall_type);
    int get_width () const;
    int get_height () const;
    unsigned int get_seed () const;

private:
    /// Forward declaration of the implementation struct
    struct impl;

    /// Shared pointer to the hidden implementation
    std::shared_ptr<impl> impl_;
};

} // namespace allegropp

#endif // MAZE_HPP
