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


#include <opc/ua/client/addon.h>
#include <opc/ua/client/client.h>
#include <opc/common/addons_core/addon_manager.h>
#include <opc/common/addons_core/config_file.h>
#include <opc/common/application.h>
#include <opc/ua/node.h>
#include <opc/common/uri_facade.h>
#include <opc/ua/server.h>


namespace OpcUa
{
  RemoteClient::RemoteClient()
  {
    Connect();
  }

  RemoteClient::RemoteClient(const std::string& endpoint)
    : Endpoint(endpoint)
  {
    Connect();
  }

  RemoteClient::~RemoteClient()
  {
    try
    {
      Disconnect();
    }
    catch(const std::exception& exc)
    {
      std::cerr << exc.what() << std::endl;
    }
  }

  void RemoteClient::Connect()
  {
    //Load condfiguration
    //const std::string configDir = configPath;
    //const Common::ModulesConfiguration& configuration = Common::ParseConfigurationFiles(configDir);
    Common::ModulesConfiguration configuration;
    //Depending on endpoint we should load correct modules. Currently we only support opc.tcp anyway
    std::clog << "Loading modules" << std::endl;
    Common::ModuleConfiguration moduleConfig;
    moduleConfig.ID = "opc.tcp";
    configuration.push_back(moduleConfig);
    moduleConfig.Path = "libopc_tcp_client.so";
    //Now start application
    Application = OpcUa::CreateApplication();
    std::vector<Common::AddonInformation> infos(configuration.size());
    std::transform(configuration.begin(), configuration.end(), infos.begin(), std::bind(&Common::GetAddonInfomation, std::placeholders::_1));
    Application->Start(infos);

    const Common::Uri uri(Endpoint);
    const OpcUa::Client::Addon::SharedPtr addon = Application->GetAddonsManager().GetAddon<OpcUa::Client::Addon>(uri.Scheme());
    Server = addon->Connect(Endpoint);

    OpcUa::Remote::SessionParameters session;
    session.ClientDescription.URI = Uri;
    session.ClientDescription.ProductURI = Uri;
    session.ClientDescription.Name.Text = SessionName;
    session.ClientDescription.Type = OpcUa::ApplicationType::CLIENT;
    session.SessionName = SessionName;
    session.EndpointURL = Endpoint;
    session.Timeout = 1200000;

    Server->CreateSession(session);
    Server->ActivateSession();
  }

  void RemoteClient::Disconnect()
  {
    std::clog << "closing session" << std::endl;
    Server->CloseSession();
    Server.reset();
    Application->Stop();
    std::clog << "finished" << std::endl;
  }

  Node RemoteClient::GetNode(NodeID nodeId) const
  {//FIXME: the validity check might have to be put in node code....
    Node node(Server, nodeId);
    Variant var = node.GetAttribute(OpcUa::AttributeID::BROWSE_NAME);
    if (var.Type == OpcUa::VariantType::QUALIFIED_NAME)
    {
      QualifiedName qn = var.Value.Name.front();
      return Node(Server, nodeId, qn);
    }
    return Node(Server); //Root node. TODO: exception!
  }

  Node RemoteClient::GetRoot() const
  {
    return Node(Server);
  }

  Node RemoteClient::GetObjectsFolder() const
  {
    return Node(Server, OpcUa::ObjectID::ObjectsFolder);
  }

} // namespace OpcUa

