SELECT
    person.name as name,
    menu.pizza_name as pizza_name,
    menu.price as price,
    CAST(
        menu.price / 100 * (
            100 - person_discounts.discount
        ) AS DECIMAL(10, 2)
    ) as discount_price,
    pizzeria.name as pizzeria_name
FROM person_discounts
    JOIN person ON person.id = person_discounts.person_id
    JOIN menu on menu.pizzeria_id = person_discounts.pizzeria_id
    JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
ORDER BY 1, 2;