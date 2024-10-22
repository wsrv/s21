ALTER TABLE person_discounts
ADD
    CONSTRAINT ch_nn_person_id CHECK (person_id is not null),
ADD
    CONSTRAINT ch_nn_pizzeria_id CHECK (pizzeria_id is not null),
ADD
    CONSTRAINT ch_nn_discount CHECK (discount is not null),
    ALTER discount
set default 0,
ADD
    CONSTRAINT ch_range_discount CHECK (
        discount >= 0
        and discount <= 100
    );