#include "camera.h"

OrthographicCamera::OrthographicCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY)
    : m_position(position), m_forward(forward), m_resolutionX(resolutionX), m_resolutionY(resolutionY)
{
}

Ray OrthographicCamera::ConstructRay(int pixelX, int pixelY) const
{
    //float pixelWidth = 2.0f / m_resolutionX;
    //float pixelHeight = 2.0f / m_resolutionY;

    //float pixelCenterX = -1.0f + (pixelX + 0.5f) * pixelWidth;
    //float pixelCenterY = +1.0f - (pixelY + 0.5f) * pixelHeight;

    //Ray ray(Vector3{ pixelCenterX, pixelCenterY, 0 }, Vector3{ 0, 0, 1 });

    Ray ray{ m_position + Vector3{(float)pixelX, (float)pixelY, 0}, m_forward };

    return ray;
}

//void render(
//    const Options& options,
//    const std::vector<std::unique_ptr<Object>>& objects,
//    const std::vector<std::unique_ptr<Light>>& lights)
//{
//    Matrix44f cameraToWorld;
//    Vec3f* framebuffer = new Vec3f[options.width * options.height];
//    Vec3f* pix = framebuffer;
//    float scale = tan(deg2rad(options.fov * 0.5));
//    float imageAspectRatio = options.width / (float)options.height;
//    Vec3f orig;
//    cameraToWorld.multVecMatrix(Vec3f(0), orig);
//    for (uint32_t j = 0; j < options.height; ++j)
//    {
//        for (uint32_t i = 0; i < options.width; ++i)
//        {
//            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
//            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
//            Vec3f dir;
//            cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
//            dir.normalize();
//            *(pix++) = castRay(orig, dir, objects, lights, options, 0);
//        }
//    }
//
//    // Save result to a PPM image (keep these flags if you compile under Windows)
//    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
//    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
//    for (uint32_t i = 0; i < options.height * options.width; ++i)
//    {
//        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
//        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
//        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
//        ofs << r << g << b;
//    }
//
//    ofs.close();
//
//    delete[] framebuffer;
//}