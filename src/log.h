#ifndef SRC_LOG_H_
#define SRC_LOG_H_

void _platform_log (const char * msg, const char * file, int line);

#ifdef DISABLE_LOG
#define log_error(___msg) _platform_log ("Error: "#___msg, __FILE__, __LINE__)
#else
#define log_error(___msg) do{}while(0)
#endif
#endif /* SRC_LOG_H_ */
