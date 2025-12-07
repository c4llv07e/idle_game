#include <stddef.h>
#include <stdint.h>

#define max_width 1600.0f
#define max_height 900.0f

typedef struct Color {
	int r, g, b;
} Color;

extern void ctx_set_fill_color(int r, int g, int b);
extern void ctx_fill_rect(int x, int y, int w, int h);
extern void request_animation_frame(void *func);
extern void console_log_str(const char *text);
extern void console_log_int(int val);

int real_width;
int real_height;

void to_real(float *x, float *y) {
	*x *= real_width / max_width;
	*y *= real_height / max_height;
}

void on_resize(int width, int height) {
	console_log_str("resize");
	real_width = width;
	real_height = height;
}

void draw_rect(float x, float y, float w, float h, struct Color color) {
	to_real(&x, &y);
	to_real(&w, &h);
	ctx_set_fill_color(color.r, color.g, color.b);
	ctx_fill_rect((int)x, (int)y, (int)w, (int)h);
}

void on_draw(void) {
	draw_rect(0, 0, 1600, 900, (Color){0, 255, 0});
	draw_rect(100, 200, 100, 100, (Color){255, 0, 0});
	request_animation_frame(on_draw);
}

int init(void) {
	request_animation_frame(on_draw);
	return 0;
}
