/*
 * Copyright (c) 2016-2022 Vera Visions LLC.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define CUSTOMPLAYERPHYSICS

#ifdef CUSTOMPLAYERPHYSICS
	void PMoveCustom_Init(void);
	#ifdef SERVER
	void PMoveCustom_StartFrame(void);
	#endif
#endif

#ifndef PMOVE_STEPHEIGHT
	#define PMOVE_STEPHEIGHT 18
#endif

#ifndef PMOVE_AIRSTEPHEIGHT
	#define PMOVE_AIRSTEPHEIGHT 18
#endif

#ifndef PMOVE_FRICTION
	#define PMOVE_FRICTION 4
#endif

#ifndef PMOVE_EDGEFRICTION
	#define PMOVE_EDGEFRICTION 1
#endif

#ifndef PMOVE_STOPSPEED
	#define PMOVE_STOPSPEED 75
#endif

#ifndef PMOVE_GRAVITY
	#define PMOVE_GRAVITY 800
#endif

#ifndef PMOVE_AIRACCELERATE
	#define PMOVE_AIRACCELERATE 10
#endif

#ifndef PMOVE_WATERACCELERATE
	#define PMOVE_WATERACCELERATE 8
#endif

#ifndef PMOVE_ACCELERATE
	#define PMOVE_ACCELERATE 8
#endif

#ifndef PMOVE_MAXSPEED
	#define PMOVE_MAXSPEED 270
#endif

#ifndef PMOVE_STEP_WALKSPEED
	#define PMOVE_STEP_WALKSPEED 135
#endif

#ifndef PMOVE_STEP_RUNSPEED
	#define PMOVE_STEP_RUNSPEED 220
#endif

#ifndef PHY_VIEWPOS
	#define PHY_VIEWPOS [0,0,28]
#endif

#ifndef PHY_VIEWPOS_CROUCHED
	#define PHY_VIEWPOS_CROUCHED [0,0,12]
#endif

/* stamina system, inspired by idTech 4 */
#ifndef PMOVE_STAMINA
	#define PMOVE_STAMINA 24
#endif

#ifndef PMOVE_STAMINARATE
	#define PMOVE_STAMINARATE 0.75
#endif

#ifndef PMOVE_STAMINATHRESHOLD
	#define PMOVE_STAMINATHRESHOLD 4
#endif


/* Those are constant for HL BSP and CANNOT be changed.
 * Blame Valve for purchasing a Quake II license but not
 * scrapping hull sizes for their .bsp format... 
 * however, you can offset them */
#ifndef PHY_HULL_MIN
	#define PHY_HULL_MIN [-16,-16,-36]
#endif

#ifndef PHY_HULL_MAX
	#define PHY_HULL_MAX [16,16,36]
#endif

#ifndef PHY_HULL_CROUCHED_MIN
	#define PHY_HULL_CROUCHED_MIN [-16,-16,-18]
#endif

#ifndef PHY_HULL_CROUCHED_MAX
	#define PHY_HULL_CROUCHED_MAX [16,16,18]
#endif

/* if they're undefined by a config, they'll be set by the game/mod default */
var float autocvar_pm_stepsize = PMOVE_STEPHEIGHT;
var float autocvar_pm_airstepsize = PMOVE_AIRSTEPHEIGHT;
var float autocvar_pm_friction = PMOVE_FRICTION;
var float autocvar_pm_edgefriction = PMOVE_EDGEFRICTION;
var float autocvar_pm_stopspeed = PMOVE_STOPSPEED;
var float autocvar_pm_airaccelerate = PMOVE_AIRACCELERATE;
var float autocvar_pm_wateraccelerate = PMOVE_WATERACCELERATE;
var float autocvar_pm_accelerate = PMOVE_ACCELERATE;
var float autocvar_pm_maxspeed = PMOVE_MAXSPEED;
var float autocvar_g_gravity = PMOVE_GRAVITY;

void
PMove_Init(void)
{
	#ifdef SERVER
	cvar_set("pm_stepsize", ftos(PMOVE_STEPHEIGHT));
	cvar_set("pm_airstepsize", ftos(PMOVE_AIRSTEPHEIGHT));
	cvar_set("pm_friction", ftos(PMOVE_FRICTION));
	cvar_set("pm_edgefriction", ftos(PMOVE_EDGEFRICTION));
	cvar_set("pm_stopspeed", ftos(PMOVE_STOPSPEED));
	cvar_set("pm_airaccelerate", ftos(PMOVE_AIRACCELERATE));
	cvar_set("pm_wateraccelerate", ftos(PMOVE_WATERACCELERATE));
	cvar_set("pm_accelerate", ftos(PMOVE_ACCELERATE));
	cvar_set("pm_maxspeed", ftos(PMOVE_MAXSPEED));
	cvar_set("g_gravity", ftos(PMOVE_GRAVITY)); /* global */
	#endif

	#ifdef CUSTOMPLAYERPHYSICS
	PMoveCustom_Init();
	#endif
}

#ifdef SERVER
void
PMove_StartFrame(void)
{
	#ifdef CUSTOMPLAYERPHYSICS
	PMoveCustom_StartFrame();
	#endif
}
#endif

/* simple bounds check */
int
PMove_IsStuck(entity eTarget, vector vOffset, vector vecMins, vector vecMaxs)
{
	vector bound;

	if (eTarget.solid != SOLID_SLIDEBOX) {
		return (0);
	}

	bound = eTarget.origin + vOffset;
	tracebox(bound, vecMins, vecMaxs, bound, MOVE_NORMAL, eTarget);
	return trace_startsolid;
}

/* it all starts here, this function is called by both CLIENT and SERVER for
   obvious prediction purposes. The SERVER will usually do this in the
   Game_RunClientCommand function and the CLIENT will do so in both the
   prediction places of Predict_PreFrame and Player_ReceiveEntity */
void
PMove_Run(void)
{
	player pl = (player)self;
	pl.Physics_Run();
}
