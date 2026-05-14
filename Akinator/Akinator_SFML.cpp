#include "Akinator_SFML.hpp"



int play_akinator_sfml(FILE* fp, Node_t* root)
{   
    assert(fp);
    assert(root);

    Node_t* current_node = root;

    sf::RenderWindow window(sf::VideoMode(  window_size_x, 
                                            window_size_y), "Akinator");
    window.setFramerateLimit(FPS);    
    
    // sf::Clock clock;
    // float speed = 160;
    
    GameState currentState = GameState::Menu;
    
    sf::Texture HeartsTexture;
    HeartsTexture.loadFromFile("./Data/hearts.jpg");
    HeartsTexture.setRepeated(true);
    sf::Sprite HeartsSprite1(HeartsTexture);
    sf::Sprite HeartsSprite2(HeartsTexture);
    
    float offsetY = 0;
    sf::Vector2u HeartsTextureSize = HeartsTexture.getSize();
    float HSscaleX = static_cast<float>(window.getSize().x) / HeartsTextureSize.x;
    float HSscaleY = static_cast<float>(window.getSize().y) / HeartsTextureSize.y;
    HeartsSprite1.setScale(HSscaleX, HSscaleY);
    HeartsSprite2.setScale(HSscaleX, HSscaleY);
    HeartsSprite2.setPosition(0, window_size_y-1);
    
    sf::Texture GrafTexture;
    TreeDump(root, "./Data/Graf.dot");
    GrafTexture.loadFromFile("./Data/Graf.png");
    GrafTexture.setSmooth(true);
    sf::Sprite GrafSprite;
    GrafSprite.setTexture(GrafTexture);
    sf::Vector2u GrafTextureSize = GrafTexture.getSize();
    GrafSprite.setOrigin(GrafTextureSize.x / 2.0f, GrafTextureSize.y / 2.0f);
    GrafSprite.setPosition(window_size_x / 2.0f, window_size_y / 2.0f);
    float GSscaleX = static_cast<float>(window.getSize().x) / (GrafTextureSize.x - 100);
    float GSscaleY = static_cast<float>(window.getSize().y) / (GrafTextureSize.y - 100);
    GrafSprite.setScale(GSscaleX, GSscaleY);
    
    
    sf::Font font;
    font.loadFromFile("./Data/font.ttf");
    Button PlayButton( (float) (window_size_x*9/16), (float) window_size_y*5/8,
    window_size_x >> 2, window_size_y/6, &font, L"Play", 55);

    Button ShowButton( (float) (window_size_x*3/16), (float) window_size_y*5/8,
    window_size_x >> 2, window_size_y/6, &font, L"Tree", 55); 

    Button ReturnButton ((float) (window_size_x >> 6), (float) (window_size_y >> 5),
    window_size_x >> 3, window_size_y >> 3, &font, L"Back", 35);
    
    Button  YesButton( (float) (window_size_x*9/16), (float) window_size_y*5/8, 
    window_size_x >> 2, window_size_y/6, &font, L"Yes", 55 );
    
    Button NoButton( (float) (window_size_x*3/16), (float) window_size_y*5/8, 
    window_size_x >> 2, window_size_y/6, &font, L"No", 55 );
    
    YesButton.m_text.setLetterSpacing(2);
    NoButton.m_text.setLetterSpacing(2);
    
    size_t frames = 0;

    sf::Text mainText;
    mainText.setFont(font);
    mainText.setString("Hello! I'm Akinator!");
    // mainText.Bold;
    mainText.setLetterSpacing(2);
    mainText.setCharacterSize(60);
    mainText.setFillColor(pressedColor);
    
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int center_x = (int) (desktop.width  / 2 - window.getSize().x / 2);
    int center_y = (int) (desktop.height / 2 - window.getSize().y / 2);
    window.setPosition(sf::Vector2i(center_x, center_y));
    while (window.isOpen()) {
        
        // float SPF = clock.restart().asSeconds();
        // float SpeedStandart = speed * SPF;
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
            
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos((float)event.mouseMove.x, (float)event.mouseMove.y);
                
                if (currentState == GameState::Menu) {
                    ShowButton.update(mousePos);
                    PlayButton.update(mousePos);
                    
                } else if (currentState == GameState::Playing) {
                    YesButton.update(mousePos);
                    NoButton.update(mousePos);
                    ReturnButton.update(mousePos);

                } else if (currentState == GameState::PlayingEnd) {
                    ReturnButton.update(mousePos);

                } else if (currentState == GameState::ShowTree) {
                    ReturnButton.update(mousePos);
                
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);
                
                if (currentState == GameState::Menu) {
                    ShowButton.update(mousePos);
                    PlayButton.update(mousePos);
                    
                } else if (currentState == GameState::Playing) {
                    YesButton.update(mousePos);
                    NoButton.update(mousePos);
                    ReturnButton.update(mousePos);

                } else if (currentState == GameState::PlayingEnd) {
                    ReturnButton.update(mousePos);

                } else if (currentState == GameState::ShowTree) {
                    ReturnButton.update(mousePos);
                }
                
            }
            
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);
                
                if (currentState == GameState::Menu) {
                    if (PlayButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        ReturnButton.update(mousePos);
                        currentState = GameState::Playing;
                    }
                    if (ShowButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        currentState = GameState::ShowTree;
                    }
                    
                } else if (currentState == GameState::Playing) {
                    
                    if (YesButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        YesButton.update(mousePos);
                        
                        if (current_node->left && current_node->right) {
                            current_node = current_node->right;
                        } else {
                            currentState = GameState::PlayingEnd;
                            mainText.setString("Yes! I guessed right. :)");
                        }
                        
                    } else if (NoButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        NoButton.update(mousePos);
                        
                        if (current_node->left && current_node->right) {
                            current_node = current_node->left;
                        } else {
                            currentState = GameState::PlayingEnd;
                            mainText.setString("I couldn't guess. :(");
                        }

                    } else if (ReturnButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        ReturnButton.update(mousePos);
                        PlayButton.update(mousePos);
                        current_node = root;
                        currentState = GameState::Menu;
                        mainText.setString("Hello! I'm Akinator!");
                    }

                } else if (currentState == GameState::PlayingEnd) {
                    
                    if (ReturnButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        ReturnButton.update(mousePos);
                        PlayButton.update(mousePos);
                        current_node = root;
                        currentState = GameState::Menu;
                        mainText.setString("Hello! I'm Akinator!");
                }

                } else if (currentState == GameState::ShowTree) {

                    if (ReturnButton.m_shape.getGlobalBounds().contains(mousePos)) {
                        ReturnButton.update(mousePos);
                        PlayButton.update(mousePos);
                        current_node = root;
                        currentState = GameState::Menu;
                        mainText.setString("Hello! I'm Akinator!");
                    }
                }
                
            }
            
        }
        
        float background_speed = -0.3;
        HeartsSprite1.move(0, background_speed);
        HeartsSprite2.move(0, background_speed);
        if (HeartsSprite1.getPosition().y <= - ((float) window_size_y)) 
        HeartsSprite1.setPosition(0, window_size_y-1);
        
        if (HeartsSprite2.getPosition().y <= - ((float) window_size_y)) 
        HeartsSprite2.setPosition(0, window_size_y-1);

        
        if  (currentState == GameState::Menu) {
            
            window.clear(sf::Color(110,0,0,255));
            window.draw(HeartsSprite1);
            window.draw(HeartsSprite2);

            sf::FloatRect textRect = mainText.getLocalBounds();
            mainText.setOrigin(textRect.left + textRect.width  / 2.0f,
                               textRect.top  + textRect.height / 2.0f);
            mainText.setPosition(window_size_x / 2.0f, window_size_y*3/8);
            window.draw(mainText);
            
            ShowButton.render(window);
            PlayButton.render(window);
            
        } else if (currentState == GameState::Playing) {
            
            window.clear();
            window.draw(HeartsSprite1);
            window.draw(HeartsSprite2);
            
            ReturnButton.render(window);
            YesButton.render(window);
            NoButton.render(window);
            
            mainText.setString(std::string(current_node->question) + "?");
            
            sf::FloatRect textRect = mainText.getLocalBounds();
            mainText.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top  + textRect.height / 2.0f);
            mainText.setPosition(window_size_x / 2.0f, window_size_y*3/8);
            window.draw(mainText);
                
        } else if (currentState == GameState::PlayingEnd) {

            window.clear();
            window.draw(HeartsSprite1);
            window.draw(HeartsSprite2);
            ReturnButton.render(window);

            sf::FloatRect textRect = mainText.getLocalBounds();
            mainText.setOrigin(textRect.left + textRect.width  / 2.0f,
                               textRect.top  + textRect.height / 2.0f);
            mainText.setPosition(window_size_x / 2.0f, window_size_y*3/8);
            window.draw(mainText);
            
        } else if (currentState == GameState::ShowTree) {
            window.clear();
            window.draw(GrafSprite);
            ReturnButton.render(window);
        }
            
        window.display();
    }
    return 0;
}
    // GameOverTexture.loadFromFile("./Data/gameover.jpg");
    // GameOverTexture.setRepeated(true);
    
    // sf::Sprite GameOverSprite;
    // GameOverSprite.setTexture(GameOverTexture);
    // sf::Vector2u textureSize = GameOverTexture.getSize();
    // float scaleX = static_cast<float>(window.getSize().x) / (float) textureSize.x;
    // float scaleY = static_cast<float>(window.getSize().y) / textureSize.y;
    // GameOverSprite.setScale(0.5, 0.5);
    // GameOverSprite.setPosition(400,100);
    
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    // circle1.move(0, -(SpeedStandart*2));
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    // circle1.move(0, SpeedStandart*2);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    // circle1.move(SpeedStandart*2, 0);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    // circle1.move(-(SpeedStandart*2), 0);
    
    // GrafSprite.rotate(1);
    
    // offsetY += 0.7;
    
    // if (offsetY >= HeartsTextureSize.y) {
    //     offsetY -= HeartsTextureSize.y;
    // } else if (offsetY <= -HeartsTextureSize.y) {
    //     offsetY += HeartsTextureSize.y;
    // }
    // HeartsSprite2.setTextureRect(sf::IntRect(0, (int) (offsetY), HeartsTextureSize.x, HeartsTextureSize.y));
    