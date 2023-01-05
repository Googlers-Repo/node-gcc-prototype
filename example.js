const Log = require("./log.js")

const check = undefined

if (typeof check == 'undefined') {
    Log.e("NAPI_Example", "Check is undefined")
}