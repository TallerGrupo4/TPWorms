#ifndef BEAM_H
#define BEAM_H

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"

#include "surfaces.h"

// Class that represents a beam in the match
class Beam {
private:
    SDL2pp::Texture beam_image;
    BeamType type;
    int x;
    int y;
    int width;
    int height;

    SDL2pp::Texture assign_texture(PlatformSnapshot pltfrm, MatchSurfaces& surfaces,
                                   SDL2pp::Renderer& renderer);
    void assign_positions(SDL2pp::Renderer& renderer, int x, int y, int map_width, int map_height);
    int calculate_beam_width(int degree, float beam_actual_height, float beam_actual_width);
    int calculate_beam_height(int degree, float beam_actual_height, float beam_actual_width);

public:
    /**
     * @brief Construct a new Beam object
     * @param pltfrm Snapshot of the platform received from the server
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     * @param map_width Width of the map
     * @param map_height Height of the map
     */
    explicit Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer,
                  int map_width, int map_height);
    /**
     * @brief Renders the beam
     * @param renderer Renderer of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
};

#endif  // BEAM_H
