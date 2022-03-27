CREATE TABLE kitties (
                         id          INTEGER PRIMARY KEY,
                         name        VARCHAR UNIQUE,
                         surname     VARCHAR,
                         favorite    VARCHAR
);

INSERT INTO kitties
(name, surname, favorite) VALUES ('Thief', 'von Thieferton', 'LISA');