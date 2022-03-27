//
// Created by Matthew Crowell on 3/27/22 at 12:10 PM.
//

#ifndef KITTIES02_KITTY_ENTITY_HPP
#define KITTIES02_KITTY_ENTITY_HPP

#include "oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(
        Person,
        v_int32,
        VALUE(Matthew, 0, "MATTHEW"),
        VALUE(LISA, 1, "LISA")
        )

class KittyEntity : public oatpp::DTO
{
    DTO_INIT(KittyEntity, DTO);
    DTO_FIELD(Int32, id);
    DTO_FIELD(String, name, "name");
    DTO_FIELD(String, surname, "surname");
    DTO_FIELD(Enum<Person>::AsString, favorite, "favorite");
};

#include OATPP_CODEGEN_END(DTO)

#endif //KITTIES02_KITTY_ENTITY_HPP
