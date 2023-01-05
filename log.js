const addon = require("bindings")('android_native.node')

const Log = (function() {
	const wrapper = (level, tag, msg) => {
		if (!tag) throw new Error('Cannot logging with undefined tag')
		if (!msg) throw new Error('Cannot logging undefined message')
		if (!msg && typeof level == 'number') throw new Error('The log level is undefined or isn\'t an number')
		if (typeof tag == 'string' && typeof msg == 'string') {
			addon.native_log(level, tag, msg)
		} else {
			throw new Error('Tag and message should be an string')
		}
	}

	const VERBOSE = 2
	const DEBUG = 1
	const INFO = 3
	const WARN = 4
	const ERROR = 5
	const FATAL = 6

	return {
		VERBOSE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL,
		v(tag, msg) {
			wrapper(VERBOSE, tag, msg)
		},

		d(tag, msg) {
			wrapper(DEBUG, tag, msg)
		},

		i(tag, msg) {
			wrapper(INFO, tag, msg)
		},

		w(tag, msg) {
			wrapper(WARN, tag, msg)
		},

		e(tag, msg) {
			wrapper(ERROR, tag, msg)
		},

		wtf(tag, msg) {
			wrapper(FATAL, tag, msg)
		}
	}
})()

module.exports = Log