function decode8BitUnsignedInteger( arg1, arg2)
{
  let result = arg1 | arg2 << 7;

  return result;
}

function encode8BitUnsignedInteger(value, pdata)
{
  pdata[0] = value & 0x7f;
  pdata[1] = (value >> 7) & 0x7f;
}

function decode16BitUnsignedInteger(arg1, arg2, arg3)
{
  let result = arg1 | arg2 << 7 | arg3 << 14;

  return result;
}

function encode16BitUnsignedInteger(value, pdata)
{
  pdata[0] = value & 0x7f;
  pdata[1] = (value >> 7) & 0x7f;
  pdata[2] = (value >> 14) & 0x7f;
}

function encodeUnsignedInteger(value, size) {
  var pdata = [];
  i=0;
  mask=2**size-1;
  
  do {  
    pdata[i] = value & mask;
    console.log("value = ", value);
    i++;
    value >>= i * size;

  } while (value != 0) 
  
  return pdata; 
}
var byte1 = 88;
var byte2 = 1;

var value = 48000;
var pdata = [];

//console.log(decode8BitUnsignedInteger(byte1,byte2));
//encode16BitUnsignedInteger(value,pdata);
//console.log(pdata);
//console.log(decode16BitUnsignedInteger(pdata[0],pdata[1],pdata[2]));

var pdata = encodeUnsignedInteger(100,7);
var out = decode16BitUnsignedInteger(pdata[0], pdata[1], pdata[2]);
console.log("output = ", out);