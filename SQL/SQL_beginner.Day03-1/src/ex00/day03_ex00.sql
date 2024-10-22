SELECT
    menu.pizza_name,
    menu.price,
    pizzeria.name,
    person_visits.visit_date
FROM person
    JOIN person_visits ON person.id = person_visits.person_id
    JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    JOIN menu ON pizzeria.id = menu.pizzeria_id
WHERE (
        menu.price BETWEEN 800 AND 1000
    )
    AND person.name = 'Kate'
ORDER BY
    menu.pizza_name,
    menu.price,
    pizzeria.name;