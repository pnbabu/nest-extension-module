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

// Generated includes:
#include "config.h"

#include "mymodule.h"

// include headers with your own stuff
#include "drop_odd_spike_connection.h"
#include "pif_psc_alpha.h"
#include "step_pattern_builder.h"
#ifdef HAVE_SFML_AUDIO
#include "recording_backend_soundclick.h"
#endif
#include "recording_backend_socket.h"

// Includes from nestkernel:
#include "connection_manager_impl.h"
#include "connector_model_impl.h"
#include "exceptions.h"
#include "genericmodel.h"
#include "genericmodel_impl.h"
#include "io_manager_impl.h"
#include "kernel_manager.h"
#include "model.h"
#include "model_manager_impl.h"
#include "nest.h"
#include "nest_impl.h"
#include "nestmodule.h"
#include "target_identifier.h"


// -- Interface to dynamic module loader ---------------------------------------

namespace mynest
{
  
void mymodule_LTX_register_components()
{
  /* Register a neuron or device model.
     Give node type as template argument and the name as second argument.
  */
  register_pif_psc_alpha( "pif_psc_alpha" );

  /* Register a synapse type.
     Give synapse type as template argument and the name as second argument.
  */
  register_drop_odd_spike_connection( "drop_odd_synapse" );
  
  // Register connection rule.
  nest::kernel().connection_manager.register_conn_builder< StepPatternBuilder >( "step_pattern" );

#ifdef HAVE_SFML_AUDIO
  // Register recording backends.
  nest::kernel().io_manager.register_recording_backend< nest::RecordingBackendSoundClick >( "soundclick" );
#endif

  nest::kernel().io_manager.register_recording_backend< nest::RecordingBackendSocket >( "socket" );
}

}
