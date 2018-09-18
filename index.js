// function allReady() {
//     console.log("ready to roll")
// }

// const Module = {
//     onRuntimeInitialized: function() {
//     //   Module._foobar(); // foobar was exported
//         console.log(Module)
//     }
//   };

const bot = require("./wasm/twitch-bot")
// console.log(Object.keys(bot))

// // console.log(Object.keys(bot))

// setTimeout(() => {
//     bot._run()
// }, 2500)

function callback(message) {
    console.log(message)
}

const func_map = {
    0: callback
};

// C/C++ functions get a _ prefix added
function _invoke_callback(callback_id, text_ptr) {
    func_map[callback_id](bot.Pointer_stringify(text_ptr));
}

setTimeout(() => {
    bot.ccall("run", 0);
}, 2500)