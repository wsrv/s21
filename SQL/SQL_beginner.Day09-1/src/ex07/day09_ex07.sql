
CREATE OR REPLACE FUNCTION func_minimum (VARIADIC arr NUMERIC[])
RETURNS numeric AS $$
BEGIN RETURN (select min(i) FROM unnest($1) i);
END;
$$ LANGUAGE plpgsql;



SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);