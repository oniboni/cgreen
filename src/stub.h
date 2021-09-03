#ifndef STUB_H
#define STUB_H

#include <cgreen/constraint.h>
#include <cgreen/reporter.h>
#include <cgreen/internal/mocks_internal.h>

#ifdef __cplusplus
namespace cgreen {
    extern "C" {
#endif

intptr_t do_stub(TestReporter* test_reporter, RecordedExpectation *expectation, void (*stub_function_callback)(void *), CgreenVector *callback_args);

#ifdef __cplusplus
    }
}
#endif

#endif  // STUB_H