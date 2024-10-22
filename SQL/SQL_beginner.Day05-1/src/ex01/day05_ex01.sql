set enable_seqscan to off;

CREATE INDEX idx_1 ON pizzeria (rating);

EXPLAIN
ANALYZE
SELECT
    menu.pizza_name,
    pizzeria.name AS pizzeria_name
FROM pizzeria, menu
WHERE
    pizzeria.id = menu.pizzeria_id;