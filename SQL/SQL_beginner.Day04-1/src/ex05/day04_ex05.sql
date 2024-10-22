CREATE VIEW
    v_price_with_discount AS
SELECT
    name,
    m.pizza_name,
    m.price, (m.price - m.price * 0.1) :: int AS discount_price
FROM person
    JOIN person_order on person.id = person_order.person_id
    JOIN menu m on m.id = person_order.menu_id
ORDER BY 1, 2;

DROP VIEW v_price_with_discount;

SELECT * FROM v_price_with_discount;