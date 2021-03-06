//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_GEOMETRY_MESH_FACTORY_H
#define EXOGFX_GEOMETRY_MESH_FACTORY_H

#include "../utils/math_util.h"
#include <stdint.h>

typedef struct {
    float* vertices;
    float* uvs;
    uint32_t *indices;
    uint32_t vertice_size;
    uint32_t uv_size;
    uint32_t index_size;
} mesh;

struct mesh *create_sphere_mesh(void);
struct mesh *create_cube_mesh(void);
struct mesh *create_plane_mesh(float width, float height, uint32_t h_segments, uint32_t v_segments, enum axis up_axis);

#endif //EXOGFX_GEOMETRY_MESH_FACTORY_H
