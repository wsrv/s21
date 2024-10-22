
drop TRIGGER TRG_PERSON_INSERT_AUDIT on person;
drop TRIGGER trg_person_update_audit on person;
drop TRIGGER trg_person_delete_audit on person;

DROP FUNCTION fnc_trg_person_insert_audit;
DROP FUNCTION fnc_trg_person_update_audit;
DROP FUNCTION fnc_trg_person_delete_audit;


-- DROP FUNCTION fnc_trg_person_audit;

CREATE OR REPLACE FUNCTION fnc_trg_person_audit()
    RETURNS TRIGGER AS
$$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO person_audit SELECT now(), 'I', new.*;
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO person_audit SELECT now(), 'U', old.*;
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO person_audit SELECT now(), 'D', old.*;
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;


-- drop TRIGGER trg_person_audit on person;

CREATE TRIGGER trg_person_audit
    AFTER INSERT OR UPDATE OR DELETE
    ON person
    FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_audit();

INSERT INTO person(id, name, age, gender, address)  VALUES (10,'Damir', 22, 'male', 'Irkutsk');
UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;
DELETE FROM person WHERE id = 10;

select * from person_audit;