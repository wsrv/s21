SELECT
    menu.pizza_name,
    menu.price,
    pizzeria.name AS pizzeria_name
FROM menu
    FULL JOIN person_order person_order ON menu.id = person_order.menu_id
    FULL JOIN pizzeria pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE
    person_order.person_id IS NULL
ORDER BY
    menu.pizza_name,
    menu.price,
    pizzeria.name;