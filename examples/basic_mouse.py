#!/usr/bin/env python3
"""
Basic SFML Mouse Example

This example demonstrates handling basic mouse events.
"""

import pysfml3 as sf

arial = sf.Font()
arial.open_from_file("fonts/arial.ttf") # implicit conversion happens to pysfml3.Path... ew

def main():
    window = sf.RenderWindow(
        sf.VideoMode(sf.Vector2u(800, 600), 32),
        "PySFML - Basic Mouse Example",
        sf.State.NONE,
        sf.ContextSettings()
    )

    window.set_vertical_sync_enabled(True)
    mouse_inside = False
    mouse_wheel_state = {
        sf.mouse.Wheel.VERTICAL_WHEEL: 0.0,
        sf.mouse.Wheel.HORIZONTAL_WHEEL: 0.0
    }

    # Main loop
    while window.is_open():
        while event := window.poll_event():
            if keyevent := event.get_if(sf.Event.KeyPressed):
                if keyevent.code == sf.Keyboard.Key.SPACE:
                    sf.mouse.set_position(sf.Vector2i(0, 0), window)
                if keyevent.code == sf.Keyboard.Key.ESCAPE:
                    window.close()
            elif event.is_type(sf.Event.Closed):
                window.close()
            elif event.is_type(sf.Event.MouseEntered):
                mouse_inside = True
            elif event.is_type(sf.Event.MouseLeft):
                mouse_inside = False
            elif mwevent := event.get_if(sf.Event.MouseWheelScrolled):
                mouse_wheel_state[mwevent.wheel] += mwevent.delta

        debugtext = f"""Mouse Info
        get_position()={sf.mouse.get_position()}
        get_position(window)={sf.mouse.get_position(window)}
        get_position(window)={sf.mouse.get_position(window)}
        button_count()={sf.mouse.button_count()}
        is_button_pressed()={[sf.mouse.is_button_pressed(sf.mouse.Button(button)) for button in range(sf.mouse.button_count())]}
        {mouse_inside=}
        {mouse_wheel_state[sf.mouse.Wheel.VERTICAL_WHEEL]=}
        """

        window.clear(sf.Color())
        window.draw(sf.Text(arial, debugtext, 24), sf.RenderStates.DEFAULT)
        window.display()

if __name__ == "__main__":
    main()
