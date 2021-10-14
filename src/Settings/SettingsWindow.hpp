#include "raylib.h"

#include <vector>
#include <string>

#include "RaySettingsTypes.hpp"

namespace raysettings
{

    enum class WindowMode : uint32
    {
        eFullscreen = 0,
        eWindowed,
        eBorderlessWindowed,
    };

    inline constexpr uint32 c_numResolutionPairs = 18u;

    inline constexpr UIntPair c_resolutionPairs[c_numResolutionPairs] =
        {
            {800, 600},
            {1024, 768},
            {1280, 720},
            {1280, 800},
            {1280, 1024},
            {1360, 768},
            {1366, 768},
            {1440, 900},
            {1536, 864},
            {1600, 900},
            {1680, 1050},
            {1920, 1080},
            {1920, 1200},
            {2048, 1152},
            {2560, 1080},
            {2560, 1440},
            {3440, 1440},
            {3840, 2160},
    };

    inline constexpr char const *c_resolutionStrings =
        "800x600;"
        "1024x768;"
        "1280x720;"
        "1280x800;"
        "1280x1024;"
        "1360x768;"
        "1366x768;"
        "1440x900;"
        "1536x864;"
        "1600x900;"
        "1680x1050;"
        "1920x1080;"
        "1920x1200;"
        "2048x1152;"
        "2560x1080;"
        "2560x1440;"
        "3440x1440;"
        "3840x2160;";

    inline constexpr char const *c_windowModeStrings =
        "Fullscreen;"
        "Windowed;"
        "Borderless Windowed";

    struct SettingsWindowLayout
    {
        Vector2 m_anchor01 = {50, 50};
        Vector2 m_anchor02 = {200, 125};
        Vector2 m_anchor03 = {200, 540};

        Rectangle m_layoutRecs[20] = {
            Rectangle{0, 0, 1920, 1080},                                // GuiWindowBox                 0

            Rectangle{m_anchor02.x, m_anchor02.y, 1520, 300},           // GuiGroupBox VIDEO SETTINGS   1
            Rectangle{m_anchor02.x + 940, m_anchor02.y + 25, 530, 25},  // Gui drowdown DISPLAY         2
            Rectangle{m_anchor02.x + 50, m_anchor02.y + 25, 50, 25},    // Label DISPLAY                3
            Rectangle{m_anchor02.x + 1205, m_anchor02.y + 100, 25, 25}, // GuiCheckBox VSYNC            4
            Rectangle{m_anchor02.x + 50, m_anchor02.y + 100, 90, 25},   // label VSYNC                  5
            Rectangle{m_anchor02.x + 940, m_anchor02.y + 175, 530, 25}, // Gui drowdown RESOLUTION      6
            Rectangle{m_anchor02.x + 25, m_anchor02.y + 175, 75, 30},   // label RESOLUTION             7
            Rectangle{m_anchor02.x + 940, m_anchor02.y + 250, 530, 25}, // Gui drowdown WINDOW MODE     8
            Rectangle{m_anchor02.x + 20, m_anchor02.y + 250, 80, 30},   // label WINDOW MODE            9

            Rectangle{m_anchor03.x, m_anchor03.y, 1520, 225},           // GuiGroupBox AUDIO SETTINGS   10
            Rectangle{m_anchor03.x + 940, m_anchor03.y + 25, 530, 25},  // GuiSlider m_masterVolume     11
            Rectangle{m_anchor03.x + 25, m_anchor03.y + 25, 80, 25},    // GuiLabel  MASTER:            12
            Rectangle{m_anchor03.x + 940, m_anchor03.y + 100, 530, 25}, // GuiSlider MUSIC              13
            Rectangle{m_anchor03.x + 25, m_anchor03.y + 100, 80, 25},   // GuiLabel  MUSIC              14
            Rectangle{m_anchor03.x + 940, m_anchor03.y + 175, 530, 25}, // GuiSlider m_layoutRecs       15
            Rectangle{m_anchor03.x + 25, m_anchor03.y + 175, 80, 25},   // GuiLabel  FX:                16
            Rectangle{m_anchor03.x + 940, m_anchor03.y + 250, 530, 25}, // NULL
            Rectangle{m_anchor03.x + 25, m_anchor03.y + 250, 80, 25},   // NULL

            Rectangle{1650, 990, 250, 75}                               // back button
        };

        SettingsWindowLayout(uint32 p_targetWidth, uint32 p_targetHeight);
    };

    struct SettingsState
    {
        bool m_vsyncActive{};

        int m_numSupportedResolutions{};
        UIntPair const *m_resolution = &(c_resolutionPairs[0]);
        int m_activeDisplay{};
        int m_numDisplay{};
        WindowMode m_windowMode{};

        float m_masterVolumePercentage = 0.0f;
        float m_musicVolumePercentage = 0.0f;
        float m_fxVolumePercentage = 0.0f;
    };

    class SettingsWindow
    {
    public:
        SettingsWindow();
         void InitState();
       void Update();
        void Show(bool p_shouldShow);

        SettingsState GetState() const;
        void LoadState(SettingsState p_state);

        float GetMasterAudioLevel() const;
        float GetMusicAudioLevel() const;
        float GetFXAudioLevel() const;
        UIntPair GetResolution() const;

    private:
        void UpdateState(SettingsState p_newState);
        void UpdateFields();

        std::vector<char const *> m_displayNames;
        std::string m_displayStrings{};
        std::string m_resolutionStrings{};

        SettingsWindowLayout m_layout;

        bool WindowBox000Active = true;
        bool DropdownBox002EditMode = false;
        int DropdownBox002Active = 0;
        bool DropdownBox006EditMode = false;
        int DropdownBox006Active = 0;
        bool DropdownBox008EditMode = false;
        int DropdownBox008Active = 0;

        SettingsState m_state{};
    };

}