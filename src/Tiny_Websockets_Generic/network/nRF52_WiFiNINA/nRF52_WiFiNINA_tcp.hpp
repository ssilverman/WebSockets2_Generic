/****************************************************************************************************************************
  nRF52_WiFiNINA_tcp.hpp
  For nRF52 boards with WiFiNINA module/shield.
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52, SAMD21/SAMD51, SAM DUE, Teensy, RP2040 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
  Version: 1.10.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      14/07/2020 Initial coding/porting to support nRF52 and SAMD21/SAMD51 boards. Add SINRIC/Alexa support
  ...
  1.9.0   K Hoang      30/11/2021 Auto detect ESP32 core version. Fix bug in examples
  1.9.1   K Hoang      17/12/2021 Fix QNEthernet TCP interface
  1.10.0  K Hoang      18/12/2021 Supporting case-insensitive headers, according to RFC2616
  1.10.1  K Hoang      26/02/2022 Reduce QNEthernet latency
 *****************************************************************************************************************************/
 
#pragma once

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
      

#include <Tiny_Websockets_Generic/internals/ws_common.hpp>
#include <Tiny_Websockets_Generic/network/tcp_client.hpp>
#include <Tiny_Websockets_Generic/network/tcp_server.hpp>
#include <Tiny_Websockets_Generic/network/generic_esp/generic_esp_clients.hpp>

#include <WiFiNINA_Generic.h>

namespace websockets2_generic
{
  namespace network2_generic
  {
    typedef GenericEspTcpClient<WiFiClient> WiFiNINATcpClient;

    class SecuredWiFiNINATcpClient : public GenericEspTcpClient<WiFiSSLClient> 
    {
      public:
        void setInsecure() 
        {
          // KH, to fix, for v1.0.0 only
          //this->client.setInsecure();
        }
    
        void setFingerprint(const char* fingerprint) 
        {
          (void) fingerprint;
          
          // KH, to fix, for testing only
          //this->client.setFingerprint(fingerprint);
        }
#if 0    
        void setClientRSACert(const X509List *cert, const PrivateKey *sk) 
        {
          // KH, to fix, for v1.0.0 only
          //this->client.setClientRSACert(cert, sk);
        }
    
        void setTrustAnchors(const X509List *ta) 
        {
          // KH, to fix, for v1.0.0 only
          //this->client.setTrustAnchors(ta);
        }
#endif    
    };

    
    #ifndef WEBSOCKETS_PORT
      #define DUMMY_PORT    8080
    #else
      #define DUMMY_PORT    WEBSOCKETS_PORT
    #endif
    
    // KH, quick fix for WiFiNINA port
    #define CLOSED     0
    
    class WiFiNINATcpServer : public TcpServer 
    {
      public:
        WiFiNINATcpServer() : server(DUMMY_PORT) {}
        
        bool poll() override 
        {
          yield();
          
          // KH, to fix, for testing only
          //return server.hasClient();
          return true;
          //////
        }
    
        bool listen(const uint16_t port) override 
        {
          yield();
          // KH, to fix WiFiNINA_Generic => v1.5.3
          server.begin(port);
          //////
          return available();
        }
    
        TcpClient* accept() override 
        {   
          while (available()) 
          {
            yield();
            auto client = server.available();
            
            if (client)
            {         
              return new WiFiNINATcpClient{client};
            }
            // KH, from v1.0.6, add to enable non-blocking when no WS Client
            else
            {
              // Return NULL Client. Remember to test for NULL and process correctly
              return NULL;
            }            
          }
                   
          return new WiFiNINATcpClient;
        }
    
        bool available() override 
        {
          yield();
          return server.status() != CLOSED;
        }
    
        void close() override 
        {
          yield();
          
          // KH, to fix, for testing only
          //server.close();
          //////
        }
    
        virtual ~WiFiNINATcpServer() 
        {
          if (available()) close();
        }
    
      protected:
        int getSocket() const override 
        {
          return -1;
        }
    
      private:
        WiFiServer server;
    };
  }   // namespace network2_generic
}     // namespace websockets2_generic
#endif // #ifdef nRF52
