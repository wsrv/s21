SELECT
    pizza_name,
    pizzeria.name AS pizzeria_name
FROM menu
    JOIN person_order ON menu.id = person_order.menu_id
    JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    JOIN person ON person_order.person_id = person.id
WHERE
    person.name = 'Anna'
    OR person.name = 'Denis'
ORDER BY
    pizza_name,
    pizzeria_name;