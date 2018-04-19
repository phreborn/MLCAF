#########################################################################################################
# Package: CAFExample## #################################################################################
cmake_minimum_required( VERSION 2.8.12 )

# Declare the package name:
project( CAFExample )

# check if this is the top-level CMakeLists.txt
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(HAS_PARENT 0)
else()
  set(HAS_PARENT 1)
endif()

# write a setup script
execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/setup/writeSetupScript.py ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/setup ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore)

# we try to discover if we are compiling inside an ASG environment or not
find_package( AnalysisBase QUIET) 

# define dependencies on other packages
find_package( ROOT COMPONENTS Core Matrix RooFitCore Minuit2)

# set some variables for easier handling
set(CAFExampleLinkDef ${PROJECT_SOURCE_DIR}/Root/LinkDef.h)
set(CAFExamplePython ${PROJECT_SOURCE_DIR}/python/__init__.py)
file(GLOB CAFExampleSources Root/*.cxx)
file(GLOB CAFExampleHeaders CAFExample/*.h)
file(GLOB CAFExampleTests test/*.py)

IF(${AnalysisBase_FOUND})
  # this is ASG compilation, we don't need to do anything

  # Set up the usage of CTest:
  IF(NOT ${HAS_PARENT})
    atlas_ctest_setup() # Set up the project: 
    atlas_project( CAFExample 1.0.0 
      USE AnalysisBase ${AnalysisBase_VERSION} ) 
    
    # Generate an environment setup script: 
    lcg_generate_env( SH_FILE ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh )
    install( FILES ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh DESTINATION . ) 

    # Set up the usage of CPack: 
    set(CMAKE_INSTALL_PREFIX /InstallArea/x86_64-slc6-gcc49-opt)
    atlas_cpack_setup()
  ENDIF()
    
  # register this as a package to ASG
  atlas_subdir( CAFExample )

  # generate the LinkDef.h 
  execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore/QFramework/share/generateBindings.py --pkgname CAFExample --loadpackage --verbose --python ${CAFExamplePython} --linkdef ${CAFExampleLinkDef} --headers ${CAFExampleHeaders}
    )
    
  # use the standard ROOT method of dictionary generation
  atlas_add_root_dictionary( CAFExample CAFExampleCintDict
    ROOT_HEADERS ${CAFExampleHeaders} ${CAFExampleLinkDef}
    EXTERNAL_PACKAGES ROOT
    )
  
  # put everything together to make CMake compile your library
  atlas_add_library( CAFExample
    ${CAFExampleHeaders} ${CAFExampleSources} ${CAFExampleCintDict}
    PUBLIC_HEADERS CAFExample
    PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
    LINK_LIBRARIES QFramework CAFxAODUtils PileupReweightingLib MCTruthClassifierLib
    # here go all the libraries corresonding to the packages that you depend on
    PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
    )

  # also have all of your python files installed
  atlas_install_python_modules( python/*.py )

  # check if we have any test cases
  if(${CAFExampleTests})   
    # register your test cases from the "test" folder
    find_package(PythonInterp REQUIRED)
    foreach(TestScript test)
      get_filename_component(TestName ${TestScript} NAME_WE)
      atlas_add_test( ${TestName} SCRIPT ${TestScript} )
    endforeach()
  endif()
  
  # Set up the usage of CPack: 
  set(CMAKE_INSTALL_PREFIX /InstallArea/x86_64-slc6-gcc49-opt)
  atlas_cpack_setup()
else()
  # this is standalone compilation, we need to stitch together the project
  message( "compiling CAFExample in standalone mode" )
  set(WITHOUT_ASG ON )

  # set general CMake settings
  set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
  set(CMAKE_DISABLE_SOURCE_CHANGES  OFF)  
  set(CMAKE_VERBOSE_MAKEFILE OFF)
  set(CMAKE_COLOR_MAKEFILE   ON)

  # require ROOT
  find_package( ROOT REQUIRED )
  include(${ROOT_USE_FILE})

  # enabling python test cases
  find_package(PythonInterp REQUIRED)
  include(CTest)
  enable_testing()
  
  message("adding CAFCore")
  add_subdirectory(CAFCore)
endif()
