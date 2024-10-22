Напишите оператор SQL, чтобы видеть 3 любимых ресторана по посещениям и заказам 
в одном списке (добавьте столбец action_type со значениями «заказ» или «посещение», 
это зависит от данных из соответствующей таблицы). Пожалуйста, взгляните на 
образец данных ниже. Результат должен быть отсортирован по столбцу action_type 
в возрастающем режиме и по столбцу count в нисходящем режиме.


WITH visits as (
        SELECT
            pizzeria.name,
            COUNT(*),
            'visit' AS action_type
        FROM pizzeria
            join person_visits on person_visits.pizzeria_id = pizzeria.id
        GROUP BY
            pizzeria.name
        ORDER BY count DESC
        LIMIT 3
    ), orders AS(
        SELECT
            pizzeria.name,
            COUNT(*),
            'order' AS action_type
        FROM person_order
            INNER JOIN menu ON menu.id = person_order.menu_id
            INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
        GROUP BY pizzeria.name
        ORDER BY count DESC
        LIMIT 3
    )
SELECT *
FROM visits
UNION ALL
SELECT *
FROM orders
ORDER BY
    action_type ASC,
    count DESC;