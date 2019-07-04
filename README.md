# Arduino-Bluetooth


## Usage
When loaded onto an arduino board, a looping call will enitiate looking for a device to connect to
Once a connection is established with a device, the signals will be enterpreted in the style

* S100/0   (For sterring to the left)
* F-100/0  (For moving backwards)

S is for manipulitating the steering motor and F is for manipulating the motors to drive the car forward and backwards.
The minus sign is enterpreted to reverse direction from the default (left or forward) to the reverse (right or backwards).
The /0 is a string terminator where the 0 is interpreted to execute the preceding instruction.
This arrangement alows for realtime manipulation of motors from another source sending BLE requests.

There is also the potential to use ultrasonic sensors to aid with avaoiding obstacles but it's best if it's not used at all.
