-- CREATE TABLE address (
	-- address_id int primary key auto_increment
	-- ,address varchar(40) not null
	-- , address2 varchar(40)
	-- ,district varchar(40) not null
	-- ,city_id int not null
	-- ,phone int(10) zerofill not null unique
	-- ,location varchar(40)
	-- , foreign key (city_id) REFERENCES city(city_id));
	
-- ,postal_code int(5) zerofill not null  penso che quesa roba dovrebbe andare in city visto che alla fine è il CAP

create table film (
	film_id int primary key auto_increment,
	title varchar(30) not null,
	description varchar(1000),
	release_year YEAR,
	language_id int REFERENCES language(language_id),
	original_language_id int REFERENCES language(language_id),
	rental_duration int default 0,
	rental_rate int,
	lenght int,
	replacement_cost int,
	rating int CHECK (rating >= 0 and rating <= 10));

TRANSACTION

create table store (
	store_id int auto_increment primary key,
	manager_staff_id int not null references staff(staff_id),
	address_id int not null references address(address_id));
	
CREATE TABLE staff(
	staff_id int primary key auto_increment,
	first_name varchar(50) not null,
	last_name varchar(50) not null,
	address_id int references address(address_id),
	picture varchar(100),
	email VARCHAR(30),
	store_id int not null references store(store_id),
	active TINYINT default 1,
	username varchar(20),
	password varchar(100));
COMMIT

create table store (
	store_id int auto_increment primary key,
	manager_staff_id int references staff(staff_id),
	address_id int REFERENCES address(address_id)
)

create table cd_film (
	cd_film_id int auto_increment primary key,
	film_id int,
	store_id int,
	FOREIGN KEY (film_id) REFERENCES film(film_id),
	FOREIGN KEY (store_id) REFERENCES store(store_id));
	
create table customer (
	customer_id int primary key auto_increment,
	store_id int not null references store(store_id),
	first_name varchar(20),
	last_name varchar(20),
	email varchar(30),
	address_id int references address(address_id),
	active TINYINT default 1,
	create_date DATE not null
	
)

create table rental(
	rental_id int auto_increment primary key,
	rental_date date not null,
	cd_film_id int not null references cd_film(cd_film_id),
	customer_id int not null references customer(customer_id),
	return_date date not null,
	staff_id int not null REFERENCES staff(staff_id)
)



create table rental_recap (
	cd_film_id int primary key references cd_film(cd_film_id),
	available tinyint(1)
)


-- TRIGGERS-----

DELIMITER //

-- trigger per aggiungere
create trigger create_recap AFTER INSERT ON cd_film
FOR EACH ROW
BEGIN

	INSERT INTO rental_recap values (NEW.cd_film_id,1);

END;//

CREATE TRIGGER rental_recap_update AFTER UPDATE ON rental
BEGIN

	update rental_recap set available = 0 where cd_film_id = NEW.cd_film_id;

END//


--procedure di test

create procedure dimmi_orario (out orario date)
BEGIN
	select NOW() into orario;
END//





	
	
		
