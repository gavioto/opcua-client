/******************************************************************************
 *   Copyright (C) 2014-2014 by Sintef Raufoss Manufacturing                  *
 *   olivier.roulet@gmail.com                  *
 *                                          *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as          *
 *   published by the Free Software Foundation; version 3 of the License.     *
 *                                          *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.              *
 *                                          *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the                  *
 *   Free Software Foundation, Inc.,                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
 ******************************************************************************/


#pragma once

//#include <opc/ua/client/addon.h>
#include <opc/common/application.h>
#include <opc/ua/node.h>


namespace OpcUa
{
  class RemoteClient
  {
  public:
    RemoteClient();
    explicit RemoteClient(const std::string& endpoint);
    ~RemoteClient();

    RemoteClient(const RemoteClient&&) = delete;
    RemoteClient(const RemoteClient&) = delete;
    RemoteClient& operator=(const RemoteClient&) = delete;

    void SetSessionName(const std::string& str) { SessionName = str; }
    std::string GetSessionName() const { return SessionName; }

    std::string GetURI() const { return Uri; }
    void SetURI(std::string uri) { Uri = uri; }

    std::string  GetEndpoint() const { return Endpoint; }
    void SetEndpoint(std::string endpoint) { Endpoint = endpoint; }

    void SetSecurityPolicy(std::string sec) {SecurityPolicy = sec;}
    std::string GetSecurityPolicy() const { return SecurityPolicy; }

    Node GetRoot() const;
    Node GetObjectsFolder() const;
    Node GetNode(NodeID nodeid) const;

  private:
    void Connect();
    void Disconnect();

  private:
    std::string Endpoint = "opc.tcp:://localhost:4841";
    std::string SessionName = "Open source OPC-UA Client Session";
    std::string Uri = "https://github.com/treww/opc_layer.git";
    std::string ConfigPath=".";
    std::string SecurityPolicy = "none";
    OpcUa::Remote::Server::SharedPtr Server;
    OpcUa::Application::UniquePtr Application;
  };

} // namespace OpcUa
