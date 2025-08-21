SELECT AVG(r.rating) as Average_rating
FROM ratings r
JOIN movies m ON m.id = r.movie_id
WHERE m.year = 2012;
