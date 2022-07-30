-- List the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.
-- TODO


SELECT DISTINCT title FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
WHERE EXISTS(name = "Johnny Depp");
-- WHERE name in ("Johnny Depp", "Helena Bonham Carter");


-- GROUP BY name
-- HAVING (name = "Johnny Depp" AND name = "Helena Bonham Carter");


SELECT title, people.name="Johnny Depp" AND "Helena Bonham Carter"FROM movies, stars, people
WHERE stars.movie_id = movies.id AND people.id = stars.person_id;



-- WHERE name = "Johnny Depp";
-- INTERSECT
-- WHERE name = "Helena Bonham Carter";


-- WHERE person_id INTERSECT (SELECT id FROM people WHERE name = "Johnny Depp" OR name = "Helena Bonham Carter");


-- -- GEt the Ids of Jonny Depp and - Helena Bonham Carter

-- WHERE EXISTS(name = "Johnny Depp");
-- AND EXISTS(name = "Helena Bonham Carter");

-- name = "Johnny Depp" OR name = "Helena Bonham Carter";
-- -- WHERE (name = "Helena Bonham Carter")
-- -- AND (name = "Johnny Depp");
-- -- AND name = "Helena Bonham Carter";
-- -- and "Helena Bonham Carter" in name;