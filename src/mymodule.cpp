/*
 *  mymodule.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// include headers with your own stuff
#include "drop_odd_spike_connection.h"
#include "pif_psc_alpha.h"
#include "step_pattern_builder.h"
#ifdef HAVE_SFML_AUDIO
#include "recording_backend_soundclick.h"
#endif
#include "recording_backend_socket.h"

// Includes from NEST
#include "nest_extension_interface.h"

namespace mynest
{
  class MyModule : public NESTExtensionInterface
  {
  public:
    MyModule() {}
    ~MyModule() {}

    void init() override;
    
    std::string name() override { return "mymodyle"; }
    std::string contact() override { return "info@nest-initiative.org"; }
    std::string url() override { return "https://github.com/nest/nest-extension-module"; }
    std::string uri() override { return ""; }
  };
}

// Define module instance outside of namespace to avoid name-mangling problems
mynest::MyModule mymodule_LTX_module;

void mynest::MyModule::init()
{
  /* Register a neuron or device model.
   */
  mynest::register_pif_psc_alpha( "pif_psc_alpha" );

  /* Register a synapse type.
   */
  mynest::register_drop_odd_spike_connection( "drop_odd_synapse" );

  // Next three not registered for now, since they do not unload on ResetKernel
  // Register connection rule.
  //nest::kernel().connection_manager.register_conn_builder< mynest::StepPatternBuilder >( "step_pattern" );

  // TODO: Not sure how this define should get here, need to think about config file for module.
#ifdef HAVE_SFML_AUDIO
  // Register recording backends.
  //nest::kernel().io_manager.register_recording_backend< nest::RecordingBackendSoundClick >( "soundclick" );
#endif

  //nest::kernel().io_manager.register_recording_backend< mynest::RecordingBackendSocket >( "socket" );
}

