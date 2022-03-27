//
// Created by Matthew Crowell on 3/27/22 at 12:14 PM.
//

#ifndef KITTIES02_ERROR_HANDLER_H
#define KITTIES02_ERROR_HANDLER_H

#include "dtos.h"

#include "oatpp-1.3.0/oatpp/oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/web/protocol/http/outgoing/ResponseFactory.hpp"

class ErrorHandler : public oatpp::web::server::handler::ErrorHandler
{
public:
    explicit ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>&);

    std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> handleError(
            const oatpp::web::protocol::http::Status&,
            const oatpp::String&,
            const Headers&
            ) override;

private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> object_mapper;

};

#endif //KITTIES02_ERROR_HANDLER_H
