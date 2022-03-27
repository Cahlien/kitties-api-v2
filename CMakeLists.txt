cmake_minimum_required(VERSION 3.21)

set(project_name kitties02)

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-sqlite       1.3.0 REQUIRED)
find_package(oatpp-swagger      1.3.0 REQUIRED)
find_package(SQLite3            REQUIRED)

add_library(
        ${project_name}-lib
        src/advisors/error_handler.cpp
        src/configs/app_component.hpp
        src/configs/database_component.hpp
        src/configs/swagger_component.hpp
        src/controllers/kitty_controller.hpp
        src/dtos/status.hpp
        src/entities/kitty_entity.hpp
        src/models/page.hpp
        src/repos/kitty_repository.hpp
        src/services/kitty_service.cpp
)
target_include_directories(${project_name}-lib PRIVATE src src/include)
target_link_libraries(
        ${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-sqlite
        PUBLIC oatpp::oatpp-swagger
        PUBLIC SQLite::SQLite3
)

add_definitions(
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/src/resources/db.sqlite"
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test/resources/test-db.sqlite"
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/src/resources/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_executable(${project_name}.exe src/app.cpp)
target_include_directories(${project_name}.exe PRIVATE src/include)
target_link_libraries(${project_name}.exe PRIVATE ${project_name}-lib)
add_dependencies(${project_name}.exe ${project_name}-lib)

add_executable(
        ${project_name}-test
        test/app/test_client.hpp
        test/app/config/test_component.hpp
        test/app/config/test_database_component.hpp
        test/tests.cpp
        test/tests/kitty_controller_test.cpp
)
target_include_directories(
        ${project_name}-test
        PRIVATE src/include
        PRIVATE test
        PRIVATE test/app
        PRIVATE test/include
)
target_link_libraries(${project_name}-test PRIVATE ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(all-tests ${project_name}-test)