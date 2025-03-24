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
#include <allegropp/color.hpp>
#include <allegropp/display.hpp>
#include <allegropp/event_queue.hpp>
#include <allegropp/maze.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>

namespace
{
  constexpr int SCREEN_WIDTH = 800;
  constexpr int SCREEN_HEIGHT = 600;
  constexpr int SCREEN_BORDER = 25;
  constexpr int CELL_WIDTH = 30;
  constexpr int CELL_HEIGHT = 20;
  constexpr int FONT_SIZE = 48;
} // namespace

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Draw example
//! \param maze Maze object
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
draw (allegropp::maze& maze)
{
  allegropp::color brick_color (0, 60, 192);
  allegropp::color bg_color (0, 0, 0);
  al_clear_to_color (bg_color.get_implementation ());
  
  for (int y = 0;y < maze.get_height ();y++)
    {
      for (int x = 0;x < maze.get_width ();x++)
        {
            if (maze.get (x, y) == allegropp::maze::WALL)
              al_draw_filled_rectangle (
                   x * CELL_WIDTH + SCREEN_BORDER,
                   y * CELL_HEIGHT + SCREEN_BORDER,
                   x * CELL_WIDTH + CELL_WIDTH - 2 + SCREEN_BORDER,
                   y * CELL_HEIGHT + CELL_HEIGHT - 2 + SCREEN_BORDER,
                   brick_color.get_implementation ()
              );
        }
    }
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Main function
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int
main ()
{
  // Create display
  auto display = allegropp::display (SCREEN_WIDTH, SCREEN_HEIGHT);

  if (!display)
    {
      std::cerr << "Failed to create display!" << std::endl;
      return EXIT_FAILURE;
    }

  display.set_window_title ("Allegro++ Maze Example");

  // Create maze
  allegropp::maze maze (25, 27);

  // Main game loop
  allegropp::event_queue event_queue;

  event_queue.add_display_events (display);

  bool running = true;
  while (running)
    {
      ALLEGRO_EVENT event;
      event_queue.get_event (event);

      if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        running = false;

      else
        {
          draw (maze);
          display.flip ();
          al_rest (1.0);
        }
    }

  return EXIT_SUCCESS;
}
