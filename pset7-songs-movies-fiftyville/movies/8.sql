-- List the names of all people who starred in Toy Story

SELECT name FROM people
INNER JOIN stars on stars.person_id = people.id
INNER JOIN movies on movies.id = stars.movie_id
WHERE title = "Toy Story";