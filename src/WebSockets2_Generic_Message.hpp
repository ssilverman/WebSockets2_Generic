/****************************************************************************************************************************
  WebSockets2_Generic_Message.hpp
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

#ifndef _WEBSOCKETS2_GENERIC_MESSAGE_H
#define _WEBSOCKETS2_GENERIC_MESSAGE_H

#pragma once

// KH
#include <WebSockets2_Generic.h>
#include "WebSockets2_Generic_Debug.h"

#include <Tiny_Websockets_Generic/message.hpp>

namespace websockets2_generic
{
  MessageType messageTypeFromOpcode(uint8_t opcode) 
  {
    switch (opcode) 
    {
      case internals2_generic::ContentType::Binary: return MessageType::Binary;
      case internals2_generic::ContentType::Text: return MessageType::Text;
      case internals2_generic::ContentType::Ping: return MessageType::Ping;
      case internals2_generic::ContentType::Pong: return MessageType::Pong;
      case internals2_generic::ContentType::Close: return MessageType::Close;
      default: return MessageType::Empty;
    }
  }
}   // namespace websockets2_generic

#endif    // _WEBSOCKETS2_GENERIC_MESSAGE_H
