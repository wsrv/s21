-- SESSION # 1

SET
    SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN;

-- SESSION # 2

SET
    SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL READ COMMITTED;

BEGIN;

-- SESSION # 1

UPDATE pizzeria SET rating = 1 WHERE id = 1;

-- SESSION # 2

UPDATE pizzeria SET rating = 1 WHERE id = 2;

-- SESSION # 1

UPDATE pizzeria SET rating = 2 WHERE id = 2;

-- SESSION # 2

UPDATE pizzeria SET rating = 2 WHERE id = 1;

-- SESSION # 1

COMMIT;

-- SESSION # 2

COMMIT;