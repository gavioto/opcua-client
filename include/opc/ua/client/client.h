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

#ifndef CLIENT_H
#define CLIENT_H



#include <opc/common/application.h>
#include <opc/ua/node.h>


namespace OpcUa
{
  namespace Client
  {

    class Client
    {
        public:
            Client(){} 
            //Client(const std::string& configDir){this->configPath = configDir;} 
            //~Client(){disconnect();}
            void Connect(); 
            //void CreateSession();  //Shoudl also be exposed
            void Disconnect(); 

            void  SetSessionName(const std::string& str) { sessionName = str; }
            std::string  GetSessionName() { return sessionName; }
            std::string  GetURI() { return m_uri; }
            void SetURI(std::string uri) { m_uri = uri; }

            std::string  GetEndpoint() { return endpoint; }
            void SetEndpoint(std::string endpoint) { this->endpoint = endpoint; }
            void SetSecurityPolicy(std::string sec) {security_policy = sec;}
            std::string  GetSecurityPolicy() { return security_policy; }

            Node GetRootNode(); 
            Node GetObjectsNode();
            Node GetNode(NodeID nodeid); 

        protected:
            OpcUa::Remote::Server* server;
            OpcUa::Application::UniquePtr application;
            std::string  endpoint = "opc.tcp:://localhost:4841";
            std::string  sessionName = "Open source OPC-UA Client Session";
            std::string  m_uri = "https://github.com/treww/opc_layer.git";
            std::string  configPath=".";
            std::string security_policy = "none";
        };





  } //name space client
} // namespace OpcUa

#endif
