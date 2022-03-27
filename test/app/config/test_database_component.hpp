//
// Created by Matthew Crowell on 3/27/22 at 2:07 PM.
//

#ifndef KITTIES02_TEST_DATABASE_COMPONENT_HPP
#define KITTIES02_TEST_DATABASE_COMPONENT_HPP
#include "repositories.h"

class TestDatabaseComponent
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>,
    db_connection_provider)([]
    {
        auto connection_provider{std::make_shared<oatpp::sqlite::ConnectionProvider>(TESTDATABASE_FILE)};

        return oatpp::sqlite::ConnectionPool::createShared(connection_provider, 10, std::chrono::seconds(5));
    } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<KittyRepository>, kitty_repository)([]
    {
        auto executor{std::make_shared<oatpp::sqlite::Executor>(connect)};

        return std::make_shared<KittyRepository>(executor);
    } ());
};

#endif //KITTIES02_TEST_DATABASE_COMPONENT_HPP
