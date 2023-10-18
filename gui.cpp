#include "gui.h"

sf::Vector2f scaleFromDimensions(const sf::Vector2u& textureSize, int screenWidth, int screenHeight)
{
    float scaleX = screenWidth / float(textureSize.x);
    float scaleY = screenHeight / float(textureSize.y);
    float scale = std::min(scaleX, scaleY);
    return { scale, scale };
}

int slideshow()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    const float pi = 3.14159f;
    const int gameWidth = 800;
    const int gameHeight = 600;
    int imageIndex = 0;

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Image Fever",
        sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // Load an image to begin with
    sf::Texture texture;
    if (!texture.loadFromFile(getImage(imageIndex).path))
        return EXIT_FAILURE;

    // Make sure the texture fits the screen
    sf::Sprite sprite(texture);
    sprite.setScale(scaleFromDimensions(texture.getSize(), gameWidth, gameHeight));

    sf::Clock clock;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            // Window size changed, adjust view appropriately
            if (event.type == sf::Event::Resized)
            {
                sf::View view;
                view.setSize(gameWidth, gameHeight);
                view.setCenter(gameWidth / 2.f, gameHeight / 2.f);
                window.setView(view);
            }

            // Arrow key handling!
            if (event.type == sf::Event::KeyPressed)
            {
                // adjust the image index
                if (event.key.code == sf::Keyboard::Key::Left) {
                    std::vector<image> queue = getQueue();
                    imageIndex = (imageIndex + queue.size() - 1) % queue.size();
                }
                else if (event.key.code == sf::Keyboard::Key::Right) {
                    imageIndex = (imageIndex + 1) % getQueue().size();
                }
                    
                // get image filename
                const auto& imageFilename = getImage(imageIndex).path;
                // set it as the window title 
                window.setTitle(imageFilename);
                // ... and load the appropriate texture, and put it in the sprite
                if (texture.loadFromFile(imageFilename))
                {
                    sprite = sf::Sprite(texture);
                    sprite.setScale(scaleFromDimensions(texture.getSize(), gameWidth, gameHeight));
                }
            }
        }

        // Clear the window
        window.clear(sf::Color(0, 0, 0));
        // draw the sprite
        window.draw(sprite);
        // Display things on screen
        window.display();
    }
}
