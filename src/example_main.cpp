/// @author Alexander Rykovanov 2013
/// @email rykovanov.as@gmail.com
/// @brief Remote Computer implementaion.
/// @license GNU GPL
///
/// Distributed under the GNU GPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/gpl.html)
///


#include <iostream>
#include <opc/common/node.h>

#include <stdexcept>

#include <opc/ua/client/client.h>

int main(int argc, char** argv)
{
  try
  {
      OpcUa::Client::Client clt;
      std::cout << "Connecting" << std::endl;
      clt.connect("opc.tcp://192.168.56.101:48030");
      //std::cout << "Connected" << std::endl;
      //sleep(2);
      //std::cout << "stop sleep" << std::endl;
      //std::cout <<  "endpoints" << clt.server->Endpoints() << std::endl;

      OpcUa::Node objects = clt.GetObjectsNode();

      std::cout << "Objects node is: " << objects << std::endl;
      for (OpcUa::Node node : objects.Browse())
      {
          std::cout << "Child id: " << node << std::endl;
      }
      OpcUa::Node serv = objects.FindChildNode("Server");
      if (serv) {
          std::cout << "Serv is: " << serv << std::endl;
        OpcUa::Node nsnode = serv.FindChildNode("NamespaceArray");
        if (nsnode) {
          std::cout << "namspacearrar is: " << nsnode << std::endl;
            OpcUa::Variant ns  = nsnode.ReadValue();
            for (std::string d : ns.Value.String) {
                std::cout << "ns is: "  << d << std::endl;
            }
        }
        OpcUa::Node node = serv.FindChildNode("ServiceLevel");
        if (nsnode) {
          std::cout << "ServiceLevel is: " << node << std::endl;
            OpcUa::Variant ns  = node.ReadValue();
            for (uint d : ns.Value.Byte) {

                std::cout << "ServiceLevel is: "  << d << std::endl;
            }
        }

      }
      //sleep(4);

      //std::cout << "Disconnecting" << std::endl;
      clt.disconnect();
      return 0;
  }
  catch (const std::exception& exc)
  {
    std::cout << exc.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown error." << std::endl;
  }
  return -1;
}

