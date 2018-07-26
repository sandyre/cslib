option(BUILD_TESTS "Build unit tests" OFF)

SET(SOURCES
	algorithm/linear_search.cpp
)

if(BUILD_TESTS)
	include(ExternalProject)

	ExternalProject_Add(gtest
		URL https://github.com/google/googletest/archive/release-1.8.0.zip
		PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
		INSTALL_COMMAND ""
	)
	ExternalProject_Get_Property(gtest source_dir binary_dir)

	message(${binary_dir})
	add_executable(cslib_tests ${SOURCES})
	add_dependencies(cslib_tests gtest)
	include_directories(${source_dir}/googletest/include)
	target_link_libraries(cslib_tests ${binary_dir}/googlemock/gtest/libgtest.a)
	target_link_libraries(cslib_tests ${binary_dir}/googlemock/gtest/libgtest_main.a)

	enable_testing()
	add_test(NAME cslib_tests COMMAND cslib_tests)
endif()