CREATE TABLE `users` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `email` char(100) NOT NULL,
  `password_hash` tinytext NOT NULL,
  `nickname` char(20) NOT NULL,
  `pfp_url` tinytext DEFAULT NULL,
  `bio` text NOT NULL DEFAULT '',
  `auth_code` char(6) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `nickname` (`nickname`)
);