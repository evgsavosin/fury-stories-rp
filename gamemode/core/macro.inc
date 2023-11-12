/*!
	@brief Макросы
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

/// Base
#if !defined isnull
	#define isnull(%0)					((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
#endif

#define function%0(%1)     				forward %0(%1); public %0(%1)

#define abs(%0)							(%0 < 0 ? -%0 : %0)

#define GivePVarInt(%0,%1,%2)			SetPVarInt(%0,%1,GetPVarInt(%0,%1)+%2)
#define TakePVarInt(%0,%1,%2)			SetPVarInt(%0,%1,GetPVarInt(%0,%1)-%2)

#define PRESSED(%0) 					(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define HOLDING(%0)             		((newkeys & (%0)) == (%0))
#define PRESSING(%0,%1)					(%0 & (%1))
#define RELEASED(%0)					(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

/// Pformat & Psend
#define clean:<%0>						%0[0] = EOS			
#define format:%0(		    			format(%0,sizeof(%0),
									
#define pformat:(						g_small_string[0] = EOS,format(g_small_string,sizeof(g_small_string),						
#define psend:(%0,%1) 					SendClientMessage(%0,%1,g_small_string)

/// Prefixes
#define Clear:							C1_
#define Update:							U2_
#define Timer:							T3_
#define Create:							C4_
#define Destroy:						D5_
#define Load:							L6_
#define Remove:							R7_
#define Recreate:						R8_
#define Move:							M9_
#define Check:							C0_

#define PAY:							Pay_
#define INV:							Inv_

/// Other
#define GetMaxTimeForProperty()			gettime()+(60*60*24*7*4)		
#define AddDebtForProperty(%0)			(floatround((%0/(7*24))+(%0*0.02))) /// Задолжность за имущество

#define CheckSummForPay(%0,%1)			(character_data[%0][c_money] < %1 ? 0 : 1)
#define CheckCardSummForPay(%0,%1)		(character_data[%0][c_card] < %1 ? 0 : 1)
#define CheckBankSummForPay(%0,%1)		(character_data[%0][c_bank] < %1 ? 0 : 1)
#define CheckInputSumm(%0)				((0 < %0 <= 100_000))

#define EndWordSex(%0)					((character_data[%0][c_sex] == 0) ? ("") : ("а"))
#define EndWordSlot(%0)					(%0 == 1 ? ("") : (%0 == 2 || %0 == 3 || %0 == 4 ? ("а") : (%0 >= 5 || %0 == 0 ? ("ов") : (""))))
#define EndWordDamageCount(%0)			(%0 == 2 ? ("а") : (%0 == 3 ? ("а") : ((%0 == 4 ? ("а") : ("")))))