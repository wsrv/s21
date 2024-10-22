CREATE OR REPLACE FUNCTION fnc_persons (IN pperson varchar DEFAULT 'Dmitriy', IN pprice numeric DEFAULT 500, IN pdate date DEFAULT '2022-01-08')
RETURNS TABLE(name varchar) AS $$
BEGIN RETURN QUERY
        SELECT DISTINCT pizzeria.name AS pizzeria_name
        FROM person_visits person_visits
                 JOIN person_order person_order
                      ON person_order.person_id = person_visits.person_id
                          AND person_order.menu_id IN
                              (SELECT id
                               FROM menu
                               WHERE price < pprice
                                 AND pizzeria_id = person_visits.pizzeria_id)
                 JOIN pizzeria pizzeria ON pizzeria.id = person_visits.pizzeria_id
                 JOIN person  ON person.id = person_visits.person_id
        WHERE person.name = pperson
          AND person_visits.visit_date = pdate;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT *
FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna', pprice := 1300, pdate := '2022-01-01');