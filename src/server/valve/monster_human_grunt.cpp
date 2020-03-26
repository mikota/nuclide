/*
 * Copyright (c) 2016-2019 Marco Hladik <marco@icculus.org>
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

/*QUAKED monster_human_grunt (0 0.8 0.8) (-16 -16 0) (16 16 72)

HECU - Human Grunt

*/

enum {
	HECU_WALK,
	HECU_RUN,
	HECU_VICTORYDANCE,
	HECU_COWER,
	HECU_FLINCH,
	HECU_LEFTLEGFLINCH,
	HECU_RIGHTLEGFLINCH,
	HECU_RIGHTARMFLINCH,
	HECU_LEFTARMFLINCH,
	HECU_LAUNCHNADE,
	HECU_THROWNADE,
	HECU_IDLE1,
	HECU_IDLE2,
	HECU_COMBATIDLE,
	HECU_FRONTKICK,
	HECU_CROUCHIDLE,
	HECU_CROUCHWAIT,
	HECU_CROUCHSHOOTMP5,
	HECU_STANDSHOOTMP5,
	HECU_RELOADMP5,
	HECU_CROUCHSHOOTSG,
	HECU_STANDSHOOTSG,
	HECU_RELOADSG,
	HECU_SIGNALADV,
	HECU_SIGNALFLANK,
	HECU_SIGNALRETREAT,
	HECU_DROPNADE,
	HECU_LIMPWALK,
	HECU_LIMPRUN,
	HECU_TURNLEFT,
	HECU_TURNRIGHT,
	HECU_STRAFELEFT,
	HECU_STRAFERIGHT,
	HECU_DIEBACK,
	HECU_DIEFORWARD,
	HECU_DIE,
	HECU_DIEBACK2,
	HECU_DIEHS,
	HECU_DIEGUT,
	HECU_BARNACLE1,
	HECU_BARNACLE2,
	HECU_BARNACLE3,
	HECU_BARNACLE4,
	HECU_DEADSTOMACH,
	HECU_DEADSTOMACH2,
	HECU_DEADSIDE,
	HECU_DEADSITTING,
	HECU_REPELJUMP,
	HECU_REPEL,
	HECU_REPELSHOOT,
	HECU_REPELLAND,
	HECU_REPELDIE,
	HECU_DRAGHOLEIDLE,
	HECU_DRAGHOLE,
	HECU_BUSTWALL,
	HECU_HOPRAIL,
	HECU_CONVERSE1,
	HECU_CONVERSE2,
	HECU_STARTLELEFT,
	HECU_STRRTLERIGHT,
	HECU_DIVE,
	HECU_DEFUSE,
	HECU_CORNER1,
	HECU_CORNER2,
	HECU_STONETOSS,
	HECU_CLIFFDIE,
	HECU_DIVESIDEIDLE,
	HECU_DIVESIDE,
	HECU_DIVEKNEELIDLE,
	HECU_DIVEKNEEL,
	HECU_WMBUTTON,
	HECU_WM,
	HECU_WMJUMP,
	HECU_BUSTWINDOW,
	HECU_DRAGLEFT,
	HECU_DRAGRIGHT,
	HECU_TRACKWAVE,
	HECU_TRACKDIVE,
	HECU_FLYBACK,
	HECU_IMPALED,
	HECU_JUMPTRACKS,
	HECU_THROWPIPE,
	HECU_PLUNGER
};

string hecu_snddie[] = {
	"hgrunt/gr_die1.wav",
	"hgrunt/gr_die2.wav",
	"hgrunt/gr_die3.wav"
};

string hecu_sndpain[] = {
	"hgrunt/gr_pain1.wav",
	"hgrunt/gr_pain2.wav",
	"hgrunt/gr_pain3.wav",
	"hgrunt/gr_pain4.wav",
	"hgrunt/gr_pain5.wav"
};

class monster_human_grunt:CBaseMonster
{
	void() monster_human_grunt;
};

void monster_human_grunt::monster_human_grunt(void)
{
	netname = "Grunt";
	model = "models/hgrunt.mdl";
	base_mins = [-16,-16,0];
	base_maxs = [16,16,72];
	CBaseMonster::CBaseMonster();
}
