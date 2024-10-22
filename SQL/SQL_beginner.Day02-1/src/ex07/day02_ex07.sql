SELECT
    pizzeria.name AS pizzeria_name
FROM person
    JOIN person_visits ON person_id = person_visits.person_id
    JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
    JOIN menu ON menu.pizzeria_id = person_visits.pizzeria_id
WHERE
    person.name = 'Dmitriy'
    AND menu.price < 800
    AND person_visits.visit_date = '2022-01-08'