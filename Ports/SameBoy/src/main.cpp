#include <LibGUI/Application.h>
#include <LibGUI/Window.h>
#include <LibGUI/Widget.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Painter.h>
#include <LibMain/Main.h>
#include <AK/DeprecatedString.h>

#include <sameboy_core/gb.h>

class EmulatorWidget : public GUI::Widget {
public:
    EmulatorWidget()
    {
        m_bitmap = Gfx::Bitmap::create(Gfx::BitmapFormat::BGRA8888, { 160, 144 }).release_value_but_fixme_should_propagate_errors();
    }

    virtual void paint_event(GUI::PaintEvent& event) override
    {
        GUI::Painter painter(*this);
        painter.draw_scaled_bitmap(rect(), *m_bitmap, m_bitmap->rect());
    }

    RefPtr<Gfx::Bitmap> bitmap() { return m_bitmap; }

private:
    RefPtr<Gfx::Bitmap> m_bitmap;
};

        void blit_pixels(GB_gameboy_t* gb, RefPtr<Gfx::Bitmap> bitmap) {
            uint32_t* bitmap_pixels = (uint32_t*)bitmap->scanline(0);
            const uint32_t* gb_pixels = GB_get_pixels_output(gb); // Assuming this function exists

            if (!bitmap_pixels || !gb_pixels) {
                warnln("Error: Null pixel buffer!");
                return;
            }


            for (int y = 0; y < 144; ++y) {
                for (int x = 0; x < 160; ++x) {
                    bitmap_pixels[y * 160 + x] = gb_pixels[y * 160 + x];
                }
            }
        }


ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    auto app = TRY(GUI::Application::try_create(arguments));

    auto window = TRY(GUI::Window::try_create());
    window->set_title("SameBoy Emulator");
    window->resize(640, 480);

    auto emulator_widget = window->set_main_widget<EmulatorWidget>();

    // Initialize SameBoy
    GB_gameboy_t* gb = GB_new();
    if (!gb) {
        warnln("Failed to create SameBoy instance!");
        return 1;
    }

    const char* romPath = "/home/ubuntu/Downloads/Tetris (JUE) (V1.1) [!].gb";
    FILE* file = fopen(romPath, "rb");

    if (file == nullptr) {
        perror("Error opening ROM file");
        return 1;
    }

    GB_load_rom(gb, romPath);

    if (!gb->rom_loaded) {
        warnln("Failed to load ROM!");
        return 1;
    } else {
	warnln("ROM loaded successfully!");
    }

    blit_pixels(gb, emulator_widget->bitmap());

    window->show();

    //MainLoop
    while (true) {
            warnln("Running Frame");
            GB_run_frame(gb);
            warnln("Blitting Pixels");
            blit_pixels(gb, emulator_widget->bitmap());
            warnln("Updating Widget");
            emulator_widget->update();
            app->pump_events();
     }


    return app->exec();
}

