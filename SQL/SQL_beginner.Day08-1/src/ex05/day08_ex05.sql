-- SESSION #1

SET
    SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN;

-- SESSION #2

SET
    SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN;

-- SESSION #1

SELECT SUM(rating) FROM pizzeria;

-- SESSION #2

UPDATE pizzeria SET rating = 1 WHERE name = 'Pizza Hut';

COMMIT;

-- SESSION #1

SELECT SUM(rating) FROM pizzeria;

-- SESSION #1

COMMIT;

SELECT SUM(rating) FROM pizzeria;

-- SESSION #2

SELECT SUM(rating) FROM pizzeria;