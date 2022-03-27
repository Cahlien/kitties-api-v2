//
// Created by Matthew Crowell on 3/27/22 at 8:28 AM.
//

#include "oatpp-test/UnitTest.hpp"
#include "oatpp/core/base/Environment.hpp"
#include "tests/kitty_controller_test.cpp"

#include <iostream>

namespace
{
    void runTests()
    {
        OATPP_RUN_TEST(KittyControllerTest);
    }
}

int main()
{
    oatpp::base::Environment::init();

    runTests();

    std::cout << "\nEnvironment:\n";
    std::cout << "Objects Count = " << oatpp::base::Environment::getObjectsCount() << '\n';
    std::cout << "Objects Created = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);
    oatpp::base::Environment::destroy();

    return 0;
}
