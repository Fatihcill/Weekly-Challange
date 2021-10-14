#include "SettingsWindow.hpp"

#include <algorithm>

#include "extras/raygui.h"
#include "WinWrapper.hpp"

namespace raysettings
{

    SettingsState DetermineState();

    UIntPair const *FindClosestViableResolution(int p_windowWidth, int p_windowHeight)
    {
        //Exact Match
        UIntPair const *found = std::find_if(std::begin(c_resolutionPairs), std::end(c_resolutionPairs),
                                             [&p_windowWidth, &p_windowHeight](UIntPair const &pair)
                                             {
                                                 return pair.x == p_windowWidth && pair.y == p_windowHeight;
                                             });

        if (found == std::end(c_resolutionPairs))
        {
            //Closest smaller-than resolution
            UIntPair const *lastViable = std::begin(c_resolutionPairs);
            for (UIntPair const &pair : c_resolutionPairs)
            {
                if (pair.x <= p_windowWidth && pair.y <= p_windowHeight)
                {
                    lastViable = &pair;
                }
                else
                {
                    break;
                }
            }

            return lastViable;
        }
        else
        {
            return found;
        }
    }

    UIntPair const *FindClosestViableResolution(int p_monitor, int p_windowWidth, int p_windowHeight)
    {
        //Exact Match
        int const monitorWidth = GetMonitorWidth(p_monitor);
        int const monitorHeight = GetMonitorHeight(p_monitor);
        UIntPair const *found = std::find_if(std::begin(c_resolutionPairs), std::end(c_resolutionPairs),
                                             [&p_windowWidth, &p_windowHeight, &monitorWidth, &monitorHeight](UIntPair const &pair)
                                             {
                                                 return pair.x == p_windowWidth && pair.y == p_windowHeight && pair.x <= monitorWidth && pair.y <= monitorHeight;
                                             });

        if (found == std::end(c_resolutionPairs))
        {
            //Closest smaller-than resolution
            UIntPair const *lastViable = std::begin(c_resolutionPairs);
            for (UIntPair const &pair : c_resolutionPairs)
            {
                if (pair.x <= p_windowWidth && pair.y <= p_windowHeight && pair.x <= monitorWidth && pair.y <= monitorHeight)
                {
                    lastViable = &pair;
                }
                else
                {
                    break;
                }
            }

            return lastViable;
        }
        else
        {
            return found;
        }
    }

    SettingsWindow::SettingsWindow()
        : m_layout(1, 1)
    {
 
    }

    void SettingsWindow::InitState() 
    {
        m_state = DetermineState();
        m_layout = SettingsWindowLayout(m_state.m_resolution->x, m_state.m_resolution->y);
        UpdateFields();
    }
    SettingsState DetermineState()
    {
        SettingsState determinedState{};

        //Monitor
        determinedState.m_activeDisplay = GetCurrentMonitor();
        determinedState.m_numDisplay = GetMonitorCount();
        //Window mode
        if (IsWindowFullscreen())
        {
            determinedState.m_windowMode = WindowMode::eFullscreen;
        }
        else
        {
            if (IsWindowState(FLAG_WINDOW_UNDECORATED))
            {
                determinedState.m_windowMode = WindowMode::eBorderlessWindowed;
            }
            else
            {
                determinedState.m_windowMode = WindowMode::eWindowed;
            }
        }

        //Num supported resolutions
        if (
            determinedState.m_windowMode == WindowMode::eFullscreen ||
            determinedState.m_windowMode == WindowMode::eBorderlessWindowed)
        {
            int maxWidth = GetMonitorWidth(determinedState.m_activeDisplay);
            int maxHeight = GetMonitorHeight(determinedState.m_activeDisplay);

            int supportedResolutions = 0;
            for (; supportedResolutions < c_numResolutionPairs; supportedResolutions++)
            {
                UIntPair res = c_resolutionPairs[supportedResolutions];
                if (maxWidth < res.x || maxHeight < res.y)
                {
                    break;
                }
            }

            determinedState.m_numSupportedResolutions = supportedResolutions;
        }
        else
        {
            //Windowed
            int supportedResolutions = 0;

            //Window can be on any monitor, so let the user resize according to the max size
            for (int i = 0; i < determinedState.m_numDisplay; i++)
            {
                int maxWidth = GetMonitorWidth(i);
                int maxHeight = GetMonitorHeight(i);

                int targetRes = 0;
                for (; targetRes < c_numResolutionPairs; targetRes++)
                {
                    UIntPair res = c_resolutionPairs[targetRes];
                    if (maxWidth < res.x || maxHeight < res.y)
                    {
                        break;
                    }
                }

                supportedResolutions = std::max(supportedResolutions, targetRes);
            }

            determinedState.m_numSupportedResolutions = supportedResolutions;
        }

        //Resolution
        int windowWidth{}, windowHeight{};
        GetWindowSize(GetWindowHandle(), windowWidth, windowHeight);
        determinedState.m_resolution = FindClosestViableResolution(windowWidth, windowHeight);

        determinedState.m_vsyncActive = IsWindowState(FLAG_VSYNC_HINT);
        return determinedState;
    }

