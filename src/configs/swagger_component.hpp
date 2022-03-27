//
// Created by Matthew Crowell on 3/27/22 at 12:49 PM.
//

#ifndef KITTIES02_SWAGGER_COMPONENT_HPP
#define KITTIES02_SWAGGER_COMPONENT_HPP

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resource.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/macro/component.hpp"

class SwaggerComponent
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swagger_document_info)([]
    {
        oatpp::swagger::DocumentInfo::Builder builder{};
        builder
            .setTitle("Kitty Service")
            .setDescription("A simple API about the Crowell Kitties, made for practice with OatPP!")
            .setVersion("1.0.0")
            .setContactName("Matthew Crowell")
            .setContactEmail("doncha@wannagno.com")
            .setContactUrl("https://crowell.dev")
            .setLicenseName("GNU General Public License 2.0")
            .setLicenseUrl("https://github.com/Cahlien/kitties-api-v2/blob/main/LICENSE")
            .addServer("http://localhost:7777", "server on localhost");

        return builder.build();
    } ());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swagger_resources)([]
    {
        return oatpp::swager::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    } ());
};

#endif //KITTIES02_SWAGGER_COMPONENT_HPP
