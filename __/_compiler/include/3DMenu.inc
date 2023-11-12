/*
	edit by encoder, thx to sdraw
	changes: 
	 - Add SetBoxMaterial function;
	 - Add foreach;
	 - Remove SetBoxText function;
     - Add IsBlockSelected;
	-----------------------------------------------------------------------------------------------
	native Create3DMenu(playerid,Float:x,Float:y,Float:z,Float:rotation,boxes);
	native SetBoxMaterial( playerid, box, index, model, txd, texture, selectcolor, unselectcolor );
	native Select3DMenu(playerid);
	native CancelSelect3DMenu(playerid);
	native Destroy3DMenu(playerid);
	-----------------------------------------------------------------------------------------------
*/

#define MAX_BOXES 					(	8	)
#define MENU3D_KEY_DOWN 			KEY_NO
#define MENU3D_KEY_UP 				KEY_YES
#define MENU3D_KEY_SELECT 			KEY_SPRINT

forward OnPlayerSelect3DMenuBox( playerid, boxid );
forward OnPlayerChange3DMenuBox( playerid, boxid );

new SelectedMenu				[MAX_PLAYERS];
new SelectedBox 				[MAX_PLAYERS];

enum MenuParams
{
    Float: Rotation,
    Boxes,
    bool: IsExist,
    Objects             [MAX_BOXES],
    Float: OrigPosX     [MAX_BOXES],
    Float: OrigPosY     [MAX_BOXES],
    Float: OrigPosZ     [MAX_BOXES],
    Float: AddingX,
    Float: AddingY,
    SelectColor         [MAX_BOXES],
    UnselectColor       [MAX_BOXES],
    IsBlockSelected     [MAX_BOXES],
};
new MenuData[MAX_PLAYERS][MenuParams];

stock Create3DMenu(playerid,Float:x,Float:y,Float:z,Float:rotation,boxes)
{
    if(boxes > MAX_BOXES || boxes <= 0 || playerid < 0 || !IsPlayerConnected(playerid)) return false;
    if(MenuData[playerid][IsExist]) return false;
    new Float:NextLineX,Float:NextLineY;
    new lineindx,binc;
    MenuData[playerid][Rotation] = rotation;
    MenuData[playerid][Boxes] = boxes;
    MenuData[playerid][AddingX] = 0.25*floatsin(rotation,degrees);
    MenuData[playerid][AddingY] = -floatcos(rotation,degrees)*0.25;
    NextLineX = floatcos(rotation,degrees)+0.05*floatcos(rotation,degrees);
    NextLineY = floatsin(rotation,degrees)+0.05*floatsin(rotation,degrees);
    for(new b = 0; b < boxes; b++)
    {
        if(b%4 == 0 && b != 0) lineindx++,binc+=4;
        MenuData[playerid][Objects][b] = CreateDynamicObject(2661,x+NextLineX*lineindx,y+NextLineY*lineindx,z+1.65-0.55*(b-binc),0,0,rotation,-1,-1,playerid,100.0);
        GetDynamicObjectPos(MenuData[playerid][Objects][b],MenuData[playerid][OrigPosX][b],MenuData[playerid][OrigPosY][b],MenuData[playerid][OrigPosZ][b]);
        MenuData[playerid][IsBlockSelected][ b ] = 0;
    }
    MenuData[playerid][IsExist] = true;
    Streamer_Update(playerid);
    return true;
}

// edit by encoder
stock SetBoxMaterial( playerid, box, index, model, txd[], texture[], selectcolor, unselectcolor, is_blocked = 0 )
{
    if( !MenuData[playerid][IsExist] ) 
    {
    	return false;
    }

    if( box == MenuData[playerid][Boxes] || box < 0 ) 
    {
    	return false;
    }

    if( MenuData[playerid][Objects][box] == INVALID_OBJECT_ID ) 
    {
    	return false;
    }

    MenuData[ playerid ][ SelectColor ][ box ] = selectcolor;
    MenuData[ playerid ][ UnselectColor ][ box ] = unselectcolor;
    MenuData[ playerid ][ IsBlockSelected ][ box ] = is_blocked;

    if( SelectedBox[playerid] == box ) 
    {
    	SetDynamicObjectMaterial( MenuData[playerid][Objects][box], index, model, txd, texture, selectcolor );
    }
    else
    {
    	SetDynamicObjectMaterial( MenuData[playerid][Objects][box], index, model, txd, texture, unselectcolor );
    }

    return true;
}

