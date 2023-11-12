/*!
	@brief Заготовленные выражения
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

// Chat

/// Player
#define PLAYER_NO_ACCESS					"" #ERROR " У Вас нет доступа для совершения данного действия."
#define PLAYER_NO_ACTION					"" #ERROR " Вы не можете совершить данное действие."
#define PLAYER_NO_FLOOD						"" #ERROR " Вы не можете слишком часто использовать данное действие, подождите."
#define PLAYER_INCORRECT					"" #ERROR " Вы указали некорректного игрока."
#define PLAYER_MUTED						"" #ERROR " Вам временно недоступен чат. Время окончание блокировки можно узнать командой - /time."
#define PLAYER_NO_CAR						"" #ERROR " У Вас нет личного транспорта."
#define PLAYER_NO_HOUSE						"" #ERROR " У Вас отсутствует жилищное помещение."
#define PLAYER_NO_PREMISE					"" #ERROR " У Вас отсутствует помещение."
#define PLAYER_NO_BUSINESS					"" #ERROR " Вы не состоите в какой-либо компании или не являетесь её акционером."
#define PLAYER_NEED_CAR						"" #ERROR " Вы должны находиться за рулем транспорта или около него."
#define PLAYER_NO_THIS_CAR					"" #ERROR " Это не Ваш личный транспорт."
#define PLAYER_AROUND_CAR					"" #ERROR " Вы должны находиться либо за рулем личного транспорта либо около него."
#define PLAYER_NO_CASH						"" #ERROR " Недостаточно средств, для совершения данной операции."
#define PLAYER_NO_PHONE						"" #ERROR " У Вас нет телефона."
#define PLAYER_CREDIT_EXISTS				"" #ERROR " Вы не можете совершить данное действие, так как у Вас имеется непогашенный кредит."
#define PLAYER_DIED							"" #ERROR " Ваш персонаж мёртв."
#define PLAYER_ON_DUTY						"" #ERROR " Вы должны быть на дежурстве."
#define PLAYER_NO_FRACTION					"" #ERROR " Вы не состоите во фракции."

#define HOUSE_NOT_OWN						"" #ERROR " Данным домом не владеет какой-либо игрок."

#define NOT_RENT_ACCESS						"" #ERROR " Данное действие доступно только после полного приобретения имущества."
#define NOT_RENOVATION_MODE					"" #ERROR " Для использования данной команы необходимо включить режим ремонта."

#define VEHICLE_RENT_ACCESS					"" #ERROR " Данное действие нельзя совершить с арендованым транспортом."
#define VEHICLE_NO_ACCESS					"" #ERROR " У Вас нет ключей от данного транспорта."

#define CORPSE_USED							"" #ERROR " Данный труп уже используется."

/// Error
#define ERROR_SYSTEM						"" #ERROR " Произошла ошибка, сообщите об этом администрации на - " cPROJECT "" #__PROJECT_SITE ""
#define ERROR_PAY							"" #ERROR " У Вас недостаточно средств для совершения данной операции."
#define ERROR_NO_SLOTS						"" #ERROR " У Вас недостаточно места в инвентаре для взятия данного предмета."						
#define ERROR_NOT_CHOOSE_ITEM				"" #ERROR " Для выполнения данного действия необходимо выбрать предмет."
#define ERROR_NO_USE						"" #ERROR " Вы не можете использовать этот предмет таким образом."
#define ERROR_INTERFACE						"" #ERROR " Вы не можете использовать данное действие, пока у Вас открыт другой интерфейс."
#define ERROR_ACTIVE_PHONE					"" #ERROR " У Вас не назначен телефон по умолчанию. Для назначения перейдите в " #cGRAY "Настройки персонажа" #cWHITE "."
#define ERROR_DOOR_CLOSED					"" #ERROR " Дверь закрыта, используйте " #cPROJECT "/knock" #cWHITE ", чтобы постучаться."
#define ERROR_USE_PHONE						"" #ERROR " Вы не можете использовать телефон в данный момент."
#define ERROR_IN_VEHICLE                    "" #ERROR " Данное действие нельзя совершить в транспорте."

/// Help
#define HELP_RENOVATION						"" #DEFAULT " Вы включили режим ремонта. Для того, чтобы открыть меню ремонта, используйте " #cPROJECT "N" #cWHITE" или " #cPROJECT "/ren" #cWHITE "."
#define HELP_TRADE							"" #DEFAULT " " #cPROJECT "Y" #cWHITE " - принять предложение | " #cGRAY "N" #cWHITE " - отклонить предложение."
#define HELP_EDITOR							"" #DEFAULT " Используйте кнопку " #cPROJECT "БЕГ" #cWHITE " для поворота камеры, " #cPROJECT "ESC" #cWHITE" для выхода из редактора."
#define HELP_3DMENU_ONE						"" #DEFAULT " Используйте " #cPROJECT "NUM 4 / NUM 6" #cWHITE" для перелистывания, " #cPROJECT"Y / N" #cWHITE " для выбора."
#define HELP_3DMENU_TWO						"" #DEFAULT " Для покупки текстуры или выхода из редактора используйте " #cPROJECT "БЕГ" #cWHITE "."
#define HELP_PUNISHMENT						"" #DEFAULT " Мы настоятельно рекомендуем прочитать правила сервера и избегать в будущем нарушений."

/// FLOOD
#define CMD_FLOOD							"" #ERROR " Нельзя использовать данную команду слишком часто, подождите."	
#define QUERY_FLOOD							"" #ERROR " Идет обработка запроса, подождите."

// Dialog
#define HELP_TEXT_EDITOR					"Вводимый текст построчно будет соединяться после использования \"Ввод\".\nДля того, чтобы очистить предыдущую строку, используйте \"Очистить\".\nЧтобы сохранить текст, отправьте пустую строку и используйте \"Ввод\""