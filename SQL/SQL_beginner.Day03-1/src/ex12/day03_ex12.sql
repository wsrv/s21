INSERT INTO person_order
SELECT generate_series( (
            SELECT max(id) + 1
            FROM person_order
        ), (
            SELECT max(id)
            FROM person_order
        ) + (
            SELECT max(id)
            FROM
                person
        )
    ),
    generate_series( (
            SELECT min(id)
            FROM person
        ), (
            SELECT max(id)
            FROM person
        )
    ), (
        SELECT id
        FROM menu
        WHERE
            pizza_name = 'greek pizza'
    ),
    '2022-02-25';

-- SELECT * from person_order;