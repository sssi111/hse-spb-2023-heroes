#include "event_manager.hpp"

void EventManager::update(sf::Event event) {
    if (m_menu_bar->update(event, *m_window->get_render_window())) {
        set_window_is_done();
    }
    m_window->update(event);
}

void EventManager::set_window_is_done() {
    m_window->m_is_done = true;
}
