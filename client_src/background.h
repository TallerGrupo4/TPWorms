#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"

#include "Animation.h"
#include "beam.h"
#include "surfaces.h"

// Class that represents the background of the match
class Background {
private:
    std::vector<Beam> beams;
    SDL2pp::Texture bkgrnd_image;
    Animation water_an;
    int width;
    int height;
    int water_level;

public:
    /**
     * @brief Construct a new Background object
     * @param platforms Platforms of the match
     * @param map_width Width of the map
     * @param map_height Height of the map
     * @param water_level Pos y of the water
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     */
    explicit Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height,
                        int water_level, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    /**
     * @brief Renders the background
     * @param renderer Renderer of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    /**
     * @brief Renders the water
     * @param renderer Renderer of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render_water(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    /**
     * @brief Updates the water animations
     */
    void update_water();
    int get_map_width();
    int get_map_height();
};

#endif  // BACKGROUND_H
