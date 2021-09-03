#! /usr/bin/env python3

from string import Template

_C_FILE_TEMPLATE = Template('''
#include "stub.h"


intptr_t do_stub(TestReporter* test_reporter, RecordedExpectation *expectation, void (*stub_function_callback)(void *), CgreenVector *callback_args) {

#if defined (__amd64__) || defined (__x86_64__)  // TODO: check functionality on other patforms

    switch(cgreen_vector_size(callback_args)) {
    case 0:
        return ((intptr_t (*)(void))stub_function_callback)();
$cases
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
''')

def generate_switch_cases():
    tab_stop = '    '
    for i in range(1, 64):
        yield '''
'''
