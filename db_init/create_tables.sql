CREATE TABLE `users` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `email` char(100) NOT NULL,
  `password_hash` tinytext NOT NULL,
  `username` char(30) NOT NULL,
  `pfp_url` tinytext DEFAULT NULL,
  `bio` text NOT NULL DEFAULT '',
  `auth_code` char(6) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `username` (`username`)
);

create table tags(
    id int unsigned primary key auto_increment,
    label char(30) not null,
    counter int not null default (0)
);

create table events(
    id int unsigned primary key auto_increment,
    title char(70) not null,
    description text not null default '',
    picture_url tinytext,
    start datetime not null default NOW(),
    author_id int unsigned NOT NULL,
    constraint `fk_event_author_id`
      foreign key (author_id) references users (id)
      on delete restrict
      on update restrict
);

create table events_tags (
    event_id int unsigned not null,
    constraint `fk_event_id`
      foreign key (event_id) references events (id)
      on delete cascade
      on update cascade,
    tag_id int unsigned not null,
    constraint `fk_tag_id`
      foreign key (tag_id) references tags (id)
      on delete cascade
      on update cascade
);

create table suggestions (
  id int unsigned primary key not null auto_increment,
  author_id int unsigned not null,
  post_date datetime not null default now(),
  sprint_id int unsigned not null,
  votes int not null default 0,
  constraint `fk_suggestion_author_id`
    foreign key (author_id) references users (id)
    on delete restrict
    on update restrict
);

create table sprints (
  id int unsigned NOT NULL AUTO_INCREMENT PRIMARY KEY,
  state enum ('voting','implementing','ended'),
  suggestion_winner_id int unsigned unique, 
  event_id int unsigned not null,
    constraint `fk_sprint_event_id`
      foreign key (event_id) references events (id)
      on delete cascade
      on update cascade,
  CONSTRAINT `fk_suggestion_winner_id`
    FOREIGN KEY (suggestion_winner_id) REFERENCES suggestions (id)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
);

alter table suggestions add 
  constraint `fk_suggestion_sprint_id`
    foreign key (sprint_id) references sprints (id)
    on delete cascade
    on update restrict;

create table posts (
  id int unsigned primary key NOT NULL AUTO_INCREMENT,
  text_content text DEFAULT NULL,
  suggestion_id int unsigned,
  constraint `fk_post_suggestion_id`
    foreign key (suggestion_id) references suggestions (id)
    on delete cascade
    on update restrict,
  sprint_id int unsigned,
  constraint `fk_post_sprint_id`
    foreign key (sprint_id) references sprints (id)
    on delete cascade
    on update restrict
);

create table post_media (
  id int unsigned NOT NULL AUTO_INCREMENT PRIMARY KEY,
  url tinytext DEFAULT NULL,
  type enum('image', 'video', 'other'),
  post_id int unsigned NOT NULL, 
  constraint `fk_post_id`
    FOREIGN KEY (post_id) REFERENCES posts (id)
    ON DELETE CASCADE
    ON UPDATE RESTRICT
);
