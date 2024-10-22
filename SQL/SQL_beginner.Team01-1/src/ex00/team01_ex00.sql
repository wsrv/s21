WITH total_volume AS (
        SELECT
            balance.user_id,
            type,
            sum(balance.money) AS volume,
            currency_id
        FROM
            balance
            LEFT JOIN "user" u ON u.id = balance.user_id
        GROUP BY
            balance.user_id,
            type,
            balance.currency_id
    ),
    cur AS (
        SELECT currency.id, name, rate_to_usd
        FROM currency
            JOIN (
                SELECT
                    id,
                    max(updated) AS updated
                FROM
                    currency
                GROUP BY
                    id
            ) AS currency1 ON currency.updated = currency1.updated
            AND currency.id = currency1.id
    )
SELECT
    coalesce(u.name, 'not defined') AS name,
    coalesce(u.lastname, 'not defined') AS lastname,
    total_volume.type,
    total_volume.volume,
    coalesce(cur.name, 'not defined'),
    coalesce(cur.rate_to_usd, 1) AS last_rate_to_usd, 
    (volume * coalesce(cur.rate_to_usd, 1)) AS total_volume_in_usd
        FROM
            total_volume
            LEFT JOIN "user" u ON u.id = total_volume.user_id
            LEFT JOIN cur  ON currency_id = cur.id
        ORDER BY
            name DESC,
            lastname,
            type
