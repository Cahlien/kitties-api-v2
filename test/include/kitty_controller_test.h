//
// Created by Matthew Crowell on 3/27/22 at 12:57 PM.
//

#ifndef KITTIES02_KITTY_CONTROLLER_TEST_H
#define KITTIES02_KITTY_CONTROLLER_TEST_H

#include "oatpp-1.3.0/oatpp/oatpp-test/UnitTest.hpp"

class KittyControllerTest : public oatpp::test::UnitTest
{
public:
    KittyControllerTest();

    void onRun() override;
};

#endif //KITTIES02_KITTY_CONTROLLER_TEST_H