// encoder
stock UpdateSelect3DMenu( playerid )
{
    if( !MenuData[ playerid ][ IsExist ] ) 
    {
        return false;
    }

    if( SelectedBox[ playerid ] == -1 
        || MenuData[ playerid ][ IsBlockSelected ][ SelectedBox[ playerid ] ] )
    {
        Select3DMenu( playerid );
    }

    OnPlayerChange3DMenuBox( playerid, SelectedBox[ playerid ] );
    return true; 
}

stock Select3DMenu( playerid )
{
    if(!IsPlayerConnected(playerid)) return false;
    if(!MenuData[playerid][IsExist]) return false;
    if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);
    SelectedBox[playerid] = 0;

    new 
        modelid,
        txd                 [ 32 ],
        texture_name        [ 32 ],
        color;
    
    GetDynamicObjectMaterial( MenuData[playerid][Objects][0], 0, modelid, txd, texture_name, color );
    SetDynamicObjectMaterial( MenuData[playerid][Objects][0], 0, modelid, txd, texture_name, MenuData[ playerid ][ SelectColor ][ 0 ] );

    SelectedMenu[playerid] = playerid;
    
    MoveDynamicObject(MenuData[playerid][Objects][0],MenuData[playerid][OrigPosX][0]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][0]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][0],1.0);
    
    OnPlayerChange3DMenuBox( playerid, SelectedBox[ playerid ] );
    return true;
}

public OnGameModeInit()
{
    foreach( new i : Player)
    {
        for(new b = 0; b < MAX_BOXES; b++)
        {
            MenuData[i][Objects][b] = INVALID_OBJECT_ID;
            MenuData[ i ][ IsBlockSelected ][ b ] = 0;
        }
        MenuData[i][Boxes] = 0;
        MenuData[i][IsExist] = false;
        MenuData[i][AddingX] = 0.0;
        MenuData[i][AddingY] = 0.0;
    }
    if(funcidx("menu3d_OnGameModeInit") != -1) return menu3d_OnGameModeInit( );
    return 1;
}
#if defined _ALS_OnGameModeInit
#undef OnGameModeInit
#else
#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit menu3d_OnGameModeInit
forward menu3d_OnGameModeInit();

public OnGameModeExit()
{
    foreach( new i : Player)
    {
        if(MenuData[i][IsExist]) Destroy3DMenu(i);
    }
    if(funcidx("menu3d_OnGameModeExit") != -1) return menu3d_OnGameModeExit( );
    return 1;
}
#if defined _ALS_OnGameModeExit
#undef OnGameModeExit
#else
#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit menu3d_OnGameModeExit
forward menu3d_OnGameModeExit();

public OnPlayerConnect(playerid)
{
    SelectedMenu[playerid] = -1;
    SelectedBox[playerid] = -1;
    if(funcidx("menu3d_OnPlayerConnect") != -1) return menu3d_OnPlayerConnect( playerid );
    return 1;
}
#if defined _ALS_OnPlayerConnect
#undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect menu3d_OnPlayerConnect
forward menu3d_OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid,reason)
{
    if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);
    if(funcidx("menu3d_OnPlayerDisconnect") != -1) return menu3d_OnPlayerDisconnect( playerid, reason );
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
#undef OnPlayerDisconnect
#else
#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect menu3d_OnPlayerDisconnect
forward menu3d_OnPlayerDisconnect(playerid, reason);

