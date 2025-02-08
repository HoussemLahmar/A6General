#ifndef A6HTTP_H
#define A6HTTP_H

#include <Arduino.h>

class A6HTTP {
  public:
    /**
     * @brief Constructor that initializes the A6HTTP instance.
     * @param serial A pointer to the HardwareSerial object used for communication.
     */
    A6HTTP(HardwareSerial* serial);

    /**
     * @brief Initialize the HTTP service on the A6GPRS module.
     * @return true if HTTP service initialized successfully, false otherwise.
     */
    bool beginHTTP();

    /**
     * @brief Set an HTTP parameter.
     * @param parameter The parameter name (e.g., "CID", "URL", "CONTENT").
     * @param value The value to assign (for numerical parameters, pass as a string).
     * @return true if the parameter was set successfully, false otherwise.
     */
    bool setParameter(const char* parameter, const char* value);

    /**
     * @brief Execute an HTTP action.
     * @param method The HTTP method code: 0 for GET, 1 for POST (others may be supported).
     * @return true if the action was executed successfully, false otherwise.
     */
    bool httpAction(uint8_t method);

    /**
     * @brief Read the HTTP response from the module.
     * @return A String containing the HTTP response, or an empty string if failed.
     */
    String httpRead();

    /**
     * @brief Terminate the HTTP service.
     * @return true if the service was terminated successfully, false otherwise.
     */
    bool endHTTP();

  private:
    HardwareSerial* _serial;

    /**
     * @brief Helper function to send an AT command and wait for an expected response.
     * @param cmd The AT command string to send.
     * @param expectedResponse The string expected in the response.
     * @param timeout The maximum time to wait (in milliseconds).
     * @return true if the expected response was received, false otherwise.
     */
    bool sendATCommand(const char* cmd, const char* expectedResponse, unsigned long timeout = 5000);
};

#endif // A6HTTP_H
