
#include "bmlib.h"

#include <stdarg.h>

#ifdef BMLIB_HAS_PRINTF

/* write targets for *printf() */
struct write_context {
    void (*write)(struct write_context *, int data);
    char *buffer;
    int curr, max;
};


static void sprintf_write(struct write_context *c, int data)
{
    if(c->curr < c->max - 1)
        c->buffer[c->curr++] = data;
}

/*
 * endpoint for all printf() functions.
 * You need to supply you own putchar(), for example something
 * that writes to your UART or to your log buffer
 */
static void printf_write(struct write_context *c, int data)
{
    putchar(data);
    if(data == '\n') putchar('\r');
}


/*
 * MINIMAL printf implementation
 */

static void printf_string(struct write_context *ctx, char *str)
{
    if(!str) str = "(null)";
    while(*str)
        ctx->write(ctx, *str++);
}


static void printf_int(struct write_context *ctx, int i)
{
    int tmp, f = 0, neg = 0;
    char buffer[25];

    if(i < 0) {
        neg ++;
        i = - i;
    }
    do {
#ifdef BMLIB_HAS_DIV10
        tmp = i;
        i = divu10(i);
        buffer[f++] = '0' + (tmp - i * 10);
#else
        buffer[f++] = '0' + (i % 10);
        i /= 10;
#endif
    } while(i);

    if(neg) buffer[f++] = '-';
    while(f)
        ctx->write(ctx, buffer[--f]);
}

static void printf_hex(struct write_context *ctx, uint32_t n, int size)
{
    uint32_t h, i;
    for(i = size * 8; i; ) {
        i -= 4;
        h = (n >> i) & 15;
        if(h < 10) h += '0';
        else h += 'A' - 10;
        ctx->write(ctx, h);
    }
}

static void vcprintf(struct write_context *ctx, const char *fmt, va_list args)
{
    int c;

    for(;;) {
        c = *fmt;
        if(c == '\0')
            return;

        fmt ++;
        if(c == '%') {
            c = *fmt++;
            switch(c) {
            case 's':
                printf_string(ctx, va_arg(args, char *));
                break;
            case 'd':
                printf_int(ctx, va_arg(args, int));
                break;
            case 'x':
                printf_hex(ctx, va_arg(args, uint32_t), 4);
                break;
            case 'c':
                ctx->write(ctx, va_arg(args, int));
                break;
            case '\0':
            case '%':
                ctx->write(ctx, c);
                break;
            default:
                ctx->write(ctx, '%');
                ctx->write(ctx, c);
            }
        } else {
            ctx->write(ctx, c);
        }
    }
}

/* printf head */
void printf(const char *fmt, ...)
{
    va_list args;
    struct write_context ctx;

    va_start(args, fmt);

    ctx.write = printf_write;
    vcprintf(&ctx, fmt, args);

    va_end(args);
}


/* snprintf head */
void snprintf(char *buffer, int size, const char *fmt, ...)
{
    va_list args;
    struct write_context ctx;

    va_start(args, fmt);

    ctx.write = sprintf_write;
    ctx.buffer = buffer;
    ctx.curr = 0;
    ctx.max = size;
    vcprintf(&ctx, fmt, args);

    buffer[ctx.curr] = '\0';

    va_end(args);
}

#endif /* BMLIB_HAS_PRINTF */
