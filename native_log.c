#include <android/log.h>
#include <assert.h>
#include <node_api.h>
#include <stdio.h>

static napi_value Log(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 3;
	napi_value args[3];
	status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
	assert(status == napi_ok);

	if (argc < 3)
	{
		napi_throw_type_error(env, NULL, "Wrong number of arguments");
		return NULL;
	}

	napi_valuetype valuetype0;
	status = napi_typeof(env, args[2], &valuetype0);
	assert(status == napi_ok);

	napi_valuetype valuetype1;
	status = napi_typeof(env, args[1], &valuetype1);
	assert(status == napi_ok);

	napi_valuetype valuetype2;
	status = napi_typeof(env, args[0], &valuetype2);
	assert(status == napi_ok);


	if (valuetype0 != napi_string || valuetype1 != napi_string || valuetype2 != napi_number)
	{
		napi_throw_type_error(env, NULL, "Wrong arguments");
		return NULL;
	}

	char tag[1024];
	size_t tag_len;
	if (napi_get_value_string_utf8(env, args[1], (char *)&tag, 1024, &tag_len) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected string");
		return NULL;
	}

	char data[1024];
	size_t data_len;
	if (napi_get_value_string_utf8(env, args[2], (char *)&data, 1024, &data_len) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected string");
		return NULL;
	}
	/* 
	   char level[1024]; size_t level_len; if (napi_get_value_string_utf8(env, 
	   args[2], (char *)&level, 1024, &level_len) != napi_ok) {
	   napi_throw_error(env, "EINVAL", "Expected string"); return NULL; } */
	double level;
	if (napi_get_value_double(env, args[0], &level) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected number");
		return NULL;
	}

	switch ((int)level)
	{
	case 0:
		__android_log_write(ANDROID_LOG_DEFAULT, tag, data);
		break;
	case 1:
		__android_log_write(ANDROID_LOG_VERBOSE, tag, data);
		break;
	case 2:
		__android_log_write(ANDROID_LOG_DEBUG, tag, data);
		break;
	case 3:
		__android_log_write(ANDROID_LOG_INFO, tag, data);
		break;
	case 4:
		__android_log_write(ANDROID_LOG_WARN, tag, data);
		break;
	case 5:
		__android_log_write(ANDROID_LOG_ERROR, tag, data);
		break;
	case 6:
		__android_log_write(ANDROID_LOG_FATAL, tag, data);
		break;
	case 7:
		__android_log_write(ANDROID_LOG_SILENT, tag, data);
		break;
	default:
		__android_log_write(ANDROID_LOG_DEFAULT, tag, data);
	}

	return NULL;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("native_log", Log);
	status = napi_define_properties(env, exports, 1, &addDescriptor);
	assert(status == napi_ok);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
