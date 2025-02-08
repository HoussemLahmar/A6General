# A6General Arduino Library

A6General is a general purpose library designed for Arduino users working with A6GPRS modules. The library currently implements the MQTT protocol and is fully configurable to work on any hardware serial port (Serial, Serial1, Serial2, Serial3). **Note:** It does **NOT** work with SoftwareSerial. The library also allows configuration of the UART buffer size and the expected maximum size for the combined Topic + Message received.

More classes are planned for future releases (e.g., HTTP, SMTP, SMS, CALL).

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
  - [Using the Arduino Library Manager](#using-the-arduino-library-manager)
  - [Manual Installation](#manual-installation)
- [Usage](#usage)
  - [Basic Setup](#basic-setup)
- [Examples](#examples)
- [Configuration](#configuration)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Support](#support)

## Features
- **MQTT Protocol:** Implements basic MQTT protocol functionality for A6GPRS modules.
- **Hardware Serial Support:** Works with any available hardware serial port (Serial, Serial1, Serial2, Serial3).
- **UART Buffer Configuration:** Configure the size of the UART buffer.
- **Message Size Limitation:** Set the maximum expected size for the combined Topic + Message received.
- **Planned Enhancements:** Future versions will include additional protocols and services such as HTTP, SMTP, SMS, and CALL.

## Requirements
- **Arduino Board:** Compatible with Arduino boards that support A6GPRS modules.
- **Serial Port:** Must use a hardware serial port. (SoftwareSerial is not supported.)
- **A6GPRS Module:** The library is intended for use with A6GPRS modules.

## Installation

### Using the Arduino Library Manager
1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries...**
3. In the Library Manager, search for **A6General**.
4. Click **Install**.

### Manual Installation
1. Download the ZIP archive from the [GitHub repository](https://github.com/mgaman/A6General).
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3. Select the downloaded ZIP file to install.

## Usage
To get started with A6General, include the main header files in your sketch:

```cpp
#include <A6MQTT.h>
#include <A6Modem.h>
#include <A6Services.h>
```

### Basic Setup
- **Initialize the Library:** Create instances of the classes required (e.g., for MQTT communication).
- **Configure Serial Port:** The library is configurable to work on any hardware serial port. For example:

  ```cpp
  // Use Serial1 for communication
  A6MQTT mqtt(&Serial1);
  ```

- **Set Buffer and Message Limits:** Adjust the UART buffer size and maximum expected message size as needed.

## Examples
Below is a simple example that demonstrates initializing the MQTT connection:

```cpp
#include <A6MQTT.h>

// Initialize the MQTT instance with Serial1
A6MQTT mqtt(&Serial1);

void setup() {
  // Begin serial communication for debugging
  Serial.begin(9600);
  // Initialize the hardware serial port connected to the A6GPRS module
  Serial1.begin(115200);

  // Configure the UART buffer size (example value)
  mqtt.setUARTBufferSize(128);
  
  // Configure maximum topic+message size (example value)
  mqtt.setMaxMsgSize(256);
  
  // Initialize MQTT (further configuration may be required)
  if (mqtt.beginMQTT("broker.example.com", 1883)) {
    Serial.println("MQTT connection established!");
  } else {
    Serial.println("Failed to connect to MQTT broker.");
  }
}

void loop() {
  // Handle incoming MQTT messages and maintain connection
  mqtt.loop();
}
```

For a complete example and additional use cases, please refer to the `examples` folder in the repository.

## Configuration
The library allows you to adjust several parameters to suit your hardware and application needs:

- **UART Buffer Size:** Use `setUARTBufferSize(size)` to define the size of the UART buffer.
- **Maximum Message Size:** Use `setMaxMsgSize(size)` to set the maximum combined size of Topic and Message that can be received.
- **Serial Port Selection:** Pass a pointer to the hardware serial port (e.g., `Serial1`, `Serial2`) when instantiating library classes.

Refer to the source code and inline comments for more detailed configuration options.

## Roadmap
Planned future enhancements include:
- **HTTP Client:** Implementation for basic HTTP requests.
- **SMTP Client:** For sending emails.
- **SMS Functionality:** To send and receive SMS messages.
- **Call Management:** Handling voice calls via the A6GPRS module.

Your feedback and contributions toward these features are welcome!

## Contributing
Contributions are very welcome! If you would like to help improve A6General:
- **Report Bugs:** Use the [Issues](https://github.com/mgaman/A6General/issues) section to report bugs.
- **Suggest Features:** Open an issue to discuss new features or enhancements.
- **Submit Pull Requests:** Feel free to fork the repository, make your changes, and submit a pull request.

Please follow the coding style and guidelines used in the project. If you’re new to contributing, check out our [Contributing Guidelines](CONTRIBUTING.md) (if available) or refer to the community’s best practices.

## License
This project is licensed under the [MIT License](LICENSE). Please see the LICENSE file for details.

## Support
If you encounter issues or have questions:
- **Issues:** Please open an issue in the GitHub repository.
- **Documentation:** Refer to this README and inline comments in the source code.
- **Community:** Join our discussions via GitHub Discussions or the project's communication channels (if available).

---

© 2025 A6General. All rights reserved.
