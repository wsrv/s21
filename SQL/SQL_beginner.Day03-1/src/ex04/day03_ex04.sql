WITH male AS (
        SELECT
            DISTINCT pizzeria.name AS pizzeria_name
        FROM pizzeria
            JOIN person_visits on pizzeria.id = person_visits.pizzeria_id
            JOIN person on gender = 'male'
            JOIN person_order po on person.id = po.person_id
            JOIN menu menu on menu.id = po.menu_id AND person_visits.pizzeria_id = menu.pizzeria_id AND person.id = person_visits.person_id
    ), female AS (
        SELECT
            DISTINCT pizzeria.name AS pizzeria_name
        FROM pizzeria
            JOIN person_visits on pizzeria.id = person_visits.pizzeria_id
            JOIN person_order on person_visits.person_id = person_order.person_id
            JOIN menu on menu.id = person_order.menu_id
            JOIN person on gender = 'female' AND person_visits.pizzeria_id = menu.pizzeria_id AND person.id = person_visits.person_id
        ORDER BY 1
    ) (
        SELECT *
        FROM female
        EXCEPT ALL
        SELECT *
        FROM male
    )
union (
    SELECT *
    FROM male
    EXCEPT ALL
    SELECT *
    FROM female
)
ORDER BY 1;