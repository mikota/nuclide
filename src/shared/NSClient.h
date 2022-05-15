/* both NSClientPlayer and base_NSClientSpectator are based off this class */
class
NSClient:NSSurfacePropEntity
{
	vector origin_net;
	vector velocity_net;

	NSXRSpace m_xrSpace;
	NSXRInput m_xrInputHead;
	NSXRInput m_xrInputLeft;
	NSXRInput m_xrInputRight;

	void(void) NSClient;

	/* final input handling of the client */
	virtual void(void) ClientInput;

	virtual void(void) PreFrame;
	virtual void(void) PostFrame;

	virtual bool(void) IsFakeSpectator;
	virtual bool(void) IsRealSpectator;
	virtual bool(void) IsDead;
	virtual bool(void) IsPlayer;

	virtual void(void) OnRemoveEntity;

#ifdef CLIENT
	/* gives the chance to override input variables before networking */
	virtual void(void) ClientInputFrame;

	/* our camera when we're alive */
	virtual void(void) UpdateAliveCam;

	/* our camera when we're dead */
	virtual void(void) UpdateDeathcam;

	/* our camera when we're in an intermission */
	virtual void(void) UpdateIntermissionCam;

	/* run every frame before renderscene() */
	virtual float(void) predraw;
#endif
};
