SELECT missing_days.date
FROM
    generate_series(
        date '2022-01-01',
        date '2022-01-10',
        '1 day'
    ) AS missing_days
    LEFT JOIN (
        SELECT visit_date
        FROM person_visits
        WHERE
            person_id = 1
            OR person_id = 2
    ) AS dates_from_persons ON missing_days.date = dates_from_persons.visit_date
WHERE
    dates_from_persons.visit_date IS NULL;