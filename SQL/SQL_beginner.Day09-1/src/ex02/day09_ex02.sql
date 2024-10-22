


-- DROP FUNCTION fnc_trg_person_delete_audit;

CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit
() RETURNS TRIGGER AS $$  
	BEGIN
	INSERT INTO person_audit
	VALUES (now(), 'D', old.*);


RETURN NEW;

END;

$$ LANGUAGE plpgsql;

-- drop TRIGGER trg_person_delete_audit on person;

CREATE TRIGGER trg_person_delete_audit 
	AFTER
	DELETE ON person FOR EACH ROW
	EXECUTE
	    FUNCTION fnc_trg_person_delete_audit();


DELETE FROM person WHERE id = 10;

select * from person_audit;