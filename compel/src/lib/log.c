#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "log.h"

static unsigned int current_loglevel = COMPEL_DEFAULT_LOGLEVEL;
static int relative_timestamps = COMPEL_DEFAULT_RELATIVETIMESTAMPS;
static compel_log_fn logfn;

void compel_log_init(compel_log_fn log_fn, unsigned int level)
{
	logfn = log_fn;
	current_loglevel = level;
}

unsigned int compel_log_get_loglevel(void)
{
	return current_loglevel;
}

void compel_relativetimestamps_init(compel_log_fn log_fn, int timestamps)
{
	logfn = log_fn;
	relative_timestamps = timestamps;
}

void compel_print_on_level(unsigned int loglevel, const char *format, ...)
{
	va_list params;
	compel_log_fn fn = logfn;

	if (fn != NULL && !pr_quelled(loglevel)) {
		va_start(params, format);
		fn(loglevel, format, params);
		va_end(params);
	}
}
