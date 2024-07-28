# Mouse Button Remapper

A simple Windows application to remap side mouse buttons to keyboard keys using the Windows API. The GUI features a modern, pastel-themed aesthetic for a more pleasant user experience.

## Features

- Remap side mouse buttons (XBUTTON1 and XBUTTON2) to any alphabet key.
- Modern and pastel-themed GUI.
- Easy-to-use interface for setting mappings.

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Pranjol-Dev/Mouse-Maper.git
    cd Mouse-Maper
    ```

2. **Compile the code:**
    - Make sure you have GCC installed.
    - Run the following command:
    ```bash
    gcc -o Mouse Mouse.c -lgdi32
    ```

3. **Run the executable:**
    ```bash
    ./Mouse
    ```

## Usage

1. **Select Mouse Button:**
    - Click on "Side Button 1" or "Side Button 2" to select which mouse button you want to remap.

2. **Enter Key to Map:**
    - Enter the key you want to map the selected mouse button to in the text box.

3. **Set Mapping:**
    - Click "Set Mapping" to apply the remapping.

## Customization

### Changing Colors

If you want to change the colors of the GUI, modify the color definitions in the source code:

```c
#define PASTEL_PINK RGB(255, 182, 193)
#define PASTEL_BLUE RGB(173, 216, 230)
#define PASTEL_GREEN RGB(152, 251, 152)
#define PASTEL_YELLOW RGB(255, 255, 224)
#define PASTEL_PURPLE RGB(216, 191, 216)
```

### Changing Font

To change the font, modify the `CreateFont` call:

```c
HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## Acknowledgments

- Inspired by the need for custom mouse button remapping.
- Uses Windows API for low-level mouse and keyboard interactions.

---

**Developed by [Pranjol Das](https://github.com/Pranjol-Dev)**
```
