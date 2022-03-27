//
// Created by Matthew Crowell on 3/27/22 at 8:30 AM.
//
#include "../configs/app_component.hpp"
#include "../configs/database_component.hpp"
#include "../configs/swagger_component.hpp"

#include "../controllers/kitty_controller.hpp"
#include "../controllers/static_controller.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"


void run()
{
    AppComponent components;

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    oatpp::web::server::api::Endpoints endpoints{};

    endpoints.append(router->addController(KittyController::createShared())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(endpoints));
    router->addController(StaticController::createShared());

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connection_handler);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connection_provider);

    oatpp::network::Server server{connection_provider, connection_handler};

    OATPP_LOGD("Server", "running on port %s...", connection_provider->getProperty("port").toString()->c_str());

    server.run();

    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, db_connection_provider);
    db_connection_provider->stop();
}

int main(int argc, const char* argv[])
{
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::destroy();

    return 0;
}