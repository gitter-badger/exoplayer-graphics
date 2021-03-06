//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_VIDEO_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_VIDEO_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"

struct ogles_video_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
    GLuint target;

    struct
    {
        struct uniform uMVPMatrix;
        struct uniform uSTMatrix;
        struct uniform uCRatio;
        struct uniform sTexture;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;
};

ogles_filter_init(video)
(struct ogles_video_filter *filter);

ogles_filter_release(video)
(struct ogles_video_filter *filter);

ogles_filter_safe_release(video)
(struct ogles_video_filter *filter);

ogles_filter_resize(video)
(struct ogles_video_filter *filter, GLint width, GLint height);

ogles_filter_draw(video)
(struct ogles_video_filter *filter, GLuint texture, const float mvp_matrix[], const float st_matrix[], const float aspect_ratio);

ogles_filter_draw_cb(video)
(struct ogles_video_filter *filter);

ogles_filter_use_program(video)
(struct ogles_video_filter *filter);

ogles_filter_get_vertex_buffer(video)
(struct ogles_video_filter *filter);

ogles_filter_register_handle(video)
(struct ogles_video_filter *filter);

#endif //EXOGFX_GRAPHICS_OGLES_VIDEO_FILTER_H
