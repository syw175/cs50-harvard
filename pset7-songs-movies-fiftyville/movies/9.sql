-- List the names of all people who starred in a movie released in 2004, ordered by birth year
-- People with the same birth year may be listed in any order
-- If a person appeared in more than one movie in 2004, they should only appear in your results once


SELECT DISTINCT name 
    FROM people

    JOIN stars 
        ON stars.person_id = people.id
    JOIN movies 
        ON movies.id = stars.movie_id
    WHERE movies.year = 2004
    
    ORDER BY people.birth;