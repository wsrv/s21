create index idx_person_name on person(upper(name));

set enable_seqscan to off;

EXPLAIN ANALYZE SELECT * FROM person WHERE upper(name) = 'ELVIRA';