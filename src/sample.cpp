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
#include <allegropp/sample.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h> // Include the audio addon
#include <allegro5/allegro_acodec.h> // Include the audio codec addon
#include <mutex>

namespace
{
std::once_flag is_initialized_;

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Initialize Allegro audio subsystem
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
static void
_init ()
{
    al_install_audio();    // Initialize the audio addon
    al_init_acodec_addon(); // Initialize the audio codec addon
    al_reserve_samples(3);
}

} // namespace

namespace allegropp
{
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief <i>sample</i> implementation class
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class sample::impl
{
public:

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Constructors and destructor
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  impl () = default;
  impl (const impl&) = delete;
  impl (impl&&) = delete;
  explicit impl (const std::string&);
  ~impl ();

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Operators
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  impl& operator= (const impl&) = delete;
  impl& operator= (impl&&) = delete;

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  //! \brief Operator bool
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  operator bool () const noexcept
  {
     return bool (obj_);  
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  // Prototypes
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  void play (double, double, double, ALLEGRO_PLAYMODE);

private:
  //! \brief Allegro sample object
  ALLEGRO_SAMPLE *obj_ = nullptr;
  
  //! \brief Allegro sample ID
  ALLEGRO_SAMPLE_ID id_;
};

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param path Font path
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sample::impl::impl (const std::string& path)
{
    std::call_once (is_initialized_, _init);
    obj_ = al_load_sample (path.c_str ());
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Destructor
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sample::impl::~impl ()
{
    if (obj_)
        al_destroy_sample (obj_);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Play audio sample
//! \param gain Relative volume at which the sample is played; 1.0 is normal
//! \param pan 0.0 is centred, -1.0 is left, 1.0 is right
//! \param speed Relative speed at which the sample is played; 1.0 is normal.
//! \param mode ALLEGRO_PLAYMODE_ONCE, ALLEGRO_PLAYMODE_LOOP, or ALLEGRO_PLAYMODE_BIDIR
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
sample::impl::play (double gain, double pan, double speed, ALLEGRO_PLAYMODE mode)
{
  if (!al_play_sample (obj_, gain, pan, speed, mode, &id_))
    throw std::runtime_error ("failed to play audio sample");
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sample::sample ()
  : impl_ (std::make_shared <impl> ())
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Constructor
//! \param path Font path
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sample::sample (const std::string& path)
  : impl_ (std::make_shared <impl> (path))
{
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Operator bool
//! \return true/false
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sample::operator bool () const noexcept
{
  return impl_->operator bool ();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Play audio sample once
//! \param gain Relative volume at which the sample is played; 1.0 is normal
//! \param pan 0.0 is centred, -1.0 is left, 1.0 is right
//! \param speed Relative speed at which the sample is played; 1.0 is normal.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
sample::play_once (double gain, double pan, double speed)
{
  impl_->play (gain, pan, speed, ALLEGRO_PLAYMODE_ONCE);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Play audio sample in loop mode
//! \param gain Relative volume at which the sample is played; 1.0 is normal
//! \param pan 0.0 is centred, -1.0 is left, 1.0 is right
//! \param speed Relative speed at which the sample is played; 1.0 is normal.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
sample::play_loop (double gain, double pan, double speed)
{
  impl_->play (gain, pan, speed, ALLEGRO_PLAYMODE_LOOP);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//! \brief Play audio sample bidir mode
//! \param gain Relative volume at which the sample is played; 1.0 is normal
//! \param pan 0.0 is centred, -1.0 is left, 1.0 is right
//! \param speed Relative speed at which the sample is played; 1.0 is normal.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void
sample::play_bidir (double gain, double pan, double speed)
{
  impl_->play (gain, pan, speed, ALLEGRO_PLAYMODE_BIDIR);
}

} // namespace allegropp
