INSERT INTO person_discounts
SELECT
    row_number() OVER () AS id,
    person_order.person_id as person_id,
    menu.pizzeria_id as pizzeria_id, (
        case
            when count(menu.pizzeria_id) = 1 then 10.5
            when count(menu.pizzeria_id) = 2 then 22
            else 30
        end
    )
from person_order
    left join menu on menu.id = person_order.menu_id
group by
    person_order.person_id,
    menu.pizzeria_id;

select * from person_discounts 

DELETE from person_discounts where id>0 