

#define DUMP(list, img, title, ...)                                                         \
do {                                                                                        \
    if (LOG_FILE) {                                                                         \
        fprintf(LOG_FILE, "<div style=\"width:95%%\">\n");                                  \
        fprintf(LOG_FILE, "<h1>");                                                          \
        title;                                                                              \
        fprintf(LOG_FILE, "</h1>\n");                                                       \
        fprintf(LOG_FILE, "<xmp style=\"font-size: auto\">\n");                             \
        fprintf(LOG_FILE, "%s(%i) in %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);       \
        dump(list, LOG_FILE);                                                               \
        fprintf(LOG_FILE, "</xmp>\n");                                                      \
        fprintf(LOG_FILE, "<img src=%s alt=\"WTF\" style=\"width: 100%%\">\n", #img);       \
        __VA_ARGS__;                                                                        \
        fprintf(LOG_FILE, "</div>\n");                                                      \
        fprintf(LOG_FILE, "<hr>\n");                                                        \
    }                                                                                       \
} while(0)


extern FILE *LOG_FILE;


int open_log(const char *filepath);


int close_log(void);
