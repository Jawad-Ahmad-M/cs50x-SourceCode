-- write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0

SELECT DISTINCT(p.name)
FROM people p
JOIN directors d ON d.person_id = p.id
JOIN movies m ON d.movie_id = m.id
JOIN ratings r ON r.movie_id = m.id
WHERE r.rating >= 9.0
LIMIT 20;
