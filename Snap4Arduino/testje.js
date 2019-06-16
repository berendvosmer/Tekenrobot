


const Firmata = require("firmata");
const board = new Firmata("/dev/ttyUSB0");
var value = 100;
var pdata = encodeUnsignedInteger(value, 7);
var complete = false;


board.on("ready", () => {
  // Arduino is ready to communicate

  
  board.sysexResponse(0x08, isComplete); 

  pdata[0] = value & 0x7f;
  pdata[1] = (value >> 7) & 0x7f;
  pdata[2] = (value >> 14) & 0x7f;

  board.sysexCommand(new Buffer([0x08, 0x01, pdata[0], pdata[1], pdata[2]]));

  while (!complete) {
  }
});

function isComplete(message) {
  if (message[0] == 0x01) {
    complete = true;
    console.log('Message 0x01 received!');
  }
}

function encodeUnsignedInteger(value, size) {
  var pdata = [];
  i=0;
  mask=2**size-1;
  
  do {  
    pdata[i] = value & mask;
    i++;
    value >>= i * size;

  } while (value != 0); 
  
  return pdata; 
}

