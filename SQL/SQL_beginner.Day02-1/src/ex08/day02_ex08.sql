SELECT
    person.name AS person_name
FROM person
    JOIN person_order ON person_id = person_order.person_id
    JOIN menu ON menu.id = person_order.menu_id
WHERE (
        person.address = 'Moscow'
        OR person.address = 'Samara'
    )
    AND (
        menu.pizza_name = 'pepperoni pizza'
        OR menu.pizza_name = 'mushroom pizza'
    )
    AND person.gender = 'male'
GROUP BY person.name
ORDER BY person_name DESC