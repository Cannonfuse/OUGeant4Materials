# The Ohio University Edwards Accelerator Laboratory Geant4 Material Library

## Motivation
The goal of this project is to provide a material database as an easily accessible library for use in Geant4 simulations involving the Edwards Accelerator Laboratory. Common materials encounterd in the lab are available. New materials are added as the lab acquires additional samples and equipment.

## Building
The only required package is a recent version of Geant4.

## Use
Copy the header file into your include directory and the resulting library into your lib directory.

Add the following lines to your CMakeLists file for your Geant4 project:

<code>
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
</code>

<code>
    add_library(OUG4Materials SHARED IMPORTED)
    set_target_properties(OUG4Materials PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libOUG4Materials.so"
    )
</code>

and make sure to add OUG4Materials to your target_link_libraries. As an example, it might look like:

<code>
    target_link_libraries(neutron_backgrounds PUBLIC ${Geant4_LIBRARIES} OUG4Materials)
</code>