    void SettingsWindow::UpdateState(SettingsState p_newState)
    {
        //== Update Phase ===

        //Window mode
        bool videoChangeDetected{};

        if (m_state.m_windowMode != p_newState.m_windowMode)
        {
            int monitorWidth = GetMonitorWidth(p_newState.m_activeDisplay);
            int monitorHeight = GetMonitorHeight(p_newState.m_activeDisplay);

            if (p_newState.m_windowMode == WindowMode::eBorderlessWindowed)
            {
                p_newState.m_resolution = FindClosestViableResolution(monitorWidth, monitorHeight);
            }

            videoChangeDetected = true;
        }

        //Monitor
        if (m_state.m_numDisplay != p_newState.m_numDisplay)
        {
            videoChangeDetected = true;
        }

        if (m_state.m_activeDisplay != p_newState.m_activeDisplay)
        {
            p_newState.m_resolution = FindClosestViableResolution(p_newState.m_activeDisplay, p_newState.m_resolution->x, p_newState.m_resolution->y);
            videoChangeDetected = true;
        }

        //Resolution
        if (m_state.m_resolution != p_newState.m_resolution)
        {
            videoChangeDetected = true;
        }

        //Num supported resolutions
        if (m_state.m_activeDisplay != p_newState.m_activeDisplay || m_state.m_windowMode != p_newState.m_windowMode)
        {
            if (
                p_newState.m_windowMode == WindowMode::eFullscreen ||
                p_newState.m_windowMode == WindowMode::eBorderlessWindowed)
            {
                int maxWidth = GetMonitorWidth(p_newState.m_activeDisplay);
                int maxHeight = GetMonitorHeight(p_newState.m_activeDisplay);

                int supportedResolutions = 0;
                for (; supportedResolutions < c_numResolutionPairs; supportedResolutions++)
                {
                    UIntPair res = c_resolutionPairs[supportedResolutions];
                    if (maxWidth < res.x || maxHeight < res.y)
                    {
                        break;
                    }
                }

                p_newState.m_numSupportedResolutions = supportedResolutions;
            }
            else
            {
                //Windowed
                int supportedResolutions = 0;

                //Window can be on any monitor, so let the user resize according to the max size
                for (int i = 0; i < p_newState.m_numDisplay; i++)
                {
                    int maxWidth = GetMonitorWidth(i);
                    int maxHeight = GetMonitorHeight(i);

                    int targetRes = 0;
                    for (; targetRes < c_numResolutionPairs; targetRes++)
                    {
                        UIntPair res = c_resolutionPairs[targetRes];
                        if (maxWidth < res.x || maxHeight < res.y)
                        {
                            break;
                        }
                    }

                    supportedResolutions = std::max(supportedResolutions, targetRes);
                }

                p_newState.m_numSupportedResolutions = supportedResolutions;
            }
        }

        //Vsync
        if (m_state.m_vsyncActive != p_newState.m_vsyncActive)
        {
            videoChangeDetected = true;
        }

        bool audioChangeDetected{};
        if (m_state.m_masterVolumePercentage != p_newState.m_masterVolumePercentage)
        {
            audioChangeDetected = true;
        }

        if (m_state.m_musicVolumePercentage != p_newState.m_musicVolumePercentage)
        {
            audioChangeDetected = true;
        }

        if (m_state.m_fxVolumePercentage != p_newState.m_fxVolumePercentage)
        {
            audioChangeDetected = true;
        }

        m_state = p_newState;

        if (videoChangeDetected == true)
        {
            int setFlags = {};
            int clearFlags = {};

            setFlags |= FLAG_WINDOW_HIGHDPI;

            switch (m_state.m_windowMode)
            {
            case WindowMode::eBorderlessWindowed:
            {
                setFlags |= FLAG_WINDOW_UNDECORATED;
                clearFlags |= FLAG_FULLSCREEN_MODE;
                Vector2 pos = GetMonitorPosition(m_state.m_activeDisplay);
                SetWindowPosition(int(pos.x), int(pos.y));
                break;
            }
            case WindowMode::eFullscreen:
            {
                clearFlags |= FLAG_WINDOW_UNDECORATED;
                setFlags |= FLAG_FULLSCREEN_MODE;
                SetWindowMonitor(m_state.m_activeDisplay);
                break;
            }
            case WindowMode::eWindowed:
            {
                clearFlags |= (FLAG_FULLSCREEN_MODE | FLAG_WINDOW_UNDECORATED);
                SetWindowPosition(50, 50);
                break;
            }
            default:
                break;
            }

            if (m_state.m_vsyncActive)
            {
                setFlags |= FLAG_VSYNC_HINT;
            }
            else
            {
                clearFlags |= FLAG_VSYNC_HINT;
            }

            ClearWindowState(clearFlags);
            SetWindowState(setFlags);

            SetWindowSize(m_state.m_resolution->x, m_state.m_resolution->y);
            m_layout = SettingsWindowLayout{m_state.m_resolution->x, m_state.m_resolution->y};
        }

        if (audioChangeDetected)
        {
        }
    }

