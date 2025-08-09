// src/tilemap.c
#include "tilemap.h"
#include <graphx.h>
#include <stddef.h>

static const void **g_tiles = NULL;
static const uint8_t *g_solid = NULL;
static const uint8_t *g_map = NULL;
static int g_tile_w = 0;
static int g_tile_h = 0;
static int g_tile_count = 0;
static int g_map_w = 0;
static int g_map_h = 0;

void tilemap_init(const void **tiles, int tile_count, int tile_w, int tile_h, const uint8_t *solid_flags) {
    g_tiles = tiles;
    g_tile_count = tile_count;
    g_tile_w = tile_w;
    g_tile_h = tile_h;
    g_solid = solid_flags;
}

void tilemap_set_map(const uint8_t *map, int map_w, int map_h) {
    g_map = map;
    g_map_w = map_w;
    g_map_h = map_h;
}

int tilemap_tile_w(void) { return g_tile_w; }
int tilemap_tile_h(void) { return g_tile_h; }
int tilemap_map_w(void) { return g_map_w; }
int tilemap_map_h(void) { return g_map_h; }

static inline int tile_index_at(int tx, int ty) {
    if (!g_map) return -1;
    if (tx < 0 || tx >= g_map_w || ty < 0 || ty >= g_map_h) return -1;
    return g_map[ty * g_map_w + tx];
}

void tilemap_draw(int cam_x, int cam_y) {
    if (!g_map || !g_tiles) return;

    // screen size for CE: 320x240
    const int SCREEN_W = 320;
    const int SCREEN_H = 240;

    int first_tx = cam_x / g_tile_w;
    int first_ty = cam_y / g_tile_h;
    int last_tx = (cam_x + SCREEN_W  + g_tile_w - 1) / g_tile_w;
    int last_ty = (cam_y + SCREEN_H + g_tile_h - 1) / g_tile_h;

    if (first_tx < 0) first_tx = 0;
    if (first_ty < 0) first_ty = 0;
    if (last_tx > g_map_w) last_tx = g_map_w;
    if (last_ty > g_map_h) last_ty = g_map_h;

    for (int ty = first_ty; ty < last_ty; ++ty) {
        for (int tx = first_tx; tx < last_tx; ++tx) {
            int idx = tile_index_at(tx, ty);
            if (idx <= 0) continue; // treat 0 as empty (you can change this)
            if (idx >= g_tile_count) continue;
            int draw_x = tx * g_tile_w - cam_x;
            int draw_y = ty * g_tile_h - cam_y;
            gfx_TransparentSprite(g_tiles[idx], draw_x, draw_y);
        }
    }
}

int tilemap_tile_at_pixel(int px, int py) {
    if (!g_map) return -1;
    int tx = px / g_tile_w;
    int ty = py / g_tile_h;
    return tile_index_at(tx, ty);
}

int tilemap_is_solid_at_pixel(int px, int py) {
    int idx = tilemap_tile_at_pixel(px, py);
    if (idx < 0) return 0;
    if (g_solid) return g_solid[idx] ? 1 : 0;
    // default: non-zero tile = solid
    return idx != 0;
}
