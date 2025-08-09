// src/tilemap.h
#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>

// tiles: array of pointers to sprites (e.g. { tile_empty, tile_floor, tile_wall, ... })
// tile_count: number of entries in tiles[]
// solid_flags: NULL or pointer to array of uint8_t flags (1 = solid, 0 = non-solid) with length == tile_count
void tilemap_init(const void **tiles, int tile_count, int tile_w, int tile_h, const uint8_t *solid_flags);

// supply a map as a flat uint8_t array (row-major). tile indices are 0..tile_count-1
void tilemap_set_map(const uint8_t *map, int map_w, int map_h);

// draw only the visible region. cam_x / cam_y are pixel camera coords (world space)
void tilemap_draw(int cam_x, int cam_y);

// utilities
int tilemap_tile_at_pixel(int px, int py);            // returns tile index, or -1 out of bounds
int tilemap_is_solid_at_pixel(int px, int py);        // 1 if solid, 0 otherwise

// getters for tile / map sizes
int tilemap_tile_w(void);
int tilemap_tile_h(void);
int tilemap_map_w(void);
int tilemap_map_h(void);

#endif // TILEMAP_H
