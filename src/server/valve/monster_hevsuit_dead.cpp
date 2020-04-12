/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
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

/*QUAKED monster_hevsuit_dead (0 0.8 0.8) (-16 -16 0) (16 16 72)

HALF-LIFE (1998) ENTITY

HEV-Suit/Player's corpse

*/

class monster_hevsuit_dead:CBaseMonster
{
	int m_iPose;
	void(void) monster_hevsuit_dead;

	virtual void(void) Hide;
	virtual void(void) Respawn;
	virtual void(void) Gib;
};

void monster_hevsuit_dead::Gib(void)
{
	takedamage = DAMAGE_NO;
	Effect_GibHuman(this.origin);
	Hide();
}

void monster_hevsuit_dead::Hide(void)
{
	setmodel(this, "");
	solid = SOLID_NOT;
	movetype = MOVETYPE_NONE;
}

void monster_hevsuit_dead::Respawn(void)
{
	v_angle[0] = Math_FixDelta(m_oldAngle[0]);
	v_angle[1] = Math_FixDelta(m_oldAngle[1]);
	v_angle[2] = Math_FixDelta(m_oldAngle[2]);

	setorigin(this, m_oldOrigin);
	angles = v_angle;
	solid = SOLID_CORPSE;
	movetype = MOVETYPE_NONE;
	setmodel(this, m_oldModel);
	setsize(this, VEC_HULL_MIN + [0,0,36], VEC_HULL_MAX + [0,0,36]);
	takedamage = DAMAGE_YES;
	health = 0;
	velocity = [0,0,0];
	iBleeds = TRUE;
	frame = 73 + m_iPose;
	SendFlags |= NPC_BODY;
}

void monster_hevsuit_dead::monster_hevsuit_dead(void)
{
	model = "models/player.mdl";
	m_iBody = 2;

	for (int i = 1; i < (tokenize(__fullspawndata)-1); i += 2) {
		switch (argv(i)) {
		case "pose":
			m_iPose = stoi(argv(i+1));
			break;
		case "body":
			m_iBody = stoi(argv(i+1)) + 1;
			break;
		case "skin":
			skin = stoi(argv(i+1));
			break;
		default:
			break;
		}
	}

	CBaseEntity::CBaseEntity();
	precache_model(m_oldModel);
	Respawn();
}
