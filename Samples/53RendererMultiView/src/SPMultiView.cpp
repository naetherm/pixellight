/*********************************************************\
 *  File: SPMultiView.cpp                                *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Timing.h>
#include <PLMath/Rectangle.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLMesh/MeshManager.h>
#include "SPMultiView.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPMultiView)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPMultiView::SPMultiView(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_fRotation(0.0f),
	m_pMeshManager(new MeshManager(GetRenderer())),
	m_pMeshHandlerSphere(new MeshHandler()),
	m_pMeshHandlerTorus(new MeshHandler()),
	m_pMeshHandlerCube(new MeshHandler())
{
	// Create the meshes

	// Get/create the 'sphere' mesh
	m_pMeshHandlerSphere->SetMesh(m_pMeshManager->CreateMesh("PLMesh::MeshCreatorSphere", true, "Radius=\"1.0\""));

	// Get/create the 'torus' mesh
	m_pMeshHandlerTorus->SetMesh(m_pMeshManager->CreateMesh("PLMesh::MeshCreatorTorus", true, "Sides=\"15\" Rings=\"20\""));

	// Get/create the 'cube' mesh
	m_pMeshHandlerCube->SetMesh(m_pMeshManager->CreateMesh("PLMesh::MeshCreatorCube", true, "Dimension=\"1.0 1.0 1.0\""));
}

/**
*  @brief
*    Destructor
*/
SPMultiView::~SPMultiView()
{
	// Destroy our mesh handlers
	delete m_pMeshHandlerSphere;
	delete m_pMeshHandlerTorus;
	delete m_pMeshHandlerCube;

	// Destroy our mesh manager
	delete m_pMeshManager;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPMultiView::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Get the current viewport settings
	const uint32 nWidth  = static_cast<uint32>(cRenderer.GetViewport().GetWidth());
	const uint32 nHeight = static_cast<uint32>(cRenderer.GetViewport().GetHeight());
	float fMinZ, fMaxZ;
	cRenderer.GetViewport(&fMinZ, &fMaxZ);

	// Enable scissor rectangle test
	cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);

	{ // Viewport 1 (red)
		// Setup viewport and reset scissor rectangle
		const Rectangle cRect(0.0f, 0.0f, static_cast<float>(nWidth/2), static_cast<float>(nHeight));
		cRenderer.SetViewport(&cRect, fMinZ, fMaxZ);
		cRenderer.SetScissorRect();

		// Clear the content of the current used render target
		cRenderer.Clear(Clear::Color | Clear::ZBuffer, Color4::Red);

		// Draw scene
		DrawScene(0);
	}

	{ // Viewport 2 (green)
		// Setup viewport and reset scissor rectangle
		const Rectangle cRect(static_cast<float>(nWidth/2), 0.0f, static_cast<float>(nWidth), static_cast<float>(nHeight));
		cRenderer.SetViewport(&cRect, fMinZ, fMaxZ);
		cRenderer.SetScissorRect();

		// Clear the content of the current used render target
		cRenderer.Clear(Clear::Color | Clear::ZBuffer, Color4::Green);

		// Draw scene
		DrawScene(1);
	}

	{ // Viewport 3 (blue)
		// Setup viewport and reset scissor rectangle
		const float fX = static_cast<float>(nWidth/2-100);
		const float fY = static_cast<float>(nHeight/2-100);
		const Rectangle cRect(fX, fY, fX+200.0f, fY+200.0f);
		cRenderer.SetViewport(&cRect, fMinZ, fMaxZ);
		cRenderer.SetScissorRect();

		// Clear the content of the current used render target
		cRenderer.Clear(Clear::Color | Clear::ZBuffer, Color4::Blue);

		// Draw scene
		DrawScene(2);
	}

	// Increase the rotation by the current time difference (time past since the last frame)
	// -> Normally, such work should NOT be performed within the rendering step, but we want
	//    to keep the implementation simple in here...
	m_fRotation -= Timing::GetInstance()->GetTimeDifference()*100;
}
