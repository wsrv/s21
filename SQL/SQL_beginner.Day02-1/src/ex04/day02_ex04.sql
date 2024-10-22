SELECT
    menu.pizza_name,
    pizzeria.name as pizzeria_name,
    menu.price
FROM menu
    JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE
    menu.pizza_name = 'pepperoni pizza'
    OR menu.pizza_name = 'mushroom pizza'
order by
    pizza_name,
    pizzeria_name;