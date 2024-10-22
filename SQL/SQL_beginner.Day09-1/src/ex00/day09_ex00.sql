DROP TABLE person_audit;

CREATE TABLE
    person_audit (
        created timestamp
        with
            time zone DEFAULT current_timestamp NOT NULL,
            type_event char(1) CONSTRAINT ch_type_event CHECK (type_event IN ('I', 'U', 'D')),
            row_id bigint NOT NULL,
            name varchar,
            age integer,
            gender varchar,
            address varchar
    );

select * from person_audit;

-- DROP FUNCTION fnc_trg_person_insert_audit;

CREATE OR REPLACE FUNCTION FNC_TRG_PERSON_INSERT_AUDIT
() RETURNS TRIGGER AS $$  
	BEGIN
	INSERT INTO person_audit
	VALUES (now(), 'I', new.*);


RETURN NEW;

END;

$$ LANGUAGE plpgsql;

-- drop TRIGGER TRG_PERSON_INSERT_AUDIT on person;

CREATE TRIGGER TRG_PERSON_INSERT_AUDIT 
	AFTER
	INSERT ON person FOR EACH ROW
	EXECUTE
	    FUNCTION FNC_TRG_PERSON_INSERT_AUDIT();


delete from person where person.id=10;

select * from person;

INSERT INTO
    person(id, name, age, gender, address)
VALUES (
        10,
        'Damir',
        22,
        'male',
        'Irkutsk'
    );