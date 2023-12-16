## General Information:
- Major components: Custom board with STM32F103RBT6 MCU (Clock is 64MHz).
- Supporting communication protocol: UART.
- Purpose: The project simulates a two-way traffic signal system following key features:
    - Automatic mode: The system operates as normal. Green, yellow, and red are the light colors.
    - Manual mode: This option allows you to change the light colors by pressing a button.
    - Tuning mode: This option allows you to change the duration of the light timing.
    - Pedestrian scramble: Upon pressing the pedestrian's button, the light turns on and functions in opposition to the vehicle's light.
- Components' usage:
    - Two-way traffic light LEDs.
    - 4 buttons for setting modes.
    - UART Communication to control the system from a host computer.
    - One buzzer warning the time is running out when the pedestrian LED is turned ON.

![connect](https://github.com/vanphuc1208/MCUAssignment/assets/144821367/c931a758-0537-4fa5-bef3-c648de0e1953)

