#include "kitty_service.h"
#include "entities.h"

oatpp::Object<KittyEntity> KittyService::add_kitty(const oatpp::Object<KittyEntity>& kitty)
{
    auto result{kitty_repository->add_kitty(kitty)};
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage());

    auto kitty_id{oatpp::sqlite::Utils::getLastInsertRowId(result->getConnection())};
    return this->get_kitty_by_id((v_int32) kitty_id);
}

oatpp::Object<KittyEntity> KittyService::update_kitty(const oatpp::Object<KittyEntity>& kitty)
{
    auto result{kitty_repository->update_kitty(kitty)};
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage());
    return get_kitty_by_id(kitty->id);
}

oatpp::Object<KittyEntity>
KittyService::get_kitty_by_id(const oatpp::Int32& id,
                              const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection)
{
    auto result{kitty_repository->get_by_id(id, connection)};
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage());
    OATPP_ASSERT_HTTP(result->hasMoreToFetch(), Status::CODE_404, "Kitty not found");

    auto response = result->fetch<oatpp::Vector<oatpp::Object<KittyEntity>>>();
    OATPP_ASSERT_HTTP(response->size() == 1, Status::CODE_500, "Unknown error");

    return response[0];
}

oatpp::Object<Page<oatpp::Object<KittyEntity>>> KittyService::get_kitties(const oatpp::UInt32& offset,
                                                                          const oatpp::UInt32& limit)
{
    oatpp::UInt32 count_to_fetch{limit};

    if(limit > 10)
    {
        count_to_fetch = 10;
    }

    auto result{kitty_repository->get_all(offset, limit)};
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage());

    auto items= result->fetch<oatpp::Vector<oatpp::Object<KittyEntity>>>();
    auto page{Page<oatpp::Object<KittyEntity>>::createShared()};

    page->offset = offset;
    page->limit = count_to_fetch;
    page->count = items->size();
    page->content = items;

    return page;
}

oatpp::Object<StatusDTO> KittyService::remove_kitty(const oatpp::Int32& kitty_id)
{
    auto result{kitty_repository->delete_by_id(kitty_id)};
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage());

    auto status= StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Kitty was successfully removed from the database";

    return status;
}