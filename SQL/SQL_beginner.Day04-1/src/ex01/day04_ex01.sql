SELECT *
FROM v_persons_female
UNION ALL
SELECT *
FROM v_persons_male
ORDER BY name;