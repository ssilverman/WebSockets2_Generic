/****************************************************************************************************************************
  tcp_client.hpp
  For WebSockets2_Generic Library
  
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

#include <Tiny_Websockets_Generic/internals/ws_common.hpp>
#include <Tiny_Websockets_Generic/network/tcp_socket.hpp>

namespace websockets2_generic 
{
  namespace network2_generic 
  {
    struct TcpClient : public TcpSocket 
    {
      virtual bool poll() = 0;
      virtual void send(const WSString& data) = 0;
      virtual void send(const WSString&& data) = 0;
      virtual void send(const uint8_t* data, const uint32_t len) = 0;
      virtual WSString readLine() = 0;
      virtual uint32_t read(uint8_t* buffer, const uint32_t len) = 0;
      virtual bool connect(const WSString& host, int port) = 0;
      virtual ~TcpClient() {}
    };
  }   // namespace network2_generic
}     // namespace websockets2_generic 
