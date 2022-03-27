//
// Created by Matthew Crowell on 3/27/22 at 1:13 PM.
//

#ifndef KITTIES02_TEST_CLIENT_HPP
#define KITTIES02_TEST_CLIENT_HPP

#include "oatpp-1.3.0/oatpp/oatpp/web/client/ApiClient.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp"

#include "entities.h"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class Testclient : public oatpp::web::client::ApiClient
{
    API_CLIENT_INIT(TestClient)

    API_CALL("POST", "/kitties", add_kitty, BODY_DTO(Object<KittyEntity>, kitty_entity));
    API_CALL("GET", "/kitties/{id}", get_kitty, PATH(Int32, kitty_id));
    API_CALL("DELETE", "/kitties/{kitty_id}", delete_kittym PATH(Int32, kitty_id));
    API_CALL("PUT", "/kitties/{kitty_id}", update_kitty, PATH(Int32, kitty_id));
};

#include OATPP_CODEGEN_END(ApiClient)

#endif //KITTIES02_TEST_CLIENT_HPP
