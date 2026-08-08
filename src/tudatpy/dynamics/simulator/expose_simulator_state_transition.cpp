/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rights reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */
#if TUDATPY_ENABLE_DETAILED_PYBIND11_ERRORS
#define PYBIND11_DETAILED_ERROR_MESSAGES
#endif
#include "expose_simulator_bindings.h"

#include <pybind11/chrono.h>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "scalarTypes.h"
#include "tudat/astro/propagators/stateTransitionMatrixInterface.h"

namespace py = pybind11;
namespace tp = tudat::propagators;

namespace tudatpy
{
namespace dynamics
{
namespace simulator
{

void expose_simulator_state_transition_bindings( py::module& m )
{
    py::class_< tp::CombinedStateTransitionAndSensitivityMatrixInterface,
                std::shared_ptr< tp::CombinedStateTransitionAndSensitivityMatrixInterface > >(
            m,
            "CombinedStateTransitionAndSensitivityMatrixInterface",
            R"doc(

         Class establishing an interface with the simulation's State Transition and Sensitivity Matrices.

         Class establishing an interface to the State Transition and Sensitivity Matrices.
         Instances of this class are instantiated automatically upon creation of :class:`~tudatpy.estimation.estimation_analysis.Estimator` objects,
         using the simulation information in the observation, propagation and integration settings that the :class:`~tudatpy.estimation.estimation_analysis.Estimator` instance is linked to.





      )doc" )
            .def( "state_transition_sensitivity_at_epoch",
                  &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getCombinedStateTransitionAndSensitivityMatrix,
                  py::arg( "time" ),
                  py::arg( "add_central_body_dependency" ) = true,
                  py::arg( "arc_defining_bodies" ) = std::vector< std::string >( ),
                  R"doc(

         Function to get the concatenated state transition and sensitivity matrix at a given time.

         Function to get the concatenated state transition and sensitivity matrix at a given time.
         Entries corresponding to parameters which are not active at the current arc are omitted.


         Parameters
         ----------
         time : astro.time_representation.Time
             Time at which concatenated state transition and sensitivity matrix are to be retrieved.
         Returns
         -------
         numpy.ndarray[numpy.float64[m, n]]
             Concatenated state transition and sensitivity matrix at a given time.





     )doc" )
            .def( "full_state_transition_sensitivity_at_epoch",
                  &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getFullCombinedStateTransitionAndSensitivityMatrix,
                  py::arg( "time" ),
                  py::arg( "add_central_body_dependency" ) = true,
                  py::arg( "arc_defining_bodies" ) = std::vector< std::string >( ),
                  R"doc(


         Parameters
         ----------
         time : astro.time_representation.Time
             Time at which full concatenated state transition and sensitivity matrix are to be retrieved.
         Returns
         -------
         numpy.ndarray[numpy.float64[m, n]]
             Full concatenated state transition and sensitivity matrix at a given time.





     )doc" )
            .def( "full_state_transition_sensitivity_block_at_epoch",
                  &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getFullCombinedStateTransitionAndSensitivityMatrixBlock,
                  py::arg( "time" ),
                  py::arg( "start_row" ),
                  py::arg( "number_of_rows" ),
                  py::arg( "add_central_body_dependency" ) = true,
                  py::arg( "arc_defining_bodies" ) = std::vector< std::string >( ),
                  R"doc(

         Function to get a block of rows of the full concatenated state transition and sensitivity matrix at a given time.

         Function to get a block of rows of the full concatenated state transition and sensitivity matrix at a given time,
         equal to the same rows of :meth:`full_state_transition_sensitivity_at_epoch`. For multi- and hybrid-arc dynamics
         only the requested rows are assembled, avoiding the allocation of the full (mostly zero) matrix.


         Parameters
         ----------
         time : astro.time_representation.Time
             Time at which the block is to be retrieved.
         start_row : int
             First row of the full matrix to return.
         number_of_rows : int
             Number of rows of the full matrix to return.
         Returns
         -------
         numpy.ndarray[numpy.float64[m, n]]
             Requested rows of the full concatenated state transition and sensitivity matrix.





     )doc" )
            .def_property_readonly( "state_transition_size",
                                    &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getStateTransitionMatrixSize,
                                    R"doc(

         **read-only**

         Size of the (square) state transition matrix.

         :type: int
      )doc" )
            .def_property_readonly( "sensitivity_size",
                                    &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getSensitivityMatrixSize,
                                    R"doc(

         **read-only**

         Number of columns in the sensitivity matrix.

         :type: int
      )doc" )
            .def_property_readonly( "full_parameter_size",
                                    &tp::CombinedStateTransitionAndSensitivityMatrixInterface::getFullParameterVectorSize,
                                    R"doc(

         **read-only**

         Full amount of parameters w.r.t. which partials have been set up via State Transition and Sensitivity Matrices.

         :type: int
      )doc" );
}

}  // namespace simulator
}  // namespace dynamics
}  // namespace tudatpy
