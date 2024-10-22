SELECT(
        SELECT name
        FROM person
        WHERE
            id = total.person_id
    ) as person_name, (
        SELECT name
        FROM pizzeria
        WHERE
            id = total.pizzeria_id
    ) as pizzeria_name,
    total.visit_date
FROM(
        SELECT
            person_id,
            pizzeria_id,
            visit_date
        FROM person_visits
        WHERE
            visit_date BETWEEN '2022.01.07' AND '2022.01.09'
    ) as total
ORDER BY
    person_name,
    pizzeria_name DESC;