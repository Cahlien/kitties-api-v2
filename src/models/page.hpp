//
// Created by Matthew Crowell on 3/27/22 at 8:59 AM.
//

#ifndef KITTIES02_PAGE_HPP
#define KITTIES02_PAGE_HPP
#include "entities.h"

#include OATPP_CODEGEN_BEGIN(DTO)

template<typename T>
class Page : public oatpp::DTO
{
    DTO_INIT(Page, DTO);

    DTO_FIELD(UInt32, offset);
    DTO_FIELD(UInt32, limit);
    DTO_FIELD(UInt32, count);
    DTO_FIELD(Vector<T>, content);

};

class KittiesPage : public Page<oatpp::Object<KittyEntity>
{
    DTO_INIT(KittiesPage, Page<oatpp::Object<KittyEntity>>);
};

#include OATPP_CODEGEN_END(DTO)

#endif //KITTIES02_PAGE_HPP
