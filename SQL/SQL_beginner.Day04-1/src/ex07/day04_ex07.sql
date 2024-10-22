INSERT INTO
    person_visits (
        id,
        person_id,
        pizzeria_id,
        visit_date
    )
VALUES ( (
            SELECT max(id)
            FROM
                person_visits
        ) + 1, (
            SELECT id
            FROM person
            WHERE
                name = 'Dmitriy'
        ), (
            SELECT
                pizzeria.id
            FROM menu
                LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
                LEFT JOIN mv_dmitriy_visits_and_eats ON TRUE
            WHERE
                menu.price < 800
                AND mv_dmitriy_visits_and_eats.name != pizzeria.name
            LIMIT
                1
        ), '2022-01-08'
    );

-- SELECT * FRom person_visits;

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

-- SELECT * FRom mv_dmitriy_visits_and_eats;