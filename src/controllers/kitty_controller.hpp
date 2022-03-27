//
// Created by Matthew Crowell on 3/27/22 at 10:59 AM.
//

#ifndef KITTIES02_KITTY_CONTROLLER_HPP
#define KITTIES02_KITTY_CONTROLLER_HPP

#include "kitty_service.h"

#include "oatpp-1.3.0/oatpp/oatpp/web/server/api/ApiController.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class KittyController : public oatpp::web::server::api::ApiController
{
public:
    explicit KittyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
            : oatpp::web::server::api::ApiController{object_mapper}
    {

    }

    static std::shared_ptr<KittyController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
    {
        return std::make_shared<KittyController>(object_mapper);
    }

    ENDPOINT_INFO(add_kitty)
    {
        info->summary = "Add a New Kitty";
        info->addConsumes<Object<KittyEntity>>("application/json");
        info->addResponse<Object<KittyEntity>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "kitties", add_kitty, BODY_DTO(Object<KittyEntity>, kitty_entity))
    {
        return createDtoResponse(Status::CODE_200, kitty_service.add_kitty(kitty_entity));
    }

    ENDPOINT_INFO(update_kitty)
    {
        info->summary = "Update a Kitty by Kitty's Id";
        info->addConsumes<Object<KittyEntity>>("application/json");
        info->addResponse<Object<KittyEntity>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("PUT", "kitties/{kitty_id}", update_kitty, PATH(Int32, kitty_id), BODY_DTO(Object<KittyEntity>,
            kitty_entity))
    {
        kitty_entity->id = kitty_id;
        return createDtoResponse(Status::CODE_200, kitty_service.update_kitty(kitty_entity));
    }

    ENDPOINT_INFO(get_kitty_by_id)
    {
        info->summary = "Get a Kitty by Kitty's Id";
        info->addResponse<Object<KittyEntity>>(Status::CODE_200, "application/json");
        info->addResponse<Object<KittyEntity>>(Status::CODE_404, "application/json");
        info->addResponse<Object<KittyEntity>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "kitties/{id}", get_kitty_by_id, PATH(Int32, id))
    {
        return createDtoResponse(Status::CODE_200, kitty_service.get_kitty_by_id(id));
    }

    ENDPOINT_INFO(get_kitties)
    {
        info->summary = "Get All Kitties";
        info->addResponse<Object<KittyEntity>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    }
    ENDPOINT(
            "GET", "kitties",
            get_kitties,
            QUERY(UInt32, offset, "offset", 0U),
            QUERY(UInt32, limit, "limit", 10U)
            )
    {

        return createDtoResponse(Status::CODE_200, kitty_service.get_kitties(offset, limit));
    }

    ENDPOINT_INFO(remove_kitty)
    {
        info->summary = "Remove a Kitty by Kitty's Id";
        info->addResponse<Object<KittyEntity>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("DELETE", "kitties/{kitty_id}", remove_kitty, PATH(Int32, kitty_id))
    {
        return createDtoResponse(Status::CODE_200, kitty_service.remove_kitty(kitty_id));
    }
private:
    KittyService kitty_service;
};

#include OATPP_CODEGEN_END(ApiController)

#endif //KITTIES02_KITTY_CONTROLLER_HPP
