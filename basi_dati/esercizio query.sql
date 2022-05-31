--Numero negozi allocati in italia GROUP 1

select "Italiano" as "Lingua", count(*) as "Totale Negozi"
from store as S,address as A, city as C
where S.address_id = A.address_id and A.city_id = C.city_id
group by C.country_id
having C.country_id = 20;

--totale noleggi per ciascun film GROUP 2
select F.title as "Film",count(*) as "Totale Noleggi"
from rental as R,cd_film as CD,film as F
where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id
group by F.film_id;

--ottenere il film più lungo di durata
select title,length
from film
where length = (select max(F.length) from film as F);
--oppure
select title,length
from film as F
where not exists (select * from film as X where F.length < X.length);

--totale noleggi per categoria GROUP 3
select C.category_id as "Categoria",count(*) as "Totale Noleggi"
from rental as R,cd_film as CD,film as F,film_category as C
where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id and F.film_id = C.film_id
group by C.category_id;

--Calcolare il totale dei pagamenti incassati da ciascun negozio (Gruppo 4)
create view test as
select sum(P.amount) as "Totale guadagno"
from payment as P, staff as S
where P.staff_id = S.staff_id and NOW() - P.payment_date >= 0
group by S.store_id;


--Trovare i titoli dei film noleggiati nel 2020. (Gruppo 5)
create view test as
select distinct F.title, YEAR(R.rental_date) as "Anno"
from rental as R, cd_film as CD, film as F
where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id and YEAR(R.rental_date) = 2020;

--Trovare i clienti che non hanno mai effettuato un noleggio (Gruppo 6)
select C.first_name
from customer as C
where C.customer_id not in (select customer_id from rental);

--trovare gli attori che hanno recitato in almeno 3 film

select A.first_name
from actor as A,film_actor as FA
where A.actor_id = FA.actor_id
group by A.actor_id
having count(DISTINCT A.actor_id) >= 3;



--trovare film per cui esistono almeno 5 cd (GROUP 17)
select F.title
from film as F,cd_film as CD
where F.film_id = CD.film_id
group by F.film_id
having count(*) > 5;
--oppure
select F.title
from film as F
where (select count(*) from cd_film as CD where F.film_id = CD.film_id) >= 5;


--QUERY PIU COMPLESSE 12/05/2022

--Trovare i film con il maggior rental_rate
select F.title
from film as F
where not exists (select * from film where F.rental_rate < rental_rate);

--Trovare i film con il rental_cost inferiore alla media degli altri film
select F.title
from film as F
where F.rental_rate < (select avg(rental_rate) from film);

---Trovare i clienti che non hanno mai noleggiato un film horror
select C.first_name
from customer as C
where C.customer_id not in (select R.customer_id
from rental as R,cd_film as CD,film as F, film_category as FC
where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id and FC.film_id = F.film_id and FC.category_id = 11);

--Trovare i clienti che hanno noleggiato almeno un film per ciascuna categoria
select first_name
from customer as CUS
where (select count(distinct category_id)
		from rental as R,cd_film as CD, film as F,film_category as FC
		where R.customer_id = CUS.customer_id and R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id and F.film_id = FC.film_id) 
		= (select count(*) from category);
		
---Trovare gli attori che non hanno mai recitato in un film che durasse più di 2 ore
select first_name
from actor as ACT
where ACT.actor_id not in (select A.actor_id
				  from actor as A,film_actor as FA,film as F
				  where A.actor_id = FA.actor_id and FA.film_id = F.film_id and F.length > 120)
				  
--Trovare i negozi che hanno noleggiato ogni cd almeno 3 volte
select store_id
from store as ST
where not exists (select CD.cd_film_id
					from cd_film as CD
					where  CD.store_id = ST.store_id and (select count(*) 
							from rental as R
							where R.cd_film_id = CD.cd_film_id) < 3)
							
							
							



--