// edited by encoder
forward Menu3D_OnPlayerKeyStateChange( playerid, newkeys, oldkeys );
public Menu3D_OnPlayerKeyStateChange( playerid, newkeys, oldkeys )
{
    if( SelectedMenu[playerid] != -1)
    {
        if( newkeys & MENU3D_KEY_DOWN )
        {
            new 
                modelid,
                txd                 [ 32 ],
                texture_name        [ 32 ],
                color;
            
            GetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                color
            );

            SetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                MenuData[playerid][UnselectColor][SelectedBox[playerid]]
            );

            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            
            SelectedBox[playerid]++;
            
            if( SelectedBox[ playerid ] == MenuData[ playerid ][ Boxes ] 
            || MenuData[ playerid ][ IsBlockSelected ][ SelectedBox[ playerid ] ] ) 
            {
                SelectedBox[ playerid ] = 0;
            }

            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][SelectedBox[playerid]]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            
            GetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                color
            );

            SetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                MenuData[playerid][SelectColor][SelectedBox[playerid]]
            );

            OnPlayerChange3DMenuBox( playerid, SelectedBox[playerid] );

            return 0;
        }
        
        if( newkeys & MENU3D_KEY_UP )
        {
            new 
                modelid,
                txd                 [ 32 ],
                texture_name        [ 32 ],
                color;
            
            GetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                color
            );

            SetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                MenuData[playerid][UnselectColor][SelectedBox[playerid]]
            );

            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            
            SelectedBox[playerid]--;
            if( SelectedBox[playerid] < 0 ) 
            {
                for( new i = MenuData[ playerid ][ Boxes ] - 1; i > 0; i-- )
                {
                   if( MenuData[ playerid ][ IsBlockSelected ][ i ] )
                   {
                        continue;
                   }

                   SelectedBox[ playerid ] = i;
                   break;
                }
            }


            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][SelectedBox[playerid]]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            
            GetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                color
            );

            SetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
                0, 
                modelid, 
                txd, 
                texture_name, 
                MenuData[playerid][SelectColor][SelectedBox[playerid]]
            );

            OnPlayerChange3DMenuBox( playerid, SelectedBox[ playerid ] );
            return 0;
        }
        
        if( newkeys & MENU3D_KEY_SELECT )
        {
            OnPlayerSelect3DMenuBox( playerid, SelectedBox[ playerid ] );
            return 0;
        }
    }

    return 1;
}

stock CancelSelect3DMenu(playerid)
{
    if(!IsPlayerConnected(playerid)) return false;
    if(SelectedMenu[playerid] == -1) return false;

    new 
        modelid,
        txd                 [ 32 ],
        texture_name        [ 32 ],
        color;
    
    GetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
        0, 
        modelid, 
        txd, 
        texture_name, 
        color
    );

    SetDynamicObjectMaterial( MenuData[playerid][Objects][SelectedBox[playerid]], 
        0, 
        modelid, 
        txd, 
        texture_name, 
        MenuData[playerid][UnselectColor][SelectedBox[playerid]]
    );

    MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
    SelectedMenu[playerid] = -1;
    SelectedBox[playerid] = -1;
    return true;
}

stock Destroy3DMenu(playerid)
{
    if(!MenuData[playerid][IsExist]) return false;
    if(SelectedMenu[playerid] == playerid) CancelSelect3DMenu(playerid);
    for(new i = 0; i < MenuData[playerid][Boxes]; i++)
    {
        DestroyDynamicObject(MenuData[playerid][Objects][i]);
        MenuData[playerid][Objects][i] = INVALID_OBJECT_ID;
        MenuData[ playerid ][ IsBlockSelected ][ i ] = 0;
    }
    MenuData[playerid][Boxes] = 0;
    MenuData[playerid][IsExist] = false;
    MenuData[playerid][AddingX] = 0.0;
    MenuData[playerid][AddingY] = 0.0;
    Streamer_Update( playerid );
    return true;
}