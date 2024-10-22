SELECT
    person.id as person_id,
    person.name as person_name,
    person.age,
    person.gender,
    person.address,
    pizzeria.id as pizzeria_id,
    pizzeria.name as pizzeria_name,
    pizzeria.rating
FROM person, pizzeria
ORDER BY
    person.id,
    pizzeria.id;