#include "imgui.h"
#include "imgui-SFML.h"
#include "Animated.hpp"
#include "ResourceManager.h"
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    //window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;

    int nb = 10;
    int oldnb = nb;
    float factor1 = 4.0;
    float factor2 = 5.0;
    float speed = 0.2;
    float spacing = 1.0;
    bool paused = false;

    sf::Sprite s;
    s.setTexture(*game::ResourceManager::getTexture("breakout_sprites.png"));
    //Creating the sprites
    std::vector < Animated * > sprites;
    for (int i = 0; i < nb; i++) {
        Animated *an = new Animated(s);
        for (int j = 1; j < 16; j++) {
            sf::IntRect rec(j * 24, 376, 24, 24);
            an->addFrame("myanim", rec, 60);
        }
        an->playanimation("myanim", i);
        sprites.push_back(an);
    }
    double i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Parameters"); // begin window
        if (ImGui::SliderInt("# of Objects", &nb, 1, 1000, "%d") || oldnb != nb) {
            if (oldnb < nb) {
                for (int k = 0; k < (nb - oldnb); k++) {
                    Animated *an = new Animated(s);
                    for (int l = 1; l < 16; l++) {
                        sf::IntRect rec(l * 24, 376, 24, 24);
                        an->addFrame("myanim", rec, 60);
                    }
                    an->playanimation("myanim", k);
                    sprites.push_back(an);
                }
            }
            if (nb < oldnb) {
                for (int k = 0; k < (oldnb - nb); k++) {
                    auto tmp = sprites.back();
                    sprites.pop_back();
                    delete tmp;
                }
            }
            oldnb = nb;
        }
        ImGui::SliderFloat("Horizontal factor", &factor1, 0.1, 10.0, "%.1f");
        ImGui::SliderFloat("Vertical factor", &factor2, 0.1, 10.0, "%.1f");
        ImGui::SliderFloat("Speed", &speed, 0.05, 5.0, "%.1f");
        ImGui::SliderFloat("Spacing", &spacing, 0.05, 5.0, "%.1f");
        ImGui::Checkbox("Paused", &paused);
        if (ImGui::Button("Reset")) {
            nb = 10;
            factor1 = 4.0;
            factor2 = 5.0;
            speed = 0.2;
            spacing = 1.0;
        }
        if (ImGui::Button("Quit")) {
            window.close();
        }
        ImGui::End(); // end window

        double j = 0;
        if (!paused) {
            i += speed;
        }
        for (auto sprite : sprites) {
            j += spacing;
            sprite->getDrawable().setPosition(385 + 380 * sin(factor1 * (i + j) * M_PI / 180),
                                              285 + 280 * cos(factor2 * (i + j) * M_PI / 180));
            sprite->update();
        }

        window.clear(sf::Color::Black);
        for (auto sprite : sprites) {
            window.draw(sprite->getDrawable());
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    for (auto sprite : sprites) {
        delete sprite;
    }
}