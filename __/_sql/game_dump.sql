-- MySQL dump 10.13  Distrib 5.5.62, for Win64 (AMD64)
--
-- Host: localhost    Database: samp_furystories
-- ------------------------------------------------------
-- Server version	5.7.25

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admins`
--

DROP TABLE IF EXISTS `admins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admins` (
  `a_user_id` int(11) unsigned NOT NULL,
  `a_level` int(1) NOT NULL DEFAULT '0',
  `a_ip` varchar(18) NOT NULL DEFAULT '',
  `ap_developer` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_manage_admins` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_manage_helpers` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_property` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_closed_registration` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_manage_fraction` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_manage_crime` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `ap_capital` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`a_user_id`),
  UNIQUE KEY `UNIQUE` (`a_user_id`),
  CONSTRAINT `FK_admin_user_id` FOREIGN KEY (`a_user_id`) REFERENCES `users` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admins`
--

LOCK TABLES `admins` WRITE;
/*!40000 ALTER TABLE `admins` DISABLE KEYS */;
INSERT INTO `admins` VALUES (1,5,'127.0.0.1',1,1,1,1,1,1,1,1),(2,5,'176.110.235.237',1,1,1,1,1,1,1,1),(3,5,'',0,0,0,0,1,0,0,1),(4,5,'5.165.102.35',1,1,1,1,1,1,1,1);
/*!40000 ALTER TABLE `admins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `admins_log`
--

DROP TABLE IF EXISTS `admins_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admins_log` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `type` varchar(255) NOT NULL,
  `arguments` varchar(512) NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_admin_log_type_id` (`type`)
) ENGINE=InnoDB AUTO_INCREMENT=64 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admins_log`
--

LOCK TABLES `admins_log` WRITE;
/*!40000 ALTER TABLE `admins_log` DISABLE KEYS */;
INSERT INTO `admins_log` VALUES (1,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> На рассмотрении, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:57:34'),(2,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Одобрено, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:57:42'),(3,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> На доработке, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:57:48'),(4,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Одобрено, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:57:55'),(5,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> На доработке, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:58:32'),(6,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Одобрено, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:58:37'),(7,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Character Kill / Архив, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:58:41'),(8,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> , пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:58:46'),(9,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Character Kill / Архив, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:59:24'),(10,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> На доработке, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:59:27'),(11,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Character Kill / Архив, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:59:32'),(12,'CHARACTER_EDIT','Found|1|127.0.0.1|Esmond_Wheeler|3|имя -> Esmond_Wheeler, статус -> Одобрено, пол -> Мужской, раса -> Негроидная, роль -> Обычный житель, наличные -> $87449, банк -> $0, карта -> $1142845954, удержано -> $0','2020-02-03 23:59:36'),(13,'USER_EDIT','Found|1|127.0.0.1|Found|1|имя -> Found, статус -> На ретесте, сброс пароля -> нет, донат -> 2, E-mail -> evg.savosin@gmail.com, E-mail подтверждён -> да','2020-02-04 00:16:09'),(14,'USER_WARN','Found|1|127.0.0.1|test_2|3|0|1|[OFFLINE] Test','2020-02-04 00:32:22'),(15,'USER_WARN','Found|1|127.0.0.1|test_2|3|1|2|[OFFLINE] Test1','2020-02-04 00:32:33'),(16,'USER_BAN','Found|1|127.0.0.1|test_2|3|05d 12h 02m|[OFFLINE][Предупреждение (3/ 5)] 1','2020-02-04 00:35:49'),(17,'USER_BAN','Found|1|127.0.0.1|test_2|3|11d 12h 02m|[OFFLINE][UPDATE_BAN][Предупреждение (4/ 5)] 1','2020-02-04 00:35:52'),(18,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (5/ 5)] 1','2020-02-04 00:35:54'),(19,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (6/ 5)] 1','2020-02-04 00:35:56'),(20,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (7/ 5)] 1','2020-02-04 00:35:56'),(21,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (8/ 5)] 1','2020-02-04 00:35:57'),(22,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (9/ 5)] 1','2020-02-04 00:35:57'),(23,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (10/ 5)] 1','2020-02-04 00:35:57'),(24,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (11/ 5)] 1','2020-02-04 00:35:58'),(25,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (12/ 5)] 1','2020-02-04 00:35:58'),(26,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (13/ 5)] 1','2020-02-04 00:35:58'),(27,'USER_WARN','Found|1|127.0.0.1|test_2|3|13|14|[OFFLINE] еуе','2020-02-04 00:36:49'),(28,'USER_WARN','Found|1|127.0.0.1|test_2|3|14|15|[OFFLINE] еуе','2020-02-04 00:36:50'),(29,'USER_WARN','Found|1|127.0.0.1|test_2|3|15|16|[OFFLINE] еуе','2020-02-04 00:36:50'),(30,'USER_UNBAN','Found|1|127.0.0.1|test_2|3|[OFFLINE] tet','2020-02-04 00:37:34'),(31,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|16|15|[OFFLINE] 7','2020-02-04 00:37:41'),(32,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|15|14|[OFFLINE] yrey','2020-02-04 00:38:09'),(33,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|14|13|[OFFLINE] yrey','2020-02-04 00:38:11'),(34,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|13|12|[OFFLINE] yrey','2020-02-04 00:38:13'),(35,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|12|11|[OFFLINE] yrey','2020-02-04 00:38:13'),(36,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|11|10|[OFFLINE] yrey','2020-02-04 00:38:14'),(37,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|10|9|[OFFLINE] yrey','2020-02-04 00:38:14'),(38,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|9|8|[OFFLINE] yrey','2020-02-04 00:38:14'),(39,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|8|7|[OFFLINE] yrey','2020-02-04 00:38:14'),(40,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|7|6|[OFFLINE] yrey','2020-02-04 00:38:15'),(41,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|6|5|[OFFLINE] yrey','2020-02-04 00:38:15'),(42,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|5|4|[OFFLINE] yrey','2020-02-04 00:38:15'),(43,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|4|3|[OFFLINE] yrey','2020-02-04 00:38:16'),(44,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|3|2|[OFFLINE] yrey','2020-02-04 00:38:17'),(45,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|2|1|[OFFLINE] yrey','2020-02-04 00:38:17'),(46,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|1|0|[OFFLINE] yrey','2020-02-04 00:38:17'),(47,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|0|0|[OFFLINE] yrey','2020-02-04 00:38:18'),(48,'USER_WARN','Found|1|127.0.0.1|test_2|3|0|1|[OFFLINE] test','2020-02-04 00:38:24'),(49,'USER_WARN','Found|1|127.0.0.1|test_2|3|1|2|[OFFLINE] test','2020-02-04 00:38:25'),(50,'USER_BAN','Found|1|127.0.0.1|test_2|3|05d 12h 02m|[OFFLINE][Предупреждение (3/ 5)] test','2020-02-04 00:38:25'),(51,'USER_BAN','Found|1|127.0.0.1|test_2|3|11d 12h 02m|[OFFLINE][UPDATE_BAN][Предупреждение (4/ 5)] test','2020-02-04 00:38:27'),(52,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (5/ 5)] test','2020-02-04 00:38:28'),(53,'USER_WARN','Found|1|127.0.0.1|test_2|3|5|6|[OFFLINE] test','2020-02-04 00:38:30'),(54,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|6|5|[OFFLINE] yrey','2020-02-04 00:38:49'),(55,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|5|4|[OFFLINE] yrey','2020-02-04 00:38:51'),(56,'USER_BAN','Found|1|127.0.0.1|test_2|3|permanent|[OFFLINE][UPDATE_BAN][Предупреждение (5/ 5)] tu','2020-02-04 00:38:54'),(57,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|5|4|[OFFLINE] 32','2020-02-04 00:39:23'),(58,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|4|3|[OFFLINE] 32','2020-02-04 00:39:24'),(59,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|3|2|[OFFLINE] 32','2020-02-04 00:39:24'),(60,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|2|1|[OFFLINE] 32','2020-02-04 00:39:24'),(61,'USER_UNWARN','Found|1|127.0.0.1|test_2|3|1|0|[OFFLINE] 32','2020-02-04 00:39:25'),(62,'USER_UNBAN','Found|1|127.0.0.1|test_2|3|[OFFLINE] 45','2020-02-04 00:39:29'),(63,'USER_EDIT','Found|1|127.0.0.1|Found|1|имя -> Found, статус -> На ретесте, сброс пароля -> нет, донат -> 2, E-mail -> evg.savosin@gmail.com, E-mail подтверждён -> да','2020-02-04 00:39:46');
/*!40000 ALTER TABLE `admins_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `admins_log_type`
--

DROP TABLE IF EXISTS `admins_log_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admins_log_type` (
  `name` enum('USER_BAN','USER_UNBAN','USER_WARN','USER_UNWARN','USER_MUTE','USER_UNMUTE','USER_EDIT','CHARACTER_BAN','CHARACTER_UNBAN','CLOSED_REGISTRATION','CAPITAL','CHARACTER_EDIT','SET_MONEY','GIVE_ITEM','CHARACTER_CK','CHARACTER_UNCK','ADMIN_ADD','ADMIN_EDIT','ADMIN_DELETE','HELPER_ADD','HELPER_EDIT','HELPER_DELETE','GIVE_MONEY') NOT NULL,
  `full_name` varchar(255) NOT NULL,
  `format` varchar(255) NOT NULL,
  `fields` varchar(512) NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE KEY `UNIQUE_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admins_log_type`
--

LOCK TABLES `admins_log_type` WRITE;
/*!40000 ALTER TABLE `admins_log_type` DISABLE KEYS */;
INSERT INTO `admins_log_type` VALUES ('USER_BAN','Блокировка аккаунта','%s[%d][IP:%s] заблокировал аккаунт %s[%d] на %s. Причина: %s','Администратор|IP|Аккаунт|Срок|Причина'),('USER_UNBAN','Разблокировка аккаунта','%s[%d][IP:%s] разблокировал аккаунт %s[%d]. Причина: %s','Администратор|IP|Аккаунт|Причина'),('USER_WARN','Предупреждение','%s[%d][IP:%s] выдал предупреждение %s[%d] (было -> %d, стало -> %d, было всего -> %d, стало всего -> %d). Причина: %s','Администратор|IP|Аккаунт|Причина'),('USER_UNWARN','Снятие предупреждений','%s[%d][IP:%s] снял предупреждение с %s[%d] (было -> %d, стало -> %d, было всего -> %d, стало всего -> %d). Причина: %s','Администратор|IP|Аккаунт|Причина'),('USER_MUTE','Блокировка чата','%s[%d][IP:%s] заблокировал чат %s[%d] на %d мин. Причина: %s','Администратор|IP|Аккаунт|Срок|Причина'),('USER_UNMUTE','Разблокировка чата','%s[%d][IP:%s] разблокировал чат %s[%d]. Причина: %s','Администратор|IP|Аккаунт|Причина'),('USER_EDIT','Редактирование аккаунта','%s[%d][IP:%s] отредактировал аккаунт %s[%d] (%s).','Администратор|IP|Аккаунт'),('CHARACTER_BAN','Блокировка персонажа','%s[%d][IP:%s] заблокировал персонажа %s[%d] на %s. Причина: %s','Администратор|IP|Персонаж|Срок|Причина'),('CHARACTER_UNBAN','Разблокировка персонажа','%s[%d][IP:%s] разблокировал персонажа %s[%d]. Причина: %s','Администратор|IP|Персонаж|Причина'),('CLOSED_REGISTRATION','Проверка заявлений на регистрацию','%s[%d][IP:%s] проверил заявление %s[%d]. Статус: %s','Администратор|IP|Персонаж|Статус'),('CAPITAL','Проверка заявлений на рабочий капитал','%s[%d][IP:%s] проверил заявление %s[%d]. Статус: %s','Администратор|IP|Персонаж|Статус'),('CHARACTER_EDIT','Редактирование персонажа','%s[%d][IP:%s] отредактировал персонажа %s[%d] (%s).','Администратор|IP|Персонаж'),('GIVE_ITEM','Внутриигровые предметы','%s[%d][IP:%s] выдал предмет %s (ID: %i) %s[%d].','Администратор|IP|Предмет|ID предмета|Аккаунт'),('CHARACTER_CK','Выдача «Character Kill»','%s[%d][IP:%s] выдал «Character Kill» %s[%d].','Администратор|IP|Персонаж'),('CHARACTER_UNCK','Снятие «Character Kill»','%s[%d][IP:%s] снял «Character Kill» %s[%d].','Администратор|IP|Персонаж'),('ADMIN_ADD','Назначение администратора','%s[%d][IP:%s] добавил администратора %s[%d] (%s).','Администратор|IP|Аккаунт'),('ADMIN_EDIT','Редактирование администратора','%s[%d][IP:%s] отредактировал администратора %s[%d] (%s).','Администратор|IP|Аккаунт'),('ADMIN_DELETE','Удаление администратора','%s[%d][IP:%s] удалил администратора %s[%d].','Администратор|IP|Аккаунт'),('HELPER_ADD','Назначение хелпера','%s[%d][IP:%s] назначил хелпера %s[%d].','Администратор|IP|Аккаунт'),('HELPER_DELETE','Удаление хелпера','%s[%d][IP:%s] удалил хелпера %s[%d].','Администратор|IP|Аккаунт'),('GIVE_MONEY','Выдача средств','%s[%d][IP:%s] выдал средства %s[%d].','Администратор|IP|Аккаунт');
/*!40000 ALTER TABLE `admins_log_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `adverts`
--

DROP TABLE IF EXISTS `adverts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `adverts` (
  `ad_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ad_character_id` int(11) unsigned NOT NULL,
  `ad_number` int(6) NOT NULL,
  `ad_category` int(11) NOT NULL,
  `ad_type` tinyint(4) NOT NULL DEFAULT '0',
  `ad_price` int(11) NOT NULL DEFAULT '0',
  `ad_title` varchar(64) NOT NULL,
  `ad_text` varchar(128) NOT NULL,
  `ad_created_time` int(11) NOT NULL,
  PRIMARY KEY (`ad_id`),
  KEY `FK_ad_character_id` (`ad_character_id`),
  CONSTRAINT `FK_ad_character_id` FOREIGN KEY (`ad_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `adverts`
--

LOCK TABLES `adverts` WRITE;
/*!40000 ALTER TABLE `adverts` DISABLE KEYS */;
/*!40000 ALTER TABLE `adverts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bans`
--

DROP TABLE IF EXISTS `bans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bans` (
  `b_id` int(11) NOT NULL AUTO_INCREMENT,
  `b_type` enum('CHARACTER','USER') NOT NULL,
  `b_account_id` int(11) NOT NULL,
  `b_account_name` varchar(24) NOT NULL,
  `b_account_ip` varchar(17) NOT NULL,
  `b_admin_id` int(11) NOT NULL DEFAULT '-1',
  `b_admin_name` varchar(24) NOT NULL DEFAULT 'SERVER',
  `b_admin_ip` varchar(17) NOT NULL DEFAULT '127.0.0.1',
  `b_ban_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `b_before_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `b_reason` varchar(64) NOT NULL,
  `b_active` tinyint(1) NOT NULL DEFAULT '1',
  `b_user_ip` varchar(17) NOT NULL DEFAULT '',
  PRIMARY KEY (`b_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bans`
--

LOCK TABLES `bans` WRITE;
/*!40000 ALTER TABLE `bans` DISABLE KEYS */;
INSERT INTO `bans` VALUES (3,'USER',299,'ic3berg','',17,'cheesenachos','176.197.133.219','2019-12-23 15:44:56','2038-01-01 03:00:00','Троллинг в заявках.',1,''),(4,'',422,'J¦s','',257,'publicenemy','188.162.166.251','2019-12-30 21:38:31','1970-01-01 03:01:30','cheats',0,'195.58.56.167');
/*!40000 ALTER TABLE `bans` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `businesses`
--

DROP TABLE IF EXISTS `businesses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `businesses` (
  `b_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `b_character_id` int(11) NOT NULL,
  `b_name` varchar(64) NOT NULL,
  `b_type` int(2) NOT NULL,
  `b_subtype` tinyint(2) NOT NULL DEFAULT '-1',
  `b_created_time` int(11) NOT NULL,
  `b_profit` int(11) NOT NULL DEFAULT '0',
  `b_profit_weekly` int(11) NOT NULL DEFAULT '0',
  `b_profit_weekly_time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`b_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `businesses`
--

LOCK TABLES `businesses` WRITE;
/*!40000 ALTER TABLE `businesses` DISABLE KEYS */;
INSERT INTO `businesses` VALUES (1,3,'test',0,2,1579006802,0,0,1612620640);
/*!40000 ALTER TABLE `businesses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `businesses_assort`
--

DROP TABLE IF EXISTS `businesses_assort`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `businesses_assort` (
  `ba_business_id` int(11) unsigned NOT NULL,
  `ba_item_id` int(11) NOT NULL,
  `ba_item_param` int(11) NOT NULL DEFAULT '0',
  `ba_cost` int(11) NOT NULL,
  `ba_created_time` int(11) NOT NULL,
  KEY `FK_assort_business_id` (`ba_business_id`),
  CONSTRAINT `FK_assort_business_id` FOREIGN KEY (`ba_business_id`) REFERENCES `businesses` (`b_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `businesses_assort`
--

LOCK TABLES `businesses_assort` WRITE;
/*!40000 ALTER TABLE `businesses_assort` DISABLE KEYS */;
INSERT INTO `businesses_assort` VALUES (1,66,18941,80,1579498249),(1,66,18939,80,1579498250),(1,69,18950,50,1579498252),(1,69,18948,50,1579498254);
/*!40000 ALTER TABLE `businesses_assort` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `businesses_member`
--

DROP TABLE IF EXISTS `businesses_member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `businesses_member` (
  `bm_business_id` int(11) unsigned NOT NULL,
  `bm_character_id` int(11) NOT NULL,
  `bm_perm_renovation` tinyint(1) NOT NULL DEFAULT '0',
  `bm_perm_lock` tinyint(1) NOT NULL DEFAULT '0',
  `bm_perm_invite` tinyint(1) NOT NULL DEFAULT '0',
  `bm_perm_uninvite` tinyint(1) NOT NULL DEFAULT '0',
  `bm_perm_change` tinyint(1) NOT NULL DEFAULT '0',
  KEY `FK_businesses_member_id` (`bm_business_id`),
  CONSTRAINT `FK_businesses_member_id` FOREIGN KEY (`bm_business_id`) REFERENCES `businesses` (`b_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `businesses_member`
--

LOCK TABLES `businesses_member` WRITE;
/*!40000 ALTER TABLE `businesses_member` DISABLE KEYS */;
/*!40000 ALTER TABLE `businesses_member` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters` (
  `c_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `c_user_id` int(11) unsigned NOT NULL DEFAULT '0',
  `c_name` varchar(24) NOT NULL,
  `c_role` tinyint(1) NOT NULL DEFAULT '1',
  `c_status` enum('WAITING','ACCEPT','DECLINE','CHARACTER_KILL') NOT NULL DEFAULT 'ACCEPT',
  `c_status_update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_health` float NOT NULL DEFAULT '100',
  `c_pos_x` float NOT NULL DEFAULT '0',
  `c_pos_y` float NOT NULL DEFAULT '0',
  `c_pos_z` float NOT NULL DEFAULT '0',
  `c_pos_angle` float NOT NULL DEFAULT '0',
  `c_world` int(11) NOT NULL DEFAULT '0',
  `c_int` int(11) DEFAULT '0',
  `c_race` tinyint(1) NOT NULL DEFAULT '0',
  `c_sex` int(1) NOT NULL DEFAULT '0',
  `c_skin` int(3) NOT NULL DEFAULT '1',
  `c_age` tinyint(2) unsigned NOT NULL,
  `c_payday` tinyint(2) NOT NULL DEFAULT '0',
  `c_got_payday` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `c_money` int(11) NOT NULL DEFAULT '200' COMMENT 'Наличные',
  `c_refund` int(11) NOT NULL DEFAULT '0' COMMENT 'Удержано на продажах имущества',
  `c_card` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Карта',
  `c_bank` int(11) NOT NULL DEFAULT '0' COMMENT 'Счёт в банке',
  `c_start_capital` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Стартовый капитал',
  `c_start_pack_buy_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_credit_level` tinyint(1) NOT NULL DEFAULT '0',
  `c_online` int(1) NOT NULL DEFAULT '0',
  `c_last_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_register_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_desc` varchar(144) NOT NULL DEFAULT '',
  `c_desc_created_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_death` tinyint(1) NOT NULL DEFAULT '0',
  `c_attack_weapon_id` tinyint(2) NOT NULL DEFAULT '0',
  `c_attack_name_fist` varchar(24) NOT NULL DEFAULT '',
  `c_attack_name_cold` varchar(24) NOT NULL DEFAULT '',
  `c_attack_name_camera` varchar(24) NOT NULL DEFAULT '',
  `c_buy_weapon_count` tinyint(1) NOT NULL DEFAULT '0',
  `c_capital_id` int(11) unsigned NOT NULL,
  `c_capital_value` int(11) unsigned NOT NULL DEFAULT '0',
  `c_capital_end_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_history` text NOT NULL,
  `c_history_update_date` date NOT NULL DEFAULT '1970-01-01',
  `c_fuber_balance` int(11) unsigned NOT NULL DEFAULT '0',
  `c_fuber_reputation` int(11) NOT NULL DEFAULT '0',
  `c_fuber_reputation_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_fuber_method_payment` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `c_fraction_id` int(11) unsigned NOT NULL DEFAULT '0',
  `c_fraction_rank_id` int(11) unsigned NOT NULL DEFAULT '0',
  `c_fraction_unit_id` int(11) unsigned NOT NULL DEFAULT '0',
  `c_fraction_skin` int(11) unsigned NOT NULL DEFAULT '0',
  `c_fraction_duty` tinyint(1) NOT NULL DEFAULT '0',
  `c_suspect` varchar(255) NOT NULL DEFAULT '',
  `c_arrest_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `c_arrest_type` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `c_arrest_camera` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`c_id`),
  UNIQUE KEY `UNIQUE_id` (`c_id`),
  UNIQUE KEY `UNIQUE_name` (`c_name`),
  KEY `FK_character_user_id` (`c_user_id`),
  CONSTRAINT `FK_character_user_id` FOREIGN KEY (`c_user_id`) REFERENCES `users` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters`
--

LOCK TABLES `characters` WRITE;
/*!40000 ALTER TABLE `characters` DISABLE KEYS */;
INSERT INTO `characters` VALUES (3,1,'Esmond_Wheeler',0,'ACCEPT','2020-02-03 23:59:36',100,1603.18,-1249.86,17.4755,219.499,0,0,0,0,18,0,20,0,87449,0,1142845954,0,1158,'1970-01-01 00:00:00',0,1,'2021-02-06 21:16:52','2020-01-13 23:27:56','Парень крутой на стиле','2019-12-29 03:09:12',0,0,'','','',0,2,0,'1970-01-01 03:00:00','\newtewtwtwtwetewt\n 856865858585858858 Test test','2020-02-18',0,3,'1970-01-01 00:00:00',1,3,0,0,0,1,'','1970-01-01 03:00:00',0,0),(5,2,'Test_TestA',0,'ACCEPT','2019-12-29 20:39:17',100,1600.84,-1246.04,17.4692,198.819,0,0,0,0,302,0,76,0,7608,0,217636,0,0,'1970-01-01 00:00:00',0,0,'2020-02-10 00:51:02','2019-07-09 06:38:32','Парень крутой на стиле','2019-12-29 03:09:12',0,0,'','','',0,2,0,'1970-01-01 03:00:00','','1970-01-01',0,3,'1970-01-01 00:00:00',1,0,0,0,0,1,'','1970-01-01 03:00:00',0,0),(6,3,'Test_TestB',0,'ACCEPT','2019-12-29 20:39:17',98.68,1602.57,-1262.59,17.4738,182.526,0,0,0,0,302,0,3,0,7608,0,212488,0,0,'1970-01-01 00:00:00',0,0,'2019-12-30 21:51:30','2019-07-09 06:38:32','Парень крутой на стиле','2019-12-29 03:09:12',0,0,'','','',0,2,596,'2019-08-23 00:05:52','','1970-01-01',0,3,'1970-01-01 00:00:00',1,3,0,0,0,0,'','1970-01-01 00:00:00',1,0);
/*!40000 ALTER TABLE `characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_animation`
--

DROP TABLE IF EXISTS `characters_animation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_animation` (
  `character_id` int(11) unsigned NOT NULL,
  `cmd` varchar(16) NOT NULL,
  `cmd_param` tinyint(2) unsigned NOT NULL DEFAULT '0',
  `index` tinyint(2) unsigned NOT NULL DEFAULT '0',
  KEY `FK_anim_character_id` (`character_id`),
  CONSTRAINT `FK_anim_character_id` FOREIGN KEY (`character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_animation`
--

LOCK TABLES `characters_animation` WRITE;
/*!40000 ALTER TABLE `characters_animation` DISABLE KEYS */;
INSERT INTO `characters_animation` VALUES (3,'laugh',0,2);
/*!40000 ALTER TABLE `characters_animation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_delete`
--

DROP TABLE IF EXISTS `characters_delete`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_delete` (
  `c_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `c_character_id` int(11) unsigned NOT NULL COMMENT 'Персонаж, который удаляется',
  `c_user_id` int(11) unsigned NOT NULL COMMENT 'Инициатор удаления',
  `c_start_date` datetime NOT NULL,
  `c_end_date` datetime NOT NULL,
  `c_deleted` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`c_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_delete`
--

LOCK TABLES `characters_delete` WRITE;
/*!40000 ALTER TABLE `characters_delete` DISABLE KEYS */;
INSERT INTO `characters_delete` VALUES (3,4,1,'2020-02-06 00:24:39','2020-02-09 20:24:39',1),(4,7,1,'2020-02-10 02:55:42','2020-02-10 02:55:42',1);
/*!40000 ALTER TABLE `characters_delete` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_kill`
--

DROP TABLE IF EXISTS `characters_kill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_kill` (
  `ck_character_id` int(11) unsigned NOT NULL,
  `ck_character_name` varchar(24) NOT NULL,
  `ck_offer_id` int(11) unsigned NOT NULL,
  `ck_offer_name` varchar(24) NOT NULL,
  `ck_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`ck_character_id`),
  CONSTRAINT `FK_ck_character_id` FOREIGN KEY (`ck_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_kill`
--

LOCK TABLES `characters_kill` WRITE;
/*!40000 ALTER TABLE `characters_kill` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_kill` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_log`
--

DROP TABLE IF EXISTS `characters_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_log` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `type` int(11) unsigned NOT NULL,
  `arguments` varchar(512) NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_log`
--

LOCK TABLES `characters_log` WRITE;
/*!40000 ALTER TABLE `characters_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_log_type`
--

DROP TABLE IF EXISTS `characters_log_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_log_type` (
  `name` enum('TRANSFER_MONEY','TRANSFER_BANK','BUY_HOUSE','SELL_HOUSE','BUY_VEHICLE','SELL_VEHICLE','CHARITY','BUY_PREMISE','SELL_PREMISE','CHANGE_NAME') NOT NULL,
  `full_name` varchar(255) NOT NULL,
  `format` varchar(255) NOT NULL,
  `fields` varchar(255) NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE KEY `UNIQUE_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_log_type`
--

LOCK TABLES `characters_log_type` WRITE;
/*!40000 ALTER TABLE `characters_log_type` DISABLE KEYS */;
INSERT INTO `characters_log_type` VALUES ('TRANSFER_MONEY','Передача наличных','%s[%d][IP:%s] передал %s[%d][IP:%s] сумму $%d','Игрок №1|ID|IP|Игрок №2|ID|IP|Сумма'),('TRANSFER_BANK','Перевод средств через банк','%s[%d][IP:%s] перевел через банк %s[%d][IP:%s] сумму $%d','Игрок №1|ID|IP|Игрок №2|ID|IP|Сумма'),('CHARITY','Жертвование средств (/charity)','%s[%d][IP:%s] пожертвовал $%d.','Игрок|ID|IP|Сумма');
/*!40000 ALTER TABLE `characters_log_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_settings`
--

DROP TABLE IF EXISTS `characters_settings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters_settings` (
  `set_character_id` int(11) unsigned NOT NULL,
  `set_spawn` tinyint(2) NOT NULL DEFAULT '0',
  `set_spawn_street` int(2) NOT NULL DEFAULT '0',
  `set_walk` tinyint(1) NOT NULL DEFAULT '1',
  `set_talk` tinyint(1) NOT NULL DEFAULT '0',
  `set_greetings` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `set_style` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`set_character_id`),
  CONSTRAINT `FK_character_id` FOREIGN KEY (`set_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characters_settings`
--

LOCK TABLES `characters_settings` WRITE;
/*!40000 ALTER TABLE `characters_settings` DISABLE KEYS */;
INSERT INTO `characters_settings` VALUES (3,0,0,11,0,6,1),(5,0,0,1,2,6,0),(6,0,0,1,2,6,0);
/*!40000 ALTER TABLE `characters_settings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `corpses`
--

DROP TABLE IF EXISTS `corpses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `corpses` (
  `corp_id` int(11) NOT NULL AUTO_INCREMENT,
  `corp_state` tinyint(1) NOT NULL DEFAULT '0',
  `corp_reason` tinyint(1) NOT NULL DEFAULT '0',
  `corp_weapon_id` tinyint(2) NOT NULL DEFAULT '0',
  `corp_body_part` tinyint(2) NOT NULL DEFAULT '0',
  `corp_character_name` varchar(24) NOT NULL,
  `corp_attack_name_fist` varchar(24) NOT NULL,
  `corp_attack_name_cold` varchar(24) NOT NULL,
  `corp_camera_name` varchar(24) NOT NULL,
  `corp_poured_gas` tinyint(1) NOT NULL DEFAULT '0',
  `corp_skin` tinyint(3) NOT NULL,
  `corp_pos_x` float NOT NULL,
  `corp_pos_y` float NOT NULL,
  `corp_pos_z` float NOT NULL,
  `corp_pos_angle` float NOT NULL,
  `corp_world` int(11) NOT NULL,
  `corp_int` int(11) NOT NULL,
  `corp_created_time` int(11) NOT NULL,
  PRIMARY KEY (`corp_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `corpses`
--

LOCK TABLES `corpses` WRITE;
/*!40000 ALTER TABLE `corpses` DISABLE KEYS */;
/*!40000 ALTER TABLE `corpses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `credits`
--

DROP TABLE IF EXISTS `credits`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `credits` (
  `credit_character_id` int(11) unsigned NOT NULL,
  `credit_card` int(11) NOT NULL DEFAULT '0',
  `credit_limit` int(11) NOT NULL DEFAULT '0',
  `credit_expense` int(11) NOT NULL DEFAULT '0',
  `credit_give_time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`credit_character_id`),
  UNIQUE KEY `credit_character_id` (`credit_character_id`),
  CONSTRAINT `FK_credit_character_id` FOREIGN KEY (`credit_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `credits`
--

LOCK TABLES `credits` WRITE;
/*!40000 ALTER TABLE `credits` DISABLE KEYS */;
INSERT INTO `credits` VALUES (3,15000,15000,-100,1579497820);
/*!40000 ALTER TABLE `credits` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `crimes`
--

DROP TABLE IF EXISTS `crimes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crimes` (
  `cr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `cr_name` varchar(32) NOT NULL,
  `cr_leader_name` varchar(20) NOT NULL,
  `cr_type_id` int(11) NOT NULL,
  `cr_official` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `cr_money` int(11) unsigned NOT NULL DEFAULT '0',
  `cr_update_date` datetime NOT NULL,
  PRIMARY KEY (`cr_id`),
  UNIQUE KEY `UNIQUE_name` (`cr_name`)
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crimes`
--

LOCK TABLES `crimes` WRITE;
/*!40000 ALTER TABLE `crimes` DISABLE KEYS */;
INSERT INTO `crimes` VALUES (41,'Mafia Bank','Frank_Buscetta',2,0,1900,'0000-00-00 00:00:00'),(42,'Latin Kings','',2,0,1900,'0000-00-00 00:00:00');
/*!40000 ALTER TABLE `crimes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `crimes_member`
--

DROP TABLE IF EXISTS `crimes_member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crimes_member` (
  `cr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `cr_crime_id` int(11) unsigned NOT NULL,
  `cr_character_id` int(11) unsigned NOT NULL,
  `cr_leader` tinyint(1) unsigned NOT NULL,
  `cr_perm_invite` tinyint(1) unsigned NOT NULL,
  `cr_perm_uninvite` tinyint(1) unsigned NOT NULL,
  `cr_perm_buy` tinyint(1) unsigned NOT NULL,
  `cr_perm_manage` tinyint(1) unsigned NOT NULL,
  PRIMARY KEY (`cr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crimes_member`
--

LOCK TABLES `crimes_member` WRITE;
/*!40000 ALTER TABLE `crimes_member` DISABLE KEYS */;
INSERT INTO `crimes_member` VALUES (98,41,6,1,0,0,0,0),(99,41,11,0,0,0,1,0);
/*!40000 ALTER TABLE `crimes_member` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `crimes_type`
--

DROP TABLE IF EXISTS `crimes_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crimes_type` (
  `cr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `cr_name` varchar(32) NOT NULL,
  `cr_max_money` int(11) unsigned NOT NULL DEFAULT '0',
  `cr_money` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`cr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crimes_type`
--

LOCK TABLES `crimes_type` WRITE;
/*!40000 ALTER TABLE `crimes_type` DISABLE KEYS */;
INSERT INTO `crimes_type` VALUES (1,'Плохо организованная группировка',1300,650),(2,'Уличная группировка',1900,950),(3,'ОПГ',2500,1250),(4,'Синдикат',3000,1500);
/*!40000 ALTER TABLE `crimes_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `donate`
--

DROP TABLE IF EXISTS `donate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `donate` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL,
  `donate_item_id` int(11) unsigned NOT NULL,
  `create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `donate`
--

LOCK TABLES `donate` WRITE;
/*!40000 ALTER TABLE `donate` DISABLE KEYS */;
INSERT INTO `donate` VALUES (20,41,5,'2020-01-21 23:50:11'),(21,41,5,'2020-01-21 23:50:11'),(22,472,6,'2020-01-21 23:50:11'),(23,472,6,'2020-01-21 23:50:11');
/*!40000 ALTER TABLE `donate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `donate_category`
--

DROP TABLE IF EXISTS `donate_category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `donate_category` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL,
  `description` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `donate_category`
--

LOCK TABLES `donate_category` WRITE;
/*!40000 ALTER TABLE `donate_category` DISABLE KEYS */;
INSERT INTO `donate_category` VALUES (1,'Купоны','С помощью привилегий Вы можете реализовать базовые потребности.'),(2,'Кейсы','Кейсы предоставляют возможность обзавестись предметом самообороны, в том числе огнестрельным оружием. Имейте ввиду, что полученное оружие будет считаться нелегальным. '),(3,'Пакеты','Пакет капитала расширит возможности во время игры. \r\nВы сможете приобрести с помощью него более дорогое имущество или сделать существенное вложение в развитие собственного бизнеса. \r\nПакеты можно использовать только 1 раз на персонаже.'),(4,'VIP аккаунты','Покупая VIP аккаунт, Вы фактически оплачиваете увеличенные лимиты, за счёт нагрузки на сервер.');
/*!40000 ALTER TABLE `donate_category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `donate_item`
--

DROP TABLE IF EXISTS `donate_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `donate_item` (
  `id` int(11) unsigned NOT NULL,
  `category_id` int(11) unsigned NOT NULL,
  `title` varchar(255) NOT NULL,
  `description` text NOT NULL,
  `cost` int(11) DEFAULT NULL,
  `update_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UNIQUE` (`id`),
  KEY `FK_donate_category_id` (`category_id`),
  CONSTRAINT `FK_donate_category_id` FOREIGN KEY (`category_id`) REFERENCES `donate_category` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `donate_item`
--

LOCK TABLES `donate_item` WRITE;
/*!40000 ALTER TABLE `donate_item` DISABLE KEYS */;
INSERT INTO `donate_item` VALUES (1,1,'Смена имени персонажа','Данная привилегия позволяет изменить имя и фамилию персонажа.',30,'2019-07-24 00:30:24'),(2,1,'Снять предупреждение','Данная привилегия снимает с аккаунта одно предупреждение.',60,'2019-07-24 00:30:57'),(3,1,'Смена номера транспорта','Данная привилегия позволяет изменить номер транспорта. Можно использовать как цифры, так и латинские буквы.',100,'2019-07-24 03:17:36'),(4,1,'Смена номера телефона','Данная привилегия позволяет вам изменить номер телефона на желаемый. Количество цифр номера может быть от 3-х до 6-и.',80,'2019-08-14 02:10:07'),(5,2,'Оружейный кейс','Из этого кейса Вам может выпасть:\r\nКастет;\r\nКатана;\r\nМалогабаритный пистолет;\r\nМалогабаритный ПП;\r\nКоличество FPoint от 100 до 200.',150,'2019-08-14 02:19:30'),(6,2,'Армейский кейс','Из этого кейса Вам может выпасть:\r\nБронежилет;\r\nНож выживания;\r\nМалогабаритный пистолет с глушителем;\r\nПолуавтоматический пистолет;\r\nПистолет-пулемет.\r\n\r\n',220,'2019-08-14 02:19:30'),(7,3,'Стандартный пакет','Лёгкая поддержка проекта.\r\n\r\nВыпадаемая сумма:\r\n$1,500 - $3,000\r\n',20,NULL),(8,3,'Продвинутый пакет','Выпадаемая сумма:\r\n$5,000 - $15,000\r\n',150,NULL),(9,3,'Профессиональный пакет','Выпадаемая сумма:\r\n$18,000 - $35,000\r\n',300,NULL),(10,4,'Начальный VIP','\r\n\r\n\r\nПроверка заявлений и репортов в приоритете;\r\nДоступ к смене стилей боя;\r\nДоступ /vobject (для ситуаций);\r\nУвеличение зарплаты и пособий на 5%;\r\nВозможность иметь компании до 2;\r\nВозможность иметь сайты до 2.\r\n\r\n\r\n\r\nСрок действия: 30 дней с момента активации.',100,NULL),(11,4,'Стандартный VIP','Проверка заявлений и репортов в приоритете;\r\nДоступ к смене стилей боя;\r\nДоступ /vobject (для ситуаций);\r\nУвеличение зарплаты и пособий на 15%;\r\nВозможность иметь компании до 2;\r\nВозможность иметь сайты до 2;\r\nВозможность иметь домов до 3;\r\nВозможность иметь транспорт до 3;\r\nВозможность сменить имя.\r\n\r\nСрок действия: 30 дней с момента активации.',250,NULL),(12,4,'Продвинутый VIP','Проверка заявлений и репортов в приоритете;\r\nДоступ к смене стилей боя;\r\nДоступ /vobject (для ситуаций);\r\nУвеличение зарплаты и пособий на 25%;\r\nВозможность иметь компании до 2;\r\nВозможность иметь сайты до 3;\r\nВозможность иметь домов до 3;\r\nВозможность иметь транспорт до 3;\r\nВозможность сменить имя;\r\nВозможность сменить номер телефона.\r\n\r\nСрок действия: 30 дней с момента активации.',500,NULL),(13,4,'Профессиональный VIP','Проверка заявлений и репортов в приоритете;\r\nДоступ к смене стилей боя;\r\nДоступ /vobject (для ситуаций);\r\nУвеличение зарплаты и пособий на 40%;\r\nВозможность иметь компании до 2;\r\nВозможность иметь сайты до 3;\r\nВозможность иметь домов до 3;\r\nВозможность иметь транспорт до 4;\r\nВозможность сменить имя;\r\nВозможность сменить номер телефона;\r\nВозможность сменить номер авто.\r\n\r\nСрок действия: бессрочен с момента активации.',1500,NULL);
/*!40000 ALTER TABLE `donate_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `donate_stat`
--

DROP TABLE IF EXISTS `donate_stat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `donate_stat` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `donate_item_id` int(11) NOT NULL,
  `create_date` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `donate_stat`
--

LOCK TABLES `donate_stat` WRITE;
/*!40000 ALTER TABLE `donate_stat` DISABLE KEYS */;
INSERT INTO `donate_stat` VALUES (1,223,7,'2019-12-26 16:37:44'),(2,223,7,'2019-12-26 16:37:52'),(3,75,7,'2019-12-26 23:17:02'),(4,41,5,'2019-12-30 00:01:22'),(5,41,3,'2019-12-30 00:01:35'),(6,85,7,'2019-12-30 16:33:46'),(7,472,9,'2019-12-30 19:08:51'),(8,472,7,'2019-12-30 19:15:11'),(9,472,6,'2019-12-30 19:17:16'),(10,593,7,'2019-12-30 19:36:59'),(11,73,10,'2019-12-30 19:45:56'),(12,73,4,'2019-12-30 19:46:03'),(13,732,10,'2019-12-30 20:28:45'),(14,489,7,'2019-12-30 20:31:00'),(15,159,7,'2019-12-30 21:37:00'),(16,98,11,'2019-12-31 08:35:33'),(17,551,7,'2020-01-01 05:53:58');
/*!40000 ALTER TABLE `donate_stat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions`
--

DROP TABLE IF EXISTS `fractions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions` (
  `fr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fr_leader_id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Лидер',
  `fr_name` varchar(64) NOT NULL,
  `fr_alt_name` varchar(8) NOT NULL,
  `fr_color` varchar(16) NOT NULL,
  `fr_type_budget` enum('FRAC_BUDGET_GOV','FRAC_BUDGET_INDEPENDENT') NOT NULL,
  `fr_budget` decimal(5,3) unsigned NOT NULL DEFAULT '0.000',
  `fr_main` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_join_rank_id` int(11) unsigned NOT NULL DEFAULT '0',
  `fr_spawn_pos_x` float NOT NULL DEFAULT '0',
  `fr_spawn_pos_y` float NOT NULL DEFAULT '0',
  `fr_spawn_pos_z` float NOT NULL DEFAULT '0',
  `fr_spawn_pos_angle` float NOT NULL DEFAULT '0',
  `fr_spawn_int` int(11) NOT NULL DEFAULT '0',
  `fr_spawn_world` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`fr_id`),
  UNIQUE KEY `UNIQUE` (`fr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions`
--

LOCK TABLES `fractions` WRITE;
/*!40000 ALTER TABLE `fractions` DISABLE KEYS */;
INSERT INTO `fractions` VALUES (1,0,'Los Santos Government','LSG','a5c5ec00','FRAC_BUDGET_GOV',1.000,1,0,1961.47,1883.79,2519,356.983,6,150009),(2,0,'The Court of Los Santos','TCOLS','eca5a500','FRAC_BUDGET_GOV',1.010,1,0,0,0,0,0,0,0),(3,3,'Los Santos Police Department','LSPD','6D6CB800','FRAC_BUDGET_GOV',1.100,1,1,-343.627,2535.53,1504.45,90.1379,6,150000),(4,0,'Los Santos Fire Department','LSFD','d44c4c00','FRAC_BUDGET_GOV',0.900,1,0,670.623,21759.7,1504.07,271.153,6,150019),(5,3,'Los Santos County Sheriff\'s Department','LSCS','699C5800','FRAC_BUDGET_GOV',1.500,1,0,351.679,2326.81,1504.34,179.658,6,150004),(6,0,'San Andreas Network','SAN','6b83f700','FRAC_BUDGET_INDEPENDENT',1.600,1,0,-46.1076,-9.7343,3005.54,268.599,6,150006),(7,0,'Whetstone National Park','WNP','9c905800','FRAC_BUDGET_GOV',1.200,1,0,-15.0754,2031.34,1504.02,176.141,6,150007),(8,0,'All Saints General Hospital','ASGHP','3688ec00','FRAC_BUDGET_INDEPENDENT',2.000,1,0,0,0,0,0,0,0);
/*!40000 ALTER TABLE `fractions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions_attach`
--

DROP TABLE IF EXISTS `fractions_attach`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions_attach` (
  `fr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fr_fraction_id` int(11) unsigned DEFAULT NULL,
  `fr_name` varchar(32) NOT NULL,
  `fr_object_id` int(11) NOT NULL,
  PRIMARY KEY (`fr_id`),
  KEY `FK_object_fraction_id` (`fr_fraction_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions_attach`
--

LOCK TABLES `fractions_attach` WRITE;
/*!40000 ALTER TABLE `fractions_attach` DISABLE KEYS */;
INSERT INTO `fractions_attach` VALUES (2,4,'4432',33),(3,3,'test',1250),(4,3,'test',1250);
/*!40000 ALTER TABLE `fractions_attach` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions_item`
--

DROP TABLE IF EXISTS `fractions_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions_item` (
  `fr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fr_fraction_id` int(11) unsigned NOT NULL,
  `fr_item_id` int(11) unsigned NOT NULL,
  `fr_item_param_1` int(11) NOT NULL,
  `fr_item_param_2` int(11) NOT NULL,
  PRIMARY KEY (`fr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions_item`
--

LOCK TABLES `fractions_item` WRITE;
/*!40000 ALTER TABLE `fractions_item` DISABLE KEYS */;
INSERT INTO `fractions_item` VALUES (3,4,2,1,1),(4,4,16,555,0),(5,4,26,1,1),(14,1,10,60,0),(15,1,105,0,0),(17,7,8,60,0),(19,7,109,0,100),(20,7,104,0,0),(21,7,3,1,0),(22,5,10,60,0),(23,5,12,60,0),(24,5,17,120,0),(25,5,105,0,0),(26,5,109,0,100),(27,5,110,0,100),(28,3,8,100,-1);
/*!40000 ALTER TABLE `fractions_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions_object`
--

DROP TABLE IF EXISTS `fractions_object`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions_object` (
  `fo_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fo_fraction_id` int(11) unsigned DEFAULT NULL,
  `fo_name` varchar(32) NOT NULL,
  `fo_object_id` int(11) NOT NULL,
  PRIMARY KEY (`fo_id`),
  KEY `FK_object_fraction_id` (`fo_fraction_id`),
  CONSTRAINT `FK_object_fraction_id` FOREIGN KEY (`fo_fraction_id`) REFERENCES `fractions` (`fr_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions_object`
--

LOCK TABLES `fractions_object` WRITE;
/*!40000 ALTER TABLE `fractions_object` DISABLE KEYS */;
INSERT INTO `fractions_object` VALUES (1,1,'Тест',222),(2,1,'e',1566),(5,1,'test',334643),(7,3,'Test',1255);
/*!40000 ALTER TABLE `fractions_object` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions_rank`
--

DROP TABLE IF EXISTS `fractions_rank`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions_rank` (
  `fr_id` int(11) NOT NULL AUTO_INCREMENT,
  `fr_fraction_id` int(11) NOT NULL,
  `fr_name` varchar(32) NOT NULL,
  `fr_salary` int(11) unsigned NOT NULL DEFAULT '0',
  `fr_perm_invite` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_uninvite` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_set_rank` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_set_unit` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_manage` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_radio` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_object` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_attach` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_vehicle` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_clothes` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_communication` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_items` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_weapon` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_spawn_vehicle` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fr_perm_custom` varchar(255) NOT NULL DEFAULT '0|0|0|0|0|0|0|0|0|0',
  PRIMARY KEY (`fr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions_rank`
--

LOCK TABLES `fractions_rank` WRITE;
/*!40000 ALTER TABLE `fractions_rank` DISABLE KEYS */;
INSERT INTO `fractions_rank` VALUES (1,3,'Police Officer I',1980,0,1,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(3,3,'Test',440,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(4,3,'Test2',440,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(5,3,'Test',440,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(6,3,'Test2',440,0,0,1,0,0,1,0,0,1,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(7,3,'Test3',440,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0'),(8,3,'Test4',440,1,1,1,1,1,1,1,1,1,1,0,1,1,1,'0|0|0|0|0|0|0|0|0|0'),(9,5,'Test',600,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0|0|0|0|0|0|0|0|0|0');
/*!40000 ALTER TABLE `fractions_rank` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fractions_unit`
--

DROP TABLE IF EXISTS `fractions_unit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fractions_unit` (
  `fr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fr_fraction_id` int(11) unsigned NOT NULL,
  `fr_leader_id` int(11) unsigned NOT NULL DEFAULT '0',
  `fr_name` varchar(64) NOT NULL,
  `fr_alt_name` varchar(16) NOT NULL,
  `fr_skins` varchar(255) NOT NULL DEFAULT '0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0',
  `fr_pos_x` float DEFAULT '0',
  `fr_pos_y` float DEFAULT '0',
  `fr_pos_z` float DEFAULT '0',
  `fr_pos_angle` float DEFAULT '0',
  `fr_int` int(11) unsigned NOT NULL DEFAULT '0',
  `fr_world` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`fr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fractions_unit`
--

LOCK TABLES `fractions_unit` WRITE;
/*!40000 ALTER TABLE `fractions_unit` DISABLE KEYS */;
INSERT INTO `fractions_unit` VALUES (1,3,0,'Test','TST','30|40|311|76|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0',1066.39,1922,1504.28,NULL,6,150001),(2,5,0,'Ganton','GNT','0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0',0,0,0,NULL,0,0),(4,5,0,'test','TST','0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0',0,0,0,NULL,0,0);
/*!40000 ALTER TABLE `fractions_unit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fuber_trips`
--

DROP TABLE IF EXISTS `fuber_trips`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fuber_trips` (
  `fub_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `fub_driver_character_id` int(11) unsigned NOT NULL,
  `fub_passenger_character_id` int(11) unsigned NOT NULL,
  `fub_start_pos_x` float NOT NULL,
  `fub_start_pos_y` float NOT NULL,
  `fub_start_pos_z` float NOT NULL,
  `fub_end_pos_x` float NOT NULL,
  `fub_end_pos_y` float NOT NULL,
  `fub_end_pos_z` float NOT NULL,
  `fub_driver_reputation` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fub_passenger_reputation` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `fub_cost` int(11) NOT NULL,
  `fub_create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`fub_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fuber_trips`
--

LOCK TABLES `fuber_trips` WRITE;
/*!40000 ALTER TABLE `fuber_trips` DISABLE KEYS */;
INSERT INTO `fuber_trips` VALUES (1,339,13,1027.5,-1559.61,13.5439,1926.5,-1195.61,22,0,0,24,'2019-12-30 12:11:59'),(2,291,267,1487.86,-1159.7,23.9062,1445.86,-1411.7,22,0,0,10,'2019-12-30 12:12:02'),(3,379,434,1099.58,-1412.65,13.6288,556.583,-1338.57,22,0,0,10,'2019-12-30 21:45:42');
/*!40000 ALTER TABLE `fuber_trips` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `furnitures`
--

DROP TABLE IF EXISTS `furnitures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `furnitures` (
  `f_id` int(11) NOT NULL AUTO_INCREMENT,
  `f_owner_type` tinyint(2) NOT NULL,
  `f_owner_id` int(11) NOT NULL,
  `f_item_id` int(11) NOT NULL DEFAULT '0',
  `f_pos_x` float NOT NULL DEFAULT '0',
  `f_pos_y` float NOT NULL DEFAULT '0',
  `f_pos_z` float NOT NULL DEFAULT '0',
  `f_rot_x` float NOT NULL DEFAULT '0',
  `f_rot_y` float NOT NULL DEFAULT '0',
  `f_rot_z` float NOT NULL DEFAULT '0',
  `f_texture_type` int(5) NOT NULL DEFAULT '0',
  `f_texture_index` int(5) NOT NULL DEFAULT '0',
  `f_state` tinyint(1) NOT NULL DEFAULT '0',
  `f_created_time` int(11) NOT NULL,
  PRIMARY KEY (`f_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `furnitures`
--

LOCK TABLES `furnitures` WRITE;
/*!40000 ALTER TABLE `furnitures` DISABLE KEYS */;
INSERT INTO `furnitures` VALUES (1,1,26,4001,-2715.4,-1511.18,2602.05,0,0,0,0,0,1,0);
/*!40000 ALTER TABLE `furnitures` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hostels`
--

DROP TABLE IF EXISTS `hostels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hostels` (
  `hos_id` int(11) NOT NULL AUTO_INCREMENT,
  `hos_int_type` tinyint(2) NOT NULL DEFAULT '0',
  `hos_pos_x` float NOT NULL,
  `hos_pos_y` float NOT NULL,
  `hos_pos_z` float NOT NULL,
  `hos_pos_angle` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`hos_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hostels`
--

LOCK TABLES `hostels` WRITE;
/*!40000 ALTER TABLE `hostels` DISABLE KEYS */;
INSERT INTO `hostels` VALUES (1,1,887.743,-1772.79,13.3828,359.322),(2,3,877.337,-1770.27,13.3828,81.055),(3,3,864.976,-1774.54,13.3828,107.68);
/*!40000 ALTER TABLE `hostels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `houses`
--

DROP TABLE IF EXISTS `houses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `houses` (
  `h_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `h_character_id` int(11) NOT NULL DEFAULT '0',
  `h_buy_type` tinyint(2) NOT NULL,
  `h_pos_x` float NOT NULL,
  `h_pos_y` float NOT NULL,
  `h_pos_z` float NOT NULL,
  `h_pos_angle` float NOT NULL,
  `h_world` int(11) NOT NULL DEFAULT '0',
  `h_interior` smallint(2) NOT NULL DEFAULT '0',
  `h_price` int(11) NOT NULL,
  `h_int_type` tinyint(2) NOT NULL,
  `h_lock` tinyint(1) NOT NULL DEFAULT '0',
  `h_money` int(11) NOT NULL DEFAULT '0',
  `h_debt` int(11) NOT NULL DEFAULT '0',
  `h_debt_count` tinyint(1) NOT NULL DEFAULT '0',
  `h_time` int(11) NOT NULL DEFAULT '0',
  `h_buy_time` int(11) NOT NULL DEFAULT '0',
  `h_is_credit` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`h_id`),
  UNIQUE KEY `UNIQUE` (`h_id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `houses`
--

LOCK TABLES `houses` WRITE;
/*!40000 ALTER TABLE `houses` DISABLE KEYS */;
INSERT INTO `houses` VALUES (1,0,0,2873.72,2898.82,2001.48,88.8891,100001,3,105,1,0,0,0,0,0,0,0),(2,0,0,2867.71,2898.78,2001.48,270.914,100001,3,108,1,0,0,0,0,0,0,0),(3,0,0,2867.71,2909.6,2001.48,269.371,100001,3,103,1,0,0,0,0,0,0,0),(4,0,0,2872.1,2914.36,2001.48,182.913,100001,3,104,1,0,0,0,0,0,0,0),(5,0,0,2873.6,2911.49,2001.48,88.936,100001,3,110,1,0,0,0,0,0,0,0),(6,0,0,2872.46,2890.64,2004.98,359.345,100001,3,101,1,0,0,0,0,0,0,0),(7,0,0,2867.71,2893.19,2004.98,269.418,100001,3,102,1,0,0,0,0,0,0,0),(8,0,0,2867.7,2901.29,2004.98,272.238,100001,3,104,1,0,0,0,0,0,0,0),(9,0,0,2873.56,2897.81,2004.98,92.4063,100001,3,109,1,0,0,0,0,0,0,0),(10,0,0,2867.67,2910.1,2004.98,271.635,100001,3,103,1,0,0,0,0,0,0,0),(11,0,0,2873.05,2912.42,2004.98,92.0929,100001,3,109,1,0,0,0,0,0,0,0),(12,0,0,1.6553,2716.74,2273.8,181.057,100002,3,104,1,0,0,0,0,0,0,0),(13,0,0,-0.820299,2714.23,2273.8,269.899,100002,3,108,1,1,0,0,0,0,0,0),(14,0,0,-0.712199,2704.44,2273.8,270.671,100002,3,108,1,0,0,0,0,0,0,0),(15,0,0,1.8319,2701.69,2273.8,357.32,100002,3,104,1,0,0,0,0,0,0,0),(16,0,0,4.5798,2706.93,2273.8,88.3323,100002,3,107,1,0,0,0,0,0,0,0),(17,0,0,15.6461,2709.37,2277.29,91.0073,100002,3,103,1,0,0,0,0,0,0,0),(18,0,0,15.5137,2703.83,2277.29,90.8623,100002,3,109,1,0,0,0,0,0,0,0),(19,0,0,12.9128,2701.79,2277.29,359.513,100002,3,106,1,0,0,0,0,0,0,0),(20,0,0,1.6553,2716.74,2273.8,181.057,100003,3,110,1,0,0,0,0,0,0,0),(21,0,0,-0.820299,2714.23,2273.8,269.899,100003,3,102,1,0,0,0,0,0,0,0),(22,0,0,-0.712199,2704.44,2273.8,270.671,100003,3,107,1,0,0,0,0,0,0,0),(23,0,0,1.8319,2701.69,2273.8,357.32,100003,3,107,1,0,0,0,0,0,0,0),(24,0,0,4.5798,2706.93,2273.8,88.3323,100003,3,108,1,0,0,0,0,0,0,0),(25,0,0,15.6461,2709.37,2277.29,91.0073,100003,3,107,1,0,0,0,0,0,0,0),(26,0,0,15.5137,2703.83,2277.29,90.8623,100003,3,110,1,0,0,0,0,0,0,0),(27,0,0,12.9128,2701.79,2277.29,359.513,100003,3,103,1,0,0,0,0,0,0,0),(28,0,0,2413.58,-1930.58,13.3828,331.55,0,0,1,1,0,0,0,0,0,0,0);
/*!40000 ALTER TABLE `houses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `houses_garage`
--

DROP TABLE IF EXISTS `houses_garage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `houses_garage` (
  `g_house_id` int(11) unsigned NOT NULL,
  `g_type` tinyint(1) NOT NULL DEFAULT '0',
  `g_pos_x` float NOT NULL DEFAULT '0',
  `g_pos_y` float NOT NULL DEFAULT '0',
  `g_pos_z` float NOT NULL DEFAULT '0',
  `g_pos_angle` float NOT NULL DEFAULT '0',
  `g_veh_pos_x` float NOT NULL DEFAULT '0',
  `g_veh_pos_y` float NOT NULL DEFAULT '0',
  `g_veh_pos_z` float NOT NULL DEFAULT '0',
  `g_veh_pos_angle` float NOT NULL DEFAULT '0',
  `g_addveh_pos_x` float NOT NULL DEFAULT '0',
  `g_addveh_pos_y` float NOT NULL DEFAULT '0',
  `g_addveh_pos_z` float NOT NULL DEFAULT '0',
  `g_addveh_pos_angle` float NOT NULL DEFAULT '0',
  `g_lock` tinyint(1) NOT NULL DEFAULT '0',
  `g_set_furn` tinyint(1) NOT NULL DEFAULT '0',
  KEY `FK_garage_house_id` (`g_house_id`),
  CONSTRAINT `FK_garage_house_id` FOREIGN KEY (`g_house_id`) REFERENCES `houses` (`h_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `houses_garage`
--

LOCK TABLES `houses_garage` WRITE;
/*!40000 ALTER TABLE `houses_garage` DISABLE KEYS */;
INSERT INTO `houses_garage` VALUES (28,1,2420.71,-1920.86,13.5469,309.062,2419.74,-1919.5,13.161,269.365,0,0,0,0,0,0);
/*!40000 ALTER TABLE `houses_garage` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `houses_lodger`
--

DROP TABLE IF EXISTS `houses_lodger`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `houses_lodger` (
  `lod_house_id` int(11) unsigned NOT NULL,
  `lod_character_id` int(11) NOT NULL,
  `lod_perm_safe` tinyint(1) NOT NULL DEFAULT '0',
  `lod_perm_renovation` tinyint(1) NOT NULL DEFAULT '0',
  `lod_perm_inventory` tinyint(1) NOT NULL DEFAULT '0',
  `lod_perm_garage` tinyint(1) NOT NULL DEFAULT '0',
  KEY `FK_lodger_house_id` (`lod_house_id`),
  CONSTRAINT `FK_lodger_house_id` FOREIGN KEY (`lod_house_id`) REFERENCES `houses` (`h_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `houses_lodger`
--

LOCK TABLES `houses_lodger` WRITE;
/*!40000 ALTER TABLE `houses_lodger` DISABLE KEYS */;
/*!40000 ALTER TABLE `houses_lodger` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ipbans`
--

DROP TABLE IF EXISTS `ipbans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ipbans` (
  `ib_user_ip` varchar(17) NOT NULL,
  `ib_admin_id` int(11) NOT NULL DEFAULT '-1',
  `ib_admin_name` varchar(24) NOT NULL DEFAULT 'SERVER',
  `ib_reason` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ipbans`
--

LOCK TABLES `ipbans` WRITE;
/*!40000 ALTER TABLE `ipbans` DISABLE KEYS */;
/*!40000 ALTER TABLE `ipbans` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `items`
--

DROP TABLE IF EXISTS `items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `items` (
  `inv_id` int(11) NOT NULL AUTO_INCREMENT,
  `inv_owner_type` int(11) NOT NULL DEFAULT '0',
  `inv_owner_id` int(11) NOT NULL DEFAULT '0',
  `inv_item_id` int(11) NOT NULL DEFAULT '0',
  `inv_index` int(2) NOT NULL DEFAULT '-1',
  `inv_use_slot` tinyint(1) NOT NULL DEFAULT '0',
  `inv_param_1` int(11) NOT NULL DEFAULT '0',
  `inv_param_2` int(11) NOT NULL DEFAULT '0',
  `inv_pos_x` float NOT NULL DEFAULT '0',
  `inv_pos_y` float NOT NULL DEFAULT '0',
  `inv_pos_z` float NOT NULL DEFAULT '0',
  `inv_rot_x` float NOT NULL DEFAULT '0',
  `inv_rot_y` float NOT NULL DEFAULT '0',
  `inv_rot_z` float NOT NULL DEFAULT '0',
  `inv_scale_x` float NOT NULL DEFAULT '0',
  `inv_scale_y` float NOT NULL DEFAULT '0',
  `inv_scale_z` float NOT NULL DEFAULT '0',
  `inv_bone` tinyint(1) NOT NULL DEFAULT '0',
  `inv_create_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `inv_update_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`inv_id`)
) ENGINE=InnoDB AUTO_INCREMENT=129 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `items`
--

LOCK TABLES `items` WRITE;
/*!40000 ALTER TABLE `items` DISABLE KEYS */;
INSERT INTO `items` VALUES (4,0,3,105,8,1,911,2,0,0,0,0,0,0,0,0,0,0,'2020-01-04 18:37:07','2020-01-19 04:00:54'),(108,0,3,26,1,1,1,0,0,0,0,0,0,0,0,0,0,0,'2020-01-06 16:09:52','2020-01-06 16:09:54'),(116,0,3,1,0,0,302,0,0,0,0,0,0,0,0,0,0,0,'2020-01-19 03:39:24','2020-01-19 03:39:24'),(117,0,3,113,5,0,1,0,0,0,0,0,0,0,1,1,1,5,'2020-01-19 17:05:45','2021-02-06 21:16:52'),(118,4,79,46,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'2020-01-20 05:29:56','2020-01-22 04:49:46'),(124,4,79,10,2,0,100,0,0,0,0,0,0,0,0,0,0,0,'2020-01-20 07:09:00','2020-01-22 04:49:39'),(126,0,3,69,4,0,18950,0,0,0,0,0,0,0,0,0,0,0,'2020-01-20 08:31:08','2021-02-06 21:16:52'),(127,0,3,69,7,0,18950,0,0,0,0,0,0,0,0,0,0,0,'2020-01-20 08:31:13','2021-02-06 21:16:52'),(128,0,3,8,6,0,100,-1,0,0,0,0,0,0,0,0,0,0,'2020-01-22 04:43:39','2021-02-06 21:16:52');
/*!40000 ALTER TABLE `items` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `licenses`
--

DROP TABLE IF EXISTS `licenses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `licenses` (
  `l_id` int(11) NOT NULL AUTO_INCREMENT,
  `l_character_id` int(11) unsigned NOT NULL,
  `l_type` enum('DRIVE','BOAT','FLY','WEAPON') NOT NULL,
  `l_gave_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `l_gave_name` varchar(24) NOT NULL DEFAULT '',
  `l_take_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `l_take_name` varchar(24) NOT NULL DEFAULT '',
  PRIMARY KEY (`l_id`,`l_character_id`),
  KEY `FK_license_character_id` (`l_character_id`),
  CONSTRAINT `FK_license_character_id` FOREIGN KEY (`l_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `licenses`
--

LOCK TABLES `licenses` WRITE;
/*!40000 ALTER TABLE `licenses` DISABLE KEYS */;
INSERT INTO `licenses` VALUES (1,3,'DRIVE','2019-07-12 10:45:24','Centre Of Licenses','1970-01-01 00:00:00','');
/*!40000 ALTER TABLE `licenses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `logs`
--

DROP TABLE IF EXISTS `logs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `logs` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `type` enum('LOG_MONEY','LOG_CARD') DEFAULT NULL,
  `format` varchar(255) NOT NULL,
  `arguments` varchar(512) NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `logs`
--

LOCK TABLES `logs` WRITE;
/*!40000 ALTER TABLE `logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `logs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `music`
--

DROP TABLE IF EXISTS `music`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `music` (
  `m_character_id` int(11) unsigned NOT NULL,
  `m_name` varchar(64) NOT NULL,
  `m_url` varchar(128) NOT NULL,
  `m_created_time` int(11) NOT NULL,
  KEY `FK_music_character_id` (`m_character_id`),
  CONSTRAINT `FK_music_character_id` FOREIGN KEY (`m_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `music`
--

LOCK TABLES `music` WRITE;
/*!40000 ALTER TABLE `music` DISABLE KEYS */;
/*!40000 ALTER TABLE `music` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phones`
--

DROP TABLE IF EXISTS `phones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phones` (
  `ph_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ph_col_panel` tinyint(1) NOT NULL,
  `ph_music` tinyint(1) NOT NULL DEFAULT '1',
  `ph_status` tinyint(1) NOT NULL DEFAULT '1',
  `ph_number` int(7) NOT NULL DEFAULT '0',
  `ph_created_time` int(11) NOT NULL,
  `ph_paid_time` int(11) NOT NULL,
  `ph_anogram_name` varchar(32) NOT NULL DEFAULT '',
  `ph_radio` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ph_id`),
  UNIQUE KEY `UNIQUE` (`ph_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phones`
--

LOCK TABLES `phones` WRITE;
/*!40000 ALTER TABLE `phones` DISABLE KEYS */;
INSERT INTO `phones` VALUES (1,0,1,1,302800,1578316190,0,'',0);
/*!40000 ALTER TABLE `phones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phones_anogram`
--

DROP TABLE IF EXISTS `phones_anogram`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phones_anogram` (
  `ph_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ph_phone_id` int(11) unsigned NOT NULL,
  `ph_from_phone_id` int(11) unsigned NOT NULL,
  `ph_to_phone_id` int(11) unsigned NOT NULL,
  `ph_text` varchar(128) NOT NULL,
  `ph_date` datetime NOT NULL,
  PRIMARY KEY (`ph_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phones_anogram`
--

LOCK TABLES `phones_anogram` WRITE;
/*!40000 ALTER TABLE `phones_anogram` DISABLE KEYS */;
/*!40000 ALTER TABLE `phones_anogram` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phones_contact`
--

DROP TABLE IF EXISTS `phones_contact`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phones_contact` (
  `pc_phone_id` int(11) unsigned NOT NULL,
  `pc_number` int(11) NOT NULL,
  `pc_name` varchar(64) NOT NULL,
  `pc_created_time` int(11) NOT NULL,
  KEY `FK_phone_id` (`pc_phone_id`),
  CONSTRAINT `FK_phone_id` FOREIGN KEY (`pc_phone_id`) REFERENCES `phones` (`ph_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phones_contact`
--

LOCK TABLES `phones_contact` WRITE;
/*!40000 ALTER TABLE `phones_contact` DISABLE KEYS */;
/*!40000 ALTER TABLE `phones_contact` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phones_conversation`
--

DROP TABLE IF EXISTS `phones_conversation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phones_conversation` (
  `pc_id` int(11) NOT NULL AUTO_INCREMENT,
  `pc_from_number` int(7) NOT NULL,
  `pc_to_number` int(7) NOT NULL,
  `pc_created_time` int(11) NOT NULL,
  `pc_updated_time` int(11) NOT NULL,
  PRIMARY KEY (`pc_id`),
  UNIQUE KEY `pc_from_number` (`pc_from_number`,`pc_to_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phones_conversation`
--

LOCK TABLES `phones_conversation` WRITE;
/*!40000 ALTER TABLE `phones_conversation` DISABLE KEYS */;
/*!40000 ALTER TABLE `phones_conversation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phones_message`
--

DROP TABLE IF EXISTS `phones_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phones_message` (
  `pm_id` int(11) NOT NULL AUTO_INCREMENT,
  `pm_from_number` int(7) NOT NULL,
  `pm_to_number` int(7) NOT NULL,
  `pm_text` varchar(120) NOT NULL,
  `pm_created_time` int(11) NOT NULL,
  `pm_type` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`pm_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phones_message`
--

LOCK TABLES `phones_message` WRITE;
/*!40000 ALTER TABLE `phones_message` DISABLE KEYS */;
/*!40000 ALTER TABLE `phones_message` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `premises`
--

DROP TABLE IF EXISTS `premises`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `premises` (
  `pr_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `pr_character_id` int(11) NOT NULL,
  `pr_buy_type` tinyint(1) NOT NULL,
  `pr_name` varchar(32) NOT NULL,
  `pr_pos_x` float NOT NULL,
  `pr_pos_y` float NOT NULL,
  `pr_pos_z` float NOT NULL,
  `pr_pos_angle` float NOT NULL,
  `pr_price` int(11) NOT NULL,
  `pr_int_type` int(2) NOT NULL,
  `pr_world` int(11) NOT NULL,
  `pr_interior` int(11) NOT NULL,
  `pr_lock` tinyint(1) NOT NULL,
  `pr_debt` int(11) NOT NULL,
  `pr_debt_count` tinyint(1) NOT NULL DEFAULT '0',
  `pr_time` int(11) NOT NULL,
  `pr_buy_time` int(11) NOT NULL DEFAULT '0',
  `pr_business_id` int(11) NOT NULL DEFAULT '0',
  `pr_cash_pos_x` float NOT NULL DEFAULT '0',
  `pr_cash_pos_y` float NOT NULL DEFAULT '0',
  `pr_cash_pos_z` float NOT NULL DEFAULT '0',
  `pr_profit` int(11) NOT NULL DEFAULT '0',
  `pr_entrance` int(11) NOT NULL DEFAULT '0',
  `pr_assort_stock` int(11) NOT NULL DEFAULT '0',
  `pr_is_credit` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`pr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `premises`
--

LOCK TABLES `premises` WRITE;
/*!40000 ALTER TABLE `premises` DISABLE KEYS */;
INSERT INTO `premises` VALUES (1,3,2,'',1734.97,-1725.02,13.5469,146.061,1,1,0,0,0,0,55,1579093168,1579006768,1,1713.76,1147.52,2468.5,0,0,966,0);
/*!40000 ALTER TABLE `premises` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rooms`
--

DROP TABLE IF EXISTS `rooms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rooms` (
  `r_id` int(11) NOT NULL AUTO_INCREMENT,
  `r_owner_type` tinyint(1) NOT NULL,
  `r_owner_id` int(11) NOT NULL,
  `r_number` tinyint(2) NOT NULL,
  `r_roof` int(11) NOT NULL,
  `r_floor` int(11) NOT NULL,
  `r_wall` int(11) NOT NULL,
  PRIMARY KEY (`r_id`)
) ENGINE=InnoDB AUTO_INCREMENT=59 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rooms`
--

LOCK TABLES `rooms` WRITE;
/*!40000 ALTER TABLE `rooms` DISABLE KEYS */;
INSERT INTO `rooms` VALUES (1,1,1,0,0,0,0),(2,1,1,1,0,0,0),(3,1,2,0,0,0,0),(4,1,2,1,0,0,0),(5,1,3,0,0,0,0),(6,1,3,1,0,0,0),(7,1,4,0,0,0,0),(8,1,4,1,0,0,0),(9,1,5,0,0,0,0),(10,1,5,1,0,0,0),(11,1,6,0,0,0,0),(12,1,6,1,0,0,0),(13,1,7,0,0,0,0),(14,1,7,1,0,0,0),(15,1,8,0,0,0,0),(16,1,8,1,0,0,0),(17,1,9,0,0,0,0),(18,1,9,1,0,0,0),(19,1,10,0,0,0,0),(20,1,10,1,0,0,0),(21,1,11,0,0,0,0),(22,1,11,1,0,0,0),(23,1,12,0,0,0,0),(24,1,12,1,0,0,0),(25,1,13,0,0,0,0),(26,1,13,1,0,0,0),(27,1,14,0,0,0,0),(28,1,14,1,0,0,0),(29,1,15,0,0,0,0),(30,1,15,1,0,0,0),(31,1,16,0,0,0,0),(32,1,16,1,0,0,0),(33,1,17,0,0,0,0),(34,1,17,1,0,0,0),(35,1,18,0,0,0,0),(36,1,18,1,0,0,0),(37,1,19,0,0,0,0),(38,1,19,1,0,0,0),(39,1,20,0,0,0,0),(40,1,20,1,0,0,0),(41,1,21,0,0,0,0),(42,1,21,1,0,0,0),(43,1,22,0,0,0,0),(44,1,22,1,0,0,0),(45,1,23,0,0,0,0),(46,1,23,1,0,0,0),(47,1,24,0,0,0,0),(48,1,24,1,0,0,0),(49,1,25,0,0,0,0),(50,1,25,1,0,0,0),(51,1,26,0,0,0,0),(52,1,26,1,0,0,0),(53,1,27,0,0,0,0),(54,1,27,1,0,0,0),(55,3,1,0,0,0,0),(56,3,1,1,0,0,0),(57,1,28,0,0,0,0),(58,1,28,1,0,0,0);
/*!40000 ALTER TABLE `rooms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sessions` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL,
  `character_id` int(11) unsigned DEFAULT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  `ip` varchar(17) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_session_user_id` (`user_id`),
  KEY `FK_session_character_id` (`character_id`),
  CONSTRAINT `FK_session_character_id` FOREIGN KEY (`character_id`) REFERENCES `characters` (`c_id`) ON DELETE SET NULL ON UPDATE SET NULL,
  CONSTRAINT `FK_session_user_id` FOREIGN KEY (`user_id`) REFERENCES `users` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sessions`
--

LOCK TABLES `sessions` WRITE;
/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
INSERT INTO `sessions` VALUES (3,1,3,'2019-08-07 20:28:56','2019-08-07 00:28:58','127.0.0.1');
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sites`
--

DROP TABLE IF EXISTS `sites`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sites` (
  `s_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `s_character_id` int(11) unsigned NOT NULL,
  `s_address` varchar(32) NOT NULL,
  `s_template` smallint(6) NOT NULL DEFAULT '0',
  `s_color` smallint(2) NOT NULL DEFAULT '0',
  `s_name` varchar(32) NOT NULL,
  `s_slogan` varchar(64) NOT NULL,
  `s_description` varchar(128) NOT NULL,
  `s_name_page_1` varchar(16) NOT NULL,
  `s_name_page_2` varchar(16) NOT NULL,
  `s_name_page_3` varchar(16) NOT NULL,
  `s_name_page_4` varchar(16) NOT NULL,
  `s_desc_page_1` varchar(512) NOT NULL,
  `s_desc_page_2` varchar(512) NOT NULL,
  `s_desc_page_3` varchar(512) NOT NULL,
  `s_desc_page_4` varchar(512) NOT NULL,
  `s_is_darknet` tinyint(1) NOT NULL,
  `s_rent_time` int(11) NOT NULL,
  `s_created_time` int(11) NOT NULL,
  PRIMARY KEY (`s_id`),
  KEY `FK_site_character_id` (`s_character_id`),
  CONSTRAINT `FK_site_character_id` FOREIGN KEY (`s_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sites`
--

LOCK TABLES `sites` WRITE;
/*!40000 ALTER TABLE `sites` DISABLE KEYS */;
/*!40000 ALTER TABLE `sites` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sites_favorite`
--

DROP TABLE IF EXISTS `sites_favorite`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sites_favorite` (
  `sf_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `sf_character_id` int(11) unsigned NOT NULL,
  `sf_address` varchar(64) NOT NULL,
  `sf_name` varchar(32) NOT NULL,
  `sf_created_time` int(11) NOT NULL,
  PRIMARY KEY (`sf_id`),
  KEY `FK_sf_character_id` (`sf_character_id`),
  CONSTRAINT `FK_sf_character_id` FOREIGN KEY (`sf_character_id`) REFERENCES `characters` (`c_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sites_favorite`
--

LOCK TABLES `sites_favorite` WRITE;
/*!40000 ALTER TABLE `sites_favorite` DISABLE KEYS */;
/*!40000 ALTER TABLE `sites_favorite` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `u_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `u_name` varchar(24) NOT NULL,
  `u_password` varchar(255) NOT NULL,
  `u_email` varchar(32) NOT NULL,
  `u_email_confirm` int(1) NOT NULL DEFAULT '0',
  `u_status` enum('ACTIVE','RETEST','DISABLED') NOT NULL DEFAULT 'ACTIVE',
  `u_mute` int(4) unsigned NOT NULL DEFAULT '0',
  `u_warn` int(1) unsigned NOT NULL DEFAULT '0',
  `u_warn_all` int(2) unsigned NOT NULL DEFAULT '0',
  `u_register_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `u_last_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `u_reg_ip` varchar(32) NOT NULL,
  `u_last_ip` varchar(32) NOT NULL DEFAULT '',
  `u_cash_action` int(11) NOT NULL DEFAULT '0',
  `u_helper` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `u_online` int(1) unsigned NOT NULL DEFAULT '0',
  `u_web_last_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `u_web_activity_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  `u_web_last_ip` varchar(32) NOT NULL DEFAULT '',
  `u_donate` float unsigned NOT NULL DEFAULT '0',
  `u_vip` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `u_vip_date` datetime NOT NULL DEFAULT '1970-01-01 00:00:00',
  PRIMARY KEY (`u_id`,`u_last_ip`),
  UNIQUE KEY `UNIQUE_email` (`u_email`),
  UNIQUE KEY `UNIQUE_name` (`u_name`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'evgsavosin','423b18e52aada23f4d34ed270ff03d6bb77b72bc2d902587dff6b06288a2f71222da9dcaddc17b18426dcf236bd1f008','evg.savosin@gmail.com',1,'ACTIVE',0,0,0,'2019-07-08 10:43:40','2021-02-06 21:16:52','\'\'','127.0.0.1',0,1,1,'2020-02-06 00:25:11','2020-02-11 02:41:10','127.0.0.1',2,0,'1970-01-01 00:00:00'),(2,'Guru','423b18e52aada23f4d34ed270ff03d6bb77b72bc2d902587dff6b06288a2f71222da9dcaddc17b18426dcf236bd1f008','bolonessi@yandex.ru',1,'ACTIVE',0,0,0,'2019-11-23 01:08:48','2020-02-10 00:51:02','','127.0.0.1',0,0,0,'2019-12-28 22:51:04','2020-01-01 18:29:46','176.110.250.236',100,0,'1970-01-01 00:00:00'),(3,'test_2','423b18e52aada23f4d34ed270ff03d6bb77b72bc2d902587dff6b06288a2f71222da9dcaddc17b18426dcf236bd1f008','flavogrp@gmail.com',1,'ACTIVE',0,0,0,'2019-11-23 01:22:00','2019-11-23 01:21:41','','',0,0,0,'2019-12-17 21:32:29','2019-12-31 19:06:00','176.109.247.236',0,0,'1970-01-01 00:00:00'),(4,'test_3','423b18e52aada23f4d34ed270ff03d6bb77b72bc2d902587dff6b06288a2f71222da9dcaddc17b18426dcf236bd1f008','bygaga159159@gmail.com',1,'ACTIVE',0,0,0,'2019-11-23 01:22:03','2019-12-30 21:27:44','','5.3.231.121',0,0,0,'2019-12-26 20:38:01','2019-12-30 23:08:39','5.3.231.121',0,0,'1970-01-01 00:00:00');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users_settings`
--

DROP TABLE IF EXISTS `users_settings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users_settings` (
  `set_user_id` int(11) unsigned NOT NULL,
  `set_inventory` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `set_visible_object` int(3) unsigned NOT NULL DEFAULT '600',
  `set_visible_pickup` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `set_admin_message` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `set_pm_message` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `set_b_message` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `set_design` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `set_google_auth` varchar(255) NOT NULL DEFAULT '',
  `set_logo` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `set_visible_names` tinyint(1) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`set_user_id`),
  CONSTRAINT `FK_user_id` FOREIGN KEY (`set_user_id`) REFERENCES `users` (`u_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users_settings`
--

LOCK TABLES `users_settings` WRITE;
/*!40000 ALTER TABLE `users_settings` DISABLE KEYS */;
INSERT INTO `users_settings` VALUES (1,0,600,1,1,1,1,1,'',1,1),(2,0,600,1,1,1,1,1,'',1,1),(3,0,600,1,1,1,1,1,'',1,1),(4,0,600,1,1,1,1,1,'',1,1);
/*!40000 ALTER TABLE `users_settings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicles`
--

DROP TABLE IF EXISTS `vehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicles` (
  `v_id` int(11) NOT NULL AUTO_INCREMENT,
  `v_buy_type` tinyint(4) NOT NULL DEFAULT '1',
  `v_owner_id` int(11) NOT NULL DEFAULT '-1',
  `v_owner_type` tinyint(1) NOT NULL DEFAULT '0',
  `v_spawned` tinyint(1) NOT NULL DEFAULT '0',
  `v_model` int(3) NOT NULL DEFAULT '401',
  `v_color` varchar(32) NOT NULL DEFAULT '0|0',
  `v_int` int(2) NOT NULL DEFAULT '0',
  `v_world` int(11) NOT NULL DEFAULT '0',
  `v_pos_x` float NOT NULL,
  `v_pos_y` float NOT NULL,
  `v_pos_z` float NOT NULL,
  `v_pos_angle` float NOT NULL,
  `v_mileage` float NOT NULL DEFAULT '0',
  `v_health` float NOT NULL DEFAULT '1000',
  `v_fuel` float NOT NULL DEFAULT '100',
  `v_state` float NOT NULL DEFAULT '100',
  `v_lock` int(1) NOT NULL DEFAULT '0',
  `v_number` varchar(32) NOT NULL DEFAULT '',
  `v_last_time` int(11) NOT NULL DEFAULT '0',
  `v_rent_time` int(11) NOT NULL DEFAULT '0',
  `v_buy_time` int(11) NOT NULL DEFAULT '0',
  `v_is_credit` tinyint(1) NOT NULL DEFAULT '0',
  `v_radio` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `v_siren` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `v_desc` varchar(144) NOT NULL DEFAULT '',
  PRIMARY KEY (`v_id`)
) ENGINE=MyISAM AUTO_INCREMENT=90 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicles`
--

LOCK TABLES `vehicles` WRITE;
/*!40000 ALTER TABLE `vehicles` DISABLE KEYS */;
INSERT INTO `vehicles` VALUES (77,2,3,2,1,430,'1|0',0,0,1927.37,235.616,2785.93,327.452,0,1000,800,100,0,'TEST',0,0,1578301673,0,0,0,''),(78,2,3,2,0,420,'0|0',0,0,1927.37,235.616,2785.93,327.452,0,1000,18,100,0,'TEST-ABC',0,0,1578301715,0,0,0,''),(79,2,3,2,0,420,'0|0',0,0,1532.09,-1681.96,13.1618,164.774,0.001843,1000,17.9998,100,0,'ABC-TEST',0,0,1578303093,0,0,1,''),(80,2,5,2,0,420,'0|0',0,0,303.817,-178.876,1.57811,106.721,0,1000,18,100,0,'ABC-TEST',0,0,1578316791,0,0,0,''),(81,2,3,2,0,420,'0|0',6,150000,1916.58,235.735,2785.93,202.421,0,1000,18,100,0,'ABC-TEST',0,0,1578345950,0,0,0,''),(82,2,3,1,0,400,'1|1',4,28,-1573.74,-1774.43,2501.06,0.494558,0.008414,1000,24.9993,100,1,'',0,0,1578947477,0,0,0,''),(83,2,3,1,0,402,'1|1',0,0,1107.7,-869.309,43.0176,1.058,0,1000,19,100,0,'',0,0,1578947558,0,0,0,''),(84,2,3,2,0,411,'0|0',0,0,1537.08,-1686.39,13.5469,220.561,0,1000,19,100,0,'ABC-T',0,0,1579659204,0,0,1,''),(85,2,3,2,0,411,'0|0',0,0,1539.07,-1685.25,13.5469,165.048,0.00019,994.083,19,100,0,'TEST-11',0,0,1579659350,0,0,1,''),(86,2,3,2,0,560,'0|0',0,0,1534.77,-1693.15,13.5469,163.977,0,1000,20,100,0,'AB-T',0,0,1579661040,0,0,1,''),(87,2,3,2,0,422,'0|0',0,0,1536.42,-1694,13.5469,204.238,0,1000,17,100,0,'TES-T',0,0,1579661062,0,0,0,''),(88,2,3,2,0,400,'0|0',0,0,1534.03,-1703.27,13.3828,45.1413,0,1000,25,100,0,'TET-4',0,0,1579661518,0,0,1,''),(89,2,3,2,0,402,'0|0',0,0,1534.18,-1703.34,15.3272,45.1582,0,1000,19,100,0,'TET-2',0,0,1579661525,0,0,0,'');
/*!40000 ALTER TABLE `vehicles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'samp_furystories'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-02-06 21:23:43
