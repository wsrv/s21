WITH
    RECURSIVE possible_route AS (
        SELECT
            point1 :: bpchar AS route,
            point1,
            point2,
            cost,
            cost as sum
        FROM nodes_name
        WHERE point1 = 'A'
        UNION ALL
        SELECT
            pr.route || ',' || pr.point2 AS route,
            cr.point1,
            cr.point2,
            pr.cost,
            pr.sum + cr.cost as sum
        FROM nodes_name as cr
            INNER JOIN possible_route as pr ON cr.point1 = pr.point2
        WHERE
            route NOT LIKE '%' || pr.point2 || '%'
    )
SELECT
    sum AS total_cost,
    '{' || route || ',' || point2 || '}' as route
FROM possible_route
WHERE
    length(route) = 7
    AND point2 = 'A'
    and (
        sum = (
            SELECT min(sum)
            FROM
                possible_route
            WHERE
                length(route) = 7
                AND point2 = 'A'
        )
        OR sum = (
            SELECT max(sum)
            FROM
                possible_route
            WHERE
                length(route) = 7
                AND point2 = 'A'
        )
    )
ORDER BY total_cost, route