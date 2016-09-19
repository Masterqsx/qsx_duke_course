int m_init();
int m_fl_cal(size_t size);
void *m_expand(size_t size);
void ts_free(void *addr);
void *ts_malloc(size_t size);
void *m_coalesce_next(char *addr);
void *m_coalesce_pre(char *addr);
void *m_add_fl(char *addr);
void *m_split(char *addr, size_t size);
void display_free();
void display_all();


