# flameGuard

📌 Wiring Setup for Smart Temperature Alert System
This setup will:
✅ Measure temperature using a thermistor
✅ Turn on a fan when it gets too hot
✅ Trigger a buzzer and LED as alerts

1️⃣ Wiring the Thermistor (Temperature Sensor)
Why?

The thermistor changes resistance based on temperature.
A 10kΩ resistor is used to create a voltage divider so Arduino can read temperature properly.
Connections:

One leg of the thermistor → A1 (Analog Pin on Arduino)
Same leg → 10kΩ resistor, then to 5V
Other leg of the thermistor → GND (Arduino)
What happens?

Arduino reads the voltage at A1, converts it into temperature, and decides whether to turn on the fan, buzzer, or LED.

2️⃣ Wiring the Fan (Cooling System)
Why?

The fan turns ON when temperature crosses the set threshold and helps cool down the system.
Connections:

Fan Red (+) → D6 (PWM Pin on Arduino)
Fan Black (-) → GND (Arduino)
📌 If the fan runs all the time, it’s probably connected directly to 5V instead of D6.


3️⃣ Wiring the Buzzer (Sound Alert)
Why?

When the temperature goes above the limit, the buzzer will beep to alert the user.
Connections:

Buzzer + (Red) → D8 (Arduino Digital Output)
Buzzer - (Black) → GND (Arduino)
📌 If the buzzer doesn’t work, check if it’s an active buzzer (which works with just HIGH/LOW signals).


4️⃣ Wiring the LED (Visual Alert)
Why?

The LED provides a visual warning when the temperature is too high.
Connections:

LED Anode (+, Long Leg) → D9 (Digital Output)
LED Cathode (-, Short Leg) → GND (Arduino)
Optional: Use a 220Ω resistor between D9 and the LED anode to prevent damage.
📌 If the LED doesn’t turn on, try swapping the legs—it only works in one direction!

🔥 Summary of Pin Connections
Component	Arduino Pin	Extra Info
Thermistor	A1 (Analog Input)	10kΩ resistor to 5V
Fan	D6 (PWM Output)	Turns ON/OFF based on temp
Buzzer	D8 (Digital Output)	Beeps when temp is high
LED	D9 (Digital Output)	Lights up when temp is high
🚀 How It Works
At normal temperature → Everything stays OFF.
When temp goes above the threshold (e.g., 50°C):
✅ Fan turns ON
✅ Buzzer starts beeping
✅ LED lights up
When temp drops below threshold → Everything turns OFF again.
