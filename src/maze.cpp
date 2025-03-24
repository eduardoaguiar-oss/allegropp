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
#include <allegropp/maze.hpp>
#include <vector>
#include <random>

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @struct maze::Impl
// @brief Private implementation details of the maze class (PIMPL).
//
// Contains the maze grid, dimensions, random number generator, and generation logic.
// Hidden from the public interface to reduce coupling and improve encapsulation.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
struct maze::impl
{
    int width;                          ///< Grid width (columns)
    int height;                         ///< Grid height (rows)
    std::vector <wall_type> walls;      ///< Grid data: 0 = passage, >0 = wall types
    std::mt19937 rng;                   ///< Mersenne Twister random number generator
    unsigned int seed;                  ///< Seed value for reproducible generation

    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // @brief Checks if a position is within the maze bounds.
    // @param x X-coordinate to check.
    // @param y Y-coordinate to check.
    // @return True if (x, y) is within bounds, false otherwise.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    bool
    in_bounds (int x, int y) const
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // @brief Recursively carves paths through the maze.
    // @param x Starting X-coordinate (must be odd).
    // @param y Starting Y-coordinate (must be odd).
    //
    // Uses a two-cell step variant of Recursive Backtracking to create wider paths.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    void
    carve_path (int x, int y)
    {
        walls[y * width + x] = maze::PASSAGE;

        std::vector<std::pair<int, int>> directions = {
            {0, -2}, {2, 0}, {0, 2}, {-2, 0}
        };

        // Shuffle directions for random exploration
        for (int i = directions.size() - 1; i > 0; --i)
          {
            std::uniform_int_distribution<int> dist (0, i);
            int j = dist (rng);
            std::swap (directions[i], directions[j]);
          }

        // Explore each direction
        for (const auto& [dx, dy] : directions)
          {
            int new_x = x + dx;
            int new_y = y + dy;

            if (in_bounds (new_x, new_y) && walls[new_y * width + new_x] != maze::PASSAGE)
              {
                // Carve intermediate cell
                walls[(y + dy / 2) * width + (x + dx / 2)] = maze::PASSAGE;
                carve_path (new_x, new_y);
              }
          }
    }

    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // @brief Constructs the implementation with given dimensions and seed.
    // @param w Desired width (adjusted to odd).
    // @param h Desired height (adjusted to odd).
    // @param s Seed value; if 0, generates a random seed.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    impl (int w, int h, unsigned int s)
      : width(w), height(h)
    {
        // Ensure odd dimensions for a wall border
        if (width % 2 == 0) width++;
        if (height % 2 == 0) height++;

        // Initialize grid with standard walls
        walls.resize (width * height, maze::WALL);

        // Set seed: random if 0, otherwise use provided value
        if (s)
          seed = s;

        else
          {
            std::random_device rd;
            seed = rd();
          }

        rng.seed (seed);

        // Generate maze        
        std::uniform_int_distribution<int> dist_x (1, width - 2);
        std::uniform_int_distribution<int> dist_y (1, height - 2);
        int start_x = dist_x (rng) | 1;  // Ensure odd
        int start_y = dist_y (rng) | 1;  // Ensure odd
        carve_path (start_x, start_y);
    }
};

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Constructs a maze with specified dimensions and an optional seed.
// @param width Desired width of the maze (adjusted to odd if even).
// @param height Desired height of the maze (adjusted to odd if even).
// @param seed Random seed for generation; if 0, a random seed is generated.
//
// @details Generates the maze using a Recursive Backtracking variant.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
maze::maze (int width, int height, unsigned int seed)
    : impl_ (std::make_shared<impl> (width, height, seed))
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Gets the obstacle type at a given position.
// @param x X-coordinate (column) of the position.
// @param y Y-coordinate (row) of the position.
// @return The type of obstacle (e.g., PASSAGE, WALL) at (x, y); WALL if out of bounds.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
maze::wall_type
maze::get(int x, int y) const
{
    if (impl_->in_bounds (x, y))
      return impl_->walls[y * impl_->width + x];

    return WALL;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Sets the obstacle type at a given position.
// @param x X-coordinate (column) of the position.
// @param y Y-coordinate (row) of the position.
// @param type The type to set (e.g., PASSAGE, IRON_WALL).
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
maze::set (int x, int y, wall_type type) {
    if (impl_->in_bounds (x, y))
        impl_->walls[y * impl_->width + x] = type;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Gets the width of the maze grid.
// @return The number of columns in the maze.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int
maze::get_width () const
{
    return impl_->width;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Gets the height of the maze grid.
// @return The number of rows in the maze.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int
maze::get_height() const
{
    return impl_->height;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// @brief Gets the seed used for maze generation.
// @return The seed value (user-provided or randomly generated).
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
unsigned int
maze::get_seed() const
{
    return impl_->seed;
}

} // namespace allegropp
