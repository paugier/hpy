#include <stdarg.h>
#include "acutest.h" // https://github.com/mity/acutest
#include "hpy/debug/src/debug_internal.h"

static void check_DHQueue(DHQueue *q, HPy_ssize_t size, ...)
{
    va_list argp;
    va_start(argp, size);
    DHQueue_sanity_check(q);
    TEST_CHECK(q->size == size);
    DebugHandle *h = q->head;
    while(h != NULL) {
        DebugHandle *expected = va_arg(argp, DebugHandle*);
        TEST_CHECK(h == expected);
        h = h->next;
    }
    va_end(argp);
}

void test_DHQueue_init(void)
{
    DHQueue q;
    DHQueue_init(&q);
    TEST_CHECK(q.head == NULL);
    TEST_CHECK(q.tail == NULL);
    TEST_CHECK(q.size == 0);
    DHQueue_sanity_check(&q);
}

void test_DHQueue_append(void)
{
    DHQueue q;
    DebugHandle h1;
    DebugHandle h2;
    DebugHandle h3;
    DHQueue_init(&q);
    DHQueue_append(&q, &h1);
    DHQueue_append(&q, &h2);
    DHQueue_append(&q, &h3);
    check_DHQueue(&q, 3, &h1, &h2, &h3);
}




#define MYTEST(X) { #X, X }

TEST_LIST = {
    MYTEST(test_DHQueue_init),
    MYTEST(test_DHQueue_append),
    { NULL, NULL }
};