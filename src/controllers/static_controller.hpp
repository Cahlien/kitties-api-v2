//
// Created by Matthew Crowell on 3/27/22 at 11:56 AM.
//

#ifndef KITTIES02_STATIC_CONTROLLER_HPP
#define KITTIES02_STATIC_CONTROLLER_HPP

#include "oatpp-1.3.0/oatpp/oatpp/web/server/api/ApiController.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class StaticController : public oatpp::web::server::api::ApiController
{
public:
    StaticController(const std::shared_ptr <ObjectMapper>& object_mapper)
            : oatpp::web::server::api::ApiController(object_mapper)
    {
    }

    static std::shared_ptr<StaticController>
        createShared(OATPP_COMPONENT(std::shared_ptr <ObjectMapper>, object_mapper))
    {
        return std::make_shared<StaticController>(object_mapper);
    }

    ENDPOINT("GET", "/", root)
    {
            const char* html =
                    "<html lang='en-us'>"
                    "  <head>"
                    "    <meta charset=utf-8 />"
                    "  </head>"
                    "  <body>"
                    "    <p>Welcome to the Kitties API v2 by the Developers Crowell!</p>"
                    "    <a href='swagger/ui/>Checkout Swagger-UI Page</a>"
                    "  </body>"
                    "</html>";

            auto response = createResponse(Status::CODE_200, html);
            response->putHeader(Header::CONTENT_TYPE, "text/html");

            return response;
    };
};

#include OATPP_CODEGEN_END(ApiController)

#endif //KITTIES02_STATIC_CONTROLLER_HPP
