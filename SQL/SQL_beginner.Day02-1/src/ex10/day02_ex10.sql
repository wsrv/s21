SELECT
    person1.name AS person_name_1,
    person2.name AS person_name_2,
    person1.address as common_address
FROM person person1
    JOIN person person2 ON person1.address = person2.address AND person1.id > person2.id
order by
    person_name_1,
    person_name_2,
    common_address;