insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');
--
SELECT COALESCE("user".name, 'not defined') AS name,
       COALESCE("user".lastname, 'not defined') AS lastname,
       cur.name AS currency_name,
       cur.money * COALESCE(min, max) AS currency_in_usd
FROM (SELECT balance.user_id,
             currency.id,
             currency.name,
             balance.money,
             --
             (SELECT currency.rate_to_usd
              FROM currency
              WHERE currency.id = balance.currency_id AND currency.updated < balance.updated
            ORDER BY 1 LIMIT 1) AS min,
              --
             (SELECT currency.rate_to_usd
              FROM currency
              WHERE currency.id = balance.currency_id  AND currency.updated > balance.updated
            ORDER BY 1 LIMIT 1) AS max
              --
      FROM currency JOIN balance ON currency.id = balance.currency_id
      GROUP BY balance.money,
               currency.name,
               currency.id,
               balance.updated,
               balance.currency_id,
               balance.user_id
       ORDER BY min DESC, max) AS cur
         LEFT JOIN "user" ON cur.user_id = "user".id
         ORDER BY 1 DESC, 2, 3;


--
delete from  currency where id=100 and  name ='EUR' and  rate_to_usd=0.85 and  updated='2022-01-01 13:29';
delete from  currency where id=100 and  name ='EUR' and  rate_to_usd=0.79 and  updated='2022-01-08 13:29';
