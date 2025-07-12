var memory;
var wasmModule;
var instance;
var ctx;
async function init() {
  var importObject = {
    env: {
      memory: new WebAssembly.Memory({ initial: 256 }),
      console_log_str: function (addr) {
        var length = (new Uint8Array(memory.buffer, addr)).indexOf(0);
        var str = (new TextDecoder()).decode(new Uint8Array(memory.buffer, addr, length));
        console.log(str);
      },
      console_log_int: function (val) {
        console.log(val);
      },
      request_animation_frame: function (f) {
        requestAnimationFrame(instance.exports.__indirect_function_table.get(f));
      },
      ctx_fill_rect: function (x, y, w, h) {
        ctx.fillRect(x, y, w, h);
      },
      ctx_set_fill_color: function (r, g, b) {
        ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;
      },
      ctx_save: function () {
        ctx.save();
      },
      ctx_restore: function() {
        ctx.restore();
      },
      ctx_rotate: function(angle) {
        console.log(angle);
        ctx.rotate(angle);
      },
    }
  };
  wasmModule = await WebAssembly.instantiateStreaming(
    fetch("./game.wasm"), importObject
  );
  instance = wasmModule.instance;
  memory = instance.exports.memory;
  function onResize(e) {
    var width = document.documentElement.clientWidth * 0.9;
    var height = document.documentElement.clientHeight * 0.9;
    var normalized_width = width / 16;
    var normalized_height = height / 9;
    var minVal = Math.min(normalized_width, normalized_height);
    gamecanvas.width = minVal * 16;
    gamecanvas.height = minVal * 9;
    instance.exports.on_resize(gamecanvas.width, gamecanvas.height);
  };
  function onMouse(e) {
    instance.exports.on_mouse(e.offsetX, e.offsetY);
  };
  window.addEventListener("resize", onResize);
  gamecanvas.addEventListener("mousemove", onMouse);
  onResize();
  instance.exports.init();
};
ctx = gamecanvas.getContext("2d");
init();
