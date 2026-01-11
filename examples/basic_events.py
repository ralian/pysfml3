#!/usr/bin/env python3
"""
Basic SFML Events Example

This example demonstrates handling various event types including keyboard,
mouse, window, and text input events.
"""

import pysfml3 as sf

def main():
    window = sf.RenderWindow(
        sf.VideoMode(sf.Vector2u(800, 600), 32),
        "PySFML - Basic Events Example",
        sf.State.NONE,
        sf.ContextSettings()
    )

    window.set_vertical_sync_enabled(True)
    
    event_log = []
    max_log_entries = 50
    print_to_log = lambda msg: [event_log.append(msg), print(msg)]
    
    last_mouse_pos = sf.Vector2i(0, 0)
    window_size = sf.Vector2u(800, 600)
    has_focus = True
    text_input = ""
    
    while window.is_open():
        while event := window.poll_event():
            # Window events
            if event.is_type(sf.Event.Closed):
                window.close()
            elif resize_event := event.get_if(sf.Event.Resized):
                window_size = resize_event.size
                print_to_log(f"Window resized to {window_size.x}x{window_size.y}")
            elif event.is_type(sf.Event.FocusGained):
                has_focus = True
                print_to_log("Window gained focus")
            elif event.is_type(sf.Event.FocusLost):
                has_focus = False
                print_to_log("Window lost focus")
            
            # Keyboard events
            elif key_event := event.get_if(sf.Event.KeyPressed):
                modifiers = []
                if key_event.alt:
                    modifiers.append("Alt")
                if key_event.control:
                    modifiers.append("Ctrl")
                if key_event.shift:
                    modifiers.append("Shift")
                if key_event.system:
                    modifiers.append("System")
                
                mod_str = f" [{'+'.join(modifiers)}]" if modifiers else ""
                print_to_log(f"Key pressed: {key_event.code}{mod_str}")
                
                if key_event.code == sf.Keyboard.Key.ESCAPE:
                    window.close()
            elif key_event := event.get_if(sf.Event.KeyReleased):
                print_to_log(f"Key released: {key_event.code}")
            
            # Mouse button events
            elif mouse_event := event.get_if(sf.Event.MouseButtonPressed):
                print_to_log(f"Mouse button pressed: {mouse_event.button} at ({mouse_event.position.x}, {mouse_event.position.y})")
            elif mouse_event := event.get_if(sf.Event.MouseButtonReleased):
                print_to_log(f"Mouse button released: {mouse_event.button} at ({mouse_event.position.x}, {mouse_event.position.y})")
            
            # Mouse movement events
            elif mouse_event := event.get_if(sf.Event.MouseMoved):
                last_mouse_pos = mouse_event.position
                # Only log every 10th movement to avoid spam
                if len(event_log) == 0 or not event_log[-1].startswith("Mouse moved"):
                    print_to_log(f"Mouse moved to ({mouse_event.position.x}, {mouse_event.position.y})")
            elif raw_event := event.get_if(sf.Event.MouseMovedRaw):
                # Raw mouse movement (relative, not affected by window focus)
                if len(event_log) == 0 or not event_log[-1].startswith("Mouse moved raw"):
                    print_to_log(f"Mouse moved raw: delta ({raw_event.delta.x}, {raw_event.delta.y})")
            
            # Mouse enter/leave events
            elif event.is_type(sf.Event.MouseEntered):
                print_to_log("Mouse entered window")
            elif event.is_type(sf.Event.MouseLeft):
                print_to_log("Mouse left window")
            
            # Mouse wheel events
            elif wheel_event := event.get_if(sf.Event.MouseWheelScrolled):
                wheel_name = "Vertical" if wheel_event.wheel == sf.mouse.Wheel.VERTICAL_WHEEL else "Horizontal"
                print_to_log(f"Mouse wheel scrolled ({wheel_name}): {wheel_event.delta} at ({wheel_event.position.x}, {wheel_event.position.y})")
            
            # Text input events
            elif text_event := event.get_if(sf.Event.TextEntered):
                # Filter out control characters
                if ord(text_event.unicode[0]) >= 32:  # Printable characters
                    char = chr(ord(text_event.unicode[0]))
                    text_input += char
                    print_to_log(f"Text entered: '{char}' (Unicode: {text_event.unicode})")
            
            # Joystick events
            elif joy_event := event.get_if(sf.Event.JoystickConnected):
                print_to_log(f"Joystick {joy_event.joystick_id} connected")
            elif joy_event := event.get_if(sf.Event.JoystickDisconnected):
                print_to_log(f"Joystick {joy_event.joystick_id} disconnected")
            elif joy_event := event.get_if(sf.Event.JoystickButtonPressed):
                print_to_log(f"Joystick {joy_event.joystick_id} button {joy_event.button} pressed")
            elif joy_event := event.get_if(sf.Event.JoystickButtonReleased):
                print_to_log(f"Joystick {joy_event.joystick_id} button {joy_event.button} released")
            elif joy_event := event.get_if(sf.Event.JoystickMoved):
                print_to_log(f"Joystick {joy_event.joystick_id} axis {joy_event.axis} moved to {joy_event.position}")
            
            # Touch events (for touch-enabled devices)
            elif touch_event := event.get_if(sf.Event.TouchBegan):
                print_to_log(f"Touch began: finger {touch_event.finger} at ({touch_event.position.x}, {touch_event.position.y})")
            elif touch_event := event.get_if(sf.Event.TouchMoved):
                print_to_log(f"Touch moved: finger {touch_event.finger} to ({touch_event.position.x}, {touch_event.position.y})")
            elif touch_event := event.get_if(sf.Event.TouchEnded):
                print_to_log(f"Touch ended: finger {touch_event.finger} at ({touch_event.position.x}, {touch_event.position.y})")
            
            # Sensor events
            elif sensor_event := event.get_if(sf.Event.SensorChanged):
                print_to_log(f"Sensor changed: type {sensor_event.type}, value ({sensor_event.value.x}, {sensor_event.value.y}, {sensor_event.value.z})")
        
        # Keep only the last N log entries
        if len(event_log) > max_log_entries:
            event_log = event_log[-max_log_entries:]
        
        window.clear(sf.Color(30, 30, 30))
        window.display()


if __name__ == "__main__":
    main()
