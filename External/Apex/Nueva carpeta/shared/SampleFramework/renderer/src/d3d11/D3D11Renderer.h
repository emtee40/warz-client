/*
 * Copyright 2009-2011 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
#ifndef D3D11_RENDERER_H
#define D3D11_RENDERER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <Renderer.h>
#include <vector>
#include <tuple>

#if defined(RENDERER_DEBUG)
//#define D3D_DEBUG_INFO 1
#endif

#define RENDERER_ENABLE_VFACE_SCALE          1
#define RENDERER_ENABLE_SHADOWS              0

#if RENDERER_ENABLE_SINGLE_PASS_LIGHTING
#define RENDERER_MAX_LIGHTS 4
#else
#define RENDERER_MAX_LIGHTS 1
#endif

#define INITGUID
#pragma warning(push)
// Disable macro redefinition warnings
#pragma warning(disable: 4005)
#include <d3d11.h>
#pragma warning(pop)
#include <xnamath.h>
#undef INITGUID

namespace SampleRenderer
{
class RendererDesc;
class RendererColor;

void convertToD3D11(XMFLOAT3& dxcolor, const RendererColor& color);
void convertToD3D11(XMFLOAT4& dxcolor, const RendererColor& color);
void convertToD3D11(XMFLOAT3& dxvec,   const PxVec3& vec);
void convertToD3D11(XMFLOAT4X4& dxmat, const physx::PxMat44& mat);
void convertToD3D11(XMFLOAT4X4& dxmat, const RendererProjection& mat);
void convertToD3D11(XMMATRIX& dxmat,   const physx::PxMat44& mat);
void convertToD3D11(XMMATRIX& dxmat,   const RendererProjection& mat);

class D3D11RendererVariableManager;
class D3D11RendererResourceManager;
class D3D11RendererResource;
class D3D11RendererMaterial;
class D3D11RendererMesh;
class D3D11RendererVertexBuffer;
class D3D11RendererIndexBuffer;
class D3D11RendererTexture2D;

class D3DX11;

class D3D11Renderer : public Renderer
{
	friend class D3D11RendererResource;
	friend class D3D11RendererMesh;
public:
	class D3D11ShaderEnvironment
	{
		friend class D3D11Renderer;
		friend class D3D11RendererSpotLight;
		friend class D3D11RendererDirectionalLight;

	public:
		D3D11ShaderEnvironment();

		void bindFrame() const;
		void bindLight(PxU32 lightIndex = 0) const;
		void bindModel() const;
		void bindBones() const;
		void bindFogState() const;
		void bindAmbientState() const;
		void bindVFaceScale() const;

		void reset();

	protected:
		XMFLOAT4X4 modelMatrix;
		XMFLOAT4X4 modelViewMatrix;
		XMFLOAT4X4 modelViewProjMatrix;

		XMFLOAT4X4 viewMatrix;
		XMFLOAT4X4 projMatrix;
		XMFLOAT4X4 invViewProjMatrix;
		XMFLOAT4X4 lightShadowMatrix;

		XMFLOAT4X4 boneMatrices[RENDERER_MAX_BONES];
		PxU32      numBones;

		XMFLOAT4   fogColorAndDistance;

		XMFLOAT3   eyePosition;
		XMFLOAT3   eyeDirection;

		XMFLOAT3   ambientColor;

		XMFLOAT3   lightColor[RENDERER_MAX_LIGHTS];
		XMFLOAT3   lightDirection[RENDERER_MAX_LIGHTS];
		XMFLOAT3   lightPosition[RENDERER_MAX_LIGHTS];
		float      lightIntensity[RENDERER_MAX_LIGHTS];
		float      lightInnerRadius[RENDERER_MAX_LIGHTS];
		float      lightOuterRadius[RENDERER_MAX_LIGHTS];
		float      lightInnerCone[RENDERER_MAX_LIGHTS];
		float      lightOuterCone[RENDERER_MAX_LIGHTS];
		int        lightType[RENDERER_MAX_LIGHTS];
		mutable int numLights;

		D3D11RendererTexture2D*   lightShadowMap;

		float              vfs;

		D3D11RendererVariableManager* constantManager;
	};

public:
	D3D11Renderer(const RendererDesc& desc, const char* assetDir);
	virtual ~D3D11Renderer(void);

	ID3D11Device*                 getD3DDevice(void) { return m_d3dDevice;	}
	ID3D11DeviceContext*          getD3DDeviceContext(void) { return m_d3dDeviceContext; }
	D3DX11*                       getD3DX11(void) { return m_d3dx; }
	D3D11ShaderEnvironment&       getShaderEnvironment(void) { return m_environment; }
	const D3D11ShaderEnvironment& getShaderEnvironment(void) const { return m_environment; }
	D3D11RendererResourceManager* getResourceManager(void) { return m_resourceManager; }
	D3D11RendererVariableManager* getVariableManager(void) { return m_constantManager; }

	bool multisamplingEnabled(void) const;
	bool tessellationEnabled(void) const;
	bool isTessellationSupported(void) const;

private:
	bool checkResize(bool resetDevice);

public:
	void onDeviceLost(void);
	void onDeviceReset(void);

public:
	// clears the offscreen buffers.
	virtual void clearBuffers(void);

	// presents the current color buffer to the screen.
	// returns true on device reset and if buffers need to be rewritten.
	virtual bool swapBuffers(void);

	// get the device pointer (void * abstraction)
	virtual void* getDevice()
	{
		return static_cast<void*>(getD3DDevice());
	}

	// get the window size
	void getWindowSize(PxU32& width, PxU32& height) const;

	// gets a handle to the current frame's data, in bitmap format
	//    note: subsequent calls will invalidate any previously returned data
	//    return true on successful screenshot capture
	bool captureScreen(PxU32 &width, PxU32& height, PxU32& sizeInBytes, const void*& screenshotData);

	D3D_FEATURE_LEVEL getFeatureLevel() const { return (D3D_FEATURE_LEVEL)m_d3dDeviceFeatureLevel; }

	virtual RendererVertexBuffer*   createVertexBuffer(const RendererVertexBufferDesc&   desc);
	virtual RendererIndexBuffer*    createIndexBuffer(const RendererIndexBufferDesc&    desc);
	virtual RendererInstanceBuffer* createInstanceBuffer(const RendererInstanceBufferDesc& desc);
	virtual RendererTexture2D*      createTexture2D(const RendererTexture2DDesc&      desc);
	virtual RendererTexture3D*      createTexture3D(const RendererTexture3DDesc&      desc);
	virtual RendererTarget*         createTarget(const RendererTargetDesc&         desc);
	virtual RendererMaterial*       createMaterial(const RendererMaterialDesc&       desc);
	virtual RendererMesh*           createMesh(const RendererMeshDesc&           desc);
	virtual RendererLight*          createLight(const RendererLightDesc&          desc);

	virtual void                    setVsync(bool on);

	virtual bool                    initTexter();
	virtual void                    closeTexter();

	void                            bind(RendererMaterialInstance* materialInstance);

private:
	virtual bool beginRender(void);
	virtual void endRender(void);
	virtual void bindViewProj(const physx::PxMat44& eye, const RendererProjection& proj);
	virtual void bindFogState(const RendererColor& fogColor, float fogDistance);
	virtual void bindAmbientState(const RendererColor& ambientColor);
	virtual void bindDeferredState(void);
	virtual void bindMeshContext(const RendererMeshContext& context);
	virtual void beginMultiPass(void);
	virtual void endMultiPass(void);
	virtual void beginTransparentMultiPass(void);
	virtual void endTransparentMultiPass(void);
	virtual void renderDeferredLight(const RendererLight& light);
	virtual PxU32 convertColor(const RendererColor& color) const;

	virtual bool isOk(void) const;
	
	virtual	void setupTextRenderStates();
	virtual	void resetTextRenderStates();
	virtual	void renderTextBuffer(const void* vertices, PxU32 nbVerts, const PxU16* indices, PxU32 nbIndices, RendererMaterial* material);
	virtual	void renderLines2D(const void* vertices, PxU32 nbVerts);
	virtual	void setupScreenquadRenderStates();
	virtual	void resetScreenquadRenderStates();

public:
	enum BlendState
	{
		BLEND_DEFAULT = 0,
		BLEND_MULTIPASS,
		BLEND_TRANSPARENT,
		BLEND_TRANSPARENT_ALPHA_COVERAGE,
		NUM_BLEND_STATES
	};
	void setBlendState(BlendState state = BLEND_DEFAULT);

	void setRasterizerState(D3D11_FILL_MODE = D3D11_FILL_SOLID, D3D11_CULL_MODE = D3D11_CULL_BACK, PxI32 depthBias = 0);

	enum DepthStencilState
	{
		DEPTHSTENCIL_DEFAULT = 0,
		DEPTHSTENCIL_DISABLED,
		DEPTHSTENCIL_TRANSPARENT,
		NUM_DEPTH_STENCIL_STATES
	};
	void setDepthStencilState(DepthStencilState state);

	enum StateType
	{
		STATE_BLEND,
		STATE_DEPTHSTENCIL,
		STATE_RASTERIZER,
		NUM_STATE_TYPES
	};
	void pushState(StateType stateType);
	void popState(StateType stateType);

	void setTessellationState();

private:
	void addResource(D3D11RendererResource& resource);
	void removeResource(D3D11RendererResource& resource);
	void notifyResourcesLostDevice(void);
	void notifyResourcesResetDevice(void);

private:
	PxU32                            m_displayWidth;
	PxU32                            m_displayHeight;
	ID3DBlob*                        m_displayBuffer;
	bool                             m_vsync;
	PxI32                            m_multipassDepthBias;

	IDXGIFactory*                    m_d3d;
	IDXGISwapChain*                  m_d3dSwapChain;

	ID3D11BlendState*                m_d3dBlendStates[NUM_BLEND_STATES];
	ID3D11Device*                    m_d3dDevice;
	ID3D11DeviceContext*             m_d3dDeviceContext;
	PxU32                            m_d3dDeviceFeatureLevel;
	ID3D11Texture2D*                 m_d3dDepthStencilBuffer;
	ID3D11DepthStencilView*          m_d3dDepthStencilView;
	ID3D11DepthStencilState*         m_d3dDepthStencilStates[NUM_DEPTH_STENCIL_STATES];
	ID3D11Texture2D*                 m_d3dRenderTargetBuffer;
	ID3D11RenderTargetView*          m_d3dRenderTargetView;

	std::tr1::tuple<D3D11_FILL_MODE, D3D11_CULL_MODE, int> m_boundRasterizerStateKey;

	RendererMaterialInstance*        m_boundMaterial;

	std::vector<D3D11RendererMesh*>         m_textMeshes;
	std::vector<D3D11RendererVertexBuffer*> m_textVertices;
	std::vector<D3D11RendererIndexBuffer*>  m_textIndices;
	PxU32                                   m_currentTextMesh;
	D3D11RendererMesh*               m_linesMesh;
	D3D11RendererVertexBuffer*       m_linesVertices;

	DXGI_SWAP_CHAIN_DESC             m_swapChainDesc;
	physx::PxMat44					 m_viewMatrix;

	// non-managed resources...
	std::vector<D3D11RendererResource*> m_resources;

	D3DX11*                             m_d3dx;
	D3D11ShaderEnvironment              m_environment;
	D3D11RendererVariableManager*       m_constantManager;
	D3D11RendererResourceManager*       m_resourceManager;
};

class D3D11RendererResource
{
	friend class D3D11Renderer;
public:
	D3D11RendererResource(void)
	{
		m_d3dRenderer = 0;
	}

	virtual ~D3D11RendererResource(void)
	{
		if (m_d3dRenderer)
		{
			m_d3dRenderer->removeResource(*this);
		}
	}

public:
	virtual void onDeviceLost(void) = 0;
	virtual void onDeviceReset(void) = 0;

private:
	D3D11Renderer* m_d3dRenderer;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
