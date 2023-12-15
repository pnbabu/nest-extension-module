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

#include "mymodule.h"

// Generated includes:
#include "config.h"

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
#include "dynamicloader.h"
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

// Includes from sli:
#include "booldatum.h"
#include "integerdatum.h"
#include "sliexceptions.h"
#include "tokenarray.h"

// -- Interface to dynamic module loader ---------------------------------------

/*
 * There are three scenarios, in which MyModule can be loaded by NEST:
 *
 * 1) When loading your module with `Install`, the dynamic module loader must
 * be able to find your module. You make the module known to the loader by
 * defining an instance of your module class in global scope. (LTX_MODULE is
 * defined) This instance must have the name
 *
 * <modulename>_LTX_mod
 *
 * The dynamicloader can then load modulename and search for symbol "mod" in it.
 *
 * 2) When you link the library dynamically with NEST during compilation, a new
 * object has to be created. In the constructor the DynamicLoaderModule will
 * register your module. (LINKED_MODULE is defined)
 *
 * 3) When you link the library statically with NEST during compilation, the
 * registration will take place in the file `static_modules.h`, which is
 * generated by cmake.
 */
#if defined( LTX_MODULE ) | defined( LINKED_MODULE )
mynest::MyModule mymodule_LTX_mod;
#endif
// -- DynModule functions ------------------------------------------------------

mynest::MyModule::MyModule()
{
#ifdef LINKED_MODULE
  // register this module at the dynamic loader
  // this is needed to allow for linking in this module at compile time
  // all registered modules will be initialized by the main app's dynamic loader
  nest::DynamicLoaderModule::registerLinkedModule( this );
#endif
}

mynest::MyModule::~MyModule() = default;

const std::string
mynest::MyModule::name() const
{
  return std::string( "My NEST Module" ); // Return name of the module
}

//-------------------------------------------------------------------------------------

void
mynest::MyModule::init( SLIInterpreter* i )
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
} // MyModule::init()
