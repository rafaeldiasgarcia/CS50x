SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.id IN (
    SELECT s_kb.movie_id
    FROM stars s_kb
    JOIN people p_kb ON s_kb.person_id = p_kb.id
    WHERE p_kb.name = 'Kevin Bacon' AND p_kb.birth = 1958
)
AND NOT (p.name = 'Kevin Bacon' AND p.birth = 1958);
