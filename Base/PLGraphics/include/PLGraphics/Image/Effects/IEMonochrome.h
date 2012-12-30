/*********************************************************\
 *  File: IEMonochrome.h                                 *
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


#ifndef __PLGRAPHICS_IMAGEEFFECT_MONOCHROME_H__
#define __PLGRAPHICS_IMAGEEFFECT_MONOCHROME_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImageEffect.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image effect: Convert color to grayscale using "human eye formula" (red*0.299 + green*0.587 + blue*0.114)
*
*  @note
*    - The color format "ColorPalette" is not supported
*/
class IEMonochrome : public ImageEffect {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, IEMonochrome, "PLGraphics", PLGraphics::ImageEffect, "Image effect: Convert color to gray scale using \"human eye formula\" (red*0.299 + green*0.587 + blue*0.114)")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGRAPHICS_API IEMonochrome();

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~IEMonochrome();


	//[-------------------------------------------------------]
	//[ Public virtual ImageEffect functions                  ]
	//[-------------------------------------------------------]
	public:
		PLGRAPHICS_API virtual bool Apply(ImageBuffer &cBuffer) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECT_MONOCHROME_H__
