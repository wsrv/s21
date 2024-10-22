CREATE UNIQUE INDEX idx_menu_unique ON menu (pizzeria_id, pizza_name);

set enable_seqscan = off;

EXPLAIN ANALYZE SELECT pizza_name, pizzeria_id FROM menu;