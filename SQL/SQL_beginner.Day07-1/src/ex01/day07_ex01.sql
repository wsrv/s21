SELECT
    person.name,
    count(pizzeria_id) as count_of_visits
FROM person_visits
    JOIN person ON person_visits.person_id = person.id
group by person.name
order by 2 desc, 1
limit 4;