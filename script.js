var importObject = { imports: { imported_func: arg => console.log(arg) } };

WebAssembly.instantiateStreaming(fetch('main.wasm'), importObject)
.then(obj => {
  var charArray = new Int8Array(
    obj.instance.exports.memory.buffer, // WASM's memory
    obj.instance.exports.getString(), // char's pointer
    12                                 // The string's length
  );

  let string = String.fromCharCode.apply(null, charArray) // Convert from ASCII code to char
  console.log(string);

  document.getElementById("heading").innerHTML = string // Set the value of the heading to our string
});