    void SettingsWindow::UpdateFields()
    {
        m_displayNames.clear();
        for (int i = 0; i < m_state.m_numDisplay; i++)
        {
            m_displayNames.push_back(GetMonitorName(i));
        }

        m_displayStrings.clear();
        m_displayStrings.reserve(200u);
        for (int i = 0; i < m_state.m_numDisplay; i++)
        {
            m_displayStrings.append(m_displayNames.at(i));
            if (i + 1 < m_state.m_numDisplay)
            {
                m_displayStrings.append(";");
            }
        }

        char const *lastSeparator = c_resolutionStrings + 0;
        for (int i = m_state.m_numSupportedResolutions; i > 0; lastSeparator++)
        {
            if (*lastSeparator == ';')
            {
                i--;
            }

            if (*lastSeparator == '\0')
            {
                i = 0;
            }
        }

        m_resolutionStrings = std::string(c_resolutionStrings + 0, lastSeparator);
        m_resolutionStrings.pop_back();

        if (DropdownBox002Active != m_state.m_activeDisplay)
        {
            DropdownBox002Active = m_state.m_activeDisplay;
        }

        int resIndex = m_state.m_resolution - std::begin(c_resolutionPairs);
        if (DropdownBox006Active != resIndex)
        {
            DropdownBox006Active = resIndex;
        }

        if (DropdownBox008Active != static_cast<int>(m_state.m_windowMode))
        {
            DropdownBox008Active = static_cast<int>(m_state.m_windowMode);
        }
    }

