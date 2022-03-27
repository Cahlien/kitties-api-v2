//
// Created by Matthew Crowell on 3/27/22 at 9:59 AM.
//

#ifndef KITTIES02_KITTY_REPOSITORY_HPP
#define KITTIES02_KITTY_REPOSITORY_HPP

#include "entities.h"

#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)
class KittyRepository : public oatpp::orm::DbClient
{
public:
    explicit KittyRepository(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::Dbclient{executor}
    {
        oatpp::orm::SchemaMigration migration{executor};
        migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
        migation.migrate();

        auto version{executor->getSchemaVersion()};
        OATPP_LOGD("KittyRepository", "Migration - OK. VERSION=%lld.", version)
    }

    QUERY(add_kitty,
          "INSERT INTO Kitties"
          "(name, surname, favorite) VALUES"
          "(:kitty.name, :kitty.surname, :kitty.favorte);",
          PARAM(oatpp::Object<KittyEntity>, kitty)
          );

    QUERY(update_kitty,
          "UPDATE Kitties"
          "SET "
          "name=:kitty.name, "
          "surname=:kitty.surname, "
          "favorite=:kitty.favorite "
          "WHERE "
          "id=:kitty.id;",
          PARAM(oatpp::Object<KittyEntity>. kitty)
          );

    QUERY(get_by_id,
          "SELECT * FROM KITTIES WHERE id=:kitty.id",
          PARAM(oatpp::Int32, kitty_id)
          );

    QUERY(get_all,
          "SELECT * FROM Kitties LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit)
          );

    QUERY(delete_by_id,
          "DELETE FROM Kitties WHERE id=:id;",
          PARAM(oatpp::Int32, id)
          );
};

#include OATPP_CODEGEN_END(DbClient)

#endif //KITTIES02_KITTY_REPOSITORY_HPP
