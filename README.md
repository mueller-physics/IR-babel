# Infrared babel

Make the Fire TV remote talk to a [Renkforce](https://www.conrad.com/p/renkforce-tb230-soundbar-black-bluetooth-nfc-wall-brackets-1384497)
sound bar that uses weird(?) IR codes.

Command list:

NEC protocol, address 0xff00

- 0x45  power
- 0x47  mute
- 0x40  select optical input
- 0x07  select aux 1 input
- 0x15  select aux 2 input
- 0x09  select bluetooth input
- 0x19  volume up
- 0x1c  volume down
- 0x18  play/pause
- 0x0c  back / last track
- 0x5e  forward / next track
- 0x42  sound profile 'flat'
- 0x44  sound profile 'movie'
- 0x4a  soudn profile 'music'


