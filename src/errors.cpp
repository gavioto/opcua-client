/******************************************************************************
 *   Copyright (C) 2013-2014 by Alexander Rykovanov                        *
 *   rykovanov.as@gmail.com                                                   *
 *                                                                            *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; version 3 of the License.     *
 *                                                                            *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/

#include "errors.h"

#include <opc/common/modules.h>

#define OPCUA_CLIENT_ERROR_CODE(code) ERROR_CODE(Common::MODULE_OPCUA_CLIENT, code)
#define OPCUA_CLIENT_ERROR(name, code, message) Common::ErrorData name(OPCUA_CLIENT_ERROR_CODE(code), message)

OPCUA_CLIENT_ERROR(SizeOfReceivedMessageInvalid, 1, "It was received message with invalid data size %1% but expected %2%.");
