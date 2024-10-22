SELECT
    person.name AS person_name
FROM person
    JOIN person_order ON person.id = person_order.person_id
    JOIN menu ON menu.id = person_order.menu_id
WHERE (
        menu.pizza_name = 'pepperoni pizza'
        OR menu.pizza_name = 'cheese pizza'
    )
    AND person.gender = 'female'
GROUP BY person_name
having
    count(menu.pizza_name) > 1;