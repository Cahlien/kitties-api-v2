//
// Created by Matthew Crowell on 3/27/22 at 10:10 AM.
//

#ifndef KITTIES02_KITTY_SERVICE_H
#define KITTIES02_KITTY_SERVICE_H

#include "repositories.h"
#include "dtos.h"
#include "models.h"


#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class KittyService
{
public:
    oatpp::Object<KittyEntity> add_kitty(const oatpp::Object<KittyEntity>&);

    oatpp::Object<KittyEntity> update_kitty(const oatpp::Object<KittyEntity>&);

    oatpp::Object<KittyEntity> get_kitty_by_id(const oatpp::Int32& id, const
        oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);

    oatpp::Object<Page<oatpp::Object<KittyEntity>>> get_kitties(const oatpp::UInt32&, const oatpp::UInt32&);

    oatpp::Object<StatusDTO> remove_kitty(const oatpp::Int32&);

private:
    typedef oatpp::web::protocol::http::Status Status;

    OATPP_COMPONENT(std::shared_ptr<KittyRepository>, kitty_repository);
};

#endif //KITTIES02_KITTY_SERVICE_H
