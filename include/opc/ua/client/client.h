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
#include <opc/common/node.h>


namespace OpcUa
{
  namespace Client
  {

    class Client
    {
        public:
            Client(){} 
            Client(const std::string& configDir){this->configPath = configDir;} 
            //~Client(){disconnect();}

            void connect( const std::string& endpoint ); 
            void createSession(); 
            void disconnect(); 

            void  SetSessionName(const std::string& str) { sessionName = str; }
            std::string  GetSessionName() { return sessionName; }
            std::string  GetURI() { return m_uri; }
            void  SetURI(std::string uri) { m_uri = uri; }

            std::string  GetEndpoint() { return endpoint; }
            std::string  secPolicy() { return "None"; }
            // Used messages mode for the secure channel, allowed: MS_None, MS_Sign, MS_SignAndEncrypt
            //int secMessMode() { return MS_None; }

            Node GetRootNode(); 
            Node GetObjectsNode();
            Node GetNode(NodeID nodeid); 

        private:
            OpcUa::Remote::Computer::SharedPtr server;
            OpcUa::Application::UniquePtr application;
            std::string  endpoint;
            std::string  sessionName = "Open source OPC-UA Client Session";
            std::string  m_uri = "https://github.com/treww/opc_layer.git";
            std::string  configPath=".";
        };





  } //name space client
} // namespace OpcUa

#endif
