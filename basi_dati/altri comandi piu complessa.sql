create table noleggi_scaduti(codice mediumint primary key auto_increment,
							rental_id int not null unique references rental(rental_id),
							giorni_oltre_scadenza smallint);
							
create event scadenza_evento 
schedule on every 1 day starts (timestamp CURRENT_DATE + interval 1 day)
do 
BEGIN

	declare scad_cursor cursor for select , R.return_date
	from rental as R, cd_film as CD,film as F
	where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id
	  and DATEDIFF(NOW(),R.rental_date) > F.rental_duration and R.return_date is null;
	  
	  
	--rimuove tutti i noleggi che sono stati restituiti.
	delete from noleggi_scaduti as RS where RS.rental_id in (select R.rental_id from rental as R where R.return_date is not null);
	
	declare finish tinyint;
	declare rental_scaduto int;
	declare continue handler for sqlstate '02000' set finish = 1
	  
	open scad_cursor;
	
	while not finish do
		fetch scad_cursor into rental_scaduto;
		insert into noleggi_scaduti(rental_id,giorni_oltre_scadenza) values (rental_scaduto,1);
	end LOOP;
	
	--incremento le scadenze di tutti i rental scaduti
	update noleggi_scaduti set giorni_oltre_scadenza = giorni_oltre_scadenza + 1;
	
	
	close scad_cursor;
	

end//



select distinct rental_id
from rental as R, cd_film as CD,film as F
where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id
	  and DATEDIFF(NOW(),R.rental_date) > F.rental_duration and R.return_date is null;
	  
create event scadenza_evento 
on schedule every 1 day starts (timestamp CURRENT_DATE + interval 1 day)
do 
BEGIN

	declare scad_cursor cursor for select , R.return_date
	from rental as R, cd_film as CD,film as F
	where R.cd_film_id = CD.cd_film_id and CD.film_id = F.film_id
	  and DATEDIFF(NOW(),R.rental_date) > F.rental_duration and R.return_date is null;
	  
	  
	delete from noleggi_scaduti as RS where RS.rental_id in (select R.rental_id from rental as R where R.return_date is not null);
	
	declare finish tinyint;
	declare rental_scaduto int;
	declare continue handler for sqlstate '02000' set finish = 1
	  
	open scad_cursor;
	
	while not finish do
		fetch scad_cursor into rental_scaduto;
		insert into noleggi_scaduti(rental_id,giorni_oltre_scadenza) values (rental_scaduto,1);
	end LOOP;
	
	update noleggi_scaduti set giorni_oltre_scadenza = giorni_oltre_scadenza + 1;
	
	
	close scad_cursor;

end



--Trovare i film per cui nessun cd è stato noleggiato per più di 10 giorni.
select F.title
from film as F
where not exists (select CD.cd_film_id
				from cd_film as CD, rental as R
				where CD.film_id = F.film_id and CD.cd_film_id = R.cd_film_id and R.return_date is not null and datediff(R.return_date,R.rental_date) > 0)
				
--Trovare i film i cui cd sono stati noleggiati tutti almeno una volta.
select F.title
from film as F
where not exists (select *
				from cd_film as CD
				where CD.film_id = F.film_id and not exists (select * from rental as R where R.cd_film_id = CD.cd_film_id))
				
--Trovare i cd con numero di noleggi inferiori alla media.

	--creazione view che indica per cd quanti noleggi ha ricevuto
	create view cd_rentals as
	select count(*) as noleggi, CD.cd_film_id
	from cd_film as CD,rental as R
	where CD.cd_film_id = R.cd_film_id
	group by CD.cd_film_id;

	--cd con numero di noleggi inferiore alla media
	select *
	from cd_rentals as CDR
	where CDR.noleggi < (select avg(noleggi) from cd_rentals)

--Trovare il totale incassato da ciascun negozio dai soli noleggi.
	select sum(P.amount)
	from rental as R,payment as P,customer as C
	where R.rental_id = P.rental_id and P.customer_id = C.customer_id
	group by C.store_id
	
--Trovare il totale incassato da ciascun negozio da tutti i pagamenti.
	select sum(P.amount)
	from payment as P,customer as C
	where P.customer_id = C.customer_id
	group by C.store_id