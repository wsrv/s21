WITH male AS (
        SELECT
            pizzeria.name AS pizzeria_name
        FROM pizzeria
            JOIN person_visits on pizzeria.id = person_visits.pizzeria_id
            JOIN person on gender = 'male' AND person.id = person_visits.person_id
        ORDER BY
            1
    ),
    female AS (
        SELECT
            pizzeria.name AS pizzeria_name
        FROM pizzeria
            JOIN person_visits on pizzeria.id = person_visits.pizzeria_id
            JOIN person on gender = 'female' AND person.id = person_visits.person_id
        ORDER BY 1
    ) (
        SELECT *
        FROM female
        EXCEPT ALL
        SELECT *
        FROM male
    )
UNION (
    SELECT *
    FROM male
    EXCEPT ALL
    SELECT *
    FROM female
)
ORDER BY 1;