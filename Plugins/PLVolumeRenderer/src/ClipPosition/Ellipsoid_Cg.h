/*********************************************************\
 *  File: Ellipsoid_Cg.h                                 *
 *      Fragment shader source code - Cg
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the �Software�), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


// Template version
static const PLCore::String sSourceCode_Fragment_Template = STRINGIFY(
// Uniforms
uniform float4x4 VolumeSpaceToClipEllipsoidSpace_x_;	// Volume space to clip ellipsoid space matrix
uniform bool     InvertClipping_x_;						// Invert clipping?

/**
*  @brief
*    Performs an clipping operation on the given position
*
*  @param[in] Position
*    Position inside the volume to perform clipping on, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    'true' if the given position was clipped, else 'false' if the given position survived the clipping operation
*/
bool ClipPosition_x_(float3 Position)
{
	// Transform the given volume space position into clip ellipsoid space
	float3 position = mul(VolumeSpaceToClipEllipsoidSpace_x_, float4(Position, 1.0)).xyz;

	// In clip ellipsoid space, the clip ellipsoid is centered and has a radius of 0.5 along each axis (... and is actually just a simple sphere :)

	// Does the given position survive the clipping operation or is it clipped away?
	bool clipPosition = (length(position) < 0.5);
	return InvertClipping_x_ ? !clipPosition : clipPosition;
}
);	// STRINGIFY

// None-template version
static const PLCore::String sSourceCode_Fragment = sSourceCode_Fragment_Template + '\n' + STRINGIFY(
bool ClipPosition(float3 Position)
{
	// Call the function version also used by the template
	return ClipPosition_x_(Position);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
