SELECT
    pizzeria.name as name,
    COUNT(*) as count_of_orders,
    round (avg(menu.price), 2) as average_price,
    max(menu.price) as max_price,
    min(menu.price) as min_price
FROM person_order
    JOIN menu ON menu.id = person_order.menu_id
    JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY pizzeria.name
ORDER BY pizzeria.name;