-- Output a table listing the names of the songs that feature other artists
-- Songs that feature other artists will include “feat.” in the name of the song
SELECT name FROM songs WHERE name LIKE "%feat%";
