#include "CollisionDetector.h"
#include "DEBUG.h"

using TextureMask = std::vector<sf::Uint8>;

static sf::Uint8 getPixel(const TextureMask& mask, const sf::Texture& tex, uint32_t x, uint32_t y) {
    // Ensure x and y are within bounds of the texture size
    if (x >= tex.getSize().x || y >= tex.getSize().y)
        return 0; // Return transparent if out of bounds

    if (x + y * tex.getSize().x > mask.size())
        return 0;

    //DEBUG_MSG(x + y * tex.getSize().x);

    return mask[x + y * tex.getSize().x];
}

class BitmaskRegistry
{
public:
    auto& create(const sf::Texture& tex, const sf::Image& img) {
        auto mask = TextureMask(tex.getSize().x * tex.getSize().y); // Use width and height correctly

        for (uint32_t y = 0; y < tex.getSize().y; ++y)
        {
            for (uint32_t x = 0; x < tex.getSize().x; ++x)
                mask[x + y * tex.getSize().x] = img.getPixel(x, y).a;
        }

        // Store and return ref to the mask
        return (bitmasks[&tex] = std::move(mask));
    }

    auto& get(const sf::Texture& tex) {
        auto pair = bitmasks.find(&tex);
        if (pair == bitmasks.end())
        {
            return create(tex, tex.copyToImage());
        }

        return pair->second;
    }

private:
    std::map<const sf::Texture*, TextureMask> bitmasks;
};

// Gets global instance of BitmaskRegistry.
static BitmaskRegistry& bitmasks() {
    static BitmaskRegistry instance;
    return instance;
}

bool CollisionDetector::pixelPerfectTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alphaLimit) {
    sf::FloatRect intersection;
    if (!sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection))
        return false; // No intersection

    auto s1SubRect = sprite1.getTextureRect();
    auto s2SubRect = sprite2.getTextureRect();

    auto& mask1 = bitmasks().get(*sprite1.getTexture());
    auto& mask2 = bitmasks().get(*sprite2.getTexture());

    // Loop through the intersection area
    for (float i = intersection.left; i < intersection.left + intersection.width; ++i) {
        for (float j = intersection.top; j < intersection.top + intersection.height; ++j) {

            // Transform global coordinates to sprite local coordinates
            auto s1v = sprite1.getInverseTransform().transformPoint(i, j);
            auto s2v = sprite2.getInverseTransform().transformPoint(i, j);

            // Ensure we are within sprite's subrect bounds
            if (s1v.x >= 0 && s1v.y >= 0 &&
                s2v.x >= 0 && s2v.y >= 0 &&
                s1v.x < s1SubRect.width && s1v.y < s1SubRect.height &&
                s2v.x < s2SubRect.width && s2v.y < s2SubRect.height) {

                // Calculate texture coordinates and ensure they are within bounds
                int texX1 = static_cast<int>(s1v.x) + s1SubRect.left;
                int texY1 = static_cast<int>(s1v.y) + s1SubRect.top;
                int texX2 = static_cast<int>(s2v.x) + s2SubRect.left;
                int texY2 = static_cast<int>(s2v.y) + s2SubRect.top;

                if (getPixel(mask1, *sprite1.getTexture(), texX1, texY1) > alphaLimit &&
                    getPixel(mask2, *sprite2.getTexture(), texX2, texY2) > alphaLimit)
                    return true; // Collision detected

            }
        }
    }
    return false; // No collision detected
}

bool CollisionDetector::singlePixelTest(const sf::Sprite& sprite, sf::Vector2f& mousePosition, sf::Uint8 alphaLimit) {
    if (!sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        return false;

    auto subRect = sprite.getTextureRect();
    auto& mask = bitmasks().get(*sprite.getTexture());

    auto sv = sprite.getInverseTransform().transformPoint(mousePosition.x, mousePosition.y);

    // Make sure pixels fall within the sprite's subrect
    if (sv.x >= 0 && sv.y >= 0 &&
        sv.x < subRect.width && sv.y < subRect.height) {
        // Calculate texture coordinates and ensure they are within bounds
        int texX = static_cast<int>(sv.x) + subRect.left;
        int texY = static_cast<int>(sv.y) + subRect.top;
        return getPixel(mask, *sprite.getTexture(), texX, texY) > alphaLimit;
    }
    return false;
}
