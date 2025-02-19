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

var int autocvar_r_skipGlows = 0;
var int autocvar_r_skipLensFlares = 0;

/*!QUAKED env_glow (1 .5 0) (-8 -8 -8) (8 8 8) EVGLOW_ORIENT
# OVERVIEW
Client-side glare/glow orb effect like the flares in 1997's Unreal.

# KEYS
- "shader" : Material to use for the glare/glow effect.
- "model" : Sprite model to use for the glare/glow (idTech 2 BSPs only)
- "scale" : Scale multiplier.
- "rendercolor" : Material color override in RGB8.
- "renderamt" : Material alpha override in A8.

# SPAWNFLAGS
- EVGLOW_ORIENT (1) : TODO: Glow is an oriented sprite when set.

# TRIVIA
This entity was introduced in Half-Life (1998).
*/
class env_glow:NSEntity /* TODO: change to renderablentity? */
{
public:
	void env_glow(void);

	virtual void Spawned(void);
	virtual void Respawn(void);
	virtual float predraw(void);
	virtual void postdraw(void);
	virtual void SpawnKey(string,string);
	virtual void RendererRestarted(void);
	virtual bool CanSpawn(bool);

private:
	vector m_vecColor;
	float m_flAlpha;
	float m_flMaxAlpha;
	string m_strSprite;
	vector m_vecSize;
	float m_flScale;

	vector m_vecRotate;
	vector m_vecOrientation;

	nonvirtual bool IsVisible(vector);
	nonvirtual void RenderGlow(vector, vector);
};

bool
env_glow::IsVisible(vector vecPlayer)
{
	entity oother = other;

	if (autocvar_r_skipGlows)
		return (false);

	if (checkpvs(vecPlayer, this) == FALSE)
		return (false);

	other = world;
	traceline(this.origin, vecPlayer, MOVE_OTHERONLY, this);
	other = oother;

	/* If we can't trace against the player, or are two close, fade out */
	if (trace_fraction < 1.0f || vlen(origin - vecPlayer) < 128)
		m_flAlpha = m_flAlpha - frametime;
	else
		m_flAlpha = m_flAlpha + frametime;

	m_flAlpha = bound(0.0f, m_flAlpha, 1.0f);

	if (m_flAlpha <= 0.0f)
		return (false);

	return (true);
}

bool
env_glow::CanSpawn(bool clientSide)
{
	return true;
}

void env_sun_lensflare(vector, float, vector);
void
env_glow::postdraw(void)
{
	if (!autocvar_r_skipLensFlares)
		env_sun_lensflare(origin, m_flAlpha, m_vecColor);
}

void
env_glow::RendererRestarted(void)
{
	if (!model && m_strSprite) {
		precache_pic(m_strSprite);
		m_vecSize = drawgetimagesize(m_strSprite) / 2;
	} else {
		precache_model(model);
		m_strSprite = spriteframe(model, 0, 0.0f);
		m_vecSize = drawgetimagesize(m_strSprite) / 2;
	}

	if (HasSpawnFlags(1)) {
		hitcontentsmaski = CONTENTBIT_SOLID;
		decal_pickwall(this, origin);
		m_vecOrientation = vectoangles(g_tracedDecal.normal * -1);
	}
}

void
env_glow::RenderGlow(vector forg, vector fsize)
{
#ifndef FTE_QUADFIX
	R_BeginPolygon(m_strSprite, 1, 0);
	R_PolygonVertex(forg + v_right * fsize[0] - v_up * fsize[1],
		[1,1], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg - v_right * fsize[0] - v_up * fsize[1],
		[0,1], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg - v_right * fsize[0] + v_up * fsize[1],
		[0,0], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg + v_right * fsize[0] + v_up * fsize[1],
		[1,0], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_EndPolygon();
#else
	R_BeginPolygon(m_strSprite, 1, 0);
	R_PolygonVertex(forg + v_right * fsize[0] - v_up * fsize[1],
		[1,1], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg - v_right * fsize[0] - v_up * fsize[1],
		[0,1], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg - v_right * fsize[0] + v_up * fsize[1],
		[0,0], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_EndPolygon();
	R_BeginPolygon(m_strSprite, 1, 0);
	R_PolygonVertex(forg - v_right * fsize[0] - v_up * fsize[1],
		[0,1], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg - v_right * fsize[0] + v_up * fsize[1],
		[0,0], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_PolygonVertex(forg + v_right * fsize[0] + v_up * fsize[1],
		[1,0], m_vecColor * m_flMaxAlpha, m_flAlpha);
	R_EndPolygon();
#endif
}

float
env_glow::predraw(void)
{
	vector forg;
	vector fsize;
	vector vecPlayer = g_view.GetCameraOrigin();
	vector vecAngle = g_view.GetCameraAngle();
	float flDist = vlen(vecPlayer - origin);

	if (IsVisible(vecPlayer) == false)
		return (PREDRAW_NEXT);

	/* Scale the glow somewhat with the players distance */
	fsize = m_vecSize * m_flScale;
	fsize *= bound(1, flDist / 256, 4);

	/* Nudge this slightly towards the camera */
	makevectors(vectoangles(origin - vecPlayer));
	forg = origin + (v_forward * -16);

	if (HasSpawnFlags(1)) {
		vector above;
		makevectors(m_vecOrientation);
		above = origin + (v_forward * 16);

		/* we're aiming right down */
		if (above[2] > origin[2])
			makevectors(m_vecOrientation+[0, m_vecRotate[2],0]);
		else
			makevectors(m_vecOrientation+[0,0, m_vecRotate[2]]);
	} else {
		makevectors(vecAngle +[0, m_vecRotate[1], m_vecRotate[2]]);
	}

	RenderGlow(forg, fsize);

	return (PREDRAW_NEXT);
}

void
env_glow::SpawnKey(string strField, string strKey)
{
	switch (strField) {
	case "material":
	case "shader":
		model = __NULL__;
		m_strSprite = strKey;
		break;
	case "sprite":
	case "model":
		model = strKey;
		break;
	case "scale":
		m_flScale = stof(strKey);
		break;
	case "color":
		m_vecColor = stov(strKey);
		break;
	case "rendercolor":
	case "rendercolour":
		m_vecColor = stov(strKey) / 255;
		break;
	case "renderamt":
		m_flMaxAlpha = stof(strKey) / 255;
		break;
	case "rotate":
		m_vecRotate[2] = stof(strKey);
		break;
	case "rotate":
		break;
	default:
		super::SpawnKey(strField, strKey);
	}
}

void
env_glow::Respawn(void)
{
	SetSize([0,0,0], [0,0,0]);
	SetOrigin(GetSpawnOrigin());
	effects &= ~EF_NOSHADOW;
}

void
env_glow::Spawned(void)
{
	super::Spawned();
	RendererRestarted();
}

void
env_glow::env_glow(void)
{
	m_flScale = 1.0f;
	m_flMaxAlpha = 1.0f;
	m_vecColor = [1,1,1];
	drawmask = MASK_GLOWS;
	isCSQC = true;
}
