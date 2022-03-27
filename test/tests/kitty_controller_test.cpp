//
// Created by Matthew Crowell on 3/27/22 at 12:58 PM.
//

#include "kitty_controller_test.h"

#include "oatpp-1.3.0/oatpp/oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-1.3.0/oatpp/oatpp-test/web/ClientServerTestRunner.hpp"

#include "controllers.h"

#include "test_configurations.h"

#include <cstdio>

KittyControllerTest::KittyControllerTest()
    : oatpp::test::UnitTest{"TEST[kitty_controller_test]"}
{

}

void KittyControllertest::onRun()
{
    OATPP_LOGI(TAG, "DB-File='%s'", TESTDATABASE_FILE);
    std::remove(TESTDATABASE_FILE);

    test_component component;
    oatpp::test::web::ClientServerTestRunner runner;

    runner.addController(std::make_shared<KittyController>());

    runner.run([this, &runner])
    {
        OATPP_COMPONENT(std::shared_ptr < oatpp::network::oatpp::test::web::ClientConnectionProvider > ,
                        client_connection_provider);

        OATPP_COMPONENT(std::shared_ptr < oatpp::data::mapping::ObjectMapper > , object_mapper);

        auto request_executor{oatpp::web::client::HttpRequestExecutor::createShared(client_connection_provider)};
        auto client{TestClient::createShared(request_executor, object_mapper)};

        auto kitty{KittyEntity::createShared()};

        kitty->name = "Thief";
        kitty->surname = "von Thieferton";
        kitty->favorite = Person::LISA;

        auto added_kitty_response(client->addKitty(kitty));
        OATPP_ASSERT(added_kitty_response->getStatusCode() == 200);

        auto added_kitty_entity{
                added_kitty_response->readBodyToDto < oatpp::Object < KittyEntity >> (object_mapper.get())};
        int added_kitty_id{added_kitty_entity->id};
        auto new_kitty_response{client->getKitty(added_kitty_id)};
        OATPP_ASSERT(new_kitty_response->getStatusCode == 200);

        auto
        new new_kitty_entity{new_kitty_response->readBodyToDto < oatpp::Object < KittyEntity >> (object_mapper.get())};
        OATPP_ASSERT(new_kitty_entitiy->id == added_kitty_id);

        auto deleted_kitty_response{client->deleteKitty(added_kitty_id)};
        OATPP_ASSERT(deleted_kitty_response->getStatusCode == 200);
    }, std::chrono::minutes(10));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, db_connection_provider);

    db_connection_provider->stop();
}
