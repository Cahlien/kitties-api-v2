//
// Created by Matthew Crowell on 3/27/22 at 12:06 PM.
//

#ifndef KITTIES02_STATUS_HPP
#define KITTIES02_STATUS_HPP

#include "oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp"
#include "oatpp-1.3.0/oatpp/oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class StatusDTO : public oatpp::DTO
{
    DTO_INIT(StatusDTO, DTO);

    DTO_FIELD_INFO(status)
    {
        info->description = "A short-form text description of the status.";
    }
    DTO_FIELD(String, status);

    DTO_FIELD_INFO(code)
    {
        info->description = "Status Code";
    }
    DTO_FIELD(Int32, code);

    DTO_FIELD_INFO(message)
    {
        info->description = "Long-form text message";
    }
    DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif //KITTIES02_STATUS_HPP
