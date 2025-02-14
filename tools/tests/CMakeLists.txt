find_package(LibBfd)

if(LibBfd_FOUND)

  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CGREEN_PUBLIC_INCLUDE_DIRS}
    ${CURRENT_BINARY_DIR}
    ${LIBBFD_INCLUDE_DIRS})

  set(CGREEN_RUNNER_TESTS_LIBRARY
    cgreen_runner_tests
    CACHE INTERNAL "cgreen-runner tests shared library"
  )
  set(RUNNER_TESTS_SRCS
    runner_unit_tests.c
    ../discoverer.c
    ../bfd_adapter.c
    ../test_item.c)
  add_library(${CGREEN_RUNNER_TESTS_LIBRARY} SHARED ${RUNNER_TESTS_SRCS})
  target_link_libraries(${CGREEN_RUNNER_TESTS_LIBRARY}
    ${CGREEN_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${LIBBFD_LIBRARIES}
    ${EXPLICIT_INTLIB_ONLY_REQUIRED_FOR_CYGWIN}
  )

  set(DISCOVERER_ACCEPTANCE_TESTS_LIBRARY
    discoverer_acceptance_tests
    CACHE INTERNAL "discoverer acceptance tests"
  )
  set(DISCOVERER_ACCEPTANCE_TESTS_SRCS
    discoverer_acceptance_tests.c
    ../discoverer.c
    ../bfd_adapter.c
    ../test_item.c)
  add_library(${DISCOVERER_ACCEPTANCE_TESTS_LIBRARY} SHARED ${DISCOVERER_ACCEPTANCE_TESTS_SRCS})

  target_link_libraries(${DISCOVERER_ACCEPTANCE_TESTS_LIBRARY}
    ${CGREEN_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${LIBBFD_LIBRARIES}
    ${EXPLICIT_INTLIB_ONLY_REQUIRED_FOR_CYGWIN}
  )

  set(DISCOVERER_UNIT_TESTS_LIBRARY
    discoverer_unit_tests
    CACHE INTERNAL "discoverer unit tests"
  )
  set(DISCOVERER_UNIT_TESTS_SRCS
    discoverer_unit_tests.c
    ../discoverer.c
    ../test_item.c)
  add_library(${DISCOVERER_UNIT_TESTS_LIBRARY} SHARED ${DISCOVERER_UNIT_TESTS_SRCS})

  target_compile_definitions(${DISCOVERER_UNIT_TESTS_LIBRARY} PUBLIC UNITTESTING)
  target_link_libraries(${DISCOVERER_UNIT_TESTS_LIBRARY}
    ${CGREEN_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${LIBBFD_LIBRARIES})

  SET(CGREEN_RUNNER_TESTS_LIBRARY "$<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests>")
  SET(DISCOVERER_ACCEPTANCE_TESTS_LIBRARY "$<TARGET_FILE_DIR:discoverer_acceptance_tests>/$<TARGET_FILE_NAME:discoverer_acceptance_tests>")
  SET(DISCOVERER_UNIT_TESTS_LIBRARY "$<TARGET_FILE_DIR:discoverer_unit_tests>/$<TARGET_FILE_NAME:discoverer_unit_tests>")

  # Due to some (of many) CMake irregularities to reference the test libraries
  # we can't just use its CMake name variable, but have to look it up with
  # some special attributes of the library:
  #     $<TARGET_FILE_DIR:the_lib>/$<TARGET_FILE_NAME:the_lib>
  #
  macro_add_test(NAME cgreen_runner_unit_tests
    COMMAND cgreen-runner ${CGREEN_RUNNER_TESTS_LIBRARY})

  macro_add_test(NAME cgreen_runner_usage
    COMMAND cgreen-runner --help)

  macro_add_test(NAME cgreen_runner_quiet
    COMMAND cgreen-runner -q ${CGREEN_RUNNER_TESTS_LIBRARY})

  macro_add_test(NAME cgreen_runner_suite_name
    COMMAND cgreen-runner -s Suite ${CGREEN_RUNNER_TESTS_LIBRARY})

  macro_add_test(NAME cgreen_runner_fail_on_non_existing_library
    COMMAND cgreen-runner Suite non_existent_library)
  set_tests_properties(cgreen_runner_fail_on_non_existing_library PROPERTIES WILL_FAIL true)

  macro_add_test(NAME cgreen_runner_fail_on_non_existing_library_with_suite
    COMMAND cgreen-runner -s Suite non_existent_library
    WILL_FAIL)
  set_tests_properties(cgreen_runner_fail_on_non_existing_library_with_suite PROPERTIES WILL_FAIL true)

  macro_add_test(NAME cgreen_runner_verbose
    COMMAND cgreen-runner -v -C ${CGREEN_RUNNER_TESTS_LIBRARY})

  macro_add_test(NAME cgreen_runner_version
    COMMAND cgreen-runner --version)

  macro_add_test(NAME cgreen_runner_single_explicit_named_test
    COMMAND cgreen-runner $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests> Runner:can_match_test_name)

  macro_add_test(NAME cgreen_runner_patternmatched_testnames
    COMMAND cgreen-runner $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests> Runner:can*)

  macro_add_test(NAME cgreen_runner_patternmatched_testnames_in_patternmatched_context
    COMMAND cgreen-runner $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests> Run*:can*)

  macro_add_test(NAME cgreen_runner_wildcarded_tests_in_named_context
    COMMAND cgreen-runner $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests> Runner:*)

  macro_add_test(NAME cgreen_runner_wildcarded_tests_in_wildcarded_context
    COMMAND cgreen-runner $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests> *:*)

  macro_add_test(NAME cgreen_runner_with_xml_reporter
    COMMAND cgreen-runner --xml TEST --suite cgreen_runner_tests $<TARGET_FILE_DIR:cgreen_runner_tests>/$<TARGET_FILE_NAME:cgreen_runner_tests>)

  macro_add_test(NAME cgreen_runner_multiple_libraries
    COMMAND cgreen-runner ${CGREEN_RUNNER_TESTS_LIBRARY} ${CGREEN_RUNNER_TESTS_LIBRARY} ${CGREEN_RUNNER_TESTS_LIBRARY})

  macro_add_test(NAME discoverer_acceptance_tests
    COMMAND cgreen-runner ${DISCOVERER_ACCEPTANCE_TESTS_LIBRARY})

  macro_add_test(NAME discoverer_unit_tests
    COMMAND cgreen-runner ${DISCOVERER_UNIT_TESTS_LIBRARY})

endif()
