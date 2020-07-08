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

// NOTE: This is the place where you include the header files declaring
// NOTE: your own neuron/synapse models, recording/stimulation backends,
// NOTE: or connection builders.
// NOTE: For examples of any of the above, please see the fully functional
// NOTE: example module at https://github.com/nest/nest-extension-module

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


#if defined( LTX_MODULE ) | defined( LINKED_MODULE )
<<MODULE_NAMESPACE>>::<<MODULE_NAME>> <<MODULE_SYMBOL>>_LTX_mod;
#endif

<<MODULE_NAMESPACE>>::<<MODULE_NAME>>::<<MODULE_NAME>>()
{
#ifdef LINKED_MODULE
  // Register the module to allow linking this module at compile time.
  // Registered modules will be initialized by NEST's dynamic loader.
  nest::DynamicLoaderModule::registerLinkedModule( this );
#endif
}

<<MODULE_NAMESPACE>>::<<MODULE_NAME>>::~<<MODULE_NAME>>() = default;

const std::string
<<MODULE_NAMESPACE>>::<<MODULE_NAME>>::name() const
{
  return std::string( "Extension module <<MODULE_NAME>>" );
}

void
<<MODULE_NAMESPACE>>::<<MODULE_NAME>>::init( SLIInterpreter* i )
{
  // NOTE: This is the place where you register your stuff with NEST.
  // NOTE: The lines below show examples that might be helpful.
  // NOTE:   nest::register_node_model< classname >( "modelname" );
  // NOTE:   nest::register_connection_model< classname >( "modelname" );
  // NOTE:   nest::register_conn_builder< classname >( "buildername" );
  // NOTE:   nest::register_recording_backend< classname >( "backendname" );
}
