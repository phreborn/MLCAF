#########################################################################################################
# Package: Htautau## #################################################################################
cmake_minimum_required( VERSION 2.8.12 )

# Declare the package name:
project( Htautau )

# check if this is the top-level CMakeLists.txt
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(HAS_PARENT 0)
else()
  set(HAS_PARENT 1)
endif()

# we try to discover if we are compiling inside an ASG environment or not
find_package( AnalysisBase QUIET) 

# define dependencies on other packages
find_package( ROOT COMPONENTS Core Matrix RooFitCore Minuit2)

# set some variables for easier handling
set(HtautauLinkDef ${PROJECT_SOURCE_DIR}/Root/LinkDef.h)
file(GLOB HtautauPython python/*.py) #note: this does not include __init__.py since it's not generated yet!
list(APPEND HtautauPython ${PROJECT_SOURCE_DIR}/python/__init__.py)
file(GLOB HtautauTests test/*.py)

IF(${AnalysisBase_FOUND})
  # this is ASG compilation, we don't need to do anything
  file(GLOB HtautauSources Root/*.cxx)
  file(GLOB HtautauHeaders Htautau/*.h)

  # generate the LinkDef.h 
  execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore/QFramework/share/generateBindings.py --set-working-directory ${CMAKE_CURRENT_SOURCE_DIR} --pkgname Htautau --loadpackage --verbose --python ${PROJECT_SOURCE_DIR}/python/__init__.py --linkdef ${HtautauLinkDef} --headers ${HtautauHeaders}
    )

  # write a setup script
  execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/setup/writeSetupScript.py ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/setup ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore)

  # Set up the usage of CTest:
  IF(NOT ${HAS_PARENT})
    atlas_ctest_setup() # Set up the project: 
    atlas_project( Htautau 1.0.0 
      USE AnalysisBase ${AnalysisBase_VERSION} ) 
    
    # Generate an environment setup script: 
    lcg_generate_env( SH_FILE ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh )
    install( FILES ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh DESTINATION . ) 

    # Set up the usage of CPack: 
    set(CMAKE_INSTALL_PREFIX /InstallArea/x86_64-slc6-gcc49-opt)
    atlas_cpack_setup()
  ENDIF()
    
  # register this as a package to ASG
  atlas_subdir( Htautau )

  # use the standard ROOT method of dictionary generation
  atlas_add_root_dictionary( Htautau HtautauCintDict
    ROOT_HEADERS ${HtautauHeaders} ${HtautauLinkDef}
    EXTERNAL_PACKAGES ROOT
    )
  
  # put everything together to make CMake compile your library
  atlas_add_library( Htautau
    ${HtautauHeaders} ${HtautauSources} ${HtautauCintDict}
    PUBLIC_HEADERS Htautau
    PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
    LINK_LIBRARIES QFramework CAFxAODUtils PileupReweightingLib MCTruthClassifierLib
    # here go all the libraries corresonding to the packages that you depend on
    PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
    )

  # also have all of your python files installed
  atlas_install_python_modules( python/*.py )

  # check if we have any test cases
  if(HtautauTests)   
    # register your test cases from the "test" folder
    find_package(PythonInterp REQUIRED)
    foreach(TestScript ${HtautauTests})
      get_filename_component(TestName ${TestScript} NAME_WE)
      atlas_add_test( ${TestName} SCRIPT ${TestScript} )
    endforeach()
  endif()
  
  # Set up the usage of CPack: 
  set(CMAKE_INSTALL_PREFIX /InstallArea/x86_64-slc6-gcc49-opt)
  atlas_cpack_setup()
else()
  # this is standalone compilation, we need to stitch together the project
  message( "compiling Htautau in standalone mode" )
  set(WITHOUT_ASG ON )

  file(GLOB HtautauSourcesAll Root/*.cxx )
  file(GLOB HtautauHeadersAll Htautau/*.h )
  execute_process(COMMAND grep -L xAOD ${HtautauSourcesAll} OUTPUT_VARIABLE HtautauSourcesTMP )
  execute_process(COMMAND grep -L xAOD ${HtautauHeadersAll} OUTPUT_VARIABLE HtautauHeadersTMP )
  string(REGEX REPLACE "[ \r\n]+" ";" HtautauSources ${HtautauSourcesTMP})
  string(REGEX REPLACE "[ \r\n]+" ";" HtautauHeaders ${HtautauHeadersTMP})

  # generate the LinkDef.h 
  execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore/QFramework/share/generateBindings.py --set-working-directory ${CMAKE_CURRENT_SOURCE_DIR} --pkgname Htautau --loadpackage --verbose --python ${PROJECT_SOURCE_DIR}/python/__init__.py --linkdef ${HtautauLinkDef} --headers ${HtautauHeaders}
    )

  # set general CMake settings
  set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
  set(CMAKE_DISABLE_SOURCE_CHANGES  OFF)  
  set(CMAKE_VERBOSE_MAKEFILE OFF)
  set(CMAKE_COLOR_MAKEFILE   ON)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

  set(HtautauPythonDir ${CMAKE_CURRENT_BINARY_DIR}/Htautau)
  execute_process(COMMAND mkdir -p ${HtautauPythonDir})
  foreach(module ${HtautauPython})
    execute_process(COMMAND ln -sf ${module} ${HtautauPythonDir})
  endforeach()

  # write a setup script
  execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/setup/writeSetupScript.py ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/setup ${CMAKE_CURRENT_SOURCE_DIR}/CAFCore --binDir ${CMAKE_CURRENT_BINARY_DIR})

  # register all the files and directories
  include_directories ("${PROJECT_SOURCE_DIR}")
  include_directories ("${PROJECT_SOURCE_DIR}/CAFCore/QFramework")
  include_directories ("${PROJECT_SOURCE_DIR}/CAFCore/SFramework")
  include_directories ("${ROOT_INCLUDE_DIRS}")

  # generate the dictionary source code
  include(${ROOT_USE_FILE})
  ROOT_GENERATE_DICTIONARY(G__Htautau ${HtautauHeaders} LINKDEF ${HtautauLinkDef})

  # register the shared object to include both sources and dictionaries
  add_library( Htautau SHARED ${HtautauSources} G__Htautau.cxx)

  # link everything together at the end
  target_link_libraries( Htautau QFramework SFramework ${ROOT_LIBRARIES} )

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
