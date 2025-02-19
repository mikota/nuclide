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

/*!QUAKED func_illusionary (0 .5 .8) ?
# OVERVIEW
Brush that lets light to pass through it and is non-solid.

# KEYS
- "targetname" : Name

# NOTES
On idTech 2 BSPs, it will change texture variants when triggered.

# TRIVIA
This entity was introduced in Quake (1996).
*/
class
func_illusionary:NSRenderableEntity
{
public:
	void func_illusionary(void);

#ifdef SERVER
	virtual void Respawn(void);
	virtual float SendEntity(entity,float);
	virtual void Trigger(entity, triggermode_t);
#else
	virtual void Init(void);
#endif
};

#ifdef SERVER
/* we're overriding SendEntity so that we don't network func_illusionarys
 * without a targetname. They'll never experience gameplay changes
 * and therefore can be handled fully client-side */
float
func_illusionary::SendEntity(entity pvsent, float fl)
{
	if ((GetRenderMode() != RM_NORMAL) || HasTargetname())
		return super::SendEntity(pvsent, fl);
	else
		return (0);
}

void
func_illusionary::Trigger(entity act, triggermode_t state)
{
	switch (state) {
	case TRIG_OFF:
		SetSkin(0);
		break;
	case TRIG_ON:
		SetSkin(1);
		break;
	default:
		SetSkin(1-skin);
	}
}

void
func_illusionary::Respawn(void)
{
	/* reset the visual parameters */
	super::Respawn();

	/* func_illusionary specifics */
	SetMovetype(MOVETYPE_NONE);
	SetSolid(SOLID_NOT);
	SetModel(GetSpawnModel());
	SetOrigin(GetSpawnOrigin());
	SetSkin(0);
	ClearAngles();

	// TODO: Add support for (skin) -1 = Empty, -7 = Volumetric light
	if (GetSkin() < 0) {
		SetSkin(0);
	}
}
#else

void
func_illusionary::Init(void)
{
	super::Init();

	/* this entity is being controlled by the server, remove it */
	if ((GetRenderMode() != RM_NORMAL) || (targetname)) {
		Destroy();
		return;
	}

	precache_model(model);
	SetModel(model);
	SetOrigin(origin);
	SetAngles([0,0,0]);
	SetMovetype(MOVETYPE_NONE);
	SetSolid(SOLID_NOT);

	if (skin == -1 && m_iRenderMode == RM_TEXTURE)
		Hide();

	MakeStatic();
}
#endif

void
func_illusionary::func_illusionary(void)
{
#ifdef CLIENT
	isCSQC = true;
#endif
}
