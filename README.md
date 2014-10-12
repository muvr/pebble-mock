#Unit testing and mocking library for Pebble
The motivation is to allow programmers to include _proper_ testing for the Pebble apps; and to allow the test code to run on development machines. So, this library exposes mocks for the Pebble APIs, and fits well into GTest.

Onwards to an example:

```cpp
#include <gtest/gtest.h>
#include "mock.h"

using namespace pebble::mock;

class my_test : public testing::Test {
private:
    std::vector<AccelRawData> raw_data;
protected:
    static void handler(AccelRawData *data, uint32_t num_samples, uint64_t timestamp);
public:
	my_test();
};

my_test::my_test() {
    AccelRawData a = {.x = 1, .y = 100, .z = -400 };
    for (int i = 0; i < 20; i++) raw_data.push_back(a);
}

static void my_test::handler(AccelRawData *data, uint32_t num_samples, uint64_t timestamp) {
    EXPECT_EQ(...);
}

TEST_F(my_test, Demo) {
    accel_data_subscribe(20, handler);
    Pebble::accelService << raw_data;
}
```

The crucial aspects of the test are:

* ``accel_data_subscribe`` matches the Pebble API, but is controllable through the ``Pebble::accelService`` instance.
* The ``Pebble`` class exposes the service mock controls; in this case, the ``AccelService``.
