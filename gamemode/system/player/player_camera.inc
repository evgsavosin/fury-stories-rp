/**
    @brief Login Camera
    @date 09.02.2021
*/

/**
    Constants
*/

const MAX_LOGIN_CAMERA_TIME = 50000;
const MAX_LOGIN_CAMERA_COORDS = 6;
const Float: MIN_SPAWN_CAMERA_Z = -0.0;

/**
    Variables
*/

static const Float: login_camera_pos[][][MAX_LOGIN_CAMERA_COORDS] =
{
    { 
        { 1595.655761, -1205.260620, 545.469299, 1665.451538, -1322.136962, 559.159851 },
        { 1596.091552, -1205.266723, 540.488342, 1665.253540, -1321.748779, 554.178894 }
    },

    {
        { 1665.451538, -1322.136840, 559.159851, 1117.546508, -1010.965698, 559.159851 },
        { 1665.166625, -1321.771850, 554.181335, 1117.937622, -1011.157958, 554.178894 }
    },

    {
        { 1895.837646, -1098.624511, 490.892333, 2467.893310, -1837.258056, 499.547607 },
        { 1895.637573, -1099.011596, 485.911346, 2467.532714, -1837.013427, 494.566619 }
    }
};


/**
    Getters & Setters
*/

static stock GetLoginCameraPos(const index, Float: pos[MAX_LOGIN_CAMERA_COORDS], Float: pos_look_at[MAX_LOGIN_CAMERA_COORDS])
{
    pos = login_camera_pos[index][0];
    pos_look_at = login_camera_pos[index][1];
    return 1;
}

/**
    Public functions
*/

function OnPlayerLoginCameraReady(playerid)
{
    const len = sizeof(login_camera_pos) - 1;

    // Get random index from camera position list
    new index = random(len);

    new Float: pos[MAX_LOGIN_CAMERA_COORDS],
        Float: pos_look_at[MAX_LOGIN_CAMERA_COORDS];

    // Get login camera position
    GetLoginCameraPos(index, pos, pos_look_at);

    // Set camera position
    InterpolateCameraPos(playerid, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], MAX_LOGIN_CAMERA_TIME, CAMERA_MOVE);
	InterpolateCameraLookAt(
        playerid, 
        pos_look_at[0], 
        pos_look_at[1], 
        pos_look_at[2], 
        pos_look_at[3], 
        pos_look_at[4], 
        pos_look_at[5], 
        MAX_LOGIN_CAMERA_TIME,
        CAMERA_MOVE
    );

	return 1;
}

function OnPlayerAfterSpawn(playerid)
{
    if (GetCharacterInt(playerid) != 0 || GetCharacterWorld(playerid) != 0)
    {
        return 1;
    }

	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	GetSpawnInfo(playerid, x, y, z, angle);
    InterpolateSpawnCamera(playerid, x, y, z, angle);

	#if defined LoginCam_OnPlayerAfterSpawn
		return LoginCam_OnPlayerAfterSpawn(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerAfterSpawn
    #undef OnPlayerAfterSpawn
#else
    #define _ALS_OnPlayerAfterSpawn
#endif

#define	OnPlayerAfterSpawn	LoginCam_OnPlayerAfterSpawn
#if defined LoginCam_OnPlayerAfterSpawn
	forward LoginCam_OnPlayerAfterSpawn(playerid);
#endif


function OnCharacterBeforeLogout(playerid)
{
    if (GetCharacterInt(playerid) != 0 || GetCharacterWorld(playerid) != 0)
    {
        return 1;
    }

    new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);
    InterpolateLogoutCamera(playerid, x, y, z, angle);

	#if defined LoginCa_OnCharacterBeforeLogout
		return LoginCa_OnCharacterBeforeLogout(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnCharacterBeforeLogout
    #undef OnCharacterBeforeLogout
#else
    #define _ALS_OnCharacterBeforeLogout
#endif

#define	OnCharacterBeforeLogout	LoginCa_OnCharacterBeforeLogout
#if defined LoginCa_OnCharacterBeforeLogout
	forward LoginCa_OnCharacterBeforeLogout(playerid);
#endif


/**
    Other functions
*/

static stock InterpolateSpawnCamera(playerid, Float: x, Float: y, Float: z, Float: angle, time = 4000)
{
    new Float: calculate_x = x + 3 * floatsin(angle, degrees),
        Float: calculate_y = y - 3 * floatcos(angle, degrees);

    InterpolateCameraPos(playerid, calculate_x, calculate_y, z + 500, calculate_x, calculate_y, z + 1, time, CAMERA_MOVE);
    InterpolateCameraLookAt(playerid, x, y, MIN_SPAWN_CAMERA_Z, x, y, z + 0.5, time, CAMERA_MOVE);

    SetTimerEx("OnSpawnCameraBehind", time + 3000, false, "d", playerid);
}

function OnSpawnCameraBehind(playerid)
{
    SetCameraBehindPlayer(playerid);    
    return 1;
}

static stock InterpolateLogoutCamera(playerid, Float: x, Float: y, Float: z, Float: angle, time = 4000)
{
    new Float: calculate_x = x + 3 * floatsin(angle, degrees),
        Float: calculate_y = y - 3 * floatcos(angle, degrees);

    InterpolateCameraPos(playerid, calculate_x, calculate_y, z + 1, calculate_x, calculate_y, z + 500, time, CAMERA_MOVE);
    InterpolateCameraLookAt(playerid, x, y, z + 0.5, x, y, MIN_SPAWN_CAMERA_Z, time, CAMERA_MOVE);

    SetTimerEx("OnCharacterLogout", time, false, "d", playerid);
}