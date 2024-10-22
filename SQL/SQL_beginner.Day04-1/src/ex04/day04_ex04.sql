CREATE VIEW
    v_symmetric_union AS
WITH R AS (
        SELECT person_id
        FROM person_visits
        WHERE
            visit_date = '2022-01-02'
    ),
    S AS (
        SELECT person_id
        FROM person_visits
        WHERE
            visit_date = '2022-01-06'
    ),
    R_S AS (
        SELECT *
        FROM R
        EXCEPT
        SELECT *
        FROM S
    )
SELECT *
FROM R_S
UNION ALL
SELECT *
FROM S
ORDER BY person_id;

-- SELECT * FROM v_symmetric_union;