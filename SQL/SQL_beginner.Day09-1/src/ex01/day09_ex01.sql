-- DROP FUNCTION fnc_trg_person_update_audit;

CREATE OR REPLACE FUNCTION FNC_TRG_PERSON_UPDATE_AUDIT
() RETURNS TRIGGER AS $$ 
 BEGIN INSERT INTO person_audit VALUES (now(), 'U', old.*);
	RETURN NEW;
	END;
	$$ LANGUAGE plpgsql;


-- drop TRIGGER trg_person_update_audit on person;

CREATE TRIGGER trg_person_update_audit 
	AFTER
	UPDATE ON person FOR EACH ROW
	EXECUTE
	    FUNCTION fnc_trg_person_update_audit();


UPDATE person SET name = 'Bulat' WHERE id = 10;

UPDATE person SET name = 'Damir' WHERE id = 10;

select * from person_audit;