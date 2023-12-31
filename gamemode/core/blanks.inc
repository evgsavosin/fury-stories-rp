/*!
	@brief ������������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

// Chat

/// Player
#define PLAYER_NO_ACCESS					"" #ERROR " � ��� ��� ������� ��� ���������� ������� ��������."
#define PLAYER_NO_ACTION					"" #ERROR " �� �� ������ ��������� ������ ��������."
#define PLAYER_NO_FLOOD						"" #ERROR " �� �� ������ ������� ����� ������������ ������ ��������, ���������."
#define PLAYER_INCORRECT					"" #ERROR " �� ������� ������������� ������."
#define PLAYER_MUTED						"" #ERROR " ��� �������� ���������� ���. ����� ��������� ���������� ����� ������ �������� - /time."
#define PLAYER_NO_CAR						"" #ERROR " � ��� ��� ������� ����������."
#define PLAYER_NO_HOUSE						"" #ERROR " � ��� ����������� �������� ���������."
#define PLAYER_NO_PREMISE					"" #ERROR " � ��� ����������� ���������."
#define PLAYER_NO_BUSINESS					"" #ERROR " �� �� �������� � �����-���� �������� ��� �� ��������� � ����������."
#define PLAYER_NEED_CAR						"" #ERROR " �� ������ ���������� �� ����� ���������� ��� ����� ����."
#define PLAYER_NO_THIS_CAR					"" #ERROR " ��� �� ��� ������ ���������."
#define PLAYER_AROUND_CAR					"" #ERROR " �� ������ ���������� ���� �� ����� ������� ���������� ���� ����� ����."
#define PLAYER_NO_CASH						"" #ERROR " ������������ �������, ��� ���������� ������ ��������."
#define PLAYER_NO_PHONE						"" #ERROR " � ��� ��� ��������."
#define PLAYER_CREDIT_EXISTS				"" #ERROR " �� �� ������ ��������� ������ ��������, ��� ��� � ��� ������� ������������ ������."
#define PLAYER_DIED							"" #ERROR " ��� �������� ����."
#define PLAYER_ON_DUTY						"" #ERROR " �� ������ ���� �� ���������."
#define PLAYER_NO_FRACTION					"" #ERROR " �� �� �������� �� �������."

#define HOUSE_NOT_OWN						"" #ERROR " ������ ����� �� ������� �����-���� �����."

#define NOT_RENT_ACCESS						"" #ERROR " ������ �������� �������� ������ ����� ������� ������������ ���������."
#define NOT_RENOVATION_MODE					"" #ERROR " ��� ������������� ������ ������ ���������� �������� ����� �������."

#define VEHICLE_RENT_ACCESS					"" #ERROR " ������ �������� ������ ��������� � ����������� �����������."
#define VEHICLE_NO_ACCESS					"" #ERROR " � ��� ��� ������ �� ������� ����������."

#define CORPSE_USED							"" #ERROR " ������ ���� ��� ������������."

/// Error
#define ERROR_SYSTEM						"" #ERROR " ��������� ������, �������� �� ���� ������������� �� - " cPROJECT "" #__PROJECT_SITE ""
#define ERROR_PAY							"" #ERROR " � ��� ������������ ������� ��� ���������� ������ ��������."
#define ERROR_NO_SLOTS						"" #ERROR " � ��� ������������ ����� � ��������� ��� ������ ������� ��������."						
#define ERROR_NOT_CHOOSE_ITEM				"" #ERROR " ��� ���������� ������� �������� ���������� ������� �������."
#define ERROR_NO_USE						"" #ERROR " �� �� ������ ������������ ���� ������� ����� �������."
#define ERROR_INTERFACE						"" #ERROR " �� �� ������ ������������ ������ ��������, ���� � ��� ������ ������ ���������."
#define ERROR_ACTIVE_PHONE					"" #ERROR " � ��� �� �������� ������� �� ���������. ��� ���������� ��������� � " #cGRAY "��������� ���������" #cWHITE "."
#define ERROR_DOOR_CLOSED					"" #ERROR " ����� �������, ����������� " #cPROJECT "/knock" #cWHITE ", ����� �����������."
#define ERROR_USE_PHONE						"" #ERROR " �� �� ������ ������������ ������� � ������ ������."
#define ERROR_IN_VEHICLE                    "" #ERROR " ������ �������� ������ ��������� � ����������."

/// Help
#define HELP_RENOVATION						"" #DEFAULT " �� �������� ����� �������. ��� ����, ����� ������� ���� �������, ����������� " #cPROJECT "N" #cWHITE" ��� " #cPROJECT "/ren" #cWHITE "."
#define HELP_TRADE							"" #DEFAULT " " #cPROJECT "Y" #cWHITE " - ������� ����������� | " #cGRAY "N" #cWHITE " - ��������� �����������."
#define HELP_EDITOR							"" #DEFAULT " ����������� ������ " #cPROJECT "���" #cWHITE " ��� �������� ������, " #cPROJECT "ESC" #cWHITE" ��� ������ �� ���������."
#define HELP_3DMENU_ONE						"" #DEFAULT " ����������� " #cPROJECT "NUM 4 / NUM 6" #cWHITE" ��� ��������������, " #cPROJECT"Y / N" #cWHITE " ��� ������."
#define HELP_3DMENU_TWO						"" #DEFAULT " ��� ������� �������� ��� ������ �� ��������� ����������� " #cPROJECT "���" #cWHITE "."
#define HELP_PUNISHMENT						"" #DEFAULT " �� ������������ ����������� ��������� ������� ������� � �������� � ������� ���������."

/// FLOOD
#define CMD_FLOOD							"" #ERROR " ������ ������������ ������ ������� ������� �����, ���������."	
#define QUERY_FLOOD							"" #ERROR " ���� ��������� �������, ���������."

// Dialog
#define HELP_TEXT_EDITOR					"�������� ����� ��������� ����� ����������� ����� ������������� \"����\".\n��� ����, ����� �������� ���������� ������, ����������� \"��������\".\n����� ��������� �����, ��������� ������ ������ � ����������� \"����\""