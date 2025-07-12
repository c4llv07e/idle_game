#include <stddef.h>
#include <stdint.h>

#define max_width 1600.0f
#define max_height 900.0f

typedef struct Color {
	int r, g, b;
} Color;

typedef struct Laser {
	int x, y;
	struct Color color;
	float time;
	float end_time;
} Laser;

extern void ctx_set_fill_color(int r, int g, int b);
extern void ctx_fill_rect(int x, int y, int w, int h);
extern void ctx_save();
extern void ctx_restore();
extern void ctx_rotate(float angle);
extern void request_animation_frame(void *func);
extern void console_log_str(const char *text);
extern void console_log_int(int val);

int real_width, real_height;
int mouse_x, mouse_y;

struct Laser lasers[0x100];

static inline void to_real(int *x, int *y) {
	*x *= real_width / max_width;
	*y *= real_height / max_height;
}

static inline void from_real(int *x, int *y) {
	*x *= max_width / real_width;
	*y *= max_height / real_height;
}

extern void on_mouse(int x, int y) {
	mouse_x = x;
	mouse_y = y;
	from_real(&mouse_x, &mouse_y);
}

extern void on_resize(int width, int height) {
	real_width = width;
	real_height = height;
}

static void draw_rect(int x, int y, int w, int h, struct Color color) {
	to_real(&x, &y);
	to_real(&w, &h);
	ctx_set_fill_color(color.r, color.g, color.b);
	ctx_fill_rect(x, y, w, h);
}

static inline void fill_screen(struct Color color) {
	draw_rect(0, 0, max_width, max_height, color);
}

static void draw_laser(int x1, int y1, int x2, int y2, struct Color color) {
	ctx_save();
	ctx_rotate(45);
	draw_rect(x1, y1, x2 - x1, y2 - y1, color);
	ctx_restore();
}

extern void on_draw(void) {
	fill_screen((struct Color){0x12, 0x12, 0x12});
	draw_rect(mouse_x, mouse_y, 100, 100, (struct Color){255, 0, 0});
	draw_laser(100, 200, 400, 400, (struct Color){255, 255, 255});
	request_animation_frame(on_draw);
}

extern int init(void) {
	request_animation_frame(on_draw);
	return 0;
}
