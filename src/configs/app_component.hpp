//
// Created by Matthew Crowell on 3/27/22 at 12:35 PM.
//

#ifndef KITTIES02_APP_COMPONENT_HPP
#define KITTIES02_APP_COMPONENT_HPP

#include "error_handler.h"

#include "oatpp-1.3.0/oatpp/oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/web/server/HttpRouter.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp-1.3.0/oatpp/oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp-1.3.0/oatpp/oatpp/core/macro/component.hpp"

#include "configurations.h"

class AppComponent
{
public:
    SwaggerComponent swagger_component;
    DatabaseComponent database_component;

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, api_object_mapper)([]
    {
        auto object_mapper{oatpp::parser::json::mapping::ObjectMapper::createShared()};
        object_mapper->getDeserializer()->getConfig()->allowUnknownFields = false;

        return object_mapper;
    } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, server_connection_provider)([]
    {
        return oatpp::network::tcp::server::ConnectionProvider::createShared();
    } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, http_router)([]
    {
        return oatpp::web:server::oatpp::web::server::HttpRouter::createShared();
    } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, server_connection_handler)([]
    {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, object_mapper);

        auto connection_handler{oatpp::web::server::HttpConnectionHandler::createShared()};
        connection_handler->setErrorHandler(std::make_shared<ErrorHandler>(object_mapper));

        return connection_handler;
    } ());
};

#endif //KITTIES02_APP_COMPONENT_HPP
