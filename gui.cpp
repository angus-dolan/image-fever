#include "gui.h"

sf::Vector2f scaleFromDimensions(const sf::Vector2u& textureSize, int screenWidth, int screenHeight)
{
    float scaleX = screenWidth / float(textureSize.x);
    float scaleY = screenHeight / float(textureSize.y);
    float scale = std::min(scaleX, scaleY);

    return { scale, scale };
}

sf::Text placeholder(const sf::Font& font, const std::string& str, int charSize, const sf::Color& color, float x, float y) {
    sf::Text placeholder;

    placeholder.setFont(font);
    placeholder.setString(str);
    placeholder.setCharacterSize(charSize);
    placeholder.setFillColor(color);
    sf::FloatRect textRect = placeholder.getLocalBounds();
    placeholder.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    placeholder.setPosition(x, y);

    return placeholder;
}

bool preloadResources(sf::Font& font, sf::Texture& texture, int imageIndex) {
    string fontPath = string(CMAKE_DIR) + "/OpenSans-Bold.ttf";

    return font.loadFromFile(fontPath.c_str()) && texture.loadFromFile(imageQueue.getImage(imageIndex).path);
}

image updateSprite(sf::Sprite& sprite, sf::Texture& texture, int imageIndex, int gameWidth, int gameHeight, sf::RenderWindow& window) {
    const auto& image = imageQueue.getImage(imageIndex);
    window.setTitle(image.path);

    if (image.processed && texture.loadFromFile(image.path)) {
        sprite = sf::Sprite(texture);
        sprite.setScale(scaleFromDimensions(texture.getSize(), gameWidth, gameHeight));
    }

    return image;
}

void handleWindowResize(sf::RenderWindow& window, int gameWidth, int gameHeight) {
    sf::View view;

    view.setSize(gameWidth, gameHeight);
    view.setCenter(gameWidth / 2.f, gameHeight / 2.f);

    window.setView(view);
}

int slideshow()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    const float pi = 3.14159f;
    const int gameHeight = 600;
    const int gameWidth = 800;
    int imageIndex = 0;

    sf::Font font;
    sf::Texture texture;
    sf::Sprite sprite(texture);
    sf::Text placeholderImage;
    sf::Clock clock;

    // Prepare resources
    if (preloadResources(font, texture, imageIndex)) {
        placeholderImage = placeholder(font, "Image hasn't finished processing", 24, sf::Color::White, gameWidth / 2.f, gameHeight / 2.f);
        sprite.setScale(scaleFromDimensions(texture.getSize(), gameWidth, gameHeight)); // Make sure the texture fits the screen
    }
    else {
        return EXIT_FAILURE;
    }

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Image Fever", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Exit
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
                break;
            }
  
            // Resize window
            if (event.type == sf::Event::Resized) {
                handleWindowResize(window, gameWidth, gameHeight);
            }

            // Arrow keys
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::Left) {
                    imageIndex = (imageIndex + imageQueue.getQueue().size() - 1) % imageQueue.getQueue().size();
                }
                else if (event.key.code == sf::Keyboard::Key::Right) {
                    imageIndex = (imageIndex + 1) % imageQueue.getQueue().size();
                }
            }
        }

        // Draw
        window.clear(sf::Color(0, 0, 0));
        image img = updateSprite(sprite, texture, imageIndex, gameWidth, gameHeight, window);

        if (img.processed) {
            window.draw(sprite);
        }
        else {
            window.draw(placeholderImage);
        }

        window.display();
    }
}
