/*!
	@brief Античит: Driver Speed Hack
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_SPEED_HACK(playerid, data[PR_InCarSync])
{
	#pragma unused data
	
	if (GetAntiCheatSpeed(playerid) > 180)
	{
		AntiCheatDetect(playerid, AC_DRIVER_SPEED_HACK);
		return 0;
	}
	
	return 1;
}

/*GetAntiCheatVehicleMaxSpeed(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
	    case 400: return 88;
	    case 401: return 83;
	    case 402: return 104;
	    case 403: return 61;
	    case 404: return 74;
	    case 405: return 91;
	    case 406: return 61;
	    case 407: return 82;
	    case 408: return 66;
	    case 409: return 88;
	    case 410: return 72;
	    case 411: return 122;
	    case 412: return 95;
	    case 413: return 61;
	    case 414: return 68;
	    case 415: return 107;
	    case 416: return 88;
	    case 418: return 68;
	    case 419: return 82;
	    case 420: return 81;
	    case 421: return 86;
	    case 422: return 78;
	    case 423: return 66;
	    case 424: return 76;
	    case 426: return 96;
	 	case 427: return 92;
	 	case 428: return 87;
	 	case 429: return 112;
	    case 431: return 72;
	    case 432: return 81;
	    case 433: return 61;
	    case 434: return 93;
	    case 436: return 83;
	    case 437: return 88;
	    case 438: return 79;
	    case 439: return 94;
	    case 440: return 76;
	    case 442: return 77;
	    case 443: return 70;
	    case 444: return 62;
	    case 445: return 91;
	    case 448: return 93;
	    case 449: return 101;
	    case 451: return 107;
	    case 455: return 87;
	    case 456: return 59;
	    case 457: return 62;
	    case 458: return 87;
	    case 459: return 76;
	    case 461: return 88;
	    case 462: return 61;
	    case 463: return 78;
		case 466: return 82;
		case 467: return 78;
		case 468: return 78;
		case 470: return 87;
		case 471: return 61;
		case 474: return 82;
		case 475: return 97;
		case 477: return 104;
		case 478: return 66;
		case 479: return 78;
		case 480: return 102;
		case 481: return 80;
		case 482: return 87;
		case 483: return 86;
		case 485: return 56;
		case 486: return 39;
		case 489: return 77;
		case 490: return 82;
		case 491: return 82;
		case 492: return 78;
		case 494: return 118;
		case 495: return 98;
		case 496: return 90;
		case 498: return 60;
		case 499: return 68;
		case 500: return 78;
		case 502: return 119;
		case 503: return 119;
		case 504: return 96;
		case 505: return 78;
		case 506: return 100;
		case 507: return 92;
		case 508: return 60;
		case 509: return 90;
		case 510: return 110;
		case 514: return 67;
		case 515: return 79;
		case 516: return 87;
		case 517: return 88;
		case 518: return 91;
		case 521: return 109;
		case 522: return 112;
		case 523: return 104;
		case 524: return 72;
		case 525: return 89;
		case 526: return 88;
		case 527: return 83;
		case 528: return 98;
		case 529: return 83;
		case 530: return 33;
		case 531: return 39;
		case 532: return 61;
		case 533: return 93;
		case 534: return 94;
		case 535: return 88;
		case 536: return 96;
		case 539: return 55;
		case 540: return 83;
		case 541: return 113;
		case 542: return 91;
		case 543: return 84;
		case 544: return 82;
		case 545: return 82;
		case 546: return 83;
		case 547: return 79;
		case 550: return 80;
		case 551: return 87;
		case 552: return 67;
		case 554: return 80;
		case 555: return 88;
		case 556: return 62;
		case 557: return 62;
		case 558: return 87;
		case 559: return 99;
		case 560: return 94;
		case 561: return 85;
		case 562: return 99;
		case 565: return 92;
		case 566: return 89;
		case 567: return 96;
		case 568: return 81;
		case 571: return 52;
		case 572: return 33;
		case 573: return 61;
		case 574: return 33;
		case 575: return 88;
		case 576: return 88;
		case 578: return 72;
		case 579: return 88;
		case 580: return 85;
		case 581: return 110;
		case 582: return 76;
		case 583: return 47;
		case 585: return 85;
		case 586: return 107;
		case 587: return 92;
		case 588: return 60;
		case 589: return 90;
		case 596, 597, 598: return 98;
		case 599: return 88;
		case 600: return 84;
		case 601: return 61;
		case 602: return 94;
		case 603: return 95;
		case 604: return 82;
		case 605: return 84;
		case 609: return 60;
	}

	return 190;
}*/