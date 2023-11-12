/*
SQLyog Community v13.1.5  (64 bit)
MySQL - 10.1.38-MariaDB : Database - slim_web
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `applications` */

DROP TABLE IF EXISTS `applications`;

CREATE TABLE `applications` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL,
  `status` enum('WAITING','ACCEPT','DECLINE','ARCHIVE') NOT NULL DEFAULT 'WAITING',
  `name` varchar(25) NOT NULL,
  `sex` tinyint(1) unsigned NOT NULL,
  `race` tinyint(1) unsigned NOT NULL,
  `skin` int(3) unsigned NOT NULL,
  `age` tinyint(2) unsigned NOT NULL,
  `role` tinyint(1) unsigned NOT NULL,
  `spawn` tinyint(1) unsigned NOT NULL,
  `document` tinyint(1) unsigned NOT NULL,
  `item` int(1) NOT NULL,
  `history` varchar(2048) NOT NULL,
  `ip` varchar(17) NOT NULL,
  `admin_id` int(11) unsigned NOT NULL DEFAULT '0',
  `admin_ip` varchar(17) NOT NULL DEFAULT '',
  `admin_comment` varchar(512) DEFAULT '',
  `admin_view_id` int(11) unsigned NOT NULL DEFAULT '0',
  `admin_view_update` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`),
  UNIQUE KEY `UNIQ_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;

/*Data for the table `applications` */

insert  into `applications`(`id`,`user_id`,`status`,`name`,`sex`,`race`,`skin`,`age`,`role`,`spawn`,`document`,`item`,`history`,`ip`,`admin_id`,`admin_ip`,`admin_comment`,`admin_view_id`,`admin_view_update`,`create_date`,`update_date`) values 
(22,1,'ACCEPT','Testm_Testm',0,1,255,0,0,0,0,-1,'tewttw','127.0.0.1',1,'127.0.0.1','i9',0,'1970-01-01 00:00:00','2019-12-16 01:18:19','2019-12-16 01:18:19'),
(23,1,'ACCEPT','Testtt_Testewew7',0,1,255,14,0,0,1,-1,'test','127.0.0.1',1,'127.0.0.1','',0,'1970-01-01 00:00:00','2019-12-16 01:19:29','2019-12-16 01:19:29');

/*Table structure for table `applications_question` */

DROP TABLE IF EXISTS `applications_question`;