    void SettingsWindow::Update()
    {
        //Scale components to the active resolution

        if (WindowBox000Active)
        {
            SettingsState nextState = m_state;

            WindowBox000Active = !GuiWindowBox(m_layout.m_layoutRecs[0], "SETTINGS") && !GuiButton(m_layout.m_layoutRecs[19], "Back");

            GuiGroupBox(m_layout.m_layoutRecs[1], "VIDEO SETTINGS");
            GuiLabel(m_layout.m_layoutRecs[3], "DISPLAY:");
            GuiLabel(m_layout.m_layoutRecs[5], "VSYNC:");
            GuiLabel(m_layout.m_layoutRecs[7], "RESOLUTION:");
            GuiLabel(m_layout.m_layoutRecs[9], "WINDOW MODE:");
            GuiGroupBox(m_layout.m_layoutRecs[10], "AUDIO SETTINGS");
            nextState.m_masterVolumePercentage = GuiSlider(m_layout.m_layoutRecs[11], NULL, NULL, m_state.m_masterVolumePercentage, 0, 100);
            GuiLabel(m_layout.m_layoutRecs[12], "MASTER:");
            nextState.m_musicVolumePercentage = GuiSlider(m_layout.m_layoutRecs[13], NULL, NULL, m_state.m_musicVolumePercentage, 0, 100);
            GuiLabel(m_layout.m_layoutRecs[14], "MUSIC:");
            nextState.m_fxVolumePercentage = GuiSlider(m_layout.m_layoutRecs[15], NULL, NULL, m_state.m_fxVolumePercentage, 0, 100);
            GuiLabel(m_layout.m_layoutRecs[16], "FX:");
            nextState.m_vsyncActive = GuiCheckBox(m_layout.m_layoutRecs[4], NULL, m_state.m_vsyncActive);

            


                bool changeFound = false;

            if (GuiDropdownBox(m_layout.m_layoutRecs[2], m_displayStrings.c_str(), &nextState.m_activeDisplay, DropdownBox002EditMode))
            {
                DropdownBox002EditMode = !DropdownBox002EditMode;
            }

            int resIndex = nextState.m_resolution - std::begin(c_resolutionPairs);
            if (GuiDropdownBox(m_layout.m_layoutRecs[6], m_resolutionStrings.c_str(), &resIndex, DropdownBox006EditMode))
            {
                DropdownBox006EditMode = !DropdownBox006EditMode;
            }
            nextState.m_resolution = &(c_resolutionPairs[resIndex]);

            int windowModeIndex = DropdownBox008Active;
            if (GuiDropdownBox(m_layout.m_layoutRecs[8], c_windowModeStrings, &windowModeIndex, DropdownBox008EditMode))
            {
                DropdownBox008EditMode = !DropdownBox008EditMode;
            }
            nextState.m_windowMode = static_cast<WindowMode>(windowModeIndex);

            //WORKAROUND: Render last to bring to front
            if (DropdownBox002EditMode)
            {
                GuiDropdownBox(m_layout.m_layoutRecs[2], m_displayStrings.c_str(), &DropdownBox002Active, DropdownBox002EditMode);
            }
            if (DropdownBox006EditMode)
            {
                GuiDropdownBox(m_layout.m_layoutRecs[6], m_resolutionStrings.c_str(), &DropdownBox006Active, DropdownBox006EditMode);
            }
            if (DropdownBox008EditMode)
            {
                GuiDropdownBox(m_layout.m_layoutRecs[8], c_windowModeStrings, &DropdownBox008Active, DropdownBox008EditMode);
            }

            UpdateState(nextState);
            UpdateFields();
        }
   
    }

    void SettingsWindow::Show(bool p_shouldShow)
    {
        WindowBox000Active = p_shouldShow;
    }

    SettingsWindowLayout::SettingsWindowLayout(uint32 const p_targetWidth, uint32 const p_targetHeight)
    {
        float const scaleX = p_targetWidth / 1920.f;
        float const scaleY = p_targetHeight / 1080.f;

        m_anchor01.x *= scaleX;
        m_anchor01.y *= scaleY;

        m_anchor02.x *= scaleX;
        m_anchor02.y *= scaleY;

        m_anchor03.x *= scaleX;
        m_anchor03.y *= scaleY;

        for (Rectangle &rec : m_layoutRecs)
        {
            rec.x *= scaleX;
            rec.width *= scaleX;
            rec.y *= scaleY;
            rec.height *= scaleY;
        }
    }

    SettingsState SettingsWindow::GetState() const
    {
        return m_state;
    }

    void SettingsWindow::LoadState(SettingsState p_state)
    {
        UpdateState(p_state);
        UpdateFields();
    }

    float SettingsWindow::GetMasterAudioLevel() const
    {
        return m_state.m_masterVolumePercentage;
    }

    float SettingsWindow::GetMusicAudioLevel() const
    {
        return m_state.m_musicVolumePercentage;
    }

    float SettingsWindow::GetFXAudioLevel() const
    {
        return m_state.m_fxVolumePercentage;
    }

    UIntPair SettingsWindow::GetResolution() const
    {
        return *m_state.m_resolution;
    }

}