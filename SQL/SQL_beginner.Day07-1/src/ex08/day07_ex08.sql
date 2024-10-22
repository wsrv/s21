SELECT
    person.address as address,
    pizzeria.name as name,
    COUNT(*) AS count_of_orders
from person_order
    join person on person_order.person_id = person.id
    join menu ON person_order.menu_id = menu.id
    join pizzeria ON menu.pizzeria_id = pizzeria.id
GROUP BY
    person.address,
    pizzeria.name
ORDER BY
    person.address,
    pizzeria.name;