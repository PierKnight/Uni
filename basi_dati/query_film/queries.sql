--tutti i nomi dei film in cui ha partecipa penelope E nick

--PRIMO MODO letteralmente si fa la union
select title
from film
where film_id IN
	(select Z.film_id
	from actor as X, film_actor as Y, film as Z
	where X.actor_id = Y.actor_id and Y.film_id = Z.film_id and X.first_name = "penelope"
	UNION
	select Z.film_id
	from actor as X, film_actor as Y, film as Z
	where X.actor_id = Y.actor_id and Y.film_id = Z.film_id and X.first_name = "nick");
