SELECT m.title, r.rating
FROM movies m
JOIN ratings r ON r.movie_id = m.id
WHERE r.rating > 0.0 AND m.year = 2010
ORDER BY r.rating DESC, m.title ASC;
