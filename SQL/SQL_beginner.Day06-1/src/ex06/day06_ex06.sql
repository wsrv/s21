CREATE SEQUENCE seq_person_discounts START 1;

SELECT setval('seq_person_discounts', max(id)) from person_discounts;

ALTER TABLE person_discounts
ALTER COLUMN id
SET
    DEFAULT NEXTVAL('seq_person_discounts');