CREATE TABLE `applications_question` (
  `application_id` int(11) unsigned NOT NULL,
  `question_id` int(11) unsigned NOT NULL,
  `text` text NOT NULL,
  KEY `application_id` (`application_id`),
  KEY `question_id` (`question_id`),
  CONSTRAINT `FK_application_id` FOREIGN KEY (`application_id`) REFERENCES `applications` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_question_id` FOREIGN KEY (`question_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `applications_question` */

insert  into `applications_question`(`application_id`,`question_id`,`text`) values 
(22,1,'utyuity'),
(22,5,'iytityiytit'),
(22,3,'yityityit'),
(23,5,'Testwetw'),
(23,2,'wetwetewt'),
(23,1,'wetewtw');

/*Table structure for table `capitals` */

DROP TABLE IF EXISTS `capitals`;

CREATE TABLE `capitals` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `character_id` int(11) unsigned NOT NULL,
  `status` enum('WAITING','ACCEPT','DECLINE','ARCHIVE') NOT NULL DEFAULT 'WAITING',
  `text` text NOT NULL,
  `images` varchar(512) NOT NULL,
  `need_money` int(11) unsigned NOT NULL DEFAULT '0',
  `money` int(11) unsigned NOT NULL DEFAULT '0',
  `admin_id` int(11) unsigned NOT NULL DEFAULT '0',
  `admin_ip` varchar(16) NOT NULL DEFAULT '',
  `admin_comment` varchar(512) NOT NULL DEFAULT '',
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Data for the table `capitals` */

insert  into `capitals`(`id`,`character_id`,`status`,`text`,`images`,`need_money`,`money`,`admin_id`,`admin_ip`,`admin_comment`,`create_date`,`update_date`) values 
(1,19,'ACCEPT','Всякая там предыстория','',1356,633,1,'127.0.0.1','','2019-07-21 21:08:22','2019-07-23 21:08:22'),
(2,3,'ACCEPT','fafafasf','[\"dbd285e6f4a84496.png\",\"5363a36fcc2e82cc.png\",\"be225e5d098ce9f1.png\"]',932,596,1,'127.0.0.1','','2019-08-16 00:05:52','2019-08-16 00:05:52'),
(3,5,'ACCEPT','Всякая там предыстория','',1356,633,1,'127.0.0.1','','2019-07-21 21:08:22','2019-07-23 21:08:22');

/*Table structure for table `contents` */

DROP TABLE IF EXISTS `contents`;

CREATE TABLE `contents` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name_id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `content` mediumtext,
  `user_id` int(11) unsigned NOT NULL DEFAULT '0',
  `update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

/*Data for the table `contents` */

insert  into `contents`(`id`,`name_id`,`name`,`content`,`user_id`,`update_date`) values 
(1,'rules','Правила сервера','<b>                                    Тестанем!</b>',1,'2019-07-08 12:08:57'),
(2,'how-to-play','Как начать игру?','<b>Как начать играть?</b>',1,'2019-07-10 02:26:27'),
(3,'lore','Игровой лор','hdfhu5675',1,'2019-07-29 04:20:55'),
(4,'faq','FAQ','',0,'1970-01-01 00:00:00'),
(5,'lore-lspd','История Департамента полиции г. Лос-Сантос','<div class=\"content-spoiler\"><a class=\"js_spoiler_title spoiler_title\" href=\"#\">Заголовок спойлера</a>\r\n<div class=\"js_spoiler_content spoiler_content\">Содержимое спойлера</div>\r\n</div>\r\n<p>&nbsp;</p>',1,'2019-09-03 01:23:20');

/*Table structure for table `contents_history` */

DROP TABLE IF EXISTS `contents_history`;

CREATE TABLE `contents_history` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `content_id` int(11) unsigned NOT NULL,
  `user_id` int(11) unsigned NOT NULL,
  `content` mediumtext NOT NULL,
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `FK_content_id` (`content_id`),
  CONSTRAINT `FK_content_id` FOREIGN KEY (`content_id`) REFERENCES `contents` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;

/*Data for the table `contents_history` */

insert  into `contents_history`(`id`,`content_id`,`user_id`,`content`,`create_date`) values 
(1,1,1,'Test1','2019-07-08 11:42:19'),
(2,1,1,'Test1','2019-07-08 11:42:44'),
(3,1,1,'Опа история','2019-07-08 12:05:02'),
(4,1,1,'<b>                                    Тестанем!</b>','2019-07-08 12:07:58'),
(5,1,1,'Test1','2019-07-08 12:08:57'),
(6,2,1,'<b>Как начать играть?</b>','2019-07-10 02:26:27'),
(7,3,1,'5676575','2019-07-29 04:14:38'),
(8,3,1,'sdgsgdsgsgweg','2019-07-29 04:15:24'),
(9,3,1,'sdgsgdsgsgweg565','2019-07-29 04:15:41'),
(10,3,1,'sdgsgdsgsgweg565','2019-07-29 04:15:52'),
(11,3,1,'sdgsgdsgsgweg5655675','2019-07-29 04:16:18'),
(12,3,1,'sdgsgdsgsgweg5655675','2019-07-29 04:16:29'),
(13,3,1,'sdgsgdsgsgweg565567554','2019-07-29 04:16:34'),
(14,3,1,'hdfh','2019-07-29 04:20:46'),
(15,3,1,'hdfh','2019-07-29 04:20:55'),
(16,5,1,'','2019-08-20 22:50:04'),
(17,5,1,'<!DOCTYPE html>\r\n<html>\r\n<head>\r\n</head>\r\n<body>\r\n<p><strong>GF</strong></p>\r\n</body>\r\n</html>','2019-08-20 22:51:38'),
(18,5,1,'<!DOCTYPE html>\r\n<html>\r\n<head>\r\n</head>\r\n<body>\r\n<p><strong>GF</strong></p>\r\n</body>\r\n</html>','2019-09-03 01:18:46'),
(19,5,1,'<div class=\"content-spoiler\">\r\n<div class=\"js_spoiler_title title\">Заголовок спойлера</div>\r\n<div class=\"js_spoiler_content content\">Содержимое спойлера</div>\r\n</div>\r\n<p>&nbsp;</p>','2019-09-03 01:20:45'),
(20,5,1,'<div class=\"content-spoiler\">\r\n<div class=\"js_spoiler_title title\">Заголовок спойлера</div>\r\n<div class=\"js_spoiler_content content\">Содержимое спойлера</div>\r\n</div>\r\n<p>&nbsp;</p>','2019-09-03 01:21:38'),
(21,5,1,'<div class=\"content-spoiler\">\r\n<div class=\"js_spoiler_title title\">Заголовок спойлера</div>\r\n<div class=\"js_spoiler_content content\">Содержимое спойлера</div>\r\n</div>\r\n<p>&nbsp;</p>','2019-09-03 01:21:44'),
(22,5,1,'<div class=\"content-spoiler\">\r\n<div class=\"js_spoiler_title spoiler_title\">Заголовок спойлера</div>\r\n<div class=\"js_spoiler_content spoiler_content\">Содержимое спойлера</div>\r\n</div>\r\n<p>&nbsp;</p>','2019-09-03 01:23:20');

/*Table structure for table `email_confirms` */

DROP TABLE IF EXISTS `email_confirms`;

CREATE TABLE `email_confirms` (
  `user_id` int(11) unsigned NOT NULL,
  `type` enum('CONFIRM','RESTORE','CHANGE_PASSWORD','CHANGE_EMAIL','DELETE_CHARACTER') NOT NULL,
  `hash` varchar(255) NOT NULL,
  `expire` datetime DEFAULT '1970-01-01 00:00:00'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `email_confirms` */

/*Table structure for table `payments` */

DROP TABLE IF EXISTS `payments`;

CREATE TABLE `payments` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `unitpay_id` int(11) unsigned NOT NULL,
  `account` int(11) unsigned NOT NULL,
  `sum` float unsigned NOT NULL,
  `items_count` int(11) DEFAULT '1',
  `status` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `create_date` datetime DEFAULT NULL,
  `complete_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

/*Data for the table `payments` */

insert  into `payments`(`id`,`unitpay_id`,`account`,`sum`,`items_count`,`status`,`create_date`,`complete_date`) values 
(1,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(2,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(3,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(4,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(5,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(6,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(7,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(8,1,99,100,100,1,NULL,'2019-07-23 23:04:16'),
(9,1,1,100,100,1,NULL,'2019-07-23 23:04:16'),
(10,2,1,20,20,1,'2019-07-23 23:05:45','2019-07-23 23:07:18');

/*Table structure for table `questions` */

DROP TABLE IF EXISTS `questions`;

CREATE TABLE `questions` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `text` varchar(1024) DEFAULT NULL,
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*Data for the table `questions` */

insert  into `questions`(`id`,`text`,`create_date`,`update_date`) values 
(1,'Жили былиЖили былиЖили былиЖили былиЖили былиЖили были Жили были Жили были Жили были Жили были Жили были ','0000-00-00 00:00:00','1970-01-01 00:00:00'),
(2,'Каак?et2tw','0000-00-00 00:00:00','2019-07-02 04:55:44'),
(3,'wetwetwet','2019-07-02 04:52:32','1970-01-01 00:00:00'),
(5,'cxbxb','2019-07-02 04:55:51','1970-01-01 00:00:00'),
(6,'врот тебя','2019-12-17 22:31:23','2019-12-17 22:31:27'),
(7,'хеппи лох','2019-12-17 22:31:35','2019-12-17 22:31:35');

/*Table structure for table `sessions` */

DROP TABLE IF EXISTS `sessions`;

CREATE TABLE `sessions` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL,
  `token` varchar(256) NOT NULL,
  `expire` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `remember_me` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

/*Data for the table `sessions` */

insert  into `sessions`(`id`,`user_id`,`token`,`expire`,`remember_me`) values 
(12,1,'feb11e74558f306394c657209cca85d0ba74810703ba2c86557093f76bc39ac368407241a9d784f15c8ea7caabcad692','2020-05-11 02:41:10',1);

/*Table structure for table `sessions_log` */

DROP TABLE IF EXISTS `sessions_log`;

CREATE TABLE `sessions_log` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT NULL,
  `ip` varchar(16) NOT NULL,
  `date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=95 DEFAULT CHARSET=utf8;

/*Data for the table `sessions_log` */

insert  into `sessions_log`(`id`,`user_id`,`ip`,`date`) values 
(1,1,'','2019-07-04 05:38:48'),
(2,1,'127.0.0.1','2019-07-04 05:39:45'),
(3,1,'127.0.0.1','2019-07-04 07:48:32'),
(4,1,'127.0.0.1','2019-07-05 01:46:55'),
(5,1,'127.0.0.1','2019-07-05 03:20:09'),
(6,1,'127.0.0.1','2019-07-05 18:39:38'),
(7,1,'127.0.0.1','2019-07-05 20:21:38'),
(8,1,'127.0.0.1','2019-07-06 03:42:24'),
(9,1,'127.0.0.1','2019-07-06 05:29:44'),
(10,1,'127.0.0.1','2019-07-06 22:33:02'),
(11,1,'127.0.0.1','2019-07-07 00:40:03'),
(12,1,'127.0.0.1','2019-07-07 11:32:39'),
(13,1,'127.0.0.1','2019-07-07 14:07:09'),
(14,1,'127.0.0.1','2019-07-08 05:36:49'),
(15,1,'127.0.0.1','2019-07-08 09:43:51'),
(16,1,'127.0.0.1','2019-07-08 19:03:20'),
(17,1,'127.0.0.1','2019-07-09 02:05:38'),
(18,1,'127.0.0.1','2019-07-09 04:38:26'),
(19,1,'127.0.0.1','2019-07-09 06:24:10'),
(20,1,'127.0.0.1','2019-07-10 02:02:52'),
(21,1,'127.0.0.1','2019-07-10 03:25:16'),
(22,1,'127.0.0.1','2019-07-10 06:55:16'),
(23,1,'127.0.0.1','2019-07-10 06:56:35'),
(24,1,'127.0.0.1','2019-07-10 06:57:11'),
(25,1,'127.0.0.1','2019-07-11 02:43:01'),
(26,1,'127.0.0.1','2019-07-11 03:56:04'),
(27,1,'127.0.0.1','2019-07-11 04:23:03'),
(28,8,'127.0.0.1','2019-07-11 15:10:59'),
(29,1,'127.0.0.1','2019-07-11 17:09:40'),
(30,1,'127.0.0.1','2019-07-11 19:45:06'),
(31,9,'127.0.0.1','2019-07-12 07:36:41'),
(32,10,'127.0.0.1','2019-07-12 07:46:51'),
(33,11,'127.0.0.1','2019-07-12 07:55:45'),
(34,12,'127.0.0.1','2019-07-13 03:07:05'),
(35,13,'127.0.0.1','2019-07-13 03:10:50'),
(36,1,'127.0.0.1','2019-07-13 03:18:53'),
(37,1,'127.0.0.1','2019-07-18 20:30:01'),
(38,1,'127.0.0.1','2019-07-22 02:03:50'),
(39,1,'127.0.0.1','2019-07-23 00:22:55'),
(40,1,'127.0.0.1','2019-07-28 23:29:49'),
(41,1,'127.0.0.1','2019-07-28 23:45:03'),
(42,14,'127.0.0.1','2019-07-28 23:47:04'),
(43,18,'127.0.0.1','2019-07-28 23:53:20'),
(44,19,'127.0.0.1','2019-07-28 19:00:43'),
(45,1,'127.0.0.1','2019-07-28 19:02:31'),
(46,1,'127.0.0.1','2019-07-29 01:09:17'),
(47,20,'127.0.0.1','2019-07-29 01:09:39'),
(48,1,'127.0.0.1','2019-07-29 03:38:12'),
(49,20,'127.0.0.1','2019-07-29 03:38:41'),
(50,1,'127.0.0.1','2019-07-29 04:14:23'),
(51,21,'127.0.0.1','2019-07-30 00:11:31'),
(52,1,'127.0.0.1','2019-07-30 03:28:15'),
(53,1,'127.0.0.1','2019-07-30 03:29:43'),
(54,1,'127.0.0.1','2019-07-30 03:29:58'),
(55,1,'127.0.0.1','2019-08-01 04:32:30'),
(56,1,'127.0.0.1','2019-08-01 04:42:31'),
(57,1,'127.0.0.1','2019-08-02 04:01:17'),
(58,1,'127.0.0.1','2019-08-03 01:57:35'),
(59,1,'127.0.0.1','2019-08-03 03:03:38'),
(60,1,'127.0.0.1','2019-08-03 03:09:21'),
(61,1,'127.0.0.1','2019-08-03 04:26:25'),
(62,1,'127.0.0.1','2019-08-03 21:28:24'),
(63,1,'127.0.0.1','2019-08-04 05:51:00'),
(64,1,'127.0.0.1','2019-08-04 06:00:09'),
(65,1,'127.0.0.1','2019-08-04 06:01:05'),
(66,1,'127.0.0.1','2019-08-04 06:20:07'),
(67,1,'127.0.0.1','2019-08-04 06:21:22'),
(68,1,'127.0.0.1','2019-08-04 06:22:08'),
(69,1,'127.0.0.1','2019-08-04 06:23:23'),
(70,1,'127.0.0.1','2019-08-04 06:37:10'),
(71,1,'127.0.0.1','2019-08-04 06:37:38'),
(72,1,'127.0.0.1','2019-08-04 06:38:25'),
(73,1,'127.0.0.1','2019-08-04 15:26:42'),
(74,1,'127.0.0.1','2019-08-07 22:41:09'),
(75,1,'127.0.0.1','2019-08-07 22:42:11'),
(76,1,'127.0.0.1','2019-08-07 22:44:48'),
(77,1,'127.0.0.1','2019-08-07 23:34:04'),
(78,1,'127.0.0.1','2019-08-11 21:01:16'),
(79,1,'127.0.0.1','2019-08-14 01:31:30'),
(80,1,'127.0.0.1','2019-08-14 22:38:31'),
(81,1,'127.0.0.1','2019-08-21 00:29:42'),
(82,1,'127.0.0.1','2019-09-03 00:46:16'),
(83,1,'127.0.0.1','2019-10-25 01:38:32'),
(84,1,'127.0.0.1','2019-10-26 03:11:02'),
(85,1,'127.0.0.1','2019-12-14 22:25:20'),
(86,22,'127.0.0.1','2019-12-15 16:29:19'),
(87,23,'127.0.0.1','2019-12-15 16:35:08'),
(88,1,'127.0.0.1','2019-12-15 17:04:31'),
(89,1,'127.0.0.1','2019-12-15 22:25:05'),
(90,24,'127.0.0.1','2019-12-16 04:38:36'),
(91,1,'127.0.0.1','2019-12-16 14:01:40'),
(92,1,'127.0.0.1','2019-12-22 05:54:48'),
(93,1,'127.0.0.1','2019-12-24 20:38:09'),
(94,1,'127.0.0.1','2020-02-06 00:25:11');

/*Table structure for table `tests` */

DROP TABLE IF EXISTS `tests`;

CREATE TABLE `tests` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `type` enum('CREATE','RETEST') NOT NULL DEFAULT 'CREATE',
  `title` varchar(512) NOT NULL,
  `options` text NOT NULL,
  `answers` text NOT NULL,
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;

/*Data for the table `tests` */

insert  into `tests`(`id`,`type`,`title`,`options`,`answers`,`create_date`,`update_date`) values 
(2,'CREATE','Воопрос','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-12-16 03:08:32'),
(3,'CREATE','У меня есть ещё вопрос','[\"Вариант ответа №1*\",\"Вариант ответа №2*\",\"Вариант ответа №3*\",\"Вариант ответа №4* (1)\",\"Вариант ответа №5* (1)\"]','[0,0,0,1,1]','2019-07-02 03:37:43','2019-07-11 04:52:59'),
(4,'CREATE','Текст вопроса*vvv','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(5,'CREATE','Текст вопроса*66','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(6,'CREATE','Текст вопроса*555','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(7,'CREATE','Текст вопроса*1','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(8,'CREATE','Текст вопроса*4','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(11,'CREATE','Текст вопроса*ooo','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(12,'CREATE','Текст вопроса*z','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(13,'CREATE','Текст вопроса*aaaa','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(14,'CREATE','Текст вопроса*y','[\"Вариант ответа №1* (1)\",\"Вариант ответа №2*\",\"Вариант ответа №3* (1)\",\"\",\"\"]','[1,0,1,0,0]','2019-07-02 03:37:43','2019-07-02 04:27:18'),
(15,'CREATE','Tewetwtewtwe','[\"twetwtwtew\",\"43636346\",\"43636363\",\"\",\"\"]','[1,1,0,0,0]','2019-12-15 16:21:04','2019-12-15 16:21:04'),
(16,'CREATE','Tewetwtewtwe','[\"twetewtwtw\",\"wwetwtwtewtw\",\"wetwtwtewg\",\"herherhre\",\"\"]','[1,0,0,0,0]','2019-12-15 16:22:00','2019-12-15 16:22:00'),
(17,'RETEST','Retest retest kek 88 8','[\"wetwtw\",\"t436346734y673\",\"43737373 (!)\",\"\",\"\"]','[0,0,1,0,0]','2019-12-15 16:23:20','2020-02-03 22:18:44'),
(18,'RETEST','Retest','[\"123123\",\"1232131 (!)\",\"1232131 (!)\",\"\",\"\"]','[0,1,1,0,0]','2020-02-03 22:18:33','2020-02-03 22:18:33');

/* Function  structure for function  `levenshtein` */

/*!50003 DROP FUNCTION IF EXISTS `levenshtein` */;
DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` FUNCTION `levenshtein`( s1 VARCHAR(255), s2 VARCHAR(255) ) RETURNS int(11)
    DETERMINISTIC
BEGIN 
    DECLARE s1_len, s2_len, i, j, c, c_temp, cost INT; 
    DECLARE s1_char CHAR; 
    -- max strlen=255 
    DECLARE cv0, cv1 VARBINARY(256); 
    SET s1_len = CHAR_LENGTH(s1), s2_len = CHAR_LENGTH(s2), cv1 = 0x00, j = 1, i = 1, c = 0; 
    IF s1 = s2 THEN 
      RETURN 0; 
    ELSEIF s1_len = 0 THEN 
      RETURN s2_len; 
    ELSEIF s2_len = 0 THEN 
      RETURN s1_len; 
    ELSE 
      WHILE j <= s2_len DO 
        SET cv1 = CONCAT(cv1, UNHEX(HEX(j))), j = j + 1; 
      END WHILE; 
      WHILE i <= s1_len DO 
        SET s1_char = SUBSTRING(s1, i, 1), c = i, cv0 = UNHEX(HEX(i)), j = 1; 
        WHILE j <= s2_len DO 
          SET c = c + 1; 
          IF s1_char = SUBSTRING(s2, j, 1) THEN  
            SET cost = 0; ELSE SET cost = 1; 
          END IF; 
          SET c_temp = CONV(HEX(SUBSTRING(cv1, j, 1)), 16, 10) + cost; 
          IF c > c_temp THEN SET c = c_temp; END IF; 
            SET c_temp = CONV(HEX(SUBSTRING(cv1, j+1, 1)), 16, 10) + 1; 
            IF c > c_temp THEN  
              SET c = c_temp;  
            END IF; 
            SET cv0 = CONCAT(cv0, UNHEX(HEX(c))), j = j + 1; 
        END WHILE; 
        SET cv1 = cv0, i = i + 1; 
      END WHILE; 
    END IF; 
    RETURN c; 
  END */$$
DELIMITER ;

/* Function  structure for function  `levenshtein_ratio` */

/*!50003 DROP FUNCTION IF EXISTS `levenshtein_ratio` */;
DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` FUNCTION `levenshtein_ratio`( s1 VARCHAR(255), s2 VARCHAR(255) ) RETURNS int(11)
    DETERMINISTIC
BEGIN 
    DECLARE s1_len, s2_len, max_len INT; 
    SET s1_len = LENGTH(s1), s2_len = LENGTH(s2); 
    IF s1_len > s2_len THEN  
      SET max_len = s1_len;  
    ELSE  
      SET max_len = s2_len;  
    END IF; 
    RETURN ROUND((1 - LEVENSHTEIN(s1, s2) / max_len) * 100); 
  END */$$
DELIMITER ;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
