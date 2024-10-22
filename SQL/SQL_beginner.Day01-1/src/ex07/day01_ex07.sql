SELECT
    order_date as order_date,
    CONCAT(name, ' (age:', age, ')') as person_information
FROM person
    JOIN person_order on person.id = person_order.person_id
ORDER BY
    order_date,
    person_information;