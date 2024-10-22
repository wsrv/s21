
drop FUNCTION fnc_fibonacci;


CREATE OR REPLACE FUNCTION fnc_fibonacci(IN pstop integer DEFAULT 10)
    RETURNS SETOF INTEGER
    LANGUAGE SQL
AS
$fibonacci$
WITH RECURSIVE couple(Num1, Num2) AS
					(VALUES (0, 1)
					UNION ALL
					SELECT GREATEST(Num1, Num2),
						Num1 + Num2 AS FibonacciSeries
					FROM couple
					WHERE Num2 < pstop)
SELECT Num1
FROM couple;
$fibonacci$;





SELECT *
FROM fnc_fibonacci(100);
SELECT *
FROM fnc_fibonacci();