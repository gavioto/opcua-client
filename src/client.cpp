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
#include <opc/common/node.h>
#include <opc/common/uri_facade.h>
#include <opc/ua/computer.h>








namespace OpcUa
{
    namespace Client
    {
        void Client::connect(const std::string &endpoint)
        {
            //Load condfiguration
            //const std::string configDir = configPath;
            //const Common::ModulesConfiguration& configuration = Common::ParseConfigurationFiles(configDir);
            Common::ModulesConfiguration configuration;
            //Depending on endpoint we should load correct modules. Currently we only support opc.tcp anyway
            std::cout << "Loading modules" << std::endl;
            Common::ModuleConfiguration moduleConfig;
            moduleConfig.ID = "opc.tcp";
            moduleConfig.Path = "libopc_tcp_client.so";
            configuration.push_back(moduleConfig);
            //Now start application
            application = OpcUa::CreateApplication();
            std::vector<Common::AddonInformation> infos(configuration.size()); 
            std::transform(configuration.begin(), configuration.end(), infos.begin(), std::bind(&Common::GetAddonInfomation, std::placeholders::_1));
            application->Start(infos);


            const Common::Uri uri(endpoint);
            const OpcUa::Client::Addon::SharedPtr addon = application->GetAddonsManager().GetAddon<OpcUa::Client::Addon>(uri.Scheme());
            //std::shared_ptr<OpcUa::Client::Addon> addon = application->GetAddonsManager().GetAddon<OpcUa::Client::Addon>(uri.Scheme());
            this->server = addon->Connect(endpoint);

            OpcUa::Remote::SessionParameters session;
            session.ClientDescription.URI = m_uri;
            session.ClientDescription.ProductURI = m_uri;
            session.ClientDescription.Name.Text = sessionName;
            session.ClientDescription.Type = OpcUa::ApplicationType::CLIENT;
            session.SessionName = sessionName;
            session.EndpointURL = endpoint;
            session.Timeout = 1200000;

            server->CreateSession(session);
            server->ActivateSession();

      }

        void Client::disconnect()
        {
            std::cout << "closing session" << std::endl;
            server->CloseSession(); 
            application->Stop(); 
            std::cout << "finished" << std::endl;
        }

        Node Client::GetNode(NodeID nodeid)
        {
            return Node(server, nodeid);
        }

        Node Client::GetRootNode()
        {
            return Node(server, OpcUa::ObjectID::RootFolder);
        }

        Node Client::GetObjectsNode()
        {
            return Node(server, OpcUa::ObjectID::ObjectsFolder);
        }
  }
}
