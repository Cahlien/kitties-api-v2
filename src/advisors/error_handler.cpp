//
// Created by Matthew Crowell on 3/27/22 at 12:14 PM.
//

#include "error_handler.h"

ErrorHandler::ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& object_mapper)
    : object_mapper{object_mapper}
{

}

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> ErrorHandler::handleError(
        const oatpp::web::protocol::http::Status& status,
        const oatpp::String& message,
        const ErrorHandler::Headers& headers)
{
    auto error{StatusDTO::createShared()};
    error->status = "ERROR";
    error->code = status.code;
    error->message = message;

    auto response{oatpp::web::protocol::http::outgoing::ResponseFactory::createResponse(status, error, object_mapper)};

    for(const auto& pair : headers.getAll())
    {
        response->putHeader(pair.first.toString(), pair.second.toString());
    }

    return response;
}