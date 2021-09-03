#include "stub.h"


intptr_t do_stub(TestReporter* test_reporter, RecordedExpectation *expectation, void (*stub_function_callback)(void *), CgreenVector *callback_args) {

#if defined (__amd64__) || defined (__x86_64__)  // TODO: check functionality on other patforms

    switch(cgreen_vector_size(callback_args)) {
    case 0:
        return ((intptr_t (*)(void))stub_function_callback)();
    case 1:
        return ((intptr_t (*)(void *))stub_function_callback)(cgreen_vector_get(callback_args, 0));
    case 2:
        return ((intptr_t (*)(void *, void *))stub_function_callback)(cgreen_vector_get(callback_args, 0), cgreen_vector_get(callback_args, 1));
    case 3:
        return ((intptr_t (*)(void *, void *, void *))stub_function_callback)(cgreen_vector_get(callback_args, 0), cgreen_vector_get(callback_args, 1), cgreen_vector_get(callback_args, 2));
    default:
        test_reporter->assert_true(
            test_reporter,
            expectation->test_file,
            expectation->test_line,
            false,
            "Stub can't be called! Stubs are not yet supported for as much as %d args.", cgreen_vector_size(callback_args));
    }

#else
    test_reporter->assert_true(
        test_reporter,
        expectation->test_file,
        expectation->test_line,
        false,
        "Dynamic stubbing not supported on this architecture.");
#endif

    return (intptr_t)NULL;
}