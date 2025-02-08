#include "A6HTTP.h"

A6HTTP::A6HTTP(HardwareSerial* serial) : _serial(serial) {
}

bool A6HTTP::sendATCommand(const char* cmd, const char* expectedResponse, unsigned long timeout) {
  // Clear any available data from the serial buffer
  while (_serial->available()) {
    _serial->read();
  }
  
  // Send the command with a newline
  _serial->println(cmd);
  
  unsigned long startTime = millis();
  String response = "";
  
  while (millis() - startTime < timeout) {
    if (_serial->available()) {
      char c = _serial->read();
      response += c;
      // Check if the expected response appears in the reply
      if (response.indexOf(expectedResponse) != -1) {
        return true;
      }
    }
  }
  return false;
}

bool A6HTTP::beginHTTP() {
  // Initialize the HTTP service: AT+HTTPINIT
  return sendATCommand("AT+HTTPINIT", "OK");
}

bool A6HTTP::setParameter(const char* parameter, const char* value) {
  // Build the command string, e.g.: AT+HTTPPARA="CID",1 or AT+HTTPPARA="URL","http://example.com"
  String cmd = "AT+HTTPPARA=\"";
  cmd += parameter;
  cmd += "\",";
  cmd += value;
  
  return sendATCommand(cmd.c_str(), "OK");
}

bool A6HTTP::httpAction(uint8_t method) {
  // Execute HTTP action: method 0 for GET, 1 for POST, etc.
  String cmd = "AT+HTTPACTION=";
  cmd += method;
  
  // Send the command and wait for a response that includes "+HTTPACTION:"
  if (!sendATCommand(cmd.c_str(), "+HTTPACTION:")) {
    return false;
  }
  
  // Optional: delay to allow the action to complete (adjust delay as needed)
  delay(3000);
  return true;
}

String A6HTTP::httpRead() {
  // Send command to read the HTTP response: AT+HTTPREAD
  if (!sendATCommand("AT+HTTPREAD", "OK", 10000)) {
    return "";
  }
  
  String response = "";
  unsigned long startTime = millis();
  // Read additional data for a fixed period (adjust as necessary)
  while (millis() - startTime < 5000) {
    while (_serial->available()) {
      response += char(_serial->read());
    }
  }
  return response;
}

bool A6HTTP::endHTTP() {
  // Terminate the HTTP service: AT+HTTPTERM
  return sendATCommand("AT+HTTPTERM", "OK");
}
