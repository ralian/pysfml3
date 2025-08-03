#!/usr/bin/env python3
"""
Basic SFML Window Example

This example demonstrates basic window and event handling.
"""
from random import randint

import pysfml3 as sf

def main():
    mycolor = sf.Color(randint(0, 255), randint(0, 255), randint(0, 255))

    # Create the main window
    window = sf.RenderWindow(
        sf.VideoMode(sf.Vector2u(800, 600), 32),
        "PySFML - Basic Window Example",
        sf.State.NONE,
        sf.ContextSettings()
    )

    # Just turn on VSYNC - you could set the framerate too if desired.
    window.set_vertical_sync_enabled(True)
    # window.set_framerate_limit(60)

    # Main loop
    while window.is_open():
        while event := window.poll_event():
            if keyevent := event.get_if(sf.Event.KeyPressed):
                mycolor = sf.Color(randint(0, 255), randint(0, 255), randint(0, 255))
                if keyevent.code == sf.Keyboard.Key.ESCAPE:
                    window.close()
            if event.is_type(sf.Event.Closed):
                window.close()

        window.clear(mycolor)
        window.display()


if __name__ == "__main__":
    main()
