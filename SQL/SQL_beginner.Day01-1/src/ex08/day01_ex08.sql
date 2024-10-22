SELECT
    order_date,
    CONCAT(
        temp.name,
        ' (age:',
        temp.age,
        ')'
    ) as person_information
FROM person_order
    NATURAL JOIN (
        SELECT
            id as person_id,
            name,
            age
        FROM person
    ) as temp
ORDER BY
    order_date,
    person_information;