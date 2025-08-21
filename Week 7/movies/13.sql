SELECT p.name
FROM people p
JOIN stars s ON s.person_id = p.id
WHERE s.movie_id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id IN (
        SELECT id
        FROM people
        WHERE name = "Kevin Bacon" AND birth = 1958
    )
)

AND p.id != (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958);
