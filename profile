#*********************************************************#
#*  File: profile                                        *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


# This script can be used to set the path to the local (not installed)
# PixelLight runtime, which is stored in the environment variable
# PL_RUNTIME. If that variable is set, it will be prefered by the
# PixelLight runtime and used instead of searching for an installed
# runtime in /usr/ or /usr/local/.
# 
# Please note that this script must be 'sources' rather than invoked directly,
# in order to export the variables to the current shell. Also make sure that
# the current directory is the root directory of the PixelLight source
# tree, otherwise the path will be wrong.
#
# Execute this script:
#   source ./profile     (OR:)
#   . ./profile

# Detect the used OS
if [ $OSTYPE == "linux-gnu" ] ; then
	PLATFORM="Linux"
elif [ $OSTYPE == "darwin10.0" ] ; then
	PLATFORM="MacOSX"
elif [ $OSTYPE == "darwin11" ] ; then
	PLATFORM="MacOSX"
else
	PLATFORM="Unknown"
fi

# Export the environment variable pointing to the PixelLight runtime directory
export PL_RUNTIME="$PWD/Bin-$PLATFORM/Runtime/x86"

# Print the value of the environment variable
echo "PixelLight runtime variable set to:"
echo "  PL_RUNTIME = '$PL_RUNTIME'"
