

cmake_minimum_required(VERSION 3.0)

# set(libname tuio1)

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

macro(build_tuio name makefilepath)
	set(libname ${name}_c)
	project(${name})
	set(${libname}_VERSION_MAJOR 0)
	set(${libname}_VERSION_MINOR 0)
	set(${libname}_VERSION_PATCH 1)

	add_custom_command(
	  OUTPUT ${name}
	  COMMAND make
	  # DEPENDS ${SOURCE_FILES} /tmp/bin/create_foo_hh main.cpp
	  WORKING_DIRECTORY ${makefilepath}
	)

	file(GLOB_RECURSE sources src/${name}_c/src/*.c src/${name}_c/src/TUIO2/*.c src/${name}_c/src/*.cpp)
	file(GLOB test_src src/${name}_c/test/*.c)
	add_library(${libname} STATIC ${sources} ${name})
	target_include_directories(${libname} PRIVATE contrib/${name} contrib/${name}/oscpack)
	#target_include_directories(${libname} PRIVATE contrib/${name}/oscpack)

	set(tname ${libname}_test)
	link_directories(contrib/${name})
	link_libraries(libTUIO.a ${libname})

	add_executable(${tname} ${test_src} ${name})
endmacro(build_tuio)

# build_tuio(tuio1 ${CMAKE_CURRENT_SOURCE_DIR}/contrib/tuio1)
build_tuio(tuio2 ${CMAKE_CURRENT_SOURCE_DIR}/contrib/tuio2/demos)


# build_tuio(tuio2 ${CMAKE_CURRENT_SOURCE_DIR}/contrib/tuio2/demos)



#project(tuio2_c)


#add_custom_command(
#  OUTPUT tuio2
#  COMMAND make
#  # DEPENDS ${SOURCE_FILES} /tmp/bin/create_foo_hh main.cpp
#  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/contrib/tuio2/demos
#)
