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

#ifndef PHYSICS_STATIC
#define FNCPHYBX_ASLEEP 4096

/*!QUAKED func_physbox (0 .5 .8) ? x x x x x x x x x x x x FNCPHYBX_ASLEEP
# OVERVIEW
Physics brush.

# KEYS
- "targetname" : Name

# TRIVIA
This entity was introduced in Half-Life 2 (2004).
*/
class
func_physbox:NSPhysicsEntity
{
public:
	void func_physbox(void);

	virtual void Respawn(void);
	virtual void SpawnKey(string, string);

};

void
func_physbox::func_physbox(void)
{
}

void
func_physbox::Respawn(void)
{
	NSPhysicsEntity::Respawn();

	if (HasSpawnFlags(FNCPHYBX_ASLEEP))
		PhysicsDisable();
	else
		PhysicsEnable();
}

void
func_physbox::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	default:
		NSPhysicsEntity::SpawnKey(strKey, strValue);
	}
}
#else
class func_physbox:NSSurfacePropEntity
{
	void(void) func_physbox;

	virtual void(void) Respawn;
	virtual void(void) Death;
};

void
func_physbox::func_physbox(void)
{
}

void
func_physbox::Death(void)
{
	Disappear();
}

void
func_physbox::Respawn(void)
{
	NSSurfacePropEntity::Respawn();
	health = GetSpawnHealth();
	SetTakedamage(DAMAGE_YES);
	SetSolid(SOLID_BBOX);
}
#endif
