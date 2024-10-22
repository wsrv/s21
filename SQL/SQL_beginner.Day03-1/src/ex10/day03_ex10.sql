INSERT INTO person_order
VALUES( (
            SELECT max(id) + 1
            FROM person_order
        ), (
            SELECT id
            FROM person
            WHERE name = 'Denis'
        ), (
            SELECT id
            FROM menu
            WHERE
                pizza_name = 'sicilian pizza'
        ),
        '2022-02-24'
    ), ( (
            SELECT max(id) + 2
            FROM person_order
        ), (
            SELECT id
            FROM person
            WHERE name = 'Irina'
        ), (
            SELECT id
            FROM menu
            WHERE
                pizza_name = 'sicilian pizza'
        ),
        date '2022-02-24'
    );

-- SELECT * from person_order;

-- DELETE FROM person_order WHERE order_date = '2022-02-24';