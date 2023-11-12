/*!
	@brief Константы
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

/// Global constant
#if defined INVALID_DIALOG_ID
	#undef INVALID_DIALOG_ID
#endif

#define INVALID_PARAM						(-1)
#define INVALID_DIALOG_ID					(0)
#define INVALID_ITEM_ID						(-1)
#define	ANTICHEAT_ID						(0xFFCC)
#define MAX_COMMAND_NAME					(32)

/// For dynamic dialog
const MAX_ITEM_LIST = 18;

const MAX_CHAT_MESSAGE = 144;

const MAX_SPLIT_CHARS = 70,
	  MAX_VISIBLE_OBJECTS_ALL = 1000,
	  MAX_VISIBLE_OBJECTS = 600;

/// Player 
const MAX_PLAYER_IP = 17,
	  MAX_PLAYER_PASSWORD = 32,
      MAX_PLAYER_EMAIL = 32,
	  MAX_PLAYER_DESC = 144;
	  
/// Licenses
const MAX_PLAYER_LICENSES = 4;

/// Base 
const MAX_WEAPON_SLOTS = 13,
	  MAX_PLAYER_PHONES = 3;

/// Character
const MAX_CHARACTERS = 6,
	  MAX_CHARACTER_BUY_WEAPON = 2;

/// House
#if defined __DEBUG
	const MAX_HOUSES = 100,
#else
	const MAX_HOUSES = 2000,
#endif 
	  MAX_HOSTELS = 500,
	  MAX_PLAYER_HOUSES = 3, // Player	
	  MAX_LODGERS = 10;
	
/// Premises
const MAX_PREMISE_NAME = 32,
	  MAX_PREMISES = 1000,
	  MAX_PLAYER_PREMISES = 2,
	  MAX_PREMISE_VISITORS = 500;

/// Business
const MAX_BUSINESSES = 1000,
	  MAX_BUSINESS_NAME = 32,
	  MAX_BPOST_NAME = 32,
	  MAX_PLAYER_BUSINESSES = 2,
	  MAX_BUSINESS_ITEM_LIST = 20,
	  MAX_BUSINESS_MEMBERS = 20,
	  MAX_BUSINESS_SUBTYPE = 6,
	  MAX_BUSINESS_ASSORT = 30;

/// Vehicle
const MAX_SPAWNED_VEHICLES = 2,
	  MAX_PLAYER_VEHICLES = 4, ///> Player
	  MAX_SPEEDOMETER_VEHICLE_NAME = 14;
	  
/// Attaches
const MAX_INVENTORY_ATTACH = 4;
const SLOT_ATTACH_BAG = 4,
	  SLOT_ATTACH_BACK = 5,
	  SLOT_ATTACH_PHONE = 6,
	  SLOT_ATTACH_DRINK = 6,
	  SLOT_ATTACH_SMOKE = 6,
	  SLOT_ATTACH_TEMP = 6,
	  SLOT_ATTACH_FACTION_1 = 7,
	  SLOT_ATTACH_FACTION_2 = 8,
	  SLOT_ATTACH_FACTION_3 = 9;

/// Inventory
const MAX_INVENTORY_SLOTS = 10,
	  MAX_DROP_ITEMS = 300,
#if defined __DEBUG
	MAX_BAGS = 50;
#else
	MAX_BAGS = 1000;
#endif
	  
///	Phone
#if defined __DEBUG
	const MAX_PHONES = 50,
#else
	const MAX_PHONES = 1000,
#endif
	  MAX_PLAYER_PHONES = 3, // Player
	  MAX_PHONE_ITEM_LIST = 5,
	  MAX_NUMBER_LENGTH = 7,
	  MAX_CONTACTS = 35;

const MAX_FUBER_ORDERS = 100;
	
/// Furniture
#if defined __DEBUG
	const MAX_FURN_OBJECTS = 1000;
#else 
	const MAX_FURN_OBJECTS = 50000;
#endif 

/// Rooms
const MAX_ROOMS = 10;
	
/// Sites
#if defined __DEBUG
	const MAX_SITES	= 100,
#else 
	const MAX_SITES	= 1000,
#endif
	  MAX_SITE_PAGES = 4,
	  MIN_SITE_ADDRESS = 3,
	  MAX_SITE_ADDRESS = 32,
	  MAX_SITE_NAME = 32,
	  MAX_SITE_PAGE_NAME = 16,
	  MAX_SITE_PAGE_DESC = 500,
	  MAX_SITE_FAVORITES = 20,
	  MAX_ADVERTS = 20,
	  MAX_PLAYER_SITES = 3;
	  
	  
/// Music
const MAX_MUSIC_URL_LIST = 20,
	  MAX_MUSIC_URL = 128;
	  
/// Death
const MAX_DAMAGES = 20,
#if defined __DEBUG
	  MAX_CORPSES = 100;
#else
	  MAX_CORPSES = 500;
#endif 
	  
/// Admin
const MAX_ADMIN_LOG_LINES = 15,
	  MAX_ADMIN_LOG_LINE_LENGHT = 100;