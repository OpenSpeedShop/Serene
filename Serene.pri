# This file is part of the Serene 3D Graphing Library
# Copyright (C) 2010-2011 Argo Navis Technologies, LLC
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

QT += core gui opengl
LIBRARY_TARGET = Serene

#################
# INSTALL PATHS #
#################
!isEmpty($${SOURCEDIR}): SOURCE_PATH = $${SOURCEDIR}
isEmpty(SOURCE_PATH): SOURCE_PATH = $$quote($${PWD})

!isEmpty($${BUILDDIR}): BUILD_PATH = $${BUILDDIR}
isEmpty(BUILD_PATH): BUILD_PATH = $$quote($${PWD})

#########################
# DEBUG/RELEASE POSTFIX #
#########################
win32 {
  CONFIG(debug, debug|release): POSTFIX = $$quote(debug)
  else: POSTFIX = $$quote(release)
}
