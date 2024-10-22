SELECT
    COALESCE(person.name, '-') as person_name,
    our_dates.visit_date,
    COALESCE(pizzeria.name, '-')
FROM person
    FULL JOIN (
        SELECT *
        FROM person_visits
        WHERE
            visit_date >= '2022-01-01'
            AND visit_date <= '2022-01-03'
    ) AS our_dates ON our_dates.person_id = person.id
    FULL JOIN pizzeria ON pizzeria.id = our_dates.pizzeria_id
ORDER BY
    person_name,
    our_dates.visit_date,
    pizzeria.name;