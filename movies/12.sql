SELECT m.title
FROM movies m
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON p.id = s.person_id
WHERE p.name IN ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY m.id, m.title
HAVING COUNT(*) = 2;