SELECT DISTINCT person.name
FROM person
    JOIN ON person_order on person.id = person_order.person_id
ORDER BY 1