//
// Created by Matthew Crowell on 3/27/22 at 12:45 PM.
//

#ifndef KITTIES02_DATABASE_COMPONENT_HPP
#define KITTIES02_DATABASE_COMPONENT_HPP

#include "oatpp-1.3.0/oatpp/oatpp/core/macro/component.hpp"

#include "repositories.h"

class DatabaseComponent
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>,
                           db_connection_provider)([]
    {
        auto connection_provider{std::make_shared<oatpp::sqlite::ConnectionProvider>
            (DATABASE_FILE)};

        return oatpp::sqlite::ConnectionPool::createShared(connection_provider, 10,
                                                              std::chrono::seconds(5));
       } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<KittyRepository>, kitty_repository)([]
    {
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connection_provider);

        auto executor{std::make_shared<oatpp::sqlite::Executor>(connection_provider)};
        return std::make_shared<KittyRepository>(executor);
    } ());
};

#endif //KITTIES02_DATABASE_COMPONENT_HPP
