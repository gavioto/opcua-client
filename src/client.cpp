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
    namespace Client
    {
        void Client::Connect()
        {
            //Load condfiguration
            //const std::string configDir = configPath;
            //const Common::ModulesConfiguration& configuration = Common::ParseConfigurationFiles(configDir);
            Common::ModulesConfiguration modules;
            //Depending on endpoint we should load correct modules. Currently we only support opc.tcp anyway
            std::cout << "Loading modules" << std::endl;
            Common::ModuleConfiguration moduleConfig;
            moduleConfig.ID = "opc.tcp";
            moduleConfig.Path = "libopc_tcp_client.so";
            modules.push_back(moduleConfig);
            //Now start application
            //application = OpcUa::CreateApplication();
            std::transform(modules.begin(), modules.end(), std::back_inserter(infos), std::bind(&Common::GetAddonInfomation, std::placeholders::_1));
            //std::vector<Common::AddonInformation> infos(configuration.size()); 
            //std::transform(configuration.begin(), configuration.end(), infos.begin(), std::bind(&Common::GetAddonInfomation, std::placeholders::_1));
            addons = Common::CreateAddonsManager();
            for (const Common::AddonInformation& config : infos)
            {
              addons->Register(config);
            }
            addons->Start();


            const Common::Uri uri(endpoint);
            const OpcUa::Client::Addon::SharedPtr clt = addons->GetAddon<OpcUa::Client::Addon>(uri.Scheme());
            //clt = addons->GetAddon<OpcUa::Client::Addon>(uri.Scheme());
            //std::shared_ptr<OpcUa::Client::Addon> addon = application->GetAddonsManager().GetAddon<OpcUa::Client::Addon>(uri.Scheme());
            //Remote::Server::SharedPtr srv = clt->Connect(endpoint);
            sserver = clt->Connect(endpoint);
            //this->server = srv.get();
            server = sserver.get();
            //server = clt->Connect(endpoint).get();

            OpcUa::Remote::SessionParameters session;
            session.ClientDescription.URI = m_uri;
            session.ClientDescription.ProductURI = m_uri;
            session.ClientDescription.Name.Text = sessionName;
            session.ClientDescription.Type = OpcUa::ApplicationType::CLIENT;
            session.SessionName = sessionName;
            session.EndpointURL = endpoint;
            session.Timeout = 1200000;

            std::cout << "creating session" << std::endl;
            if (server == NULL){ std::cout << "Warning server is null!!!" << std::endl;}
            this->server->CreateSession(session);
            std::cout << "activating session" << std::endl;
            server->ActivateSession();

      }

        void Client::Disconnect()
        {
            std::cout << "closing session" << std::endl;
            server->CloseSession(); 
            addons->Stop(); 
            std::cout << "finished" << std::endl;
        }

        Node Client::GetNode(NodeID nodeid)
        {//FIXME: the validity check might have to be put in node code....
          Node node(server, nodeid);
          Variant var = node.Read(OpcUa::AttributeID::BROWSE_NAME); 
          if (var.Type == OpcUa::VariantType::QUALIFIED_NAME)
          {
            QualifiedName qn = var.Value.Name.front();
            node.SetBrowseNameCache(qn);
            return node;
          }
          return Node(server); //Null node
        }

        Node Client::GetRootNode()
        {
            if (server == NULL){ std::cout << "Warning server is null!!!" << std::endl;}
            return Node(server, OpcUa::ObjectID::RootFolder);
        }

        Node Client::GetObjectsNode()
        {
            return Node(server, OpcUa::ObjectID::ObjectsFolder);
        }
  }